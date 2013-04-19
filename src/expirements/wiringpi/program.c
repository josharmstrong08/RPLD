
#include <stdio.h>
#include <wiringPi.h>
/*
int OE = 9;
int SCLK = 8;
int LAT = 14;
int A = 10;
int B = 11;
int C = 12;
int D = 13;
int R1 = 2;
int G2 = 3;
int B2 = 4;
int r2 = 5;
int g2 = 6;
int b2 = 7;
*/
/*
int OE = 15;
int SCLK = 16;
int LAT = 0;
int A = 4;
int B = 12;
int C = 1;
int D = 3;
int R1 = 11;
int G1 = 14;
int B1 = 6;
int R2 = 10;
int G2 = 13;
int B2 = 5;
*/

int OE = 1;
int SCLK = 16;
int LAT = 4;
int A = 2;
int B = 6;
int C = 15;
int D = 5;
int R1 = 14;
int G1 = 11;
int B1 = 13;
int R2 = 12;
int G2 = 10;
int B2 = 3;

void setup() {
  pinMode(OE, OUTPUT);
  pinMode(SCLK, OUTPUT);
  pinMode(LAT, OUTPUT);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(G1, OUTPUT);
  pinMode(G2, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);
  
  digitalWrite(SCLK, LOW);
  digitalWrite(LAT, LOW);
  digitalWrite(OE, HIGH);
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
  digitalWrite(G1, LOW);
  digitalWrite(G2, LOW);
  digitalWrite(B1, LOW);
  digitalWrite(B2, LOW);
  //---------------------------
  digitalWrite(OE, LOW);
}

int counter = 0;
int seperator = 32;

void clockInData() {
  int column;
  for (column = 0; column < 32; column++) {
    if (column < seperator) {
      digitalWrite(R1, HIGH);
      digitalWrite(R2, LOW);
      digitalWrite(G1, LOW);
      digitalWrite(G2, HIGH);
      digitalWrite(B1, LOW);
      digitalWrite(B2, LOW);
    } else {
      digitalWrite(R1, LOW);
      digitalWrite(R2, HIGH);
      digitalWrite(G1, LOW);
      digitalWrite(G2, HIGH);
      digitalWrite(B1, HIGH);
      digitalWrite(B2, HIGH);
    }

    digitalWrite(SCLK, LOW);
    digitalWrite(SCLK, HIGH);
  }
}

void selectRow(unsigned int row) {
  digitalWrite(A, row & 0x01);
  digitalWrite(B, row & 0x02);
  digitalWrite(C, row & 0x04);
  digitalWrite(D, row & 0x08);
}

void loop() {
  counter++;
  if (counter > 1) {
    counter = 0;
    seperator--;
    if (seperator < 0) {
      seperator = 32;
    }
  }

  int row = 0;
  for (row = 0; row < 16; row++) {
    // disable output
    //digitalWrite(oe, HIGH);
    // latch data load in previous cycle
    digitalWrite(LAT, HIGH);

    // select the row
    selectRow(row);

    // renable output
    //digitalWrite(oe, LOW);
    // unlatch
    digitalWrite(LAT, LOW);

    clockInData();
    delayMicroseconds(1000);
  }
}

int main() {
  if (wiringPiSetup() == -1) {
    printf("Wiring pi setup failed\n");
    return 1; 
  }

  piHiPri(99);
  
  setup();
  
  while (1) {
    loop();
  }
  
  return 0;
}
