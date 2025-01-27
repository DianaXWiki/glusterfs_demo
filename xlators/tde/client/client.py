import grpc
from proto import tde_pb2_grpc, tde_pb2

def send_data_to_server(data):
    with grpc.insecure_channel('localhost:50051') as channel:
        stub = tde_pb2_grpc.TDEServiceStub(channel)
        response = stub.ProcessData(tde_pb2.ProcessDataRequest(input_data=data))
        return response.encrypted_data

if __name__ == "__main__":
    input_data = "Hello, GlusterFS!"
    encrypted_data = send_data_to_server(input_data)
    print(f"Encrypted Data from Server: {encrypted_data}")
