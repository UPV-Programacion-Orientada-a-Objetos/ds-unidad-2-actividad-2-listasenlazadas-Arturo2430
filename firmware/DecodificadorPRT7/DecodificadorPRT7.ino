/*
 * Simulador PRT-7 para ESP32
 * Envia tramas segun el protocolo del README
 * Formato: L,<caracter> o M,<numero>
 */

// Tramas a enviar (exactamente como en el README)
const char* tramas[] = {
  "L,H",
  "L,O",
  "L,L",
  "M,2",
  "L,A",
  "L,Space",      // L,Space (usar texto en vez de un espacio)
  "L,W",
  "M,-2",
  "L,O",
  "L,R",
  "L,L",
  "L,D"
};

const int NUM_TRAMAS = 12;
int tramaIndex = 0;

void setup() {
  Serial.begin(115200);
  
  tramaIndex = 0;
  
  delay(2000);  // Esperar 2 segundos antes de empezar
}

void loop() {
  if (tramaIndex < NUM_TRAMAS) {
    // Enviar la trama actual
    Serial.println(tramas[tramaIndex]);
    
    // Avanzar al siguiente índice
    tramaIndex++;
    
    // Esperar 1 segundo (delay entre tramas)
    delay(1000);
  } else {
    // Cuando termine, reiniciar después de 5 segundos
    delay(5000);
    tramaIndex = 0;
    Serial.println("\n--- REINICIANDO SECUENCIA ---\n");
  }
}
