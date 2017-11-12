#include <BMI160.h>
#include <CurieIMU.h>

#include <Servo.h>
int serialVal;
int STBY = 6; //standby

//Motor A
int PWMA = 9; //Speed control
int AIN1 = 7; //Direction
int AIN2 = 8; //Direction

//Motor B
int PWMB = 3; //Speed control
int BIN1 = 4; //Direction
int BIN2 = 5; //Direction
int dirr = 1;
int dirl = 1;
int M1=0;
int M2=0;
String buf;
char character;

void setup();
void loop();
void move(int motor, int speed, int direction);
void stop();
void setup(){
        pinMode(13,INPUT);
        Serial.begin(115200);
        Serial1.begin(9600);
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
    move(1,M1,dirl);
    move(0,M2,dirr);
    if(M1==0&&M2==0) {
            stop();
    }
  }
  
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

void stop(){
//enable standby
        digitalWrite(STBY, LOW);
}


