#include "home.h"

#include <M5Dial.h>

namespace Home {
namespace {

struct MenuItem {
    const char *name;
    App app;
};

constexpr MenuItem items[] = {
    {"QR Manager", App::QrManager},
    {"Device Info", App::DeviceInfo},
};
constexpr int item_count = sizeof(items) / sizeof(items[0]);
int selected = 0;

void drawFinder(int x, int y) {
    auto &d = M5Dial.Display;
    d.drawRect(x, y, 14, 14, WHITE);
    d.fillRect(x + 4, y + 4, 6, 6, WHITE);
}

}  // namespace

void show() {
    auto &d = M5Dial.Display;
    d.fillScreen(BLACK);
    d.setTextDatum(middle_center);
    d.drawCircle(120, 120, 117, DARKGREY);

    d.setFont(&fonts::Font2);
    d.setTextColor(CYAN, BLACK);
    d.drawString("APPS", 120, 32);

    if (item_count > 1) {
        d.fillRoundRect(4, 83, 30, 74, 10, DARKGREY);
        d.fillRoundRect(206, 83, 30, 74, 10, DARKGREY);
        d.setTextColor(WHITE, DARKGREY);
        d.drawString("<", 19, 120);
        d.drawString(">", 221, 120);
    }

    d.fillRoundRect(38, 55, 164, 143, 18, 0x1082);
    if (items[selected].app == App::QrManager) {
        drawFinder(94, 80);
        drawFinder(127, 80);
        drawFinder(94, 113);
        d.fillRect(127, 113, 6, 6, WHITE);
        d.fillRect(137, 113, 4, 4, WHITE);
        d.fillRect(127, 123, 4, 4, WHITE);
        d.fillRect(137, 125, 6, 6, WHITE);
    } else {
        d.drawCircle(120, 108, 33, WHITE);
        d.setFont(&fonts::Font7);
        d.setTextColor(WHITE, 0x1082);
        d.drawString("i", 120, 105);
    }

    d.setFont(&fonts::Font4);
    d.setTextColor(WHITE, 0x1082);
    d.drawString(items[selected].name, 120, 166);

    d.setFont(&fonts::Font2);
    d.setTextColor(CYAN, BLACK);
    d.drawString(String(selected + 1) + "/" + String(item_count) + "  PRESS TO OPEN", 120, 218);
}

void move(long delta) {
    if (item_count < 2) return;
    selected = (selected + delta % item_count + item_count) % item_count;
    show();
}

App selectedApp() {
    return items[selected].app;
}

}  // namespace Home
