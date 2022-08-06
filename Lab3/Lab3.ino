#include <LiquidCrystal.h>

// Macros para pines
#define BOTON_SELECT 9
#define BOTON_LEFT   8
#define BOTON_RIGTH  7
#define BOTON_UP     6
#define BOTON_DOWN   10
// Macro para operaciones de imprimir bits
#define PRINT_4BIT(VAL) lcd.print(VAL>>3);        \
                      lcd.print((VAL&1<<2)>>2); \
                      lcd.print((VAL&1<<1)>>1); \
                      lcd.print(VAL&1);

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
uint8_t pulsos = 2; // de 1 a 20 -> 00001 a 10100 -> 5 bits
uint8_t bipolar = 10;
uint8_t unipolar = 12;
bool corriendo = 0;
bool izquierda = 0;
unsigned long tiempo_previo = 0;

void setup()
{
    lcd.begin(16, 2); // col, fila
    lcd.clear();
    pinMode(BOTON_DOWN, INPUT);
    pinMode(BOTON_UP, INPUT);
    pinMode(BOTON_LEFT, INPUT);
    pinMode(BOTON_RIGTH, INPUT);
    pinMode(BOTON_SELECT, INPUT);
}

void loop()
{
  // Almacenar inputs
  bool btn_select = digitalRead(BOTON_SELECT);
  bool btn_left   = digitalRead(BOTON_LEFT);
  bool btn_rigth  = digitalRead(BOTON_RIGTH);
  bool btn_up     = digitalRead(BOTON_UP);
  bool btn_down   = digitalRead(BOTON_DOWN);

    // Pulsos por segundo varían con up y down entre 1pps a 20pps
  pulsos += btn_up*(pulsos<20) - btn_down*(pulsos>0);
  
  lcd.clear();
  // Imprime pulso actual
  lcd.setCursor(12,1);
  if (pulsos < 10)
    lcd.print(0);
  lcd.print(pulsos);
  lcd.setCursor(10,0);
  lcd.print("PULSOS");
  
  lcd.setCursor(5,1);
  if (corriendo)
  {
    lcd.print("RUN");
    corriendo = !btn_select;
    // Imprimir el set de arriba de Qx
    lcd.setCursor(0,0);
    PRINT_4BIT(bipolar);
    // Imprimir el set de abajo de Qx
    lcd.setCursor(0,1);
    PRINT_4BIT(bipolar);
    
    // Imprimir el set de Sx
    lcd.setCursor(5,0);
    PRINT_4BIT(unipolar);
    
    // Imprimir el signo de dirección actual
    lcd.setCursor(9,1);
    lcd.print(izquierda ? ">>" : "<<");
    
    // Correr logica la cantidad de pulsos cada segundo
    if (millis() - tiempo_previo >= 1000)
    {
      for (int i = 0; i < pulsos; i++) {
        switch(bipolar)
        {
        case 10: bipolar = 9*!izquierda + 6*izquierda;  break;
        case 9:  bipolar = 5*!izquierda + 10*izquierda; break;
        case 5:  bipolar = 6*!izquierda + 9*izquierda;  break;
        case 6:  bipolar = 10*!izquierda + 5*izquierda; break;
        }
        switch(unipolar)
        {
        case 12: unipolar = 6*!izquierda + 9*izquierda;  break;
        case 6:  unipolar = 3*!izquierda + 12*izquierda; break;
        case 3:  unipolar = 9*!izquierda + 6*izquierda;  break;
        case 9:  unipolar = 12*!izquierda + 3*izquierda; break;
        }
      }
      tiempo_previo = millis();
    }
  }
  else
  {
    lcd.print("STOP");
    corriendo = btn_select;
  }
}
