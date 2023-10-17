#include "IO_Port_8bit.h"

/*

AD - FL A4 A3 A2 A1 A0
      1  1  1  X X   X
Addres A2 - A0 Defines the Colum on Display

/RST /CE /WR /RD
 1    0   0   1

DATA - D7 D6 D5 D4 D3 D2 D1 D0
N -     0  1  0  0  1  1  1  0
*/

IO_Port_8bit myport(2, 3, 4, 5, 6, 7, 8, 9, 'O'); // create output port
//Data bits above   D0, D1, D2, D3, D4, D5, D6, D7


void setup() // nothing required in setup
{
pinMode(11, OUTPUT);           // /WR PIN DISPLAY
pinMode(12, OUTPUT);           //  A1 PIN ON DISPLAY
pinMode(13, OUTPUT);           //  A0 PIN ON DISPLAY
digitalWrite(11, LOW);      
}

/* A function to write characters */
void write_character(char ch,char colun){
  digitalWrite(11, HIGH);       // turn on pullup resistors
  switch(colun){
    case 0:
      digitalWrite(12, LOW);       // turn on pullup resistors
      digitalWrite(13, LOW);
    break;
    case 1:
      digitalWrite(12, LOW);       // turn on pullup resistors
      digitalWrite(13, HIGH);
    break;
    case 2:
      digitalWrite(12, HIGH);       // turn on pullup resistors
      digitalWrite(13, LOW);
    break;
    default:
      digitalWrite(12, HIGH);       // turn on pullup resistors
      digitalWrite(13, HIGH);
  }
  myport.send_8bit_data(ch);
  digitalWrite(11, LOW);       // turn on pullup resistors 
}

/* Clear the first 4 coluns on display: That are used */
void reset_display(){
  write_character(0x20,0);
  write_character(0x20,1);
  write_character(0x20,2);
  write_character(0x20,3);
}

/* A function to blink a cursor on display */
void blink_cursor(){
  while(true){
    myport.send_8bit_data(0x5F);
    delay(500);
    myport.send_8bit_data(0x20);
    delay(500);
  }
}

/* write a text on display, Finalize with a blink cursor */
/* See the Avago Data Sheet to get the characters values */
void loop()
{
  reset_display();
  write_character(0x72,0);
  delay(500);
  write_character(0x6D,1);
  delay(500);
  write_character(0x64,2);
  delay(500);
  write_character(0x20,3);
  delay(500);
  blink_cursor();
}
