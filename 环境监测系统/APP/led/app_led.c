#include "led/bsp_led.h"
#include "types/app_sensor_data.h"

#define HUMIDITY_THRESHOLD					70.0f
#define TEMPERATURE_THRESHOLD				32.0f
#define LIGHT_PERCENTAGE_THRESHOLD	30.0f

extern DisplayData global_display_data;

void StartLEDTask(void *argument)
{
	while (1)
	{
		if (global_display_data.humi_value >= HUMIDITY_THRESHOLD)
		{
			LED_On(LED_RED);
		}
		else
		{
			LED_Off(LED_RED);
		}

		if (global_display_data.temp_value >= TEMPERATURE_THRESHOLD)
		{
			LED_On(LED_GREEN);
		}
		else
		{
			LED_Off(LED_GREEN);
		}

		if (global_display_data.light_percentage_value <= LIGHT_PERCENTAGE_THRESHOLD)
		{
			LED_On(LED_BLUE);
		}
		else
		{
			LED_Off(LED_BLUE);
		}
	}
}
