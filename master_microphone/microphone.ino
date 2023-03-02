#include <SoftwareSerial.h>   // 引用程式庫
SoftwareSerial BT(10, 11); // 接收腳, 傳送腳
#define inputPin A5  // selecting the analog input pin
#define DIFFERENCE 500
#define TrashTimes 10000
#define SWITCH 'K'
#define DONE 'R'
unsigned int inputSample; // placeholder for a single measurement
unsigned int inputMax;
unsigned int inputMin;
int diff;

void setup() {
  Serial.begin(9600);   // 與電腦序列埠連線
  BT.begin(9600);
}

void loop() {
  char val = '\0';  // 儲存接收資料的變數
  
  _readSound();  // loop for the window
  _displayDiff(); // send the values on serial
  
  if (diff > DIFFERENCE) {
    BT.print(SWITCH);
    delay(500);
  }
  
  if (BT.available()) {
    val = BT.read();
    if (val == DONE) 
      _readSound();
  }
  delay(500);
}

void _readSound() {
  inputMax = 0;
  inputMin = 1024;
  diff = 0;
  for (unsigned int i = 0; i < TrashTimes; i++) {
    inputSample = analogRead(inputPin); // read in a single value
    inputMin = min(inputMin, inputSample);  // get the minimum and maximum value
    inputMax = max(inputMax, inputSample);
  }
}

void _displayDiff() {
  Serial.println("---");
  diff = inputMax - inputMin;
  Serial.print("\tTarget\t:\t");
  Serial.println(DIFFERENCE);
  Serial.print("\tNow\t:\t");
  Serial.println(diff);
  if (diff > DIFFERENCE) {
    Serial.println(">>\tTurn On/ Off");  
  }
  else {
    Serial.println(">>>\tLouder !!!");
  }
  Serial.println("---");
}
