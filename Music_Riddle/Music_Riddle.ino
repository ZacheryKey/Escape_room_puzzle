#include <LiquidCrystal.h>

#define ACTIVATED LOW
#define NOTE_B5  988
#define NOTE_G5  784
#define NOTE_A5  880

// Initialize the LCD library by associating any needed LCD pins to the arduino 
// pin it is to be connected to. 
const int rs = 12, en = 11, d4 = 4, d5 = 8, d6 = 9, d7 = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//-----------------------------------------------------------------------------//
const int PIEZO = 2;
const int LED = 13;

const int BUTTON_B1 = 5;
const int BUTTON_A1 = 6;
const int BUTTON_G1 = 7;

int ButtonStateA1 = 0;
int ButtonStateB1 = 0;
int ButtonStateG1 = 0;
int LastButtonStateA1 = 0;
int LastButtonStateB1 = 0;
int LastButtonStateG1 = 0;

// Hot Cross Buns Melody 
int melody[] = {5,6,7,5,6,7,7,7,7,7,6,6,6,6,5,6,7};
int tryMelody[17] = {0}; //Set all of the elements equal to zero
int i = 0;

// Variable to compare the tryMelody adn melody arrays 
bool isSame;

void setup()
{
  // Set up the button pins as input and sound and led as output 
  pinMode(LED, OUTPUT);
  digitalWrite(LED,LOW);
  
  pinMode(BUTTON_B1, INPUT);
  digitalWrite(BUTTON_B1,HIGH);
  
  pinMode(BUTTON_A1, INPUT);
  digitalWrite(BUTTON_A1,HIGH);
  
  pinMode(BUTTON_G1, INPUT);
  digitalWrite(BUTTON_G1,HIGH);

  // Set up the baud rate (information sharing speed) to the inputs and the arduino.
  Serial.begin(9600);

  // Set up the LCD to begin 
  lcd.begin(16,2); //16 columns, 2 rows
  // Print out the Puzzle name
  lcd.print("Music Madness");
  lcd.setCursor(0,1);
}

void loop()
{
  // Initialize the ButtonState Variables to record the state of the buttons
   ButtonStateA1 = digitalRead(BUTTON_A1);
   ButtonStateB1 = digitalRead(BUTTON_B1);
   ButtonStateG1 = digitalRead(BUTTON_G1);

  // When a particular button is pressed, add that pressed button note to an array
  if(ButtonStateB1 != LastButtonStateB1){
    if(ButtonStateB1 == ACTIVATED){
      tryMelody[i] = 5;
      i++;
      Serial.print(tryMelody[i-1]);}}
      LastButtonStateB1 = ButtonStateB1;
      
  if(ButtonStateA1 != LastButtonStateA1){
    if(ButtonStateA1 == ACTIVATED){
      tryMelody[i] = 6;
      i++;
      Serial.print(tryMelody[i-1]);}}
      LastButtonStateA1 = ButtonStateA1;

  if(ButtonStateG1 != LastButtonStateG1){
    if(ButtonStateG1 == ACTIVATED){
      tryMelody[i] = 7;
      i++;
      Serial.print(tryMelody[i-1]);}}
      LastButtonStateG1 = ButtonStateG1;

  // Play sound when you press the Buttons on the arduino board. Each sound has 
  // been assigned its own note value (or sound). 
  while(digitalRead(BUTTON_A1) == ACTIVATED){
    tone(PIEZO,NOTE_A5);
    }
  while(digitalRead(BUTTON_B1) == ACTIVATED){
    tone(PIEZO,NOTE_B5);
    }
  while(digitalRead(BUTTON_G1) == ACTIVATED){
    tone(PIEZO,NOTE_G5);
    } 

  // Compare the user created array to the song array. If they are the same. turn the 
  // LED light to high.
  for(int c = 0; c<17 ;c++){
    if(tryMelody[c]==melody[c]){
      isSame = true;
      }else if(tryMelody[c]!=melody[c]){ isSame = false;}
    }

    // If the melody array and the button pressed generated array are the same, 
    // then turn on the LCD Screen.
    if(isSame){
      digitalWrite(LED, HIGH);
      lcd.setCursor(0,0);
      lcd.print("              ");
      lcd.print("Your clue is... GOOD LUCK!");
      lcd.scrollDisplayLeft();
      delay(300);
      }
    else{digitalWrite(LED, LOW);}


  // Set a default of notone for the buzzer so that when buttons not pressed, 
  // no sound comes out of the buzzer.
  noTone(PIEZO);
  // Avoid "bouncing" by using a delay in your loop before reading Counters
  delay(50);

}
