#ifndef OLED_STUFF_H
#define OLED_STUFF_H

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// TODO : Remove hardcoded values. Make sizes dynamic depending on the screen resolution

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT  32

#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display( SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET );

#define SPRITE_W 12
#define SPRITE_H 8


static const unsigned char PROGMEM play_sprite[] = {
  0b11000000,0b00000000,
  0b11111000,0b00000000,
  0b11111111,0b00000000,
  0b11111111,0b11000000,
  0b11111111,0b11000000,
  0b11111111,0b00000000,
  0b11111000,0b00000000,
  0b11000000,0b00000000
  };

static const unsigned char PROGMEM pause_sprite[] = {
  0b01111001,0b11100000,
  0b01111001,0b11100000,
  0b01111001,0b11100000,
  0b01111001,0b11100000,
  0b01111001,0b11100000,
  0b01111001,0b11100000,
  0b01111001,0b11100000,
  0b01111001,0b11100000
  };

static const unsigned char PROGMEM next_sprite[] = {
  0b11100000,0b01110000,
  0b11111000,0b01110000,
  0b11111100,0b01110000,
  0b11111111,0b01110000,
  0b11111111,0b01110000,
  0b11111100,0b01110000,
  0b11111000,0b01110000,
  0b11100000,0b01110000
  };

static const unsigned char PROGMEM previous_sprite[] = {
  0b11100000,0b01110000,
  0b11100001,0b11110000,
  0b11100011,0b11110000,
  0b11101111,0b11110000,
  0b11101111,0b11110000,
  0b11100011,0b11110000,
  0b11100001,0b11110000,
  0b11100000,0b01110000
  };

static const unsigned char PROGMEM volume_sprite[] = {
  0b00000011,0b00000000,
  0b00001111,0b00000000,
  0b11111111,0b01100000,
  0b11111111,0b00010000,
  0b11111111,0b00010000,
  0b11111111,0b01100000,
  0b00001111,0b00000000,
  0b00000011,0b00000000
  };


void init_display()
{
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if( !display.begin( SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS ) )
  {
    Serial.println( F("SSD1306 allocation failed") );
    for(;;); // Don't proceed, loop forever
  }

  // Clear the buffer
  display.clearDisplay();
}


void drawActiveSprite( uint8_t x, uint8_t y, const unsigned char * sprite )
{
  display.fillRoundRect( x, y, SPRITE_W + 8, SPRITE_H + 2, 2, SSD1306_WHITE );
  display.drawBitmap( x + 4, y + 1, sprite, SPRITE_W, SPRITE_H, SSD1306_BLACK, SSD1306_WHITE );
}


void drawInactiveSprite( uint8_t x, uint8_t y, const unsigned char * sprite )
{
  display.drawBitmap( x + 4, y + 1, sprite, SPRITE_W, SPRITE_H, 1 );
}


void drawSprites( uint8_t x, uint8_t y, uint8_t activeIndex )
{
  display.clearDisplay();

  // Previous
  if( activeIndex == 0 )
    drawActiveSprite(   x + 0, y, previous_sprite );
  else
    drawInactiveSprite( x + 0, y, previous_sprite );

  // Play
  if( activeIndex == 1 )
    drawActiveSprite(   x + 20, y, play_sprite );
  else
    drawInactiveSprite( x + 20, y, play_sprite );

  // Pause
  if( activeIndex == 2 )
    drawActiveSprite(   x + 40, y, pause_sprite );
  else
    drawInactiveSprite( x + 40, y, pause_sprite );

  // Next
  if( activeIndex == 3 )
    drawActiveSprite(   x + 60, y, next_sprite );
  else
    drawInactiveSprite( x + 60, y, next_sprite );

  // Volume
  if( activeIndex == 4 )
    drawActiveSprite(   x + 80, y, volume_sprite );
  else
    drawInactiveSprite( x + 80, y, volume_sprite );

  display.display();
}


void drawVolumeBar( uint8_t volume )
{
  display.clearDisplay();

  uint8_t volume_bar = map( volume, 0, 127, 0, 100 );
  display.drawRoundRect( 10, 10, 104, 12, 5, SSD1306_WHITE );
  display.fillRoundRect( 12, 12, volume_bar,  8, 5, SSD1306_WHITE );

  display.display();
}
#endif
