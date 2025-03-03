import grpc
from concurrent import futures
import shard_service_pb2
import shard_service_pb2_grpc

class ShardServiceServicer(shard_service_pb2_grpc.ShardServiceServicer):
    def SendShard(self, request, context):
        shard_data = request.data
        offset = request.offset

        print(f"Received shard at offset {offset}, size: {len(shard_data)} bytes")

        # Save shard data to a file (optional)
        with open(f"shard_{offset}.bin", "wb") as f:
            f.write(shard_data)

        return shard_service_pb2.ShardResponse(status="OK")

def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    shard_service_pb2_grpc.add_ShardServiceServicer_to_server(ShardServiceServicer(), server)
    server.add_insecure_port("[::]:50051")
    server.start()
    print("Shard gRPC Server is running...")
    server.wait_for_termination()

if __name__ == "__main__":
    serve()
