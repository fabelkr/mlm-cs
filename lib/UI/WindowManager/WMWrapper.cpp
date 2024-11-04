#include "WM.h"
#include "../Export.h"

extern "C" {
    EXPORT WM* WM_Create() {
        return new WM();
    }

    EXPORT void WM_Destroy(WM* wm) {
        delete wm;
    }

    EXPORT void WM_CreateWindow(WM* wm, int Width, int Height, const char* Title) {
        wm->CreateWindow(Width, Height, Title);
    }

    EXPORT void WM_Show(WM* wm) {
        wm->Show();
    }

    EXPORT void MM_AddElement(WM* wm, int type, float width, float height) {
        wm->GetRenderer()->CreateElement(type, width, height);
    }
}