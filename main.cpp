//"I Mouaiad Hejazi,001220081 certify that this material is my original work. No other person's work has been used without due acknowledgement. I have not made my work available to anyone else."

// Stage 5 completed

/* A header file that contains all the definitions and prototypes of the functions that are used in the
Arduino library. */
#include <Arduino.h>
/* Defining the value of ALARM_DISABLED to be 0. */
#define ALARM_DISABLED 0
/* Defining the value of ALARM_ENABLE to be 1. */
#define ALARM_ENABLE 1
/* Defining the value of ALARM_COUNTDOWN to be 2. */
#define ALARM_COUNTDOWN 2
/* Defining the value of ALARM_ACTIVE to be 3. */
#define ALARM_ACTIVE 3
/* Defining the value of PIN_PIR to be D5. */
#define PIN_PIR D5
/* Defining the value of PIN_BUTTON to be D6. */
#define PIN_BUTTON D6
/* Defining the value of LIGHT_ACTIVE to be false. */
#define LIGHT_ACTIVE false
/* Defining the value of LIGHT_OFF to be true. */
#define LIGHT_OFF true
/* Defining the value of BUTTON_PRESSED to be 0. */
#define BUTTON_PRESSED 0
/* Defining the value of BUTTON_NOT_PRESSED to be 1. */
#define BUTTON_NOT_PRESSED 1
/* Defining the value of TEN_SEC to be 10000. */
#define TEN_SEC 10000
/* Declaring a variable called iAlarmState and assigning it the value of ALARM_ENABLE. */
int iAlarmState = ALARM_ENABLE;
/* Declaring a variable called iButton and assigning it the value of BUTTON_NOT_PRESSED. */
int iButton = BUTTON_NOT_PRESSED;
/* Declaring a variable called bPIR and assigning it the value of false. */
bool bPIR = false;
/* A variable that is used to count the number of times the LED blinks. */
int count = 0;

/**
 * The setup() function is called once when the Arduino is powered on or reset. 
 * 
 * The setup() function is where you initialize variables, pin modes, start using libraries, etc. The
 * setup() function will only run once, after each powerup or reset of the Arduino board.
 */
void setup()
{
  /* Used to initialize the serial communication at a baud rate of 115200. */
  Serial.begin(115200);
  /* Setting the LED_BUILTIN pin to be an output pin. */
  pinMode(LED_BUILTIN, OUTPUT);
  /* Setting the PIN_PIR pin to be an input pin. */
  pinMode(PIN_PIR, INPUT);
  /* Setting the PIN_BUTTON pin to be an input pin with a pull-up resistor. */
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  /* Turning off the LED. */
  digitalWrite(LED_BUILTIN, LIGHT_OFF);
}

/* Collecting the inputs from the PIR sensor and the button. */
void collectInputs()
{
  /* Reading the value of the PIR sensor and assigning it to the variable bPIR. */
  bPIR = digitalRead(PIN_PIR);
  /* Reading the value of the button and assigning it to the variable iButton. */
  iButton = digitalRead(PIN_BUTTON);
}

/* The function checkAlarmState() is used to check the state of the alarm. It checks if the alarm is
enabled, if it is counting down, if it is active, or if it is disabled. */
void checkAlarmState()
{
  /* The switch statement is used to execute one statement from multiple conditions. It checks the
  value of the variable iAlarmState and executes the code that is associated with that value. */
  switch (iAlarmState)
  {
  /* Checking if the alarm is enabled. */
  case ALARM_ENABLE:
    /* Checking if the PIR sensor is detecting motion. */
    if (bPIR)
    {
      /* Assigning the value of ALARM_COUNTDOWN to the variable iAlarmState. */
      iAlarmState = ALARM_COUNTDOWN;
      Serial.println("Motion Detected!, it will be activated in 10 seconds");
    }
    break;
  /* Checking if the alarm is counting down. */
  case ALARM_COUNTDOWN:
    /* The while loop is used to execute a statement or a block of statements repeatedly as long as a
    given condition is true. The while loop checks if the value of the variable iButton is equal to
    the value of the constant BUTTON_NOT_PRESSED and if the value of the variable count is less than
    the value of the constant TEN_SEC. If both of these conditions are true, then the code inside
    the while loop will be executed. */
    while (iButton == BUTTON_NOT_PRESSED && count < TEN_SEC)
    {
      /* Turning on the LED. */
      digitalWrite(LED_BUILTIN, LIGHT_ACTIVE);
      delay(TEN_SEC / 80);
      digitalWrite(LED_BUILTIN, LIGHT_OFF);
      delay(TEN_SEC / 80);
      iButton = digitalRead(PIN_BUTTON);
      /* Incrementing the value of the variable count by the value of TEN_SEC / 40. */
      count += TEN_SEC / 40;
    }
    delay(TEN_SEC / 40);
    /* Checking if the value of the variable count is equal to the value of the constant TEN_SEC. */
    if (count == TEN_SEC)
    {
      /* Assigning the value of ALARM_ACTIVE to the variable iAlarmState. */
      iAlarmState = ALARM_ACTIVE;
      Serial.println("Alarm activated");
    }
    else
    {
      /* Assigning the value of ALARM_DISABLED to the variable iAlarmState. */
      iAlarmState = ALARM_DISABLED;
      Serial.println("Alarm Disabled");
    }
    break;
  /* Turning on the LED. */
  case ALARM_ACTIVE:
    /* Turning on the LED. */
    digitalWrite(LED_BUILTIN, LIGHT_ACTIVE);
    break;
  /* Turning off the LED and checking if the button is pressed. If the button is pressed, then the
  alarm is enabled. */
  case ALARM_DISABLED:
    /* Turning off the LED. */
    digitalWrite(LED_BUILTIN, LIGHT_OFF);
    /* Reading the value of the button and assigning it to the variable iButton. */
    iButton = digitalRead(PIN_BUTTON);
    /* This code is checking if the button is pressed. If the button is pressed, then the alarm is enabled. */
    if (iButton == BUTTON_PRESSED)
    {
      /* Assigning the value of ALARM_ENABLE to the variable iAlarmState. */
      iAlarmState = ALARM_ENABLE;
      Serial.println("Alarm Enabled");
    }
    break;
  default:
    /* Assigning the value of ALARM_ENABLE to the variable iAlarmState. */
    iAlarmState = ALARM_ENABLE;
    break;
  }
}

/* The loop() function is called repeatedly until the Arduino is powered off or reset. */
void loop()
{
  /* The collectInputs() function is used to collect the inputs from the PIR sensor and the button. */
  collectInputs();
  /* The checkAlarmState() function is used to check the state of the alarm. It checks if the alarm is
  enabled, if it is counting down, if it is active, or if it is disabled. */
  checkAlarmState();
  /* The variable count is used to count the number of times the LED blinks. The value of the variable
  count is incremented by the value of TEN_SEC / 40. The value of the variable count is reset to 0
  after the LED blinks 10 times. */
  count = 0;
}