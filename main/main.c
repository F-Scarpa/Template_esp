#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"

void app_main()
{
   //duty cycle = how much time a signal stays high during the period
   //how much of a pulse is being driven
   //-   -   -    -  short duty cycle
   //---- ---- ---- long duty cycle

    //config timer where we set up frequency
  ledc_timer_config_t timer = {
      .speed_mode = LEDC_LOW_SPEED_MODE,            //speed = hardware slow = software
      .duty_resolution = LEDC_TIMER_10_BIT,         //duty cycle = divide frequency by this amount (10bit )
      .timer_num = LEDC_TIMER_0,                    
      .freq_hz = 5000,          //hz
      .clk_cfg = LEDC_AUTO_CLK  //simple configuration for clock
    };
    ledc_timer_config(&timer);      





   //config channel to control duty cycle, power pushing out 
          ledc_channel_config_t channel = {
      .gpio_num = 4,                            //output pin
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .channel = LEDC_CHANNEL_0,                    
      .timer_sel = LEDC_TIMER_0,                //timer we configured before
      .duty = 1024,                                //how much of a pulse we want to drive
                                                //duty cycle range depends on timer's duty resolution
                                                // (0 - 1024 for 10 bits)

      .hpoint = 0               //when duty cycle trigger, classic PWM = hpoint 0
    };
    ledc_channel_config(&channel);

    ledc_fade_func_install(0);      //needed to use ledc set duty and update
    for (int i = 0; i < 1024; i++)
    {
        ledc_set_duty_and_update(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0,i,0);       //params
                                                                                //1.speed mode
                                                                                //2.led channel
                                                                                //3.duty value
                                                                                //4.0
        // ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, i);
        // ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
        vTaskDelay(10 / portTICK_PERIOD_MS);
        printf("cc\n");
    }

  while(true)
  {
    
    ledc_set_fade_time_and_start(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0,0,1000,LEDC_FADE_WAIT_DONE);   
                                                //params:
                                                    //1. speed mode
                                                    //2. channel
                                                    //3. target duty (fully on = 0)
                                                    //how much time to get to that point
                                                    //5. wait for the full cycle to finish
    ledc_set_fade_time_and_start(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0,1024,1000,LEDC_FADE_WAIT_DONE);
  }



}
