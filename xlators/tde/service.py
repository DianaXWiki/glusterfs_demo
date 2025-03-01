import grpc
from concurrent import futures
import time
import argparse

import tde_pb2
import tde_pb2_grpc

class TDEServiceServicer(tde_pb2_grpc.TDEServiceServicer):
    def CommunicateWithShard(self, request, context):
        # Check the operation type: encrypt or decrypt
        if request.operation == "encrypt":
            # For demo purposes, "encrypt" simply prefixes the data
            encrypted_data = b"[ENCRYPTED] " + request.data
            return tde_pb2.TDEResponse(success=True,
                                        message="Data encrypted",
                                        data=encrypted_data)
        elif request.operation == "decrypt":
            prefix = b"[ENCRYPTED] "
            if request.data.startswith(prefix):
                decrypted_data = request.data[len(prefix):]
            else:
                decrypted_data = request.data
            return tde_pb2.TDEResponse(success=True,
                                        message="Data decrypted",
                                        data=decrypted_data)
        else:
            context.set_code(grpc.StatusCode.INVALID_ARGUMENT)
            context.set_details("Unsupported operation")
            return tde_pb2.TDEResponse(success=False,
                                        message="Unsupported operation",
                                        data=b"")

def serve(port):
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    tde_pb2_grpc.add_TDEServiceServicer_to_server(TDEServiceServicer(), server)
    server.add_insecure_port(f'[::]:{port}')
    server.start()
    print(f"TDE gRPC service is running on port {port}...")
    try:
        while True:
            time.sleep(86400)
    except KeyboardInterrupt:
        server.stop(0)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='TDE gRPC Service')
    parser.add_argument('--port', type=int, default=50051,
                        help='Port for the gRPC service')
    args = parser.parse_args()
    serve(args.port)
