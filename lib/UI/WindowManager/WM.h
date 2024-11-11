#pragma once
// #include <Renderer/Renderer.h>

class WMImpl;

class WM {
    public:
        WM();
        ~WM();

        void CreateWindow(int width, int height, const char* title);
        void Show();

    public:
        WMImpl* m_impl;
};