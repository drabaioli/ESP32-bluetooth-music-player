
// OLED Display pins
// SCL -> GPIO22
// SDA -> GPIO21

// Rotary Encoder pins
// CLK  -> GPIO19
// DATA -> GPIO18
// BTN  -> GPIO05

// DAC Output pins
// LEFT  -> GPIO25
// RIGHT -> GPIO26

#define DISABLE_A2DP // Disable A2DP while prototyping the interface as it leads to huge build times 

#include "oled_stuff.h"
#include "rotary_encoder_stuff.h"
#include "a2dp_stuff.h"

// STATE
uint8_t menu_position  = 0;
uint8_t MENU_SIZE      = 5;
bool    volume_setting = false;
uint8_t volume         = 10; // range [0, 100]


////////
// SETUP
///
void setup()
{
  Serial.begin( 115200 );

  display_init();
  rotary_encoder_init( MENU_SIZE - 1 );
  a2dp_init( volume );

  display_drawSprites( 10, 10, 0 );
}


////////
// LOOP
///
void loop()
{

  if( !volume_setting )
  {
    // Get encoder position
    if( rotaryEncoder.encoderChanged() )
    {
      menu_position = rotaryEncoder.readEncoder();
      display_drawSprites( 10, 10, menu_position );
    }
  
    // Trigger on button
    if( rotaryEncoder.isEncoderButtonClicked() )
    {
      switch( menu_position )
      {
        case 0: a2dp_previous(); break;
        case 1: a2dp_play();     break;
        case 2: a2dp_pause();    break;
        case 3: a2dp_next();     break;
        case 4:
        {
          volume_setting = true;
          rotary_encoder_set_range( 0, 127, volume );
          break;
        }
      }
    }
  }
  else
  {
    // Get encoder position
    if( rotaryEncoder.encoderChanged() )
    {
      volume = rotaryEncoder.readEncoder();
      a2dp_set_volume( volume );
      display_drawVolumeBar( volume );
    }

    // Trigger on button
    if( rotaryEncoder.isEncoderButtonClicked() )
    {
      volume_setting = false;
      rotary_encoder_set_range( 0, MENU_SIZE - 1, menu_position );
    }
  }

  delay( 50 );
}
