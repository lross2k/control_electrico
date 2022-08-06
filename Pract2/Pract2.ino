bool mux_2x1(bool D1, bool D2, bool S0) {
    return(D2*S0+D1*!S0);
}

bool mux_4x1(bool D1, bool D2, bool D3, bool D4, bool S1, bool S0) {
    return(D1*(!S1&!S0) + D2*(!S1&S0) + D3*(S1&!S0) + D4*(S1&S0));
}

bool mux_8x1(bool D1, bool D2, bool D3, bool D4, bool D5, bool D6, bool D7, bool D8, bool S2, bool S1, bool S0) {
    return((!S2&!S1&!S0)*D1 + (!S2&!S1&S0)*D2 + (!S2&S1&!S0)*D3 + (!S2&S1&S0)*D4 +
            (S2&!S1&!S0)*D5 + (S2&!S1&S0)*D6 + (S2&S1&!S0)*D7 + (S2&S1&S0)*D8);
}

void setup() {
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, OUTPUT);
}

void loop() {
    bool A = digitalRead(3);
    bool B = digitalRead(4);
    bool C = digitalRead(5);
    bool D = digitalRead(6);
    /* Implementados por menos significativa */
    digitalWrite(7,mux_8x1(0, D, D, !D, !D, 0, !D, D, A, B, C));
    //digitalWrite(7,mux_2x1(mux_4x1(0, D, D, !D, B, C),mux_4x1(!D, 0, !D, D, B, C),A));
    /* Implementados por mas significativos */
	//digitalWrite(7,mux_8x1(A,0,0,!A,A,!A,!A,A,B,C,D));
  	//digitalWrite(7,mux_2x1(mux_4x1(A,0,0,!A,C,D),mux_4x1(A,!A,!A,A,C,D),B));
    delay(100);
}

