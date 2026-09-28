#pragma once

namespace Home {

enum class App {
    QrManager,
};

void show();
void move(long delta);
App selectedApp();

}  // namespace Home
