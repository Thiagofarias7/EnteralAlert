const int ldrPin = 36;      // Pino do LDR
const int buzzerPin = 13;   // Pino do Buzzer
const int ledCalibration = 11; //Led indicador de calibração
//-----------------------------------------------------------
const int calibrationTime = 10000;  // Tempo de calibração em milissegundos
const int calibrationInterval = 1000;  // Intervalo de amostragem durante a calibração em milissegundos
const float detectionThreshold = 0.8;  // Limite de detecção em relação ao valor de referência
//Esse valor é alterado de acordo com testes
int ldrValue = 0;           // Valor lido do LDR
int threshold = 500;        // Limiar de luminosidade para acionar o buzzer
int referenceValue;      //Valor que o sistema vai comparar

void setup() {
  pinMode(ldrPin, INPUT);
  pinMode(ledCalibration, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
// Calibração automática
  calibrateSystem();
// Indica visualmente ao usuário que a calibração findou
  calibrationCompleted()  
// Verificar estado do sistema
  checkSystemState();
}

void calibrateSystem() {
  Serial.println("Calibrating...");
  digitalWrite(ledCalibration, HIGH);
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
  Serial.print("Calibração Completa. Valor de referêcia: ");
  Serial.println(referenceValue);
  // Reinicializar variáveis para próxima calibração
  ldrValue = 0;
}
void calibrationCompleted() {
  for (int repetition = 0; repetition < 3; repetition++){
  digitalWrite(ledCalibration, LOW);
  delay(500);
  digitalWrite(ledCalibration, HIGH);
  delay(500);
  }
}
void checkSystemState() {
    // Fazer a leitura atual do LDR
    int currentValue = analogRead(ldrPin);
    // Comparar com o valor de referência
    if (currentValue < referenceValue * detectionThreshold) {
      // Ativar o alarme
      Serial.println("Food running low! Take necessary measures.");
      // TODO: Acionar o alarme, por exemplo, acender um LED ou emitir um som
      digitalWrite(buzzerPin, HIGH); // Ativa o Buzzer
    }else {
      digitalWrite(buzzerPin, LOW);  // Desativa o Buzzer
  }
}
