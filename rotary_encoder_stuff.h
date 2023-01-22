#ifndef ROTARY_ENCODER_STUFF_H
#define ROTARY_ENCODER_STUFF_H

#include "AiEsp32RotaryEncoder.h"

#define ROTARY_ENCODER_A_PIN      19
#define ROTARY_ENCODER_B_PIN      18
#define ROTARY_ENCODER_BUTTON_PIN  5
#define ROTARY_ENCODER_STEPS       4

AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder( ROTARY_ENCODER_A_PIN,
                                                           ROTARY_ENCODER_B_PIN,
                                                           ROTARY_ENCODER_BUTTON_PIN,
                                                           -1,
                                                           ROTARY_ENCODER_STEPS );


void IRAM_ATTR readEncoderISR()
{
  rotaryEncoder.readEncoder_ISR();
}


void rotary_encoder_set_range( int min_value, int max_value, int value )
{
  rotaryEncoder.setBoundaries( min_value, max_value, false );
  rotaryEncoder.setAcceleration( ( max_value - min_value ) / 25 );
  rotaryEncoder.setEncoderValue( value );
}


void rotary_encoder_init( uint8_t max_val )
{
  pinMode( ROTARY_ENCODER_A_PIN, INPUT_PULLUP );
  pinMode( ROTARY_ENCODER_B_PIN, INPUT_PULLUP );

  rotaryEncoder.begin();
  rotaryEncoder.setup( readEncoderISR );
  rotary_encoder_set_range( 0, max_val, 0 );
}

#endif
