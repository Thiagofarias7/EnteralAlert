const int ldrPin = A0;      // Pino do LDR
const int calibrationTime = 10000;  // Tempo de calibração em milissegundos
const int calibrationInterval = 1000;  // Intervalo de amostragem durante a calibração em milissegundos
const float detectionThreshold = 0.8;  // Limite de detecção em relação ao valor de referência

int ldrValue;  // Valor lido do LDR durante a calibração
float referenceValue;  // Valor de referência para a luminosidade ambiente com comida

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Calibração automática
  calibrateSystem();

  // Verificar estado do sistema
  checkSystemState();
}

void calibrateSystem() {
  Serial.println("Calibrating...");

  // Inicializar variáveis
  long startTime = millis();
  int totalSamples = 0;
  long calibrationEndTime = startTime + calibrationTime;

  // Realizar aquisição de amostras durante o tempo de calibração
  while (millis() < calibrationEndTime) {
    ldrValue += analogRead(ldrPin);
    totalSamples++;
    delay(calibrationInterval);
  }

  // Calcular valor de referência
  referenceValue = ldrValue / (float)totalSamples;

  Serial.print("Calibration completed. Reference Value: ");
  Serial.println(referenceValue);

  // Reinicializar variáveis para próxima calibração
  ldrValue = 0;
}

void checkSystemState() {
  // Fazer a leitura atual do LDR
  int currentValue = analogRead(ldrPin);

  // Comparar com o valor de referência
  if (currentValue < referenceValue * detectionThreshold) {
    // Ativar o alarme
    Serial.println("Food running low! Take necessary measures.");
    // TODO: Acionar o alarme, por exemplo, acender um LED ou emitir um som
  }
}
