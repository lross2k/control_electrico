// Estructura de datos para manejo más simple de memoria
struct datos_estado {
    bool estado;
    uint8_t salida;
    uint8_t pines_entradas[];
};

// Declaración de estructuras de datos
volatile struct datos_estado ff_jk = {0,11,{3,4}}; // Flip Flop JK
volatile struct datos_estado ff_d = {0,13,{6}}; // Flip Flop D
volatile struct datos_estado ff_t = {0,12,{5}}; // Flip Flop T
volatile struct datos_estado l_sr = {0,0,{7,8}}; //Latch SR

// Pines de entradas
const uint8_t clr = 9;
const uint8_t prst = 10;

// Setup de pines e interrupt
void setup() {
    attachInterrupt(digitalPinToInterrupt(2), isr_flanco_positivo, RISING);
    // Pines activados por registros (menos líneas)
    DDRD |= B11111101;
    DDRB |= B00000111;
    DDRB &= !B00111000;
}

// Elementos asincrónicos
void loop() {
    // Lógica para SR Latch
    bool s = digitalRead(l_sr.pines_entradas[0]), r = digitalRead(l_sr.pines_entradas[1]);
    l_sr.estado = l_sr.estado*(!s&&!r) + (s&&!r) + (s&&r); // sr latch con prioridad al set

    // Aplicar efecto de clear y preset
    bool vclr = digitalRead(clr), vprst = digitalRead(prst);
    if (vclr && !vprst) {
        l_sr.estado = ff_jk.estado = ff_d.estado = ff_t.estado = 0;
    } else if (!vclr && vprst) {
        l_sr.estado = ff_jk.estado = ff_d.estado = ff_t.estado = 1;
    } else if (vclr && vprst) {
        l_sr.estado = ff_jk.estado = ff_d.estado = ff_t.estado = 0; // prioridad al clear
    }

    // Activación de LEDs
    digitalWrite(l_sr.salida, l_sr.estado);
    digitalWrite(ff_d.salida, ff_d.estado);
    digitalWrite(ff_t.salida, ff_t.estado);
    digitalWrite(ff_jk.salida, ff_jk.estado);

    // Delay, obvs
    //delay(100);
}

// Lógica para elementos sincrónicos, en flanco positivo
void isr_flanco_positivo() {
    // Lógica para FF D
    ff_d.estado = digitalRead(ff_d.pines_entradas[0]);
    // Lógica para FF T
    ff_t.estado = !ff_t.estado*digitalRead(ff_t.pines_entradas[0]) + ff_t.estado*!digitalRead(ff_t.pines_entradas[0]);
    // Lógica para FF JK
    bool j = digitalRead(ff_jk.pines_entradas[0]), k = digitalRead(ff_jk.pines_entradas[1]);
    ff_jk.estado = ff_jk.estado*(!j&&!k) + (j&&!k) + (j&&k)*!ff_jk.estado;
}

