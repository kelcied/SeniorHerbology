#include <FreeRTOS_TEENSY4.h>
#include <Arduino.h>

#include "../err/err.h"
#include "msg.h"
#include "rain_main.h"
#include "rain_msg.h"
#include "../types.h"

portBASE_TYPE rain_thread_id;

uint8 pwm_value;
bool rain;

static void rain_thread( void * arg );

bool rain_init()
{
bool ret_val = false;

rain_thread_id = xTaskCreate(rain_thread, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);
rain_queue  = xQueueCreate( 10, sizeof( msg_t ) );

return ret_val;
}

/***********************************************************************************
*
*   Procedure Name: rain_msg_proc
*
*       Purpose: process rain message
*
***********************************************************************************/
err_type rain_msg_proc( msg_t * msg )
{
err_type ret_val = ERR_BAD_MSG;
rain_cfg_t * rain_cfg;

if( msg != NULL )
    {
    switch (msg->type)
        {
        case MSG_CFG:
            rain_cfg = ( rain_cfg_t * )msg->type;

            break;

        default:
            break;
        }
    }

return ret_val;
}

static void rain_thread( void * arg )
{
msg_t msg;
err_type err_val;
if( uxQueueMessagesWaiting( rain_queue ) > 0 )
    {
    xQueueReceive( rain_queue, &msg, 0 );
    rain_msg_proc( &msg );
    }

vPortFree( &msg );

vTaskDelay((50L * configTICK_RATE_HZ) / 1000L);
}