/*---- Include Libraries ----*/
#include "IRremote.h"

/*---- Declare pin functions ----*/
#define dir 8
#define stp 9
#define MS1 10
#define MS2 11
#define EN 12

/*---- Variables ----*/

int turndir;	// holds the turning direction
int receiver = 13;
IRrecv irrecv(receiver);    // create instance of 'irrecv'
decode_results results;     // create instance of 'decode_results'
int x;

void setup() {
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(EN, OUTPUT);
  resetEDPins(); //Set step, direction, microstep and enable pins to default states

  irrecv.enableIRIn(); // Start the receiver
  Serial.begin(9600);	// To monitor what inputs the IR receiver is getting
  // and general debuggery
}

void loop() {
  digitalWrite(EN, LOW); //Pull enable pin low to allow motor control
  if (irrecv.decode(&results)) // have we received an IR signal?
  {
    switch(results.value)
    {

      case 0xFFE01F: // down arrow button pressed
					  turndir = results.value;
                      Serial.println("Forward");
                      //delay(50); 
                      break;

      case 0xFF906F: // up arrow button pressed
                      turndir = results.value;
                      Serial.println("Reverse");
                      //delay(50);
                      break;
     case 0xFFFFFFFF: // a button is being held
        switch(turndir)
        {
          case 0xFFE01F: // down arrow button pressed
                      Serial.println("Forward again");
                      StepForwardDefault();
                      break;

        case 0xFF906F: // up arrow button pressed
                      Serial.println("Reverse again");
                      StepReverseDefault();
                      break;
        
                
    }
    }
    
      irrecv.resume(); // receive the next value
	  // stop turning the stepper motor so it can turn again
	  resetEDPins();
  }  
}

/*--- Functions ---*/

void StepForwardDefault()
{
  digitalWrite(dir, LOW); //Pull direction pin low to move "forward"
  for(x= 0; x<50; x++)  //Loop forward 100 steps, hopefully 1/4 rev
  {
    digitalWrite(stp,HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
}

void StepReverseDefault()
{
  digitalWrite(dir, HIGH); //Pull direction pin high to move in "reverse"
  for(x= 0; x<50; x++)  //Loop reverse 100 steps, 1/4 rev
  {
    digitalWrite(stp,HIGH); //Trigger one step
    delay(1);
    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
}

void resetEDPins()
{
  digitalWrite(stp, LOW);
  digitalWrite(dir, LOW);
  digitalWrite(MS1, LOW);
  digitalWrite(MS2, LOW);
  digitalWrite(EN, HIGH);
}
