import grpc
import sharding_info_pb2
import sharding_info_pb2_grpc
import time
import argparse

def get_all_shards(stub, volume_name):
    """Obține informații despre toate shard-urile unui volum"""
    request = sharding_info_pb2.GetAllShardsRequest(volume_name=volume_name)
    response = stub.GetAllShards(request)
    return response.shards

def get_shard_info(stub, volume_name, shard_id):
    """Obține informații despre un shard specific"""
    request = sharding_info_pb2.GetShardInfoRequest(
        volume_name=volume_name,
        shard_id=shard_id
    )
    response = stub.GetShardInfo(request)
    return response.shard

def stream_shard_changes(stub, volume_name, include_file_ops=True):
    """Streaming de modificări în shard-uri în timp real"""
    request = sharding_info_pb2.StreamShardChangesRequest(
        volume_name=volume_name,
        include_file_operations=include_file_ops
    )
    for change in stub.StreamShardChanges(request):
        yield change

def display_shard_info(shard):
    """Afișează informații despre un shard într-un format citibil"""
    print(f"Shard ID: {shard.shard_id}")
    print(f"Host Brick: {shard.host_brick}")
    print(f"Size: {shard.size_bytes / (1024*1024):.2f} MB")
    print(f"Files: {shard.file_count}")
    
    if hasattr(shard, 'stats'):
        print("\nStats:")
        print(f"  Read Operations: {shard.stats.read_ops}")
        print(f"  Write Operations: {shard.stats.write_ops}")
        print(f"  Average Access Time: {shard.stats.avg_access_time:.3f} ms")
        print(f"  Rebalance Count: {shard.stats.rebalance_count}")
    
    if hasattr(shard, 'files') and len(shard.files) > 0:
        print("\nFiles:")
        for file in shard.files:
            print(f"  {file.path} ({file.size / 1024:.2f} KB, {file.chunk_count} chunks)")

def main():
    parser = argparse.ArgumentParser(description='GlusterFS Sharding Info Client')
    parser.add_argument('--server', default='localhost:50051', help='gRPC server address')
    parser.add_argument('--volume', required=True, help='Volume name')
    parser.add_argument('--mode', choices=['list', 'details', 'stream'], default='list',
                       help='Mode of operation')
    parser.add_argument('--shard', help='Shard ID (required for details mode)')
    args = parser.parse_args()
    
    # Creăm canalul gRPC și stub-ul
    with grpc.insecure_channel(args.server) as channel:
        stub = sharding_info_pb2_grpc.ShardingInfoStub(channel)
        
        if args.mode == 'list':
            shards = get_all_shards(stub, args.volume)
            print(f"Found {len(shards)} shards in volume {args.volume}:")
            for shard in shards:
                print(f"- {shard.shard_id} ({shard.size_bytes / (1024*1024):.2f} MB, {shard.file_count} files)")
        
        elif args.mode == 'details':
            if not args.shard:
                print("Error: --shard is required for details mode")
                return
            shard = get_shard_info(stub, args.volume, args.shard)
            display_shard_info(shard)
        
        elif args.mode == 'stream':
            print(f"Streaming shard changes for volume {args.volume}. Press Ctrl+C to stop.")
            try:
                for change in stream_shard_changes(stub, args.volume):
                    timestamp = time.strftime('%Y-%m-%d %H:%M:%S', 
                                             time.localtime(change.timestamp))
                    print(f"[{timestamp}] {change.shard_id}: {change.change_type}")
                    if change.HasField('affected_file'):
                        print(f"  Affected file: {change.affected_file.path}")
            except KeyboardInterrupt:
                print("Streaming stopped by user")

if __name__ == '__main__':
    main()