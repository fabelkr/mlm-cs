#ifndef __APPLE__
    #error "This file is only for macOS"
#endif
#ifndef __OBJC__
    #error "This file must be compiled as Objective-C++"
#endif
#ifndef Renderer_mm // Prevents redefinition error
    #define Renderer_mm
    #include <QuartzCore/CAMetalLayer.h>
    #include <Metal/Metal.h>
#endif

class Renderer {
    public:
        Renderer(NSView* view, NSRect* rect, NSDevice) {
            m_view = view;
            m_device = MTLCreateSystemDefaultDevice();
            m_commandQueue = [m_device newCommandQueue];
            m_layer = [CAMetalLayer layer];
            m_layer.device = m_device;
            m_layer.pixelFormat = MTLPixelFormatBGRA8Unorm;
            m_layer.framebufferOnly = YES;
            m_layer.contentsScale = [view window].backingScaleFactor;
            [m_view setLayer:m_layer];
            [m_view setWantsLayer:YES];
        }
}
    