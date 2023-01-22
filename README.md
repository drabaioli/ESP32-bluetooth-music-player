# ESP32-bluetooth-music-player
Use your ESP32 to play and control music from a bluetooth audio source.
PS: This is work in progress.

# Components List
- ESP32 Development Board
- SSD1306 OLED Display
- HW-040 Rotary Encoder
- 8 Ohm 5W Speaker (no amplification)

## Components
![Components](/img/components.jpg)

## Playback control screen
![Playback control screen](/img/playback_control.jpg)

## Volume control screen
![Volume control screen](/img/volume_control.jpg')

# Dependencies:
- Adafruit SSD1306 : https://github.com/adafruit/Adafruit_SSD1306
- Ai ESP32 Rotary Encoder : https://github.com/igorantolic/ai-esp32-rotary-encoder
- ESP32 A2DP : https://github.com/pschatzmann/ESP32-A2DP

# Usage
- Turn the Esp32 on
- Connect your phone to the Esp32 Bluetooth ("Diego_BT_Music" by default)
- Start music app on your phone
- Use rotary encoder to navigate through the playback control menu
- Press rotary encoder button to select playback action or to go to the volume control screen
- Use rotary encoder to lower or increase volume, then press rotary encoder to go back to the playback control screen
