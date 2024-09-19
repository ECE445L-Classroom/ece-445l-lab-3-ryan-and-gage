
const uint16_t lightModeClock [] = ;
	
const uint16_t darkModeClock [] = ;


struct hourHand 
{
	uint16_t color = 0;
	uint
};
	

void LCDDisplay_Init()
{
  SSD1306_Init(SSD1306_SWITCHCAPVCC);
	SSD1306_ClearBuffer();
  SSD1306_OutBuffer();
}

void DisplayTimeLightMode(uint16_t hour, uint16_t minute, uint16_t second);
{
	ST7735_DrawBitmap(4, 159, lightModeClock, 120, 160);
	ST7735_DrawLine
	
}

void DisplayTimeDarkMode()
{
	ST7735_DrawBitmap(4, 159, darkModeClock, 120, 160);
	
}

void DisplayDigitalTime()
{
	
	
}

void AlarmStateBlinking() //takes current display state and flashes it 
{
	//wait for a timer that triggers a couple times a second
	
	
	
}