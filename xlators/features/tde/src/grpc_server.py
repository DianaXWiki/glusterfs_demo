import grpc
from concurrent import futures
import shard_service_pb2
import shard_service_pb2_grpc

class ShardServiceServicer(shard_service_pb2_grpc.ShardServiceServicer):
    def SendShardInfo(self, request, context):
        print(f"Received shard info: Path={request.shard_path}, Index={request.shard_index}, Size={request.shard_size}")
        return shard_service_pb2.ShardResponse(status="OK")

def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    shard_service_pb2_grpc.add_ShardServiceServicer_to_server(ShardServiceServicer(), server)
    server.add_insecure_port("[::]:50051")
    server.start()
    print("Shard gRPC server running on port 50051...")
    server.wait_for_termination()

if __name__ == "__main__":
    serve()
