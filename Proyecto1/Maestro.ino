// Maestro
// Incluir biblioteca para usar protocolo I2C
#include <Wire.h>

// Se configuran los pines para actuar como OUTPUT
void setup() {
    // Incializar objeto de Wire para maestro
    Wire.begin();
    /* Equivalente a pinMode(...) mediante registros
     * esto tiene la misma velocidad que usar pinMode 
     * (a menos que el compilador no sea bueno) pero 
     * también es mucho más limpio en el código */
    DDRB |= B11111111;
    DDRD |= B11111111;
}

// Ciclo del Arduino
void loop() {
    Wire.requestFrom(4,2); // Solicitar 2 bytes al dispositivo 4
    // Mostrar primer byte a la izq
    display_write(0, Wire.read());
    display_write(7, Wire.read());
    delay(50); // Para que el esclavo pueda generar los datos
}

// Simple función que asigna valores a un array de 7 datos
void asignar_valores(bool *array, bool A, bool B, bool C,
                     bool D, bool E, bool F, bool G) {
    array[0] = !A; array[1] = !B; array[2] = !C;
    array[3] = !D; array[4] = !E; array[5] = !F;
    array[6] = !G;
}

/* Abstraccion para pines del display
 * argumentos A, B, C, D, E, F, G
 * pasar un 1 o HIGH significa que se enciende */
void display_write(uint8_t pin_inicial, uint8_t valor) {
    bool segmentos[7]; // Array con el estado para cada segmento
    // Elegir los estados según el número que se necesite
    switch (valor) {
        case 0: asignar_valores(segmentos,1,1,1,1,1,1,0); break;
        case 1: asignar_valores(segmentos,0,1,1,0,0,0,0); break;
        case 2: asignar_valores(segmentos,1,1,0,1,1,0,1); break;
        case 3: asignar_valores(segmentos,1,1,1,1,0,0,1); break;
        case 4: asignar_valores(segmentos,0,1,1,0,0,1,1); break;
        case 5: asignar_valores(segmentos,1,0,1,1,0,1,1); break;
        case 6: asignar_valores(segmentos,1,0,1,1,1,1,1); break;
        case 7: asignar_valores(segmentos,1,1,1,0,0,0,0); break;
        case 8: asignar_valores(segmentos,1,1,1,1,1,1,1); break;
        case 9: asignar_valores(segmentos,1,1,1,1,0,1,1); break;
    }
    // Encender/Apagar cada segmento con los estados definidos
    for (int i = 0; i < 7; i++)
        digitalWrite(pin_inicial+i, segmentos[i]);
}

