import socket

def recibir_datos():
    server_socket = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)

    host = ""  # Dirección Bluetooth del adaptador local
    port = 1  # Puerto RFCOMM utilizado por el dispositivo Bluetooth

    server_socket.bind((host, port))
    server_socket.listen(1)

    print("Esperando conexiones Bluetooth...")
    client_socket, client_address = server_socket.accept()
    print("Cliente conectado:", client_address)

    while True:
        try:
            data = client_socket.recv(1024)
            if not data:
                break
            datos = data.decode("utf-8")
            print("Datos recibidos:", datos)
        except socket.error as e:
            print("Error de conexión:", str(e))
            break

    client_socket.close()
    server_socket.close()

if __name__ == "__main__":
    recibir_datos()


