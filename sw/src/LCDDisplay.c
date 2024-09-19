
const uint16_t lightModeClock [] =
	
const uint16_t darkModeClock [] =
	



void LCDDisplay_Init()
{
  SSD1306_Init(SSD1306_SWITCHCAPVCC);
	SSD1306_ClearBuffer();
  SSD1306_OutBuffer();
}

void Draw