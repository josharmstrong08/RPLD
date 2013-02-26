int oe = 9;
int sclk = 8;
int lat = 10;
int a = A0;
int b = A1;
int c = A2;
int d = A3;
int r1 = 2;
int g1 = 3;
int b1 = 4;
int r2 = 5;
int g2 = 6;
int b2 = 7;

void setup() {
  pinMode(oe, OUTPUT);
  pinMode(sclk, OUTPUT);
  pinMode(lat, OUTPUT);
  
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(g1, OUTPUT);
  pinMode(g2, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  
  digitalWrite(sclk, LOW);
  digitalWrite(lat, LOW);
  digitalWrite(oe, HIGH);
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(r1, LOW);
  digitalWrite(r2, LOW);
  digitalWrite(g1, LOW);
  digitalWrite(g2, LOW);
  digitalWrite(b1, LOW);
  digitalWrite(b2, LOW);
  //---------------------------
  digitalWrite(oe, LOW);
}

int counter = 0;
int seperator = 32;

void clockInData() {
  int column;
  for (column = 0; column < 32; column++) {
    if (column < seperator) {
      digitalWrite(r1, HIGH);
      digitalWrite(r2, LOW);
      digitalWrite(g1, LOW);
      digitalWrite(g2, HIGH);
      digitalWrite(b1, LOW);
      digitalWrite(b2, LOW);
    } else {
      digitalWrite(r1, LOW);
      digitalWrite(r2, HIGH);
      digitalWrite(g1, LOW);
      digitalWrite(g2, HIGH);
      digitalWrite(b1, HIGH);
      digitalWrite(b2, HIGH);
    }
    
    digitalWrite(sclk, LOW);
    digitalWrite(sclk, HIGH);
  }
}

void selectRow(unsigned int row) {
  digitalWrite(a, row & _BV(0));
  digitalWrite(b, row & _BV(1));
  digitalWrite(c, row & _BV(2));
  digitalWrite(d, row & _BV(3));
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
    digitalWrite(lat, HIGH);
    
    // select the row
    selectRow(row);
    
    // renable output
    //digitalWrite(oe, LOW);
    // unlatch
    digitalWrite(lat, LOW);
    
    clockInData();
  }
}
