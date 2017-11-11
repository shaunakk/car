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
int buf;
byte character;
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
    character = Serial1.read(); //read the first byte on serial
    Serial.write(Serial1.read());
    if(character != 10 && character != ','){ //newline(10) and , are special
        buf = buf*10;
        buf += (int)(character - '0'); //these two lines turn the string into an integer
    } else if(character == 'L'){
        M1 = buf; //after a comma the buffer has the x coordinate
        buf = 0;
    } else if(character == 'R'){
        M2 = buf; //after a space the buffer has the y coordinate
        buf = 0;
    } else if(character == 'A'){
        dirl = buf; //after a space the buffer has the y coordinate
        buf = 0;
    } else if(character == 'B'){
        dirr = buf; //after a space the buffer has the y coordinate
        buf = 0;
    }
        if(M1==0&&M2==0) {
                stop();
        }
        else{
                move(1,M1,dirl);
                move(0,M2,dirr);

        }
//        Serial.print(String(buf));
//        Serial.print(String(M1));
//        Serial.print(String(dirl));
//        Serial.print(String(M2));
//        Serial.print(String(dirr));
delay(10);
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
