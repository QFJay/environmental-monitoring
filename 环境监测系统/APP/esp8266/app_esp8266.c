#include "esp8266/app_esp8266.h"
#include "esp8266/bsp_esp8266.h"
#include "types/app_sensor_data.h"
#include "cmsis_os2.h"
#include "FreeRTOS.h"

#define ESP8266_AP_SSID					"Play6T"
#define ESP8266_AP_PWD					"qazwsxedc"

#define ESP8266_TCP_SERVER_IP		"192.168.181.43"
#define ESP8266_TCP_SERVER_PORT	8000

extern osMessageQueueId_t ESP8266SendQueueHandle;

bool ESP8266_Preparation(void)
{
	printf(">>> ESP8266 is powered on for initialization...\r\n");

	ESP8266_Init();
	printf(">>> ESP8266 has been initialized and is now ready to receive...\r\n");

	printf(">>> ESP8266 is undergoing software reset...\r\n");
	if (ESP8266_SoftReset_WaitReady() == true)
	{
		printf(">>> ESP8266 has been reset.\r\n");
	}
	else
	{
		printf(">>> ESP8266 reset timeout!\r\n");
		return false;
	}

	if (ESP8266_Test() == true)
	{
		printf(">>> ESP8266 has passed the test.\r\n");
	}
	else
	{
		printf(">>> ESP8266 is unavailable!\r\n");
		return false;
	}

	if (ESP8266_SetNetMode(STA) == true)
	{
		printf(">>> ESP8266 has been set to STA mode.\r\n");
	}
	else
	{
		printf(">>> ESP8266 failed to set the working mode!\r\n");
		return false;
	}

	if (ESP8266_SetConnMode(SINGLE_CONN) == true)
	{
		printf(">>> ESP8266 has been set to single connection mode.\r\n");
	}
	else
	{
		printf(">>> ESP8266 failed to set the connection mode!\r\n");
		return false;
	}

	if (ESP8266_ConnectWifi(ESP8266_AP_SSID, ESP8266_AP_PWD) == CONNECT_OK)
	{
		printf(">>> Wi-Fi connected.\r\n");
	}
	else
	{
		printf(">>> Wi-Fi failed to connect!\r\n");
		return false;
	}

	if (ESP8266_ConnectTCPServer(ESP8266_TCP_SERVER_IP, ESP8266_TCP_SERVER_PORT, 0) == true)
	{
		printf(">>> Successfully connected to the TCP server.\r\n");
	}
	else
	{
		printf(">>> Failed to connect to the TCP server!\r\n");
		return false;
	}

	if (ESP8266_SetTransparentMode(TRANSPARENT_ON) == true)
	{
		printf(">>> ESP8266 has activated transparent transmission mode.\r\n");
	}
	else
	{
		printf(">>> ESP8266 failed to activate transparent transmission mode!\r\n");
		return false;
	}

	if (ESP8266_SetSendMode() == true)
	{
		printf(">>> ESP8266 has entered the data sending mode.\r\n>");
	}
	else
	{
		printf(">>> ESP8266 failed to enter the data sending mode!\r\n");
		return false;
	}

	return true;
}

void StartESP8266SendTask(void *argument)
{
	while (1)
	{
		char send_buf[128];
		SensorData *sensor_data;

		osMessageQueueGet(ESP8266SendQueueHandle, &sensor_data, 0, osWaitForever);

		if (sensor_data->dht11_check_result == DHT11_DATA_OK)
		{
			snprintf(send_buf, sizeof(send_buf), "Humidity: %+07.3f %%RH, Temperature: %+07.3f °C, Light: %06.2f %%\r\n", sensor_data->humi_value, sensor_data->temp_value, sensor_data->light_percentage_value);
		}
		else
		{
			snprintf(send_buf, sizeof(send_buf), "Humidity: DATA ERROR, Temperature: DATA ERROR, Light: %06.2f %%\r\n", sensor_data->light_percentage_value);
		}

		ESP8266_SendString(send_buf);

		vPortFree(sensor_data);
		sensor_data = NULL;
	}
}
