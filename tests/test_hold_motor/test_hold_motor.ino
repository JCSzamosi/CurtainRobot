#include "Stepper.h"
#include "IRremote.h"

/*----- Variables, Pins -----*/
#define STEPS  32   // Number of steps per revolution of Internal shaft
int  Steps2Take;  // 2048 = 1 Revolution
int receiver = 12; // Signal Pin of IR receiver to Arduino Digital Pin 12

/*-----( Declare objects )-----*/
// Setup of proper sequencing for Motor Driver Pins
// In1, In2, In3, In4 in the sequence 1-3-2-4

Stepper small_stepper(STEPS, 8, 10, 9, 11);
IRrecv irrecv(receiver);    // create instance of 'irrecv'
decode_results results;     // create instance of 'decode_results'
int turndir;	// declare a variable to hold the turning direction

void setup()
{ 
  irrecv.enableIRIn(); // Start the receiver
  // Serial.begin(9600);	// To monitor what inputs the IR receiver is getting
  // and general debuggery
}

void turncw(){
  // Turn 1/8 revolution clockwise
  small_stepper.setSpeed(480); // Max seems to be 500
  Steps2Take = 256; // A quarter rotation clockwise
  small_stepper.step(Steps2Take);
  //delay(62);
}

void turnccw(){
  // Turn 1/8 revolution counterclockwise
  small_stepper.setSpeed(480);
  Steps2Take = -256; // A quarter rotation counterclockwise
  small_stepper.step(Steps2Take);
  //delay(62);
}

void loop()
{
  
  if (irrecv.decode(&results)) // have we received an IR signal?
  {
    switch(results.value)
    {

      case 0xFFE01F: // down arrow button pressed
                      turndir = results.value;
                      // Serial.println("Thing one");
                      //delay(50); 
                      break;

      case 0xFF906F: // up arrow button pressed
                      turndir = results.value;
                      // Serial.println("Thing two");
                      //delay(50);
                      break;
     case 0xFFFFFFFF: // a button is being held
        switch(turndir)
        {
          case 0xFFE01F: // down arrow button pressed
                      // Serial.println("Thing one again");
                      turnccw();
                      break;

        case 0xFF906F: // up arrow button pressed
                      // Serial.println("Thing two again");
                      turncw();
                      break;
        
                
    }
    }
    
      irrecv.resume(); // receive the next value
	  			// stop turning the stepper motor so it can turn again
                 digitalWrite(8, LOW);
                 digitalWrite(9, LOW);
                 digitalWrite(10, LOW);
                 digitalWrite(11, LOW);       
  }  


}/* --end main loop -- */
