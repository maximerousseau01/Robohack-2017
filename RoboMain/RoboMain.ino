#include <Servo.h>          // Include servo library

Servo servoCam;

int motorLeftF = 3;  // PIN 3 Forward
int motorLeftB = 5;  // PIN 5 Backward
int motorRightF = 6; // PIN 6 Forward
int motorRightB = 9; // PIN 9 Backward

int state = 0;
int flag = 0;        //makes sure that the serial only prints once the state
int pressedFor = 500; //delay until next command

//setup bluetooth commands

int commandRight = 1;
int commandLeft = 2;
int commandBackward = 3;
int commandForward = 4;

void setup() {
    // sets the pins as outputs:
    pinMode(motorLeftF, OUTPUT);
    pinMode(motorLeftB, OUTPUT);
    pinMode(motorRightF, OUTPUT);
    pinMode(motorRightB, OUTPUT);
    //pinMode(enablePin, OUTPUT);
    
    // sets enablePin high so that motor can turn on:
    //digitalWrite(enablePin, HIGH);
    
    // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);

     //initialize servo
     //servoCam.attach(13);  //PIN 13
}

void loop() {
  
    //if some date is sent, reads it and saves in state
    if(Serial.available()){     
      state = Serial.read();   
      flag=0;
    }
    
    // if the state is '0' the DC motor will turn off
    if (state == '0') { 
      stopMotor();
    }
    
    // if the state is '1' the motor will turn right
    else if (state == '1') {
        forward();
        //state = 0;
        //Serial.println(state);
    }
    
    // if the state is '2' the motor will turn left
    else if (state == '2') {
        backward();
    }
    
    else if (state == '3') {
        left();
    }
    
    else if (state == '4') {
        right();
    }
}

void stopMotor (){
    digitalWrite(motorLeftF, LOW); // set pin 3 on L293D low
    digitalWrite(motorLeftB, LOW); // set pin 5 on L293D low
    digitalWrite(motorRightF, LOW); // set pin 6 on L293D low
    digitalWrite(motorRightB, LOW); // set pin 9 on L293D low
    if(flag == 0){
       Serial.println("Motor: off");
       flag=1;
    }
}

void forward (){  
    digitalWrite(motorLeftF, HIGH); // set pin 3 on L293D high
    digitalWrite(motorLeftB, LOW); // set pin 5 on L293D low
    digitalWrite(motorRightF, HIGH); // set pin 6 on L293D high
    digitalWrite(motorRightB, LOW); // set pin 9 on L293D low
    if(flag == 0){
        Serial.println("Motor: forward");
        flag=1;
    }
    delay(pressedFor);
    //stopMotor();
    //state = 0;
    //Serial.println(state);
}


void backward () {
    digitalWrite(motorLeftF, LOW); // set pin 3 on L293D low
    digitalWrite(motorLeftB, HIGH); // set pin 5 on L293D high
    digitalWrite(motorRightF, LOW); // set pin 6 on L293D low
    digitalWrite(motorRightB, HIGH); // set pin 9 on L293D high
     if(flag == 0){
        Serial.println("Motor: backward");
        flag=1;
     }
    delay(pressedFor);
    stopMotor();
}

void left (){
    digitalWrite(motorLeftF, HIGH); // set pin 3 on L293D high
    digitalWrite(motorLeftB, LOW); // set pin 5 on L293D low
    digitalWrite(motorRightF, LOW); // set pin 6 on L293D high
    digitalWrite(motorRightB, HIGH); // set pin 9 on L293D 
     if(flag == 0){
        Serial.println("Motor: left");
        flag=1;
     }
    delay(pressedFor);
    stopMotor();
}

void right(){
    digitalWrite(motorLeftF, LOW); // set pin 3 on L293D high
    digitalWrite(motorLeftB, HIGH); // set pin 5 on L293D low
    digitalWrite(motorRightF, HIGH); // set pin 6 on L293D high
    digitalWrite(motorRightB, LOW); // set pin 9 on L293D 
      if(flag == 0){
        Serial.println("Motor: right");
        flag=1;
     }
     
    delay(pressedFor);
    stopMotor();
}



