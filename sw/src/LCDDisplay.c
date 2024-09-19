
const uint16_t lightModeClock [] = ;
	
const uint16_t darkModeClock [] = ;


struct clockHand 
{
	uint16_t color;
	uint16_t length;
	//uint16_t startPosition; 
	uint16_t time;

} hourHand, minuteHand, secondHand;
	
uint8_t = currentSecondDisplayed;
uint8_t = currentMinuteDisplayed;
uint8_t = currentHourDisplayed;

void LCDDisplay_Init()
{
  SSD1306_Init(SSD1306_SWITCHCAPVCC);
	SSD1306_ClearBuffer();
  SSD1306_OutBuffer();
}

void DisplayTimeLightMode(uint16_t hour, uint16_t minute, uint16_t second);
{
	ST7735_DrawBitmap(4, 159, lightModeClock, 120, 160);
	ST7735_Line(0,0,0,0,hourHand.color);
	ST7735_Line(0,0,0,0,hourHand.color);
	ST7735_Line(0,0,0,0,hourHand.color);
	
}

void DisplayTimeDarkMode()
{
	ST7735_DrawBitmap(4, 159, darkModeClock, 120, 160);
	ST7735_Line(0,0,0,0,hourHand.color);
	ST7735_Line(0,0,0,0,hourHand.color);
	ST7735_Line(0,0,0,0,hourHand.color);
}

void DisplayDigitalTime()
{
	
	
}

void AlarmStateBlinking() //takes current display state and flashes it 
{
	//wait for a timer that triggers a couple times a second during snooze alarm
	//toggle between current display and background color
	
}