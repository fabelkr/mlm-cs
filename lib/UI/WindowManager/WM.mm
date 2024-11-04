#ifndef __APPLE__
    #error "This file is only for macOS"
#endif
#ifndef __OBJC__
    #error "This file must be compiled as Objective-C++"
#endif

#ifndef WM_mm // Prevents redefinition error
    #define WM_mm
    #include "WM.h"
    #include <QuartzCore/CAMetalLayer.h>
    #include <Metal/Metal.h>
    #include <Cocoa/Cocoa.h>
    #include <iostream>
    #include <array>
#endif

class WMImpl {
public:
    NSWindow* m_window;
    NSView* m_view;
    NSRect m_rect;
    const char* m_title;
    id<MTLDevice> device;
    id<MTLCommandQueue> commandQueue;
    std::array<int, 2> m_size;

    WMImpl() : m_window(nullptr), m_view(nullptr), m_size({0, 0}), m_title(nullptr) {}

public:

    void Cleanup() {
        // glfwDestroyWindow(m_window);
        // glfwTerminate();
        // m_window = nullptr;
        // m_size = {0, 0};
        // m_title = nullptr;
        // delete m_renderer;
        // m_renderer = nullptr;
        std::cout << "Cleaned up window manager" << std::endl;
    }

    void CreateWindow(int Width, int Height, const char* Title) {
        std::cout << "Creating window" << std::endl;
        m_size = {Width, Height};
        m_title = Title;
        
        NSApplication* app = [NSApplication sharedApplication];
        [app setActivationPolicy:NSApplicationActivationPolicyRegular];
        id menubar = [[NSMenu alloc] init];
        id appMenuItem = [[NSMenuItem alloc] init];
        [menubar addItem:appMenuItem];
        [app setMainMenu:menubar];
        id appMenu = [[NSMenu alloc] init];
        id appName = [[NSProcessInfo processInfo] processName];
        id quitTitle = [@"Quit " stringByAppendingString:appName];
        id quitMenuItem = [
            [NSMenuItem alloc] initWithTitle:quitTitle
                action:@selector(terminate:)
                keyEquivalent:@"q"
        ];
        [appMenu addItem:quitMenuItem];
        [appMenuItem setSubmenu:appMenu];

        m_rect = NSMakeRect(0, 0, Width, Height);
        m_window = [[
            NSWindow alloc] initWithContentRect:m_rect
                styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable)
                backing:NSBackingStoreBuffered
                    defer:NO
        ];
        [m_window setTitle:@(m_title)];
        [m_window makeKeyAndOrderFront:nil];

        m_view = [[NSView alloc] initWithFrame:m_rect];
        [m_window setContentView:m_view];

        CAMetalLayer* metalLayer = [CAMetalLayer layer];
        metalLayer.device = MTLCreateSystemDefaultDevice();
        metalLayer.pixelFormat = MTLPixelFormatBGRA8Unorm;
        [m_view setLayer:metalLayer];
        [m_view setWantsLayer:YES];

        // m_renderer = new Render(m_view);

        // std::cout << "Creating window with width " << Width << ", height " << Height << ", and title " << Title << std::endl;
    }

    void Show() {
        // Show the window
        if(!m_window) {
            std::cerr << "Window not created" << std::endl;
            return;
        }

        while(true) {
            @autoreleasepool {
                NSEvent* event = [NSApp nextEventMatchingMask:NSEventMaskAny untilDate:[NSDate distantFuture] inMode:NSDefaultRunLoopMode dequeue:YES];
                if(event) {
                    [NSApp sendEvent:event];
                    [NSApp updateWindows];
                }

                if([event type] == NSEventTypeApplicationDefined && [event subtype] == 0) {
                    break;
                }
            }
        }

        Cleanup();
    }
};

WM::WM() {
    m_impl = new WMImpl();
}

WM::~WM() {
    delete m_impl;
}

void WM::CreateWindow(int Width, int Height, const char* Title) {
    m_impl->CreateWindow(Width, Height, Title);
}

void WM::Show() {
    m_impl->Show();
}

