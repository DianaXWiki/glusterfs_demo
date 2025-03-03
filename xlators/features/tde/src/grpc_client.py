import grpc
import socket
import shard_service_pb2
import shard_service_pb2_grpc

# Unix socket path
SOCKET_PATH = "/tmp/tde_shard_socket"

# Connect to gRPC server
channel = grpc.insecure_channel("localhost:50051")
stub = shard_service_pb2_grpc.ShardServiceStub(channel)


# Create a Unix socket listener
def start_unix_socket_listener():
    sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
    
    try:
        sock.bind(SOCKET_PATH)
    except OSError:
        print("Removing existing socket and rebinding...")
        os.remove(SOCKET_PATH)
        sock.bind(SOCKET_PATH)

    sock.listen(5)
    print(f"Listening for shard info on {SOCKET_PATH}...")

    while True:
        conn, _ = sock.accept()
        data = conn.recv(256).decode()
        if data:
            # Parse shard data
            shard_path, shard_index, shard_size = data.split("|")
            shard_index = int(shard_index)
            shard_size = int(shard_size)

            # Send data via gRPC
            request = shard_service_pb2.ShardRequest(
                shard_path=shard_path,
                shard_index=shard_index,
                shard_size=shard_size
            )

            response = stub.SendShardInfo(request)
            print(f"gRPC Response: {response.status}")

        conn.close()

if __name__ == "__main__":
    start_unix_socket_listener()
