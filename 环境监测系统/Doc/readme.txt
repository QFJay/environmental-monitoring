一、简介
基于 HAL 库 + FreeRTOS 的 STM32F103 环境监测系统。

二、功能
1. 每 1 秒采集一次：
(1)DHT11：温度、湿度
(2)光敏传感器：光照

2. ESP8266 上传数据（温度、湿度、光照百分比）到本地 TCP 服务器

3. 按键切换 OLED 显示画面：
(1)画面1：湿度（当前 / 最大 / 最小）
(2)画面2：温度（当前 / 最大 / 最小）
(3)画面3：光照百分比（当前 / 最大 / 最小）

4. LED 报警：
(1)湿度 > 阈值 → 红灯亮
(2)温度 > 阈值 → 绿灯亮
(3)光照百分比 < 阈值 → 蓝灯亮

5. 串口（CH340）输出调试信息

三、硬件接线
1. DHT11：
VCC → 3.3V
GND → GND
DATA → PB12

2. 光敏传感器：
VCC → 3.3V
GND → GND
AO → PA4
DO → 悬空

3. ESP-01 (ESP8266)：
3V3 → 3.3V
EN → 3.3V
GND → GND
TX → PB11
RX → PB10
RST → PB13
IO0 → 悬空
IO2 → 悬空

4. 按键：
一端 → 3.3V
另一端 → PA6

5. 0.96 寸 OLED：
VDD → 3.3V
GND → GND
SCK → PB8
SDA → PB9

6. LED：
红灯正极 → 3.3V，负极 → PA1
绿灯正极 → 3.3V，负极 → PA2
蓝灯正极 → 3.3V，负极 → PA3

7. USB 转串口 CH340：
VCC → 3V3（短接）
GND → GND
TXD → PA10
RXD → PA9

四、软件配置
1. 报警阈值（APP\led\app_led.c）
(1)HUMIDITY_THRESHOLD：湿度阈值
(2)TEMPERATURE_THRESHOLD：温度阈值
(3)LIGHT_PERCENTAGE_THRESHOLD：光照百分比阈值

2. Wi-Fi 和服务器（APP\esp8266\app_esp8266.c）
(1)ESP8266_AP_SSID：Wi-Fi 名称
(2)ESP8266_AP_PWD：Wi-Fi 密码
(3)ESP8266_TCP_SERVER_IP：TCP 服务器 IP
(4)ESP8266_TCP_SERVER_PORT：TCP 服务器端口

五、使用说明
1. 按硬件接线说明连接好各模块

2. 打开手机热点，运行 PC 端 TCP 服务器

3. 修改 APP\esp8266\app_esp8266.c 中的 Wi-Fi 和服务器信息

4. 根据需要修改 APP\led\app_led.c 中的报警阈值

5. 编译下载到 STM32

6. 打开串口助手查看调试信息