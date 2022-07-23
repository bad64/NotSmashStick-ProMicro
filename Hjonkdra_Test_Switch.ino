/******************************************************************
# Dependencies:                                                   #
# 	- SwitchControlLibrary                                        #
#		(https://github.com/celclow/SwitchControlLibrary)             #
#   - AnalogLever-ProMicro                                        #
#   (https://github.com/bad64/AnalogLever-ProMicro)               #
# 	- Whatever the above depends on                               #
#                                                                 #
#          ┏━┓   ┏━┓   ┏━┓   ┏━   ┏┓╻   ━┳━   ┏━┓   ╻             #
#          ┣━┛   ┣━┫   ┣┳┛   ┣━   ┃┃┃    ┃    ┣━┫   ┃             #
#          ╹     ╹ ╹   ╹╹    ┗━   ╹┗┛    ╹    ╹ ╹   ┗━            #
#                                                                 #
#           ██  ███  ██ ██ ███  ████  ███  ████  ██ ██            #
#          █  █ █  █  █ █   █  █     █   █ █   █  █ █             #
#          ████ █  █  █ █   █   ███  █   █ ████   ███             #
#          █  █ █  █  █ █   █      █ █   █ █   █   █              #
#          █  █ ███    █   ███ ████   ███  █   █   █              #
#                                                                 #
#                U L T R A  M E S S Y  C O D E                    #
#                                                                 #
# - Bad64                                                         # 
******************************************************************/

#include <SwitchControlLibrary.h>
#include <AnalogLever-ProMicro.h>

// Pin defs
#define PIN_R           0
#define PIN_X           1
#define PIN_ZR          4
#define PIN_B           5
#define PIN_Y           6
#define PIN_START       8
#define PIN_L           9
#define PIN_A           15
#define PIN_C_UP        7
#define PIN_C_DOWN      14
#define PIN_C_LEFT      3
#define PIN_C_RIGHT     2
#define PIN_LS_DP       16

bool fgcMode;
bool stickLock;

Coordinates coords;

// Debug stuff
void clearBuffer(char* dbgBuf)
{
  strcpy(dbgBuf, "\r");
  for (int i = 0; i < 255; i++)
    strcat(dbgBuf, " ");
}

void setup()
{
  // Set pins
  for (int i = 0; i < 10; i++)
    pinMode(i, INPUT_PULLUP);
  
  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);

  // Create coordinates interface
  coords = Coordinates(A1, A0, 3, 10, 60, -7, 0);

  // Check for FGC mode
  if (digitalRead(PIN_START) == LOW) fgcMode = true;
  else fgcMode = false;
}

void loop()
{
  if (fgcMode == false)   // Layout based on a Pro Controller
  {
    // Z
    if (digitalRead(PIN_R) == LOW) SwitchControlLibrary().pressButton(Button::X); // Don't ask, I don't know why X and ZR are reversed either
    else SwitchControlLibrary().releaseButton(Button::X);

    // X
    if (digitalRead(PIN_X) == LOW) SwitchControlLibrary().pressButton(Button::R);
    else SwitchControlLibrary().releaseButton(Button::R);

    // R
    if (digitalRead(PIN_ZR) == LOW) SwitchControlLibrary().pressButton(Button::ZR);
    else SwitchControlLibrary().releaseButton(Button::ZR);

    // B
    if (digitalRead(PIN_B) == LOW) SwitchControlLibrary().pressButton(Button::B);
    else SwitchControlLibrary().releaseButton(Button::B);

    // Y
    if (digitalRead(PIN_Y) == LOW) SwitchControlLibrary().pressButton(Button::Y);
    else SwitchControlLibrary().releaseButton(Button::Y);

    // START
    if (digitalRead(PIN_START) == LOW) SwitchControlLibrary().pressButton(Button::PLUS);
    else SwitchControlLibrary().releaseButton(Button::PLUS);

    // L
    if (digitalRead(PIN_L) == LOW) SwitchControlLibrary().pressButton(Button::L);
    else SwitchControlLibrary().releaseButton(Button::L);

    // A
    if (digitalRead(PIN_A) == LOW) SwitchControlLibrary().pressButton(Button::A);
    else SwitchControlLibrary().releaseButton(Button::A);

    // C-Buttons
    if ((digitalRead(PIN_C_UP) == LOW) && (digitalRead(PIN_C_DOWN) == HIGH))
    {
      if ((digitalRead(PIN_C_LEFT) == LOW) && (digitalRead(PIN_C_RIGHT) == HIGH))
        SwitchControlLibrary().moveRightStick(Stick::MIN, Stick::MIN);
      else if ((digitalRead(PIN_C_LEFT) == HIGH) && (digitalRead(PIN_C_RIGHT) == LOW))
        SwitchControlLibrary().moveRightStick(Stick::MAX, Stick::MIN);
      else
        SwitchControlLibrary().moveRightStick(Stick::NEUTRAL, Stick::MIN);
    }
    else if ((digitalRead(PIN_C_UP) == HIGH) && (digitalRead(PIN_C_DOWN) == LOW))
    {
      if ((digitalRead(PIN_C_LEFT) == LOW) && (digitalRead(PIN_C_RIGHT) == HIGH))
        SwitchControlLibrary().moveRightStick(Stick::MIN, Stick::MAX);
      else if ((digitalRead(PIN_C_LEFT) == HIGH) && (digitalRead(PIN_C_RIGHT) == LOW))
        SwitchControlLibrary().moveRightStick(Stick::MAX, Stick::MAX);
      else
        SwitchControlLibrary().moveRightStick(Stick::NEUTRAL, Stick::MAX);
    }
    else
    {
      if ((digitalRead(PIN_C_LEFT) == LOW) && (digitalRead(PIN_C_RIGHT) == HIGH))
        SwitchControlLibrary().moveRightStick(Stick::MIN, Stick::NEUTRAL);
      else if ((digitalRead(PIN_C_LEFT) == HIGH) && (digitalRead(PIN_C_RIGHT) == LOW))
        SwitchControlLibrary().moveRightStick(Stick::MAX, Stick::NEUTRAL);
      else
        SwitchControlLibrary().moveRightStick(Stick::NEUTRAL, Stick::NEUTRAL);
    }
  }
  else  // Standard fightstick layout
  {
    // P1
    if (digitalRead(PIN_C_LEFT) == LOW) SwitchControlLibrary().pressButton(Button::X);
    else SwitchControlLibrary().releaseButton(Button::X);

    // P2
    if (digitalRead(PIN_C_UP) == LOW) SwitchControlLibrary().pressButton(Button::Y);
    else SwitchControlLibrary().releaseButton(Button::Y);

    // P3
    if (digitalRead(PIN_C_RIGHT) == LOW) SwitchControlLibrary().pressButton(Button::R);
    else SwitchControlLibrary().releaseButton(Button::R);

    // P4
    if (digitalRead(PIN_Y) == LOW) SwitchControlLibrary().pressButton(Button::L);
    else SwitchControlLibrary().releaseButton(Button::L);

    // K1
    if ((digitalRead(PIN_B) == LOW) || (digitalRead(PIN_A) == LOW)) SwitchControlLibrary().pressButton(Button::B);
    else SwitchControlLibrary().releaseButton(Button::B);

    // K2
    if (digitalRead(PIN_X) == LOW) SwitchControlLibrary().pressButton(Button::A);
    else SwitchControlLibrary().releaseButton(Button::A);

    // K3
    if (digitalRead(PIN_R) == LOW) SwitchControlLibrary().pressButton(Button::ZR);
    else SwitchControlLibrary().releaseButton(Button::ZR);

    // K4
    if (digitalRead(PIN_ZR) == LOW) SwitchControlLibrary().pressButton(Button::ZL);
    else SwitchControlLibrary().releaseButton(Button::ZL);

    // START
    if (digitalRead(PIN_START) == LOW) SwitchControlLibrary().pressButton(Button::PLUS);
    else SwitchControlLibrary().releaseButton(Button::PLUS);

    // SELECT
    if (digitalRead(PIN_L) == LOW) SwitchControlLibrary().pressButton(Button::MINUS);
    else SwitchControlLibrary().releaseButton(Button::MINUS);
  }

  // Analog
  coords.get();
  if (digitalRead(PIN_LS_DP) == LOW)
  {
    // Emulated Dpad
    SwitchControlLibrary().moveLeftStick(127, 127);   // Center analog stick

    if (coords.polar().r() > coords.deadzone())
    {
      if (((coords.polar().asDegrees() > 337.5) && (coords.polar().asDegrees() < 360)) || ((coords.polar().asDegrees() >= 0) && (coords.polar().asDegrees() < 22.5))) SwitchControlLibrary().moveHat(Hat::LEFT);
      else if ((coords.polar().asDegrees() >= 22.5) && (coords.polar().asDegrees() < 67.5)) SwitchControlLibrary().moveHat(Hat::UP_LEFT);
      else if ((coords.polar().asDegrees() >= 67.5) && (coords.polar().asDegrees() < 112.5)) SwitchControlLibrary().moveHat(Hat::UP);
      else if ((coords.polar().asDegrees() >= 112.5) && (coords.polar().asDegrees() < 157.5)) SwitchControlLibrary().moveHat(Hat::UP_RIGHT);
      else if ((coords.polar().asDegrees() >= 157.5) && (coords.polar().asDegrees() < 202.5)) SwitchControlLibrary().moveHat(Hat::RIGHT);
      else if ((coords.polar().asDegrees() >= 202.5) && (coords.polar().asDegrees() < 247.5)) SwitchControlLibrary().moveHat(Hat::DOWN_RIGHT);
      else if ((coords.polar().asDegrees() >= 247.5) && (coords.polar().asDegrees() < 292.5)) SwitchControlLibrary().moveHat(Hat::DOWN);
      else if ((coords.polar().asDegrees() >= 292.5) && (coords.polar().asDegrees() < 337.5)) SwitchControlLibrary().moveHat(Hat::DOWN_LEFT);
      else SwitchControlLibrary().moveHat(Hat::NEUTRAL);
    }
    else SwitchControlLibrary().moveHat(Hat::NEUTRAL);
  }
  else
  {
    // Real analog
    SwitchControlLibrary().moveHat(Hat::NEUTRAL);   // Center dpad
    SwitchControlLibrary().moveLeftStick(coords.x(), coords.y());
  }

  // Send report
  SwitchControlLibrary().sendReport();
}
