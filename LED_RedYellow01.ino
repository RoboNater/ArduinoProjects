#include <ArduinoLowerPower.h>

//-------------------------------
const uint32_t cnDelayBeforeActive_s = 7;

const uint8_t flickerPin1 = 6;
const uint8_t flickerPin2 = 10;
const uint8_t flickerPin3 = 11;

//-------------------------------
bool gbNextModeActive = false;
uint32_t gnTotalTimeInLowerPowerMode_s = 0;

//-------------------------------
void AllOff()
{
 analogWrite(5, 0);
 analogWrite(6, 0);
 analogWrite(10, 0);
 analogWrite(11, 0);
}

void AllSet(uint8_t lnBrightness)
{
 analogWrite(5, lnBrightness);
 analogWrite(6, lnBrightness);
 analogWrite(10, lnBrightness);
 analogWrite(11, lnBrightness);
}

void FlickerOff()
{
 analogWrite(flickerPin1, 0);
 analogWrite(flickerPin2, 0);
 analogWrite(flickerPin3, 0);

}

void FlickerSet(uint8_t lnBrightness)
{
 analogWrite(flickerPin1, lnBrightness);
 analogWrite(flickerPin2, lnBrightness);
 analogWrite(flickerPin3, lnBrightness);
}

//-------------------------------
void setup() 
{
  // put your setup code here, to run once:
 AllOff();
 delay(100);
 AllSet(128);
 delay(100);
 AllOff();
 delay(1000);
 while ( millis() < 2000)
 {
   delay(1);
 }
 AllSet(128);
 delay(100);
 AllOff();
}




//-------------------------------
void loop3() 
{
  // put your main code here, to run repeatedly:

for (int liLoop = 0; liLoop < 10; liLoop++)
{
 AllOff();
 delay(1000);
 AllSet(255);
 delay(100);
}
AllOff();
delay(1000);

for (int liLoop = 0; liLoop < 10; liLoop++)
{
AllSet(255);
delay(1000);
AllOff();
delay(1000);
}

AllSet(255);
delay(30000);
AllOff();
delay(1000);

 
}



//-------------------------------
void loop2() {
analogWrite(flickerPin1, random(206)+50);
analogWrite(flickerPin2, random(50)+10);
analogWrite(flickerPin3, random(206)+50);
delay(random(90)+10);
if (random(100) < 2)
{
  FlickerSet(255);
  delay(50);
  FlickerSet(0);
  delay(10);
}
}


//-------------------------------
void LowerPowerLoop()
{
  uint32_t lnNow = millis();
  if (
    // (lnNow < 2000) || // Rollover
    (gnTotalTimeInLowerPowerMode_s >= cnDelayBeforeActive_s) )
  {
    gbNextModeActive = true;
  }
  else
  {
    delay(1000);  // replace with low power sleep
    gnTotalTimeInLowerPowerMode_s += 1;
  }
}

//-------------------------------
void ActiveLoop()
{
  static uint32_t lnNextFlickerTime = 0
  uint32_t lnNow = millis();
  
  // TODO - Left off here
  /* 
    Main Glow LEDS:  
      Calculate random time to remain asleep (10 to 20 seconds)
      Sleep until time elapses
      Snap awake (50ms to full brightness)
      Calculate random time to stay awake (45 to 90 seconds) 
      Stay on until time elapses
      Blink at probability 50% for a 20 second interval (assuming 5msec sample rate, prob = 0.999827 of not blinking) 
        Can't blink within 5 seconds of awakening or going to sleep
      If blink, dim down in 15msec and then back again to full in 15msec (like eye blinking) 
      Going to sleep - Dim down over 5 second interval
    Flicker LEDs:
      If asleep, run at 10% luminosity
      If awake, breathing mode:  Breaths at 0.3 to 0.6 Hz; breathe in at 20% luminosity; breathe out ramp to 100% luminosity in 50msec
      Standard flicker quantized to 5msec
      Going to sleep, dim to 10% over 3 seconds
  */
      
}

//-------------------------------
void loop()
{
  if (gbNextModeActive == true)
  {
    ActiveLoop();
  }
  else
  {
    LowerPowerLoop();
  }
}

