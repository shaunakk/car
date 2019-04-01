#include <BMI160.h>
#include <CurieIMU.h>

#include <Servo.h>
#include <LiquidCrystal.h>

int hrs=0;
int mins=0;
int secs=0;
LiquidCrystal lcd(A5,A4,A3,A2,A1,A0);
int serialVal;
int STBY = 6; //standby
int counter=0;
//Motor A
int PWMA = 9; //Speed control
int AIN1 = 2; //Direction
int AIN2 = 5; //Direction

//Motor B
int PWMB = 3; //Speed control
int BIN1 = 7; //Direction
int BIN2 = 8; //Direction
int dirr = 1;
int dirl = 1;
int M1=0;
int M2=0;
String buf;
char character;

void move(int motor, int speed, int direction);
void stop();
void setup(){
        pinMode(13,INPUT);
        Serial.begin(115200);
        Serial1.begin(115200);
        pinMode(STBY, OUTPUT);
        pinMode(PWMA, OUTPUT);
        pinMode(AIN1, OUTPUT);
        pinMode(AIN2, OUTPUT);
        pinMode(PWMB, OUTPUT);
        pinMode(BIN1, OUTPUT);
        pinMode(BIN2, OUTPUT);
        pinMode(13, INPUT);
        pinMode(A1, INPUT);
        pinMode(A2, INPUT);
        pinMode(A3, INPUT);
        pinMode(A4, INPUT);
        pinMode(A5, INPUT);
        lcd.begin(16, 2);
        lcd.clear();
        lcd.print("Welcome!");
        delay(2000);
        lcd.clear();
        lcd.print("By Shaunak Kale");
        delay(4000);
        CurieIMU.begin();
        CurieIMU.setGyroRange(360);

}

void loop(){
  if(Serial1.available()){
    character = Serial1.read(); //read the first byte on serial

     if(character != 'L' && character != 'R' && character != 'A' && character != 'B'){ 
         buf+=character;
    } else if(character == 'L'){
        Serial.print(buf);
        M1=buf.toInt();
        buf = "";
    } else if(character == 'R'){
        Serial.print(buf);
        M2=buf.toInt();
        buf = "";
    } else if(character == 'A'){
        Serial.print(buf);
        dirl=buf.toInt();
        buf = "";
    } else if(character == 'B'){
        Serial.print(buf);
        dirr=buf.toInt();
        buf = "";
    } 
    else if(character == 'X'){
        Serial.print(buf);
        dirr=buf.toInt();
        move(1,255,1);
        move(0,255,1);
        delay(2000);
        move(1,255,0);
        move(0,255,0);
        delay(2000);
        move(1,255,1);
        move(0,255,0);
        delay(2000);
        move(1,255,0);
        move(0,255,1);
        delay(2000);
        move(1,255,1);
        move(0,255,1);
        delay(2000);
        move(1,255,0);
        move(0,255,0);
        buf = "";
    } 
    move(1,M1,dirl);
    move(0,M2,dirr);
    if(M1==0&&M2==0) {
            stop();
    }
  }

  if(counter==100000){
    if(Serial1.available()){
    lcd.setCursor(0,0);
    lcd.print("Not Available    ");
  }
  else LCD();
    counter=0;
  }
  counter++; 
  
}
float convertRawGyro(int gRaw) {
  // since we are using 250 degrees/seconds range
  // -250 maps to a raw value of -32768
  // +250 maps to a raw value of 32767
  
  float g = (gRaw * 2500.0) / 32768.0;

  return g;
}

void move(int motor, int speed, int direction){
//Move specific motor at speed and direction
//motor: 0 for B 1 for A
//speed: 0 is off, and 255 is full speed
//direction: 0 clockwise, 1 counter-clockwise

        digitalWrite(STBY, HIGH); //disable standby

        boolean inPin1 = LOW;
        boolean inPin2 = HIGH;

        if(direction == 1) {
                inPin1 = HIGH;
                inPin2 = LOW;
        }

        if(motor == 1) {
                digitalWrite(AIN1, inPin1);
                digitalWrite(AIN2, inPin2);
                analogWrite(PWMA, speed);
        }else{
                digitalWrite(BIN1, inPin1);
                digitalWrite(BIN2, inPin2);
                analogWrite(PWMB, speed);
        }
}
void LCD(){
   lcd.setCursor(0,0);
  int gxRaw, gyRaw, gzRaw;         // raw gyro values
  float gx, gy, gz;
  // read raw gyro measurements from device
  CurieIMU.readGyro(gxRaw, gyRaw, gzRaw);

  // convert the raw gyro data to degrees/second
  gx = convertRawGyro(gxRaw);
  gy = convertRawGyro(gyRaw);
  gz = convertRawGyro(gzRaw);

  // display tab-separated gyro x/y/z values

  lcd.print(String("X:") + gx +" Y:"+ gy );
  lcd.setCursor(0,1);

  lcd.print("UPTIME: ");
  secs=millis()/1000;
  hrs=secs/3600;
  mins=secs/60;
  if(hrs<10)lcd.print("0");
  lcd.print(hrs);
  lcd.print(":");
  mins=(secs%3600)/60;
  if(mins<10) lcd.print("0");
  lcd.print(mins);
  lcd.print(":");
  if(secs%60<10) lcd.print("0");
  lcd.print(secs%60);
}
void stop(){
//enable standby
        digitalWrite(STBY, LOW);
}
