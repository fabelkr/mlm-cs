using System;
using System.Runtime.InteropServices;
namespace MLM {

    internal class Project {
        //C++ EXTERNALS
        // Window Manager (WM)
        [DllImport("lib/UI/libWM.dylib", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr WM_Create();

        [DllImport("lib/UI/libWM.dylib", CallingConvention = CallingConvention.Cdecl)]
        public static extern void WM_Destroy(IntPtr wm);

        [DllImport("lib/UI/libWM.dylib", CallingConvention = CallingConvention.Cdecl)]
        public static extern void WM_CreateWindow(IntPtr wm, int width, int height, string title);

        [DllImport("lib/UI/libWM.dylib", CallingConvention = CallingConvention.Cdecl)]
        public static extern void WM_Show(IntPtr wm);

        // [DllImport("lib/UI/libWM.dylib", CallingConvention = CallingConvention.Cdecl)]
        // public static extern void MM_AddElement(IntPtr wm, int type, float widht, float height);
        public static void Main(string[] args) {
            System.Console.WriteLine("Hello, World!");
            IntPtr wm = WM_Create();
            WM_CreateWindow(wm, 800, 600, "MLM");
            // MM_AddElement(wm, 0, 100, 100);
            WM_Show(wm);
        }
    }
}