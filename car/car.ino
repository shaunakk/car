#include <BMI160.h>
#include <CurieIMU.h>

#include <Servo.h>
float serialval=0;
int STBY = 6; //standby

//Motor A
int PWMA = 9; //Speed control
int AIN1 = 7; //Direction
int AIN2 = 8; //Direction

//Motor B
int PWMB = 3; //Speed control
int BIN1 = 4; //Direction
int BIN2 = 5; //Direction

void setup();
void loop();
void move(int motor, int speed, int direction);
void stop();
void setup(){
        pinMode(13,INPUT);
        Serial.begin(9600);
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
}

void loop(){
        
        if (Serial.available()) { // If anything comes in Serial (USB),
                Serial1.write(Serial.read()); // read it and send it out Serial1 (pins 0 & 1)
        }

        if (Serial1.available()) { // If anything comes in Serial1 (pins 0 & 1)
                Serial.write(Serial1.read()); // read it and send it out Serial (USB)
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
