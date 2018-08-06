#include <Keypad.h>

const int rowPin1=14;
int rowPin2=15;
int rowPin3=16;
int rowPin4=17;
int colPin1=8;
int colPin2=9;
int colPin3=10;
int colPin4=11;


const byte rows = 4; //four rows
const byte cols = 4; //four columns
char keys[rows][cols] = {
  {'1','2','3','4'},
  {'5','6','7','8'},
  {'9','0','R','X'},
  {'F','S','T','E'}
}; 
byte rowPins[rows] = {rowPin1, rowPin2, rowPin3, rowPin4}; //connect to the row pinouts of the keypad
byte colPins[cols] = {colPin1, colPin2, colPin3, colPin4}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );
char input="";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  input=keypad.getKey();
  if(input!=NO_KEY){
  Serial.println(input);
  input="";
  }

}
