#include "MCUFRIEND_kbv.h"
//#include "Fonts/FreeSans9pt7b.h"

#define LCD_CS 16 // Chip Select goes to Analog 3
#define LCD_CD 15 // Command/Data goes to Analog 2
#define LCD_WR 14 // LCD Write goes to Analog 1
#define LCD_RD 13 // LCD Read goes to Analog 0
#define LCD_RST 17 // Can alternately just connect to Arduino's reset pin

MCUFRIEND_kbv tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RST);

/*
Lib tambahan yang bisa dipakai nanti jika ingin dipakai kedepannya.
#include "TouchScreen.h" // only when you want to use touch screen
#include "bitmap_mono.h" // when you want to display a bitmap image from library
#include "bitmap_RGB.h" // when you want to display a bitmap image from library
#include "Fonts/FreeSans9pt7b.h"    // when you want other fonts
#include "Fonts/FreeSans12pt7b.h" // when you want other fonts
#include "Fonts/FreeSerif12pt7b.h" // when you want other fonts
#include "FreeDefaultFonts.h" // when you want other fonts
#include "SPI.h"  // using sdcard for display bitmap image
#include "SD.h"
*/

// Assign human-readable names to some common 16-bit color values:
#define BLACK 0x0000
//#define NAVY 0x000F
//#define DARKGREEN 0x03E0
//#define DARKCYAN 0x03EF
//#define MAROON 0x7800
//#define PURPLE 0x780F
//#define OLIVE 0x7BE0
//#define LIGHTGREY 0xC618
#define DARKGREY 0x7BEF
//#define BLUE 0x001F
//#define GREEN 0x07E0
//#define CYAN 0x07FF
#define RED 0xF800
//#define MAGENTA 0xF81F
//#define YELLOW 0xFFE0
#define WHITE 0xFFFF
//#define ORANGE 0xFD20
//#define GREENYELLOW 0xAFE5
//#define PINK 0xF81F

/*
void showmsgXY(int x, int y, int sz, const GFXfont *f, const char *msg)
{
  int16_t x1, y1;
  uint16_t wid, ht;
  tft.setFont(f);
  tft.setCursor(x, y);
  tft.setTextColor(BLACK);
  tft.setTextSize(sz);
  tft.print(msg);
}
*/

void setup() {
  uint16_t ID = tft.readID();
  tft.begin(ID);
  Serial.begin(9600);
  Serial.print("LCD ID = 0x");
  Serial.println(ID, HEX);
  Serial.print("LCD width = ");
  Serial.println(tft.width());
  Serial.print("LCD height = ");
  Serial.println(tft.height());
  tft.setRotation(1);               //0=0 1=90 2=180 3=270
  tft.fillScreen(DARKGREY);
  tft.fillRect(5,5,310,115,RED);
  tft.fillRect(5,120,310,115,WHITE);
  tft.setCursor(80,108);
  tft.setTextColor(BLACK);
  tft.setTextSize(3);
  tft.print("XIRKA");
}

void loop() {
  
}
