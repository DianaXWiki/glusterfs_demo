import json
import time
import grpc
import threading
from concurrent import futures
import sharding_info_pb2
import sharding_info_pb2_grpc
import argparse
import os
import logging

# Configurarea logging-ului
logging.basicConfig(level=logging.INFO, 
                   format='%(asctime)s - %(name)s - %(levelname)s - %(message)s')
logger = logging.getLogger('ShardingServer')

class ShardingInfoServicer(sharding_info_pb2_grpc.ShardingInfoServicer):
    def __init__(self, data_path='/var/lib/glusterfs/sharding_data.json'):
        self.data_path = data_path
        self._last_data = None
        self._lock = threading.Lock()
        self._start_monitoring()
    
    def _start_monitoring(self):
        """Pornește un thread care monitorizează fișierul de date"""
        self._monitor_thread = threading.Thread(target=self._monitor_file)
        self._monitor_thread.daemon = True
        self._monitor_thread.start()
    
    def _monitor_file(self):
        """Monitorizează fișierul de date și actualizează starea internă"""
        last_mtime = 0
        
        while True:
            try:
                if os.path.exists(self.data_path):
                    mtime = os.path.getmtime(self.data_path)
                    
                    if mtime > last_mtime:
                        with open(self.data_path, 'r') as f:
                            data = json.load(f)
                            
                        with self._lock:
                            self._last_data = data
                            
                        last_mtime = mtime
                        logger.info(f"Updated data from {self.data_path}")
                else:
                    logger.warning(f"Data file {self.data_path} does not exist")
            
            except Exception as e:
                logger.error(f"Error monitoring file: {str(e)}")
            
            # Verificăm la fiecare 3 secunde
            time.sleep(3)
    
    def _get_current_data(self):
        """Returnează datele curente într-un mod thread-safe"""
        with self._lock:
            if self._last_data is None:
                return None
            return dict(self._last_data)  # Copie pentru a evita race conditions
    
    def GetAllShards(self, request, context):
        """Implementează metoda GetAllShards din serviciul gRPC"""
        data = self._get_current_data()
        if not data:
            context.set_code(grpc.StatusCode.NOT_FOUND)
            context.set_details("No sharding data available")
            return sharding_info_pb2.GetAllShardsResponse()
        
        response = sharding_info_pb2.GetAllShardsResponse()
        
        # Verificăm dacă volumul cerut există în date
        volume_name = request.volume_name
        if volume_name != data.get('volume'):
            context.set_code(grpc.StatusCode.NOT_FOUND)
            context.set_details(f"Volume {volume_name} not found")
            return response
        
        # Construim răspunsul
        for shard_data in data.get('shards', []):
            shard_info = sharding_info_pb2.ShardInfo(
                shard_id=shard_data.get('shard_id', ''),
                host_brick=shard_data.get('host_brick', ''),
                size_bytes=shard_data.get('size_bytes', 0),
                file_count=shard_data.get('file_count', 0)
            )
            
            # Adăugăm statistici dacă există
            if 'stats' in shard_data:
                stats = sharding_info_pb2.ShardingStats(
                    read_ops=shard_data['stats'].get('read_ops', 0),
                    write_ops=shard_data['stats'].get('write_ops', 0),
                    avg_access_time=shard_data['stats'].get('avg_access_time', 0.0),
                    rebalance_count=shard_data['stats'].get('rebalance_count', 0)
                )
                shard_info.stats.CopyFrom(stats)
            
            # Adăugăm informații despre fișiere dacă există
            if 'files' in shard_data:
                for file_data in shard_data['files']:
                    file_info = sharding_info_pb2.FileInfo(
                        path=file_data.get('path', ''),
                        original_gfid=file_data.get('original_gfid', ''),
                        size=file_data.get('size', 0),
                        chunk_count=file_data.get('chunk_count', 0)
                    )
                    file_info.shard_gfids.extend(file_data.get('shard_gfids', []))
                    shard_info.files.append(file_info)
            
            response.shards.append(shard_info)
        
        return response
    
    def GetShardInfo(self, request, context):
        """Implementează metoda GetShardInfo din serviciul gRPC"""
        data = self._get_current_data()
        if not data:
            context.set_code(grpc.StatusCode.NOT_FOUND)
            context.set_details("No sharding data available")
            return sharding_info_pb2.GetShardInfoResponse()
        
        # Verificăm dacă volumul cerut există în date
        volume_name = request.volume_name
        if volume_name != data.get('volume'):
            context.set_code(grpc.StatusCode.NOT_FOUND)
            context.set_details(f"Volume {volume_name} not found")
            return sharding_info_pb2.GetShardInfoResponse()
        
        # Căutăm shard-ul specific
        shard_id = request.shard_id
        for shard_data in data.get('shards', []):
            if shard_data.get('shard_id') == shard_id:
                shard_info = sharding_info_pb2.ShardInfo(
                    shard_id=shard_data.get('shard_id', ''),
                    host_brick=shard_data.get('host_brick', ''),
                    size_bytes=shard_data.get('size_bytes', 0),
                    file_count=shard_data.get('file_count', 0)
                )
                
                # Adăugăm statistici dacă există
                if 'stats' in shard_data:
                    stats = sharding_info_pb2.ShardingStats(
                        read_ops=shard_data['stats'].get('read_ops', 0),
                        write_ops=shard_data['stats'].get('write_ops', 0),
                        avg_access_time=shard_data['stats'].get('avg_access_time', 0.0),
                        rebalance_count=shard_data['stats'].get('rebalance_count', 0)
                    )
                    shard_info.stats.CopyFrom(stats)
                
                # Adăugăm informații despre fișiere dacă există
                if 'files' in shard_data:
                    for file_data in shard_data['files']:
                        file_info = sharding_info_pb2.FileInfo(
                            path=file_data.get('path', ''),
                            original_gfid=file_data.get('original_gfid', ''),
                            size=file_data.get('size', 0),
                            chunk_count=file_data.get('chunk_count', 0)
                        )
                        file_info.shard_gfids.extend(file_data.get('shard_gfids', []))
                        shard_info.files.append(file_info)
                
                response = sharding_info_pb2.GetShardInfoResponse(shard=shard_info)
                return response
        
        # Shard-ul nu a fost găsit
        context.set_code(grpc.StatusCode.NOT_FOUND)
        context.set_details(f"Shard {shard_id} not found")
        return sharding_info_pb2.GetShardInfoResponse()
    
    def StreamShardChanges(self, request, context):
        """Implementează streaming pentru modificările shard-urilor"""
        volume_name = request.volume_name
        last_timestamp = 0
        
        while context.is_active():
            data = self._get_current_data()
            if data and data.get('volume') == volume_name:
                timestamp = data.get('timestamp', 0)
                
                if timestamp > last_timestamp:
                    for shard_data in data.get('shards', []):
                        # Aici ar trebui să implementați logica pentru a detecta schimbările
                        # Momentan, simplu raportăm toate shard-urile ca fiind modificate
                        change = sharding_info_pb2.ShardChange(
                            shard_id=shard_data.get('shard_id', ''),
                            change_type=sharding_info_pb2.ShardChange.MODIFIED,
                            timestamp=timestamp
                        )
                        yield change
                    
                    last_timestamp = timestamp
            
            time.sleep(5)  # Verificăm la fiecare 5 secunde

def serve(data_path, port=50051, max_workers=10):
    """Pornește serverul gRPC"""
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=max_workers))
    sharding_info_pb2_grpc.add_ShardingInfoServicer_to_server(
        ShardingInfoServicer(data_path), server)
    server.add_insecure_port(f'[::]:{port}')
    server.start()
    logger.info(f"Server started on port {port}")
    
    try:
        while True:
            time.sleep(3600)  # Serverul va rula până când este întrerupt manual
    except KeyboardInterrupt:
        server.stop(0)
        logger.info("Server stopped")

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='GlusterFS Sharding Info gRPC Server')
    parser.add_argument('--data-path', 
                      default='/var/lib/glusterfs/sharding_data.json',
                      help='Path to the exported sharding data JSON file')
    parser.add_argument('--port', type=int, default=50051,
                      help='Port to listen on')
    args = parser.parse_args()
    
    serve(args.data_path, args.port)