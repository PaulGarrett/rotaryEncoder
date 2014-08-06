/*Rotary Encoder Demo
Budd Churchward WB7FHC
11-20-13 

From demo at https://www.youtube.com/watch?v=FGxLXqzPe3Q
This is Budd's code "re-interpreted" to remove Youtube/G+ 
typographical glitches
*/

const byte pinA = 2; // encoder pin A to Arduino pin 2 which is also interrupt pin 0 which we will use
const byte pinB = 3; // encoder pin B to Arduino pin 3 which is also interrupt pin 1 but we won't use it

byte state = 0; // will store two bits for pins A & B on the encoder which we will get from the pins above

int level = 0; // a value bumped up or down by the encoder

//For demo purposes we will create an array of these binary digits
String bits[] = {"00","01","10","11"};

/* A truth table of possible moves 
   1 for clockwise  
  -1 for counter clockwise 
   0 for error - keybounce */
   
int bump[] = {0,0,-1,1};


void setup(){
 pinMode(pinA,INPUT); // reads Pin A of the encoder
 pinMode(pinB,INPUT); // reads Pin B of the encoder 
 
// Writing to an Input pin turns on an internal pull up resistor

 digitalWrite(pinA,HIGH);
 digitalWrite(pinB,HIGH); 
 
 // Set up to call our knob function any time pinA rises
 
 attachInterrupt(0,knobTurned,RISING); // calls our 'knobTurned()' function when pinA goes from LOW to HIGH 
 
 level = 50; // a value to start with

// Set up for using the on-screen monitor 
 Serial.begin(115200); // make sure your monitor baud rate matches this
 
 Serial.println("Encoder Ready");
 Serial.print("level = ");
 Serial.println(level); // to remind us where we're starting
}

void loop(){
 // main programming will go here later for now we'll just do nothing until we get an interrupt 
}

void knobTurned(){
 // AH HA! the knob was turned 
 state = 0; // reset this value each time
 state = state + digitalRead(pinA); // add the state of Pin A
 state <<= 1; // shift the bit over one spot
 state = state + digitalRead(pinB); // add the state of Pin B 
 
 /* now we have a two bit binary 
number that holds the state of both pins 
   00 - something is wrong we must have got here with a key bounce 
   01 - sames as above - first bit should never be 0 
   10 - knob was turned backwards 
   11 - knob was turned forwards 
   
We can pull a value out of our truth table and add it to the current level */

level = level + bump[state];  // Let's see what happened

Serial.print(bits[state] + "      " ); //show us the two bits 
Serial.print(bump[state],DEC); // show us the direction of the turn
Serial.print("    ");
Serial.println(level);         // show us the new value
}
