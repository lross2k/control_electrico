// El de arriba, generador de señal

void setup()
{
    pinMode(A5, INPUT);
    pinMode(13, OUTPUT);
}

void loop()
{
    static unsigned long tiempo_anterior = 0;
    unsigned long tiempo_actual = millis();
    uint16_t lectura = analogRead(A5);
    double intervalo = map(lectura, 0, 1023, 0, 500); // 0 a 500 Hz
    static bool proxima_salida = 0;
    intervalo = (1/intervalo)*1000/2.0f; // se convierte a segundos
  /*
    intervalo = 1/intervalo;
    intervalo *= 1000.0; // se convierte a millis
    intervalo /= 2.0; // se divide para 50% del ciclo
    */
    if (tiempo_actual - tiempo_anterior >= intervalo) {
        digitalWrite(13, proxima_salida);
        tiempo_anterior = tiempo_actual;
        proxima_salida = !proxima_salida;
    }
}

