//
// Created by Kryštof Fabel on 31.10.2024.
//

#include <WM.h>

int main() {
    WM wm = WM();
    wm.CreateWindow(800, 600, "Hello World");
    wm.GetRenderer()->CreateElement(0, 50, 50);
    wm.Show();
    return 0;
}


