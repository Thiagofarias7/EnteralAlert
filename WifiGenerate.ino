#include <WiFi.h>

const char* ssid = "NomeDaRedeWiFi"; // Nome da sua rede Wi-Fi
const char* password = "SenhaDaRedeWiFi"; // Senha da sua rede Wi-Fi

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP); // Modo de acesso point (AP)
  WiFi.softAP(ssid, password); // Cria uma rede Wi-Fi com o nome e senha fornecidos
  Serial.println("Rede Wi-Fi criada");

  // Mostra o IP do ESP32
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("Endereço IP do ESP32: ");
  Serial.println(myIP);
}

void loop() {
  // Verifica se um dispositivo se conectou ao AP
  if (WiFi.softAPgetStationNum() > 0) {
    Serial.println("Dispositivo conectado ao AP");
    
    // Mostra o endereço IP do dispositivo conectado
    Serial.print("Endereço IP do dispositivo conectado: ");
    Serial.println(WiFi.softAPgetStationIP(0));

    delay(5000); // Aguarda 5 segundos antes de verificar novamente
  }
}
