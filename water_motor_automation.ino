#include <LiquidCrystal.h>

// LCD pins <--> Arduino pins
const int RS = 11, EN = 12, D4 = 2, D5 = 3, D6 = 4, D7 = 5;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

//motor
const int RELAY_PIN = A5;

//ultrasonic sensor
int trigPin = 7;    // TRIG pin
int echoPin = 13;    // ECHO pin
int trigPin2 = 8;
int echoPin2 = 9;
float duration_us, distance_cm;

float sumpPercentage,tankPercentage;
float distance1,distance2;

void setup()
{
  lcd.begin(16, 2); // set up number of columns and rows
  pinMode(RELAY_PIN, OUTPUT);

  // lcd
  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("Water Motor");        // print message at (0, 0)
  lcd.setCursor(0, 1);         // move cursor to   (2, 1)
  lcd.print("Automation"); // print message at (2, 1)
  delay(1000);
  lcd.clear();  
  // lcd.print("Onning the motor...");
  // delay(1000);
  // lcd.clear();

  //ultrasonic
  Serial.begin (9600);
  // configure the trigger pin to output mode
  pinMode(trigPin2, OUTPUT);
  // configure the echo pin to input mode `````````````````````````````````````
  pinMode(echoPin2, INPUT);
  // configure the trigger pin to output mode
  pinMode(trigPin, OUTPUT);
  // configure the echo pin to input mode `````````````````````````````````````
  pinMode(echoPin, INPUT);

  
  
}

void loop()
{

  if(sumpPercentage<7)
  {
    if(tankPercentage>0&&tankPercentage<=10)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Switching Motor");
      lcd.setCursor(0,1);
      lcd.print(" onn!...");
      delay(5000);
      onMotor();

      while(true)
      {
        lcd.clear();
        lcd.print("Filling tank..");
        if(tankPercentage>0&&tankPercentage<=95)
        {
          lcd.print("Switching off");
          lcd.setCursor(0,1);
          lcd.print(" Motor!...");
          lcd.setCursor(0,1);
          delay(5000);
          lcd.setCursor(0,0);
          sump();
          lcd.setCursor(0,1);
          lcd.print("Tank full!");
          offMotor();
          exit(0);
        }
        if(sumpPercentage<=7)
        {
          lcd.clear();
          sump();
          lcd.setCursor(0,0);
          lcd.print("Switching off");
          lcd.setCursor(0,1);
          lcd.print(" Motor!...");
          delay(5000);
          lcd.setCursor(0,0);
          sump();
          lcd.setCursor(0,1);
          lcd.print("Call the tanker!");
          offMotor();
          exit(0);
        }
      }
      
    }
    else{
      lcd.clear();
      lcd.setCursor(0,0);
      tank();
      lcd.setCursor(0,1);
      lcd.print("No change!");
      delay(2000);
      exit(0);      
    }
    

    
  }
  else{
    lcd.clear();
    lcd.setCursor(0,0);
    sump();
    lcd.setCursor(0,1);
    lcd.print("Call the tanker!");
    exit(0);    
  }
}

int ultrasonic(int echo,int trig)
{
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(echo, HIGH);

  // calculate the distance
  distance_cm = 0.017 * duration_us;

  // print the value to Serial Monitor
  return distance_cm;
}

void tank()
{
  distance1=ultrasonic(echoPin,trigPin);
  distance1=ultrasonic(echoPin,trigPin);
  
  tankPercentage=100-((distance1/12)*100);
  lcd.print("Tank:");
  lcd.print(tankPercentage,2);
  lcd.print("%");
}

void sump()
{
  distance2=ultrasonic(echoPin2,trigPin2);
  distance2=ultrasonic(echoPin2,trigPin2);

  sumpPercentage=100-((distance2/18)*100);
  lcd.print("Sump:");
  lcd.print(sumpPercentage,2);
  lcd.print("%");
}

void onMotor()
{
  digitalWrite(RELAY_PIN, HIGH);
}

void offMotor()
{
  digitalWrite(RELAY_PIN, LOW);
}
