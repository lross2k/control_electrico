// Esclavo
// Incluir biblioteca para usar protocolo I2C
#include <Wire.h>

//Definir variables
/* uint8_t es otra manera de decir unsignet short int o 
 * unsigned char
 * básicamente almacena 1 byte (8 bits) de 0 a 255 */
uint8_t primer_byte = 0, segundo_byte = 0; // Bytes para I2C

// Setup del Arduino
void setup() {
    Wire.begin(4); // Iniciar protocolo I2C como dispositivo 4
    /* Se asigna la función respuesta_i2c como la función que 
     * debe correr cada vez que otro dispositivo solicite 
     * una respuesta mediante I2C */
    Wire.onRequest(respuesta_i2c);
}

// Ciclo del Arduino
void loop() {
    // Declarar e inicializar valores de botones 1 bit cada uno
    bool A = digitalRead(2);
    bool B = digitalRead(3);
    bool Z = digitalRead(4);
    bool parte_b = digitalRead(5); // Slide Switch
    if ((segundo_byte > 5 || primer_byte > 1) && !parte_b) {
  	  segundo_byte = primer_byte = 0;
    }
    /* Valor del potenciómetro, se usa double para que C 
     * permita operaciones de punto flotante más adelante */
    double analog_val = analogRead(A3); // Podría ser float en vez de double
    if (!parte_b) { // Si estamos en la parte A del problema
        // Se elige el resultado que se escribe en el primer byte
        primer_byte = (A|B)*!segundo_byte + (A&B)*segundo_byte +
                      (A^B)*(segundo_byte==2) + !(A&B)*(segundo_byte==3) +
                      !(A|B)*(segundo_byte==4) + !(A^B)*(segundo_byte==5);
        // Se guarda el estado actual en el segundo byte a escribir
        segundo_byte = Z*((segundo_byte+1)*(segundo_byte<5))+!Z*segundo_byte;
        //delay(300);
    } else { // Si estamos en la parte B
        // Se debe hacer el mapeo, redondeo y manejo de decimales al display
        analog_val = analog_val/1023*5;
        // Obtener el primer entero
        primer_byte = (int)analog_val;
        // Obtener el primer decimal
        segundo_byte = (int)((analog_val-primer_byte)*10);
        // Redondear siguiente decimal
        segundo_byte += (int)((((analog_val-primer_byte)*10)-
                        (int)((analog_val-primer_byte)*10))*10);
    }
}

// Respuesta de I2C envia los dos bytes definidos
void respuesta_i2c() {
    Wire.write(primer_byte);
    Wire.write(segundo_byte);
}

