//programmed by Felipe Sanches
//released to the public domain

int BD0 = 2;
int BD1 = 3;
int BD2 = 4;
int BD3 = 5;
int BD4 = 6;
int BD5 = 7;
int BD6 = 8;
int BD7 = 9;

int S0 = A0;
int S1 = A1;
int S2 = A2;

int D0 = 10; //D6 | D2
int D1 = 11; //D7 | D3
int D2 = 12; //D5 | D1
int D3 = 13; //D4 | D0

void setup(){
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);

  pinMode(BD0, OUTPUT);
  pinMode(BD1, OUTPUT);
  pinMode(BD2, OUTPUT);
  pinMode(BD3, OUTPUT);
  pinMode(BD4, OUTPUT);
  pinMode(BD5, OUTPUT);
  pinMode(BD6, OUTPUT);
  pinMode(BD7, OUTPUT);

  pinMode(D0, INPUT);
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);

  Serial.begin(38400);
}

void loop(){

  int endereco = 0;
  int dado = 0;

  while (endereco < 20000){
    //escreve 8 bits baixos de endereço (nos pinos 3,5,7,9,11,13,15,17 da porta paralela)
    digitalWrite(BD0, endereco & (1<<0) ? HIGH : LOW);
    digitalWrite(BD1, endereco & (1<<1) ? HIGH : LOW);
    digitalWrite(BD2, endereco & (1<<2) ? HIGH : LOW);
    digitalWrite(BD3, endereco & (1<<3) ? HIGH : LOW);
    digitalWrite(BD4, endereco & (1<<4) ? HIGH : LOW);
    digitalWrite(BD5, endereco & (1<<5) ? HIGH : LOW);
    digitalWrite(BD6, endereco & (1<<6) ? HIGH : LOW);
    digitalWrite(BD7, endereco & (1<<7) ? HIGH : LOW);

    delay(1);
    //seleciona endereço 2 (010) (nos pinos 8, 2 e 1 da porta paralela)
    digitalWrite(S0, LOW);
    digitalWrite(S1, HIGH);
    digitalWrite(S2, LOW);
    
    //escreve 8 bits altos de endereço
    digitalWrite(BD0, endereco & (1<<8) ? HIGH : LOW);
    digitalWrite(BD1, endereco & (1<<9) ? HIGH : LOW);
    digitalWrite(BD2, endereco & (1<<10) ? HIGH : LOW);
    digitalWrite(BD3, endereco & (1<<11) ? HIGH : LOW);
    digitalWrite(BD4, endereco & (1<<12) ? HIGH : LOW);
    digitalWrite(BD5, endereco & (1<<13) ? HIGH : LOW);
    digitalWrite(BD6, endereco & (1<<14) ? HIGH : LOW);
    digitalWrite(BD7, endereco & (1<<15) ? HIGH : LOW);

    delay(1);
    //seleciona endereço 3 (011) (e já é suficiente também para se selecionar leitura do primeiro nibble)
    digitalWrite(S0, HIGH);
    digitalWrite(S1, HIGH);
    digitalWrite(S2, LOW);
    delay(1);
    
    //lê 4 bits dos pinos 19-21-23-25 da porta paralela
    dado = 0;
    if (digitalRead(D0)) dado += (1<<6);
    if (digitalRead(D1)) dado += (1<<7);
    if (digitalRead(D2)) dado += (1<<5);
    if (digitalRead(D3)) dado += (1<<4);

    //seleciona endereço 1 para alternar para leitura do outro nibble
    digitalWrite(S0, HIGH);
    digitalWrite(S1, LOW);
    digitalWrite(S2, LOW);

    delay(1);
    //lê 4 bits dos pinos 19-21-23-25 da porta paralela 
    if (digitalRead(D0)) dado += (1<<2);
    if (digitalRead(D1)) dado += (1<<3);
    if (digitalRead(D2)) dado += (1<<1);
    if (digitalRead(D3)) dado += (1<<0);

    Serial.print(endereco, HEX);
    Serial.print(":");
    Serial.print(dado, HEX);
    Serial.print(" '"); 
    Serial.write(dado);
    Serial.println("'");

    endereco++;
  }
}

