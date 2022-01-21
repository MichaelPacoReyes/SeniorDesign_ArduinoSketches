#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformDc     dc1;            //xy=120,430
AudioSynthWaveformSine   sine1;          //xy=120,470
AudioInputUSB            usb2; //xy=131,654
AudioMixer4              mixer1;         //xy=262,482
AudioEffectMultiply      multiply1;      //xy=309,603
AudioOutputI2S           i2s1;           //xy=461,654
AudioConnection          patchCord1(dc1, 0, mixer1, 0);
AudioConnection          patchCord2(sine1, 0, mixer1, 1);
AudioConnection          patchCord3(usb2, 0, multiply1, 1);
AudioConnection          patchCord4(usb2, 1, i2s1, 1);
AudioConnection          patchCord5(mixer1, 0, multiply1, 0);
AudioConnection          patchCord6(multiply1, 0, i2s1, 0);
AudioControlSGTL5000     sgtl5000_1;     //xy=274,101
// GUItool: end automatically generated code

void setup() {
  AudioMemory(40);
  
  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_1.volume(0.1);

   dc1.amplitude(1); 
   sine1.amplitude(0); 
   Serial.begin(115200);
}

void loop() {
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    
    if (cmd == 'd') {
      float tremolo_depth = Serial.parseFloat();
      if((tremolo_depth<=1) & (tremolo_depth>=0)){    
      float tremolo_amp = 1.0 - tremolo_depth;
      float tremolo_depth_previous =dc1.read();

        if(tremolo_depth_previous>tremolo_depth){
          dc1.amplitude(tremolo_depth); 
          sine1.amplitude(tremolo_amp);
        }
        else{
          dc1.amplitude(tremolo_depth); 
          sine1.amplitude(tremolo_amp); 
        }
      Serial.print("Set depth to: ");
      Serial.println(tremolo_depth);
      }
      else{
         Serial.print("Please chose a value between 1 and 0");
      }
    }
    if (cmd == 'r') {
      float rate = Serial.parseFloat();
      if((rate<=1) & (rate>=0)){      
        sine1.frequency(rate);
        Serial.print("Set tremolo rate to: ");
        Serial.println(rate);
      }
      else{
        Serial.print("Please chose a value between 1 and 0");
      }
    }
    if (cmd == 'v') {
      float V = Serial.parseFloat();
      if((V<=1) & (V>=0)){
      sgtl5000_1.volume(V);
      Serial.print("Set volume to: ");
      Serial.println(V);        
      }
      else{
        Serial.print("Please chose a value between 1 and 0");
      }
    }
  }
}
