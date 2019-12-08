int latchPin = 8;
int clockPin = 12;
int dataPin = 11;
char val;
char wval;

int count[16];
int Array[160];

int n = 16;

int ur,dr;

int change = 200;

byte dataUP;
byte dataDOWN;
byte dataArrayUP[5];
byte dataArrayDOWN[5];

byte RdataArrayUP[16];
byte RdataArrayDOWN[16];
byte PdataArrayUP[16];
byte PdataArrayDOWN[16];

bool first = false;
int set = 0;
int g = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);


//ランダム用配列への格納
  for(int i = 0; i < 16; i++){
    count[i] = i;
  }

  for(int j = 0;j < 10; j++){
    shuffle(count,n);
    for(int i = 0; i<n; i++){
      Array[i + set] = count[i];
    }
    set = set + 16;
  }

  //シリアル1:上段を光らせるパターン
  dataArrayUP[0] = 0xFF;
  dataArrayUP[1] = 0x88;
  dataArrayUP[2] = 0x44;
  dataArrayUP[3] = 0x22;
  dataArrayUP[4] = 0x11;
  //シリアル2:下段を光らせるパターン
  dataArrayDOWN[0] = 0xFF;
  dataArrayDOWN[1] = 0x88;
  dataArrayDOWN[2] = 0x44;
  dataArrayDOWN[3] = 0x22;
  dataArrayDOWN[4] = 0x11;

//
//  RdataArrayUP[0] = 0x88;
//  RdataArrayUP[1] = 0x84;
//  RdataArrayUP[2] = 0x82;
//  RdataArrayUP[3] = 0x81;
//  RdataArrayUP[4] = 0x48;
//  RdataArrayUP[5] = 0x44;
//  RdataArrayUP[6] = 0x42;
//  RdataArrayUP[7] = 0x41;
//  RdataArrayUP[8] = 0x28;
//  RdataArrayUP[9] = 0x24;
//  RdataArrayUP[10] = 0x22;
//  RdataArrayUP[11] = 0x21;
//  RdataArrayUP[12] = 0x18;
//  RdataArrayUP[13] = 0x14;
//  RdataArrayUP[14] = 0x12;
//  RdataArrayUP[15] = 0x11;
//
//  RdataArrayDOWN[0] = 0x88;
//  RdataArrayDOWN[1] = 0x84;
//  RdataArrayDOWN[2] = 0x82;
//  RdataArrayDOWN[3] = 0x81;
//  RdataArrayDOWN[4] = 0x48;
//  RdataArrayDOWN[5] = 0x44;
//  RdataArrayDOWN[6] = 0x42;
//  RdataArrayDOWN[7] = 0x41;
//  RdataArrayDOWN[8] = 0x28;
//  RdataArrayDOWN[9] = 0x24;
//  RdataArrayDOWN[10] = 0x22;
//  RdataArrayDOWN[11] = 0x21;
//  RdataArrayDOWN[12] = 0x18;
//  RdataArrayDOWN[13] = 0x14;
//  RdataArrayDOWN[14] = 0x12;
//  RdataArrayDOWN[15] = 0x11;


  PdataArrayUP[0] = 0x0;
  PdataArrayUP[1] = 0x10;
  PdataArrayUP[2] = 0x1;
  PdataArrayUP[3] = 0x0;
  PdataArrayUP[4] = 0x0;
  PdataArrayUP[5] = 0x11;
  PdataArrayUP[6] = 0x10;
  PdataArrayUP[7] = 0x10;
  PdataArrayUP[8] = 0x1;
  PdataArrayUP[9] = 0x1;
  PdataArrayUP[10] = 0x0;
  PdataArrayUP[11] = 0x11;
  PdataArrayUP[12] = 0x11;
  PdataArrayUP[13] = 0x10;
  PdataArrayUP[14] = 0x1;
  PdataArrayUP[15] = 0x11;

  PdataArrayDOWN[0] = 0x0;
  PdataArrayDOWN[1] = 0x0;
  PdataArrayDOWN[2] = 0x0;
  PdataArrayDOWN[3] = 0x10;
  PdataArrayDOWN[4] = 0x1;
  PdataArrayDOWN[5] = 0x0;
  PdataArrayDOWN[6] = 0x10;
  PdataArrayDOWN[7] = 0x1;
  PdataArrayDOWN[8] = 0x10;
  PdataArrayDOWN[9] = 0x1;
  PdataArrayDOWN[10] = 0x11;
  PdataArrayDOWN[11] = 0x10;
  PdataArrayDOWN[12] = 0x1;
  PdataArrayDOWN[13] = 0x11;
  PdataArrayDOWN[14] = 0x11;
  PdataArrayDOWN[15] = 0x11;
}

void loop() {

  // put your main code here, to run repeatedly:
  //シリアル通信ができてたらシリアルを読み取る
  if (Serial.available()) {
    val = Serial.read();//変数valにシリアルを代入
  }
  //Serial.print(val);
  //シリアルが1だったら入る
  if (val == '1' && first == false) {
    //for(int j = 0; j < 5; j++){
    dataUP = dataArrayUP[4];
    dataDOWN = dataArrayDOWN[4];

    digitalWrite(latchPin, 0);

    shiftOut(dataPin, clockPin, dataDOWN);
    shiftOut(dataPin, clockPin, dataUP);

    digitalWrite(latchPin, 1);
    delay(5000);

    //}
    first = true;
  } else if (val == '1' && first == true) {
    for (int j = 1; j < 5; j++) {
      dataUP = dataArrayUP[j];
      dataDOWN = dataArrayDOWN[j];

      digitalWrite(latchPin, 0);

      shiftOut(dataPin, clockPin, dataDOWN);
      shiftOut(dataPin, clockPin, dataUP);

      digitalWrite(latchPin, 1);
      delay(2000);

    }
  }
  if (val == '2') {
    for(int i = 0; i< 10; i++){
    for(int j = 0; j < 16; j++){
    dataUP = PdataArrayUP[j];
    dataDOWN = PdataArrayDOWN[j];
  
    Serial.write(wval);
    digitalWrite(latchPin, 0);

      shiftOut(dataPin, clockPin, dataDOWN);
      shiftOut(dataPin, clockPin, dataUP);

      digitalWrite(latchPin, 1);

      delay(1000);
    }
    }
    delay(10000);
  }
//ランダムで10回分
  if(val == '3'){
  for (int j = 0; j < 160; j++) {
      g = Array[j];
      dataUP = PdataArrayUP[g];
      dataDOWN = PdataArrayDOWN[g];
     Serial.println(String(set));
      digitalWrite(latchPin, 0);

      shiftOut(dataPin, clockPin, dataDOWN);
      shiftOut(dataPin, clockPin, dataUP);

      digitalWrite(latchPin, 1);
      delay(change);

    }
    delay(10000);

  }

}


//シフトアウト用関数
void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {

  int i = 0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);

  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);

  for (i = 0; i < 8; i++) {
    digitalWrite(myClockPin, 0);

    if (myDataOut & (1 << i)) {
      pinState = 1;
    } else {
      pinState = 0;
    }

    digitalWrite(myDataPin, pinState);

    digitalWrite(myClockPin, 1);
    digitalWrite(myDataPin, 0);
  }
}

//乱数生成用のシャッフル関数
void shuffle(int array[],int num){
  int i = num;
  while(i > 1){
    int j = random(0,16);
    i--;
    int t = array[i];
    array[i] = array[j];
    array[j] = t;
  }
  
}


