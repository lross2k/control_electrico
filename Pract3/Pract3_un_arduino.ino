bool QJK = 0;
bool QSR = 0;

void setup() {
  pinMode(A5, INPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(13, OUTPUT);
  for (int i = 0; i < 9; i++)
      pinMode(i, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), my_isr, RISING);
}

void loop() {
  // Lógica para SR Latch
  bool S = digitalRead(7);
  bool R = digitalRead(8);
  QSR = S+QSR*!R; // SR Latch con prioridad al set

  // Logica para clear y preset (prioridad al clear)
  bool CLR = digitalRead(4);
  bool PRST = digitalRead(3);
  if (PRST) {
    QJK = QSR = 0;
  } else if (CLR) {
    QJK = QSR = 1;
  }

  // Logica para generar pulso cuadrado sin delay
  static unsigned long tiempo_anterior = 0;
  unsigned long tiempo_actual = millis();
  uint16_t lectura = analogRead(A5);
  double intervalo = map(lectura, 0, 1023, 0, 500); // 0 a 500 Hz
  static bool proxima_salida = 0;
  intervalo = (1/intervalo)*1000/2.0; // se convierte a segundos
  if (tiempo_actual - tiempo_anterior >= intervalo) {
    digitalWrite(13, proxima_salida);
    tiempo_anterior = tiempo_actual;
    proxima_salida = !proxima_salida;
  }

  // Encender LEDs con estado correspondiente
  digitalWrite(9, QJK);
  digitalWrite(10, QSR);
  delay(40); // Para darle tiempo a TinkerCAD de pensar
}

void my_isr() {
  // Logica para el FlipFlop JK
  bool J = digitalRead(5);
  bool K = digitalRead(6);
  QJK = J*!QJK+!K*QJK;
}

