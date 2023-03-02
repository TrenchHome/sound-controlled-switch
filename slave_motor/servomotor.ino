#include <SoftwareSerial.h>
#include <Wire.h>  //引用二個函式庫SoftwareSerial及Wire SoftwareSerial 
#include <Servo.h>
#define ServoPin 9
#define SWITCH 'K'
#define DONE 'R'
SoftwareSerial I2CBT(10, 11); //定義PIN10及PIN11分別為TX及RX腳位
Servo serv;
int type = 0;
char val;  // 儲存接收資料的變數

void setup() {
  Serial.begin(9600); //Arduino鮑率
  I2CBT.begin(38400); //藍牙鮑率
  serv.attach(ServoPin);
  serv.write(77);
}

void loop() {
  val = '\0';
  
  if (I2CBT.available()) { //判斷訊息接收
    val = I2CBT.read();
    ///////////////////////_displayType ();////////////////////////
    if ( val == SWITCH )
      _switch();
  }
  
  delay(1000);
}

void _switch () { //type = 0 : 順時鐘轉 (正對sevo, 線在左方) 
                  //type = 1 : 逆時鐘轉
  int pos;
  if (type) {
    for (pos = 80; pos >= 55 ; pos -= 4)
      serv.write(pos);
    delay(300);
    serv.write(77);
  }
  else {
    for (pos = 110; pos <= 135 ; pos += 4)
      serv.write(pos);
    delay(300);
    serv.write(100);
  }
  type = (type + 1) % 2;
  I2CBT.print(DONE);
}

void _displayType () {
  Serial.print("Available. type= ");
  Serial.println(type);
}
