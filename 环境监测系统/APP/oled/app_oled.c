#include "oled/bsp_i2c_oled.h"
#include "types/app_screen_type.h"
#include "types/app_sensor_data.h"

extern ScreenType global_screen_type;
extern DisplayData global_display_data;

void StartOLEDTask(void *argument)
{
	while (1)
	{
		OLED_Clear();

		switch (global_screen_type)
		{
			case SCREEN_TYPE_HUMIDITY:
			{
				OLED_ShowString(0, 0, "[P1]Humidity", OLED_8X16);
				if (global_display_data.dht11_check_result == DHT11_DATA_OK)
				{
					OLED_Printf(0, 16, OLED_8X16, "Now: %+07.3f %%RH", global_display_data.humi_value);
				}
				else
				{
					OLED_ShowString(0, 16, "Now: DATA ERROR", OLED_8X16);
				}
				OLED_Printf(0, 32, OLED_8X16, "Max: %+07.3f %%RH", global_display_data.humi_max);
				OLED_Printf(0, 48, OLED_8X16, "Min: %+07.3f %%RH", global_display_data.humi_min);
				break;
			}
			case SCREEN_TYPE_TEMPERATURE:
			{
				OLED_ShowString(0, 0, "[P2]Temperature", OLED_8X16);
				if (global_display_data.dht11_check_result == DHT11_DATA_OK)
				{
					OLED_Printf(0, 16, OLED_8X16, "Now: %+07.3f C", global_display_data.temp_value);
				}
				else
				{
					OLED_ShowString(0, 16, "Now: DATA ERROR", OLED_8X16);
				}
				OLED_Printf(0, 32, OLED_8X16, "Max: %+07.3f C", global_display_data.temp_max);
				OLED_Printf(0, 48, OLED_8X16, "Min: %+07.3f C", global_display_data.temp_min);
				break;
			}
			case SCREEN_TYPE_LIGHT:
			{
				OLED_ShowString(0, 0, "[P3]Light", OLED_8X16);
				OLED_Printf(0, 16, OLED_8X16, "Now: %06.2f %%", global_display_data.light_percentage_value);
				OLED_Printf(0, 32, OLED_8X16, "Max: %06.2f %%", global_display_data.light_percentage_max);
				OLED_Printf(0, 48, OLED_8X16, "Min: %06.2f %%", global_display_data.light_percentage_min);
				break;
			}
			default: break;
		}

		OLED_Update();
	}
}
