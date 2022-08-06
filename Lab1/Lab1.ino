// Se descomenta la operación que se desesa emplear
//#define F1_AND_OR
//#define F2_AND_OR
//#define F1_NAND
#define F2_NAND

// Syntactic sugar para los fans de C++
using Pin = const uint8_t;

// Definición de macros para compuertas lógicas
#define AND(A,B)  A&B
#define OR(A,B)   A|B
#define NOT(A)    !A
#define NAND(A,B) !(A&B)

// Declaración de pines, sin macros porque ya era mucho
Pin pin_x   = 2;
Pin pin_y   = 3;
Pin pin_z   = 4;
Pin pin_w   = 5;
Pin pin_led = 13;

// Setup de Arduino
void setup() {
  pinMode(pin_x, INPUT);
  pinMode(pin_y, INPUT);
  pinMode(pin_z, INPUT);
  pinMode(pin_w, INPUT);
  pinMode(pin_led, OUTPUT);
}

// Loop de Arduino
void loop() {
  // Declaración de variables
  static bool val = 0;
  bool X, Y, Z, W;
  // Escritura de datos
  digitalWrite(pin_led,val);
  // Lectura de pines
  X = digitalRead(pin_x);
  Y = digitalRead(pin_y);
  Z = digitalRead(pin_z);
  W = digitalRead(pin_w);
  
  val = 
  #if defined(F1_AND_OR)
  /* WY + YX + ZWX */
  OR(OR(AND(W,Y),AND(Y,X)),AND(AND(Z,W),X))
  #elif defined(F1_NAND)
  /* ((WY)'(YX)'(ZWX)')' */
  NAND(NAND(NAND(NAND(W,Y),NAND(X,Y)),
  NAND(NAND(W,Y),NAND(X,Y))),
  NAND(NAND(NAND(Z,W),NAND(Z,W)),X))
  #elif defined(F2_AND_OR)
  /* ZY'X' + YZX + WYX + XY'W'Z' */
  OR(OR(AND(Z,AND(NOT(Y),NOT(X))),
  OR(AND(X,AND(Y,Z)),AND(X,AND(W,Y)))),
  AND(X,AND(NOT(Y),AND(NOT(W),NOT(Z)))))
  #elif defined(F2_NAND)
  /* [(ZY'X')'(YZX)'(WYX)'(XY'W'Z')']' */
  NAND(
  /* (ZY'X')'(YZX)' */
  NAND(NAND(
       /* (ZY'X')' */
       NAND(NAND(NAND(Z,NAND(Y,Y)),NAND(Z,NAND(Y,Y))),NAND(X,X)),
       /* (YZX)' */
       NAND(NAND(NAND(Y,Z),NAND(Y,Z)),X)),
       NAND(
       NAND(NAND(NAND(Z,NAND(Y,Y)),NAND(Z,NAND(Y,Y))),NAND(X,X)),
       NAND(NAND(NAND(Y,Z),NAND(Y,Z)),X)
       )),
  /* (WYX)'(XY'W'Z')' */
  NAND(
    NAND(
    /* (WYX)' */
  NAND(NAND(NAND(W,Y),NAND(W,Y)),X),
    /* (XY'W'Z')' */
  NAND(
    NAND(NAND(X,NAND(Y,Y)),NAND(X,NAND(Y,Y))),
    NAND(NAND(NAND(W,W),NAND(Z,Z)),NAND(NAND(W,W),NAND(Z,Z)))
      )),
    NAND(
  NAND(NAND(NAND(W,Y),NAND(W,Y)),X),
  NAND(
    NAND(NAND(X,NAND(Y,Y)),NAND(X,NAND(Y,Y))),
    NAND(NAND(NAND(W,W),NAND(Z,Z)),NAND(NAND(W,W),NAND(Z,Z)))
      )))
    )
  #endif
  ;
  delay(50);
}

