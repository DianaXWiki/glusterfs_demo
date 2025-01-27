from concurrent import futures
import grpc
from proto import tde_pb2_grpc, tde_pb2
from encryption import encrypt_data, decrypt_data

class TDEService(tde_pb2_grpc.TDEServicer):
    def EncryptChunk(self, request, context):
        chunk_data = request.chunk_data  # Raw chunk data
        encrypted_chunk = encrypt_data(chunk_data)
        return tde_pb2.EncryptChunkResponse(encrypted_chunk=encrypted_chunk)
    
    def DecryptChunk(self, request, context):
        encrypted_chunk = request.encrypted_chunk  # Encrypted chunk
        chunk_data = decrypt_data(encrypted_chunk)
        return tde_pb2.DecryptChunkResponse(chunk_data=chunk_data)

def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    tde_pb2_grpc.add_TDEServicer_to_server(TDEService(), server)
    server.add_insecure_port('[::]:50051')
    server.start()
    print("TDE gRPC server is running on port 50051...")
    server.wait_for_termination()

if __name__ == "__main__":
    serve()
