#include <Servo.h>          // Include servo library

Servo servoCam;

int motorRight1 = 3; // PIN 3
int motorRight2 = 5; // PIN 5
int enablePin = 5; // pin 1 on L293D IC
int state;
int flag=0;        //makes sure that the serial only prints once the state

void setup() {
    // sets the pins as outputs:
    pinMode(motorRight1, OUTPUT);
    pinMode(motorRight2, OUTPUT);
    pinMode(enablePin, OUTPUT);
    
    // sets enablePin high so that motor can turn on:
    digitalWrite(enablePin, HIGH);
    
    // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);

     //initialize servo
     //servoCam.attach(13);  //PIN 13
}

void loop() {
  
    //if some date is sent, reads it and saves in state
    if(Serial.available() > 0){     
      state = Serial.read();   
      flag=0;
    }
    
    // if the state is '0' the DC motor will turn off
    if (state == '0') {
        digitalWrite(motorRight1, LOW); // set pin 2 on L293D low
        digitalWrite(motorRight2, LOW); // set pin 7 on L293D low
        if(flag == 0){
          Serial.println("Motor: off");
          flag=1;
        }
    }
    
    // if the state is '1' the motor will turn right
    else if (state == '1') {
        digitalWrite(motorRight1, LOW); // set pin 2 on L293D low
        digitalWrite(motorRight2, HIGH); // set pin 7 on L293D high
        if(flag == 0){
          Serial.println("Motor: right");
          flag=1;
        }
    }
    
    // if the state is '2' the motor will turn left
    else if (state == '2') {
        digitalWrite(motorRight1, HIGH); // set pin 2 on L293D high
        digitalWrite(motorRight2, LOW); // set pin 7 on L293D low
        if(flag == 0){
          Serial.println("Motor: left");
          flag=1;
        }
    }
}
