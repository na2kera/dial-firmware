#include "device_info.h"

#include <M5Dial.h>

namespace DeviceInfo {

void show() {
    auto &d = M5Dial.Display;
    d.fillScreen(BLACK);
    d.setTextDatum(middle_center);
    d.drawCircle(120, 120, 117, DARKGREY);

    d.setFont(&fonts::Font4);
    d.setTextColor(CYAN, BLACK);
    d.drawString("Device Info", 120, 46);

    d.setFont(&fonts::Font2);
    d.setTextColor(WHITE, BLACK);
    d.drawString("M5Dial v1.1", 120, 94);
    d.drawString(ESP.getChipModel(), 120, 125);
    d.drawString(String(ESP.getFlashChipSize() / (1024 * 1024)) + " MB flash", 120, 156);

    d.setTextColor(CYAN, BLACK);
    d.drawString("HOLD: HOME", 120, 214);
}

}  // namespace DeviceInfo
