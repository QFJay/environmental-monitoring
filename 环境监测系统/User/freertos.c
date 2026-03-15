#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "types/app_screen_type.h"
#include "types/app_sensor_data.h"

osThreadId_t KeyTaskHandle;
const osThreadAttr_t KeyTask_attributes =
{
  .name = "KeyTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t)osPriorityNormal,
};

osThreadId_t OLEDTaskHandle;
const osThreadAttr_t OLEDTask_attributes =
{
  .name = "OLEDTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t)osPriorityLow,
};

osThreadId_t SensorTaskHandle;
const osThreadAttr_t SensorTask_attributes =
{
  .name = "SensorTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t)osPriorityHigh,
};

osThreadId_t UpdateDataTaskHandle;
const osThreadAttr_t UpdateDataTask_attributes =
{
  .name = "UpdateDataTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t)osPriorityAboveNormal,
};

osThreadId_t LEDTaskHandle;
const osThreadAttr_t LEDTask_attributes =
{
  .name = "LEDTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t)osPriorityLow,
};

osThreadId_t ESP8266SendTaskHandle;
const osThreadAttr_t ESP8266SendTask_attributes =
{
  .name = "ESP8266SendTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t)osPriorityAboveNormal,
};

osMessageQueueId_t UpdateDataQueueHandle;
const osMessageQueueAttr_t UpdateDataQueue_attributes =
{
  .name = "UpdateDataQueue"
};

osMessageQueueId_t ESP8266SendQueueHandle;
const osMessageQueueAttr_t ESP8266SendQueue_attributes =
{
  .name = "ESP8266SendQueue"
};

void StartKeyTask(void *argument);
extern void StartOLEDTask(void *argument);
extern void StartSensorTask(void *argument);
extern void StartUpdateDataTask(void *argument);
extern void StartLEDTask(void *argument);
extern void StartESP8266SendTask(void *argument);

void FREERTOS_Init(void)
{
	/* Create the queue(s) */
  UpdateDataQueueHandle = osMessageQueueNew (16, sizeof(SensorData*), &UpdateDataQueue_attributes);
	ESP8266SendQueueHandle = osMessageQueueNew (16, sizeof(SensorData*), &ESP8266SendQueue_attributes);

	/* Create the thread(s) */
  KeyTaskHandle = osThreadNew(StartKeyTask, NULL, &KeyTask_attributes);
	if (KeyTaskHandle == NULL)
	{
		Error_Handler();
	}

	OLEDTaskHandle = osThreadNew(StartOLEDTask, NULL, &OLEDTask_attributes);
	if (OLEDTaskHandle == NULL)
	{
		Error_Handler();
	}

	SensorTaskHandle = osThreadNew(StartSensorTask, NULL, &SensorTask_attributes);
	if (SensorTaskHandle == NULL)
	{
		Error_Handler();
	}

	UpdateDataTaskHandle = osThreadNew(StartUpdateDataTask, NULL, &UpdateDataTask_attributes);
	if (UpdateDataTaskHandle == NULL)
	{
		Error_Handler();
	}

	LEDTaskHandle = osThreadNew(StartLEDTask, NULL, &LEDTask_attributes);
	if (LEDTaskHandle == NULL)
	{
		Error_Handler();
	}

	ESP8266SendTaskHandle = osThreadNew(StartESP8266SendTask, NULL, &ESP8266SendTask_attributes);
	if (ESP8266SendTaskHandle == NULL)
	{
		Error_Handler();
	}
}

__weak void StartKeyTask(void *argument)
{
  for(;;)
  {
    osDelay(1);
  }
}
