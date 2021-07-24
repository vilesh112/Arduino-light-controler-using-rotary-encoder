#include <Arduino.h>           //Ignore this library if you are using arduino ide
#include <LiquidCrystal_I2C.h> //Inport the libraries

LiquidCrystal_I2C lcd(0x27, 20, 4);

uint8_t arrow[8] = {0x0, 0x04, 0x06, 0x1f, 0x06, 0x04, 0x00, 0x00};//Vectors for arrow

//Variables for the menu encoder
int counter = 0;
int page = 1;
int Ready = 1;
int submenu = 0;
int last_counter = 0;
bool clk_State;
bool Last_State;
bool dt_State;
int pushed = 0;
int light1 = 5;
int light2 = 3;
int light3 = 10;
int light4 = 7;
#define push 2//The pin for the push button

void setup()
{
  pinMode(push, INPUT); //Define the pin as input
  pinMode(light1, OUTPUT);
  pinMode(light2, OUTPUT);
  pinMode(light3, OUTPUT);
  pinMode(light4, OUTPUT);
  lcd.init();               //Init the LCD
  lcd.backlight();          //Activate backlight
  lcd.createChar(1, arrow); //Create the arrow symbol
  lcd.home();               //Home the LCD

  PCICR |= (1 << PCIE0);   //enable PCMSK0 scan
  PCMSK0 |= (1 << PCINT0); //Set pin D8 trigger an interrupt on state change.
  PCMSK0 |= (1 << PCINT1); //Set pin D9 trigger an interrupt on state change.
  DDRB &= B11111100;       //8, 9 as input for the encoder clock and data pins

  Last_State = (PINB & B00000001); //pin 8 state (clock pin)?

  Serial.begin(19200); //Prepare the DFplayer module comunication and settings

  lcd.clear();               //Print the initial text. Delete these lines if you don't want that
  lcd.setCursor(0, 0);       //lcd.write(0);
  lcd.print("    WELCOME "); // lcd.write(0);
  lcd.setCursor(0, 1);
  lcd.print("Starting up.... ");
  delay(3000);

  lcd.clear(); //Print the first page menu.
  lcd.setCursor(0, 0);
  lcd.write(1);
  lcd.print("LIGHT1");
  lcd.setCursor(0, 1);
  lcd.print(" LIGHT2");
}

void loop()
{

  if ((last_counter > counter) || (last_counter < counter) || pushed) //Only print on the LCD when a step is detected or the button is pushed.
  {
    Ready = 1;

    if (submenu == 0) //First page of the menu
    {
      if (0 <= counter && counter < 4)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.write(1);
        lcd.print("LIGHT1");
        lcd.setCursor(0, 1);
        lcd.print(" LIGHT2");
        page = 1;
        if (pushed)
        {
          pushed = 0;
        }
      }

      if (4 < counter && counter < 8)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" LIGHT1");
        lcd.setCursor(0, 1);
        lcd.write(1);
        lcd.print("LIGHT2");
        page = 2;
        if (pushed)
        {
          pushed = 0;
        }
      }

      if (8 < counter && counter < 12)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.write(1);
        lcd.print("LIGHT3");
        lcd.setCursor(0, 1);
        lcd.print(" LIGHT4");
        page = 3;
        if (pushed)
        {
          pushed = 0;
        }
      }

      if (12 < counter && counter < 16)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" LIGHT3");
        lcd.setCursor(0, 1);
        lcd.write(1);
        lcd.print("LIGHT4");
        page = 4;
        if (pushed)
        {
          pushed = 0;
        }
      }
      if (16 < counter && counter < 20)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.write(1);
        lcd.print("BACKLIGHT");
        lcd.setCursor(0, 1);
        lcd.print(" SHUT DOWN");
        page = 5;
        if (pushed)
        {
          pushed = 0;
        }
      }
      if (20 < counter && counter < 24)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" BACKLIGHT");
        lcd.setCursor(0, 1);
        lcd.write(1);
        lcd.print("SHUT DOWN");
        page = 6;
        if (pushed)
        {
          pushed = 0;
        }
      }
    } //submenu = 0;

    //Second page of the menu
    if (submenu == 1)
    {
      if (0 <= counter && counter < 4)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.write(1);
        lcd.print("LIGHT1 to 0%");
        lcd.setCursor(0, 1);
        lcd.print(" LIGHT1 to 25%");
        page = 1;
        pushed = 0;
      }

      if (4 < counter && counter < 8)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" LIGHT1 to 0%");
        lcd.setCursor(0, 1);
        lcd.write(1);
        lcd.print("LIGHT1 to 25%");
        page = 2;
        pushed = 0;
      }

      if (8 < counter && counter < 12)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.write(1);
        lcd.print("LIGHT1 to 50%");
        lcd.setCursor(0, 1);
        lcd.print(" LIGHT1 to 100%");
        page = 3;
        pushed = 0;
      }

      if (12 < counter && counter < 16)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" LIGHT1 to 50%");
        lcd.setCursor(0, 1);
        lcd.write(1);
        lcd.print("LIGHT1 to 100%");
        page = 4;
        pushed = 0;
      }
    } //submenu = 1;

    //Third page of the menu
    if (submenu == 2)
    {
      if (0 <= counter && counter < 4)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.write(1);
        lcd.print("LIGHT2 to 0%");
        lcd.setCursor(0, 1);
        lcd.print(" LIGHT2 to 25%");
        page = 1;
        pushed = 0;
      }

      if (4 < counter && counter < 8)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" LIGHT2 to 0%");
        lcd.setCursor(0, 1);
        lcd.write(1);
        lcd.print("LIGHT2 to 25%");
        page = 2;
        pushed = 0;
      }

      if (8 < counter && counter < 12)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.write(1);
        lcd.print("LIGHT2 to 50%");
        lcd.setCursor(0, 1);
        lcd.print(" LIGHT2 to 100%");
        page = 3;
        pushed = 0;
      }

      if (12 < counter && counter < 16)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" LIGHT2 to 50%");
        lcd.setCursor(0, 1);
        lcd.write(1);
        lcd.print("LIGHT2 to 100%");
        page = 4;
        pushed = 0;
      }
    } //submenu = 2;

    //Forth page of the menu
    if (submenu == 3)
    {
      if (0 <= counter && counter < 4)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.write(1);
        lcd.print("LIGHT3 to 0%");
        lcd.setCursor(0, 1);
        lcd.print(" LIGHT3 to 25%");
        page = 1;
        pushed = 0;
      }

      if (4 < counter && counter < 8)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" LIGHT3 to 0%");
        lcd.setCursor(0, 1);
        lcd.write(1);
        lcd.print("LIGHT3 to 25%");
        page = 2;
        pushed = 0;
      }

      if (8 < counter && counter < 12)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.write(1);
        lcd.print("LIGHT3 to 50%");
        lcd.setCursor(0, 1);
        lcd.print(" LIGHT3 to 100%");
        page = 3;
        pushed = 0;
      }

      if (12 < counter && counter < 16)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" LIGHT3 to 50%");
        lcd.setCursor(0, 1);
        lcd.write(1);
        lcd.print("LIGHT3 to 100%");
        page = 4;
        pushed = 0;
      }
    } //submenu = 3;

    //Fifth page of the menu
    if (submenu == 4)
    {
      if (0 <= counter && counter < 4)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.write(1);
        lcd.print("LIGHT4 to 0%");
        lcd.setCursor(0, 1);
        lcd.print(" LIGHT4 to 25%");
        page = 1;
        pushed = 0;
      }

      if (4 < counter && counter < 8)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" LIGHT4 to 0%");
        lcd.setCursor(0, 1);
        lcd.write(1);
        lcd.print("LIGHT4 to 25%");
        page = 2;
        pushed = 0;
      }

      if (8 < counter && counter < 12)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.write(1);
        lcd.print("LIGHT4 to 50%");
        lcd.setCursor(0, 1);
        lcd.print(" LIGHT4 to 100%");
        page = 3;
        pushed = 0;
      }

      if (12 < counter && counter < 16)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" LIGHT4 to 50%");
        lcd.setCursor(0, 1);
        lcd.write(1);
        lcd.print("LIGHT4 to 100%");
        page = 4;
        pushed = 0;
      }
    } //submenu = 4;
    
    //Sixth page of the menu
    if (submenu == 5)
    {
      if (0 <= counter && counter < 4)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.write(1);
        lcd.print("ON");
        lcd.setCursor(0, 1);
        lcd.print(" OFF");
        page = 1;
        pushed = 0;
      }

      if (4 < counter && counter < 8)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" ON");
        lcd.setCursor(0, 1);
        lcd.write(1);
        lcd.print("OFF");
        page = 2;
        pushed = 0;
      }
    }
    
    //Seventh page of the menu
    if (submenu == 6)
    {
      page = 1;
      pushed = 0;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("press again");
    }

  } //end of the MENU prints on the LCD

  last_counter = counter; //Save the value of the last state

  if (digitalRead(push) == 0) //Now we detect when we push the button
  {
    if (submenu == 1)
    {
      if (page == 1)
      {
        submenu = 0;
        counter = 1;
        pushed = 0;
        Ready = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("LIGHT1");
        lcd.setCursor(0, 1);
        lcd.print("       off      ");
        analogWrite(light1, 0);
        delay(1000);
      }

      if (page == 2)
      {
        submenu = 0;
        counter = 0;
        pushed = 0;
        Ready = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("LIGHT1");
        lcd.setCursor(0, 1);
        lcd.print("     To 25%      ");
        analogWrite(light1, 63);
        delay(1000);
      }

      if (page == 3)
      {
        submenu = 0;
        counter = 0;
        pushed = 0;
        Ready = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("LIGHT1");
        lcd.setCursor(0, 1);
        lcd.print("     To 50%      ");
        analogWrite(light1, 127);
        delay(1000);
      }

      if (page == 4)
      {
        submenu = 0;
        counter = 0;
        pushed = 0;
        Ready = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("LIGHT1");
        lcd.setCursor(0, 1);
        lcd.print("    To 100%      ");
        analogWrite(light1, 255);
        delay(1000);
      }
    } //end of submenu 1

    if (submenu == 2)
    {
      if (page == 1)
      {
        submenu = 0;
        counter = 1;
        pushed = 0;
        Ready = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("LIGHT2");
        lcd.setCursor(0, 1);
        lcd.print("  TO OFF      ");
        analogWrite(light2, 0);
        delay(1000);
      }

      if (page == 2)
      {
        submenu = 0;
        counter = 0;
        pushed = 0;
        Ready = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("LIGHT2");
        lcd.setCursor(0, 1);
        lcd.print("     To 25%      ");
        analogWrite(light2, 63);
        delay(1000);
      }

      if (page == 3)
      {
        submenu = 0;
        counter = 0;
        pushed = 0;
        Ready = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("LIGHT2");
        lcd.setCursor(0, 1);
        lcd.print("     To 50%      ");
        analogWrite(light2, 127);
        delay(1000);
      }

      if (page == 4)
      {
        submenu = 0;
        counter = 0;
        pushed = 0;
        Ready = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" LIGHT2");
        lcd.setCursor(0, 1);
        lcd.print("    To 100%      ");
        analogWrite(light2, 255);
        delay(1000);
      }
    } //end of submenu 2

    if (submenu == 3)
    {
      if (page == 1)
      {
        submenu = 0;
        counter = 0;
        pushed = 0;
        Ready = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("LIGHT3   ");
        lcd.setCursor(0, 1);
        lcd.print("     TO OFF      ");
        analogWrite(light3, 0);
        delay(1000);
      }

      if (page == 2)
      {
        submenu = 0;
        counter = 0;
        pushed = 0;
        Ready = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("LIGHT3   ");
        lcd.setCursor(0, 1);
        lcd.print("     To 25%      ");
        analogWrite(light3, 63);
        delay(1000);
      }

      if (page == 3)
      {
        submenu = 0;
        counter = 0;
        pushed = 0;
        Ready = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("LIGHT3   ");
        lcd.setCursor(0, 1);
        lcd.print("     To 50%      ");
        analogWrite(light3, 127);
        delay(1000);
      }

      if (page == 4)
      {
        submenu = 0;
        counter = 0;
        pushed = 0;
        Ready = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("  LIGHT3  ");
        lcd.setCursor(0, 1);
        lcd.print("      To 100%      ");
        analogWrite(light3, 255);
        delay(1000);
      }
    } //end of submenu 3

    if (submenu == 4)
    {
      if (page == 1)
      {
        submenu = 0;
        counter = 0;
        pushed = 0;
        Ready = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("LIGHT4   ");
        lcd.setCursor(0, 1);
        lcd.print("     TO OFF      ");
        analogWrite(light4, 0);
        delay(1000);
      }

      if (page == 2)
      {
        submenu = 0;
        counter = 0;
        pushed = 0;
        Ready = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("LIGHT4   ");
        lcd.setCursor(0, 1);
        lcd.print("     To 25%      ");
        analogWrite(light4, 63);
        delay(1000);
      }

      if (page == 3)
      {
        submenu = 0;
        counter = 0;
        pushed = 0;
        Ready = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("LIGHT4   ");
        lcd.setCursor(0, 1);
        lcd.print("     To 50%      ");
        analogWrite(light4, 127);
        delay(1000);
      }

      if (page == 4)
      {
        submenu = 0;
        counter = 0;
        pushed = 0;
        Ready = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("  LIGHT4  ");
        lcd.setCursor(0, 1);
        lcd.print("      To 100%      ");
        analogWrite(light4, 255);
        delay(1000);
      }
    } //end of submenu 4

    if (submenu == 5)
    {
      if (page == 1)
      {
        submenu = 0;
        counter = 1;
        pushed = 0;
        Ready = 0;
        lcd.backlight();
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("  Backlight ON  ");
        lcd.setCursor(0, 1);
        lcd.print("      Wait      ");
        delay(1000);
      }

      if (page == 2)
      {
        submenu = 0;
        counter = 0;
        pushed = 0;
        Ready = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" Backlight  OFF");
        lcd.setCursor(0, 1);
        lcd.print("      Wait      ");
        delay(1000);
        lcd.noBacklight();
      }
    } //end of submenu 5
    if (submenu == 6)
    {
      if (page == 1)
      {
        submenu = 0;
        counter = 1;
        pushed = 0;
        Ready = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" SHUTTING DOWN  ");
        lcd.setCursor(0, 1);
        lcd.print("      Wait      ");
        delay(1000);
        digitalWrite(light1, LOW);
        digitalWrite(light2, LOW);
        digitalWrite(light3, LOW);
        digitalWrite(light4, LOW);
        lcd.noBacklight();
      }
    } //end of submenu 6

    if (submenu == 0 && Ready == 1)
    {
      if (page == 1)
      {
        submenu = 1;
        counter = 0;
        pushed = 1;
        delay(500);
      }

      if (page == 2)
      {
        submenu = 2;
        counter = 0;
        pushed = 1;
        delay(500);
      }

      if (page == 3)
      {
        submenu = 3;
        counter = 0;
        pushed = 1;
        delay(500);
      }

      if (page == 4)
      {
        submenu = 4;
        counter = 0;
        pushed = 1;
        delay(500);
      }
      if (page == 5)
      {
        submenu = 5;
        counter = 0;
        pushed = 1;
        delay(500);
      }
      if (page == 6)
      {
        submenu = 6;
        counter = 0;
        pushed = 1;
        delay(500);
      }
    } //end of submenu 0
  }

  //Add limit for the counter. Each line of the menu has 5 points. Since my menu has 4 lines the maximum counter will be from 0 to 20
  //If you add more lines for the menu, increase this value
  if (counter > 24)
  {
    counter = 24;
  }
  if (counter < 0)
  {
    counter = 0;
  }
} //end void

ISR(PCINT0_vect) //Interruption vector
{

  clk_State = (PINB & B00000001); //pin 8 state, clock pin?
  dt_State = (PINB & B00000010);
  if (clk_State != Last_State)
  {
    if (dt_State != clk_State) // If the data state is different to the clock state, that means the encoder is rotating clockwise
    {
      counter++;
    }
    else
    {
      counter--;
    }
  }
  Last_State = clk_State; // Updates the previous state of the data with the current state
}