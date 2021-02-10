
#include "omgui.h"
#include "screens.h"
#include "main.h"
#include "bitmaps.h"

#include "sh1122.h"
//#include "stm32l4xx_hal.h"
#include "tim.h"


omGuiT oledUi;
omScreenT screenMain, screenData, screenTemp, screenSetup;

static void DisplayInitCb(omGuiT *);
static void DisplayUpdateCb(omGuiT *);
static void DisplayClearCb(omGuiT *);
static void DisplayDrawPixelCb(omGuiT *, uint32_t x, uint32_t y, uint8_t color);


void GUI_Init(void)
{
  oledUi.Id = 0;
  oledUi.ResX = SH1122_OLED_WIDTH;
  oledUi.ResY = SH1122_OLED_HEIGHT;
  oledUi.InitCallback = DisplayInitCb;
  oledUi.DeInitCallback = NULL;
  oledUi.UpdateCallback = DisplayUpdateCb;
  oledUi.ClearCallback = DisplayClearCb;
  oledUi.DrawPixelCallback = DisplayDrawPixelCb;

  omGuiInit(&oledUi);

  Bitmaps_Init();

  MainScreenInit();

  // Show logo
  omDrawBitmap(&oledUi, &omBitmap_guiscreen, 0, 0, True);
  Sleep(2000);
  
  // omGuiUpdate(&oledUi);
  omScreenSelect(&screenMain);
}


static void DisplayInitCb(omGuiT *ui)
{
  SH1122_DisplayInit();
}


static void DisplayUpdateCb(omGuiT *ui)
{
  SH1122_DisplayUpdate();
}


static void DisplayClearCb(omGuiT *ui)
{
  SH1122_ClearRAM();
}


static void DisplayDrawPixelCb(omGuiT *ui, uint32_t x, uint32_t y, uint8_t color)
{
  SH1122_DrawPixel(x, y, color);
}
