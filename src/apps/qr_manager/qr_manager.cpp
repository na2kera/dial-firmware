#include "qr_manager.h"

#include <M5Dial.h>
#include "icons.h"

namespace QrManager {
namespace {

struct QrItem {
    const char *name;
    const char *content;
    const uint8_t *icon;
    unsigned int icon_size;
    const lgfx::IFont *font;
};

constexpr QrItem items[] = {
    {"X", "https://x.com/na2kera_0510", icon_x, icon_x_size, &fonts::Font2},
    {"GitHub", "https://github.com/na2kera", icon_github, icon_github_size, &fonts::Font2},
    {"PeachTech", "https://x.com/PeachTech_0927", icon_peachtech, icon_peachtech_size, &fonts::Font2},
    {"化身デモ", "https://mobile-mr-keshin.na2kera.workers.dev/demos/ex9-1-keshin/", nullptr, 0, &fonts::efontJA_16},
};
constexpr int item_count = sizeof(items) / sizeof(items[0]);

int selected = 0;
bool qr_only = false;

void drawQr(const QrItem &item, int x, int y, int size) {
    auto &d = M5Dial.Display;
    d.fillRect(x, y, size, size, WHITE);
    // Leave a white quiet zone so a phone can read the code reliably.
    d.qrcode(item.content, x + 10, y + 10, size - 20);
}

}  // namespace

void show() {
    auto &d = M5Dial.Display;
    const auto &item = items[selected];
    d.fillScreen(BLACK);
    d.setTextDatum(middle_center);

    if (qr_only) {
        drawQr(item, 36, 36, 168);
        d.setFont(&fonts::Font2);
        d.setTextColor(CYAN, BLACK);
        d.drawString("HOLD: HOME", 120, 222);
        return;
    }

    if (item.icon != nullptr) {
        d.drawPng(item.icon, item.icon_size, 57, 19, 32, 32);
    }
    d.setFont(item.font);
    d.setTextColor(WHITE, BLACK);
    d.drawString(item.name, item.icon != nullptr ? 135 : 120, 28);
    drawQr(item, 43, 55, 154);
    d.setFont(&fonts::Font2);
    d.setTextColor(CYAN, BLACK);
    d.drawString(String(selected + 1) + "/" + String(item_count) + "  HOLD: HOME", 120, 222);
}

void move(long delta) {
    selected = (selected + delta % item_count + item_count) % item_count;
    qr_only = false;
    show();
    Serial.printf("selected: %s\n", items[selected].name);
}

void toggleQrOnly() {
    qr_only = !qr_only;
    show();
}

}  // namespace QrManager
