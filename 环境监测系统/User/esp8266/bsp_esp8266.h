#ifndef __BSP_ESP8266_H
#define __BSP_ESP8266_H

#include "main.h"

typedef enum
{
	STA = 1,
	AP = 2,
	STA_AP = 3
} NetModeTypeDef;

typedef enum
{
	SINGLE_CONN = 0,
	MULTI_CONN = 1
} ConnModeTypeDef;

typedef enum
{
	CONNECT_OK = 0,
	CONNECT_TIMEOUT = 1,
	PASSWORD_ERROR = 2,
	TARGET_AP_NOT_FOUND = 3,
	CONNECT_FAIL = 4
} ConnWifiStateTypeDef;

typedef enum
{
	TRANSPARENT_OFF = 0,
	TRANSPARENT_ON = 1
} TransparentModeTypeDef;

void ESP8266_GPIO_Init(void);
void ESP8266_Reset(void);
void UART_StartReceive(void);
void ESP8266_Init(void);
void ESP8266_SendString(char *str);
bool ESP8266_Cmd(const char *cmd);
bool ESP8266_Test(void);
bool ESP8266_SoftReset_WaitReady(void);
bool ESP8266_SetNetMode(NetModeTypeDef mode);
bool ESP8266_SetConnMode(ConnModeTypeDef mode);
ConnWifiStateTypeDef ESP8266_ConnectWifi(const char *ssid, const char *password);
bool ESP8266_ConnectTCPServer(const char *ip, uint16_t port, uint8_t conn_id);
bool ESP8266_SetTransparentMode(TransparentModeTypeDef mode);
bool ESP8266_SetSendMode(void);

#endif
