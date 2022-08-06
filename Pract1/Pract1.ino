// Definición de macros para compuertas lógicas
#define AND(A,B)  A&&B
#define OR(A,B)   A||B
#define XOR(A,B)  A^B
#define NOR(A,B)  !(A||B)
#define NAND(A,B) !(A&&B)

// Definición de macros para pines de entrada
#define ENT_A     3
#define ENT_B     4

// Definición de macros para pines de salida
#define PIN_AND   8
#define PIN_OR    9
#define PIN_XOR   10
#define PIN_NOR   11
#define PIN_NAND  12

// Variables globales
bool output[5] = {0,0,0,0,0};
bool input[2] = {0,0};

// Setup del Arduino y sus pines
void setup() {
  pinMode(ENT_A,    INPUT);
  pinMode(ENT_B,    INPUT);
  pinMode(PIN_AND,  OUTPUT);
  pinMode(PIN_OR,   OUTPUT);
  pinMode(PIN_XOR,  OUTPUT);
  pinMode(PIN_NOR,  OUTPUT);
  pinMode(PIN_NAND, OUTPUT);
}

// Se activa la compuerta lógica correspondiente
void loop() {
  // Lectura de inputs
  int i;
  input[0] = digitalRead(ENT_A);
  input[1] = digitalRead(ENT_B);
  
  // Escritura de datos
  for (i = 0; i < 6; i++)
    digitalWrite(i+PIN_AND, output[i]);
  
  // Cálculo de datos
  output[0] = AND(input[0],input[1]);
  output[1] = OR(input[0],input[1]);
  output[2] = XOR(input[0],input[1]);
  output[3] = NOR(input[0],input[1]);
  output[4] = NAND(input[0],input[1]);
  
  // Se aplica un delay de 1 ms
  delay(1);
}

