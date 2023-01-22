#ifndef A2DP_STUFF_H
#define A2DP_STUFF_H

#ifdef DISABLE_A2DP
void a2dp_init( uint8_t initial_volume ) {}
void a2dp_set_volume( uint8_t value ) {}
void a2dp_previous() {}
void a2dp_play() {}
void a2dp_pause() {}
void a2dp_next() {}
#else // DISABLE_A2DP

#include "BluetoothA2DPSink.h"

BluetoothA2DPSink a2dp_sink;


void avrc_metadata_callback( uint8_t data1, const uint8_t * data2 )
{
 Serial.printf("AVRC metadata rsp: attribute id 0x%x, %s\n", data1, data2);
}


void a2dp_init( uint8_t initial_volume )
{
 // A2DP configuration
 const i2s_config_t i2s_config = {
     .mode                 = (i2s_mode_t)( I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_DAC_BUILT_IN ),
     .sample_rate          = 44100, // corrected by info from bluetooth
     .bits_per_sample      = (i2s_bits_per_sample_t) 16, /* the DAC module will only take the 8bits from MSB */
     .channel_format       =  I2S_CHANNEL_FMT_RIGHT_LEFT,
     .communication_format = (i2s_comm_format_t)I2S_COMM_FORMAT_STAND_MSB,
     .intr_alloc_flags     = 0, // default interrupt priority
     .dma_buf_count        = 8,
     .dma_buf_len          = 64,
     .use_apll             = false
 };

 // Start BT receiver and output to pins 25 and 26
 a2dp_sink.set_i2s_config( i2s_config );
 a2dp_sink.set_avrc_metadata_callback( avrc_metadata_callback );
 a2dp_sink.start( "Diego_BT_Music" );

 a2dp_sink.set_volume( initial_volume );
}


void a2dp_set_volume( uint8_t value )
{
 a2dp_sink.set_volume( value );
}

void a2dp_previous() { a2dp_sink.previous(); }
void a2dp_play()     { a2dp_sink.play();     }
void a2dp_pause()    { a2dp_sink.pause();    }
void a2dp_next()     { a2dp_sink.next();     }


#endif // DISABLE_A2DP
#endif // A2DP_STUFF_H
