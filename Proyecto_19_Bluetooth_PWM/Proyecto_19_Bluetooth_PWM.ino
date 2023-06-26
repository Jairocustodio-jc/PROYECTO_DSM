#include <SoftwareSerial.h>

SoftwareSerial bluetooth(10, 11);  // Define los pines RX y TX para la comunicación Bluetooth

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600); // Inicia la comunicación Bluetooth

  Serial.println("Listo para enviar y recibir mensajes por Bluetooth.");

  // Configuración inicial del módulo Bluetooth
  bluetooth.print("AT\r\n"); // Comando AT para verificar la comunicación
  delay(500);
  if (bluetooth.available()) {
    while (bluetooth.available()) {
      char c = bluetooth.read();
      Serial.write(c);
    }
  }
  bluetooth.print("AT+NAME=MiBluetooth\r\n"); // Cambia el nombre del dispositivo Bluetooth
  delay(500);
  if (bluetooth.available()) {
    while (bluetooth.available()) {
      char c = bluetooth.read();
      Serial.write(c);
    }
  }
  bluetooth.print("AT+PIN=1234\r\n"); // Cambia el PIN de emparejamiento
  delay(500);
  if (bluetooth.available()) {
    while (bluetooth.available()) {
      char c = bluetooth.read();
      Serial.write(c);
    }
  }
}

void loop() {
  // Envío de mensaje
  if (Serial.available()) {
    char data = Serial.read();
    bluetooth.write(data);
  }

  // Recepción de mensaje
  if (bluetooth.available()) {
    char data = bluetooth.read();
    Serial.write(data);

    // Envío de los datos a la aplicación Flask
    if (data != '\n') {
      String datos = String(data);
      enviarDatosAFlask(datos);
    }
  }
}

void enviarDatosAFlask(String datos) {
  // Dirección IP y puerto de la aplicación Flask
  String serverAddress = "192.168.119.223"; // Reemplaza con la dirección IP correcta
  int serverPort = 5001; // Reemplaza con el puerto correcto

  // Conexión a la aplicación Flask
  bluetooth.begin(9600);
  bluetooth.print("POST /datos HTTP/1.1\r\n");
  bluetooth.print("Host: " + serverAddress + "\r\n");
  bluetooth.print("Content-Type: text/plain\r\n");
  bluetooth.print("Content-Length: " + String(datos.length()) + "\r\n");
  bluetooth.print("\r\n");
  bluetooth.print(datos);

  Serial.println("Datos enviados a Flask: " + datos);
}


