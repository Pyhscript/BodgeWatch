/*BodgeWatch
 * 2018 - Benjamin Nadarević
 * Description:
 *    Simple stopwatch/timer
 * Hardware:
 *     28BYJ-48 5v with ULN2003 driver board
 *     4*4 keypad
 *     pushbutton
 * Usage:
 *     select mode then number of seconds to run and press E
 *     if you make an error in typing R will clear the input
 *     
 */

#include <Keypad.h>
#include <Stepper.h>


const int motorPin1=4;
const int motorPin2=5;
const int motorPin3=6;
const int motorPin4=7;

const int counterLED=13;

const int rowPin1=14;
const int rowPin2=15;
const int rowPin3=16;
const int rowPin4=17;

const int colPin1=8;
const int colPin2=9;
const int colPin3=10;
const int colPin4=11;


const byte rows = 4; //four rows
const byte cols = 4; //four columns
char keys[rows][cols] = {
  {'1','2','3','4'},
  {'5','6','7','8'},
  {'9','0','R','X'},
  {'F','S','T','E'}
}; 
/*
 * R - reset input(clear input)
 * X - stop motor 
 * F - blink LED as much times as there were full revolutions(for stopwatch)
 * S - stopwatch mode 
 * T - timer mode 
 * E - enter / submit 
 */

int revolutions=0;
unsigned long startTime;

byte rowPins[rows] = {rowPin1, rowPin2, rowPin3, rowPin4}; //connect to the row pinouts of the keypad
byte colPins[cols] = {colPin1, colPin2, colPin3, colPin4}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );

const int stepsPerRevolution = 2038; //using full step sequence, https://42bots.com/tutorials/28byj-48-stepper-motor-with-uln2003-driver-and-arduino-uno/ 
Stepper myStepper(stepsPerRevolution, motorPin1, motorPin2, motorPin3, motorPin4);


String input="";
char key;
char mode='S'; //stopwatch is default mode
String seconds="";


void blinkRevs(){ //blink LED as much times as there were full revolutions (in stopwatch mode);
  for(int i=0;i<revolutions;i++){
    digitalWrite(counterLED,HIGH);
    delay(1000); //it's ok to use delay here, we don't need to check for anything
    digitalWrite(counterLED,LOW);
    delay(1000);
  }
}

void startMotor()
{
  long unsigned timeToRun; //for timer mode
  int steps=0;
  
  
  
  
  if(mode=='S'){//stopwatch mode
    revolutions=0; //reset revolution counter
    while(keypad.getKey()!='X'){
      myStepper.step(1);
      steps++;
      if(steps==stepsPerRevolution){
        steps=0;
        revolutions++;
      }
    }
  }
  if(mode=='T'){//timer mode

    if(seconds==""){
    seconds="0";
    }
  
    
    timeToRun=seconds.toInt()*1000;

    startTime=millis();
    while((millis()-startTime)<timeToRun && keypad.getKey()!='X'){
      Serial.println(millis()-startTime);
      Serial.println(timeToRun);
      
      myStepper.step(1);
    }

   }

  seconds=""; //reset seconds variable after you're done
    
 }
  


void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);

 pinMode(motorPin1,OUTPUT);
 pinMode(motorPin2,OUTPUT);
 pinMode(motorPin3,OUTPUT);
 pinMode(motorPin4,OUTPUT);

 pinMode(rowPin1,INPUT);
 pinMode(rowPin2,INPUT);
 pinMode(rowPin3,INPUT);
 pinMode(rowPin4,INPUT);
 pinMode(colPin4,INPUT);
 pinMode(colPin3,INPUT);
 pinMode(colPin2,INPUT);
 pinMode(colPin1,INPUT);
 pinMode(counterLED,OUTPUT);

 myStepper.setSpeed(1);

}

void loop() {
  
  key=keypad.getKey();
  
  if(isDigit(key)){
    seconds+=key;
    
  }
  else{
  switch(key){
    case 'E':
      startMotor();
      break;
    case 'S':
      mode='S';
      break;
    case 'T':
      mode='T';
      break;
    case 'R':
      seconds="";
      mode='S';
      break;
    case 'F':
      blinkRevs();
    
   }
  }
}
