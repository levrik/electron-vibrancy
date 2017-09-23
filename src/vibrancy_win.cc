//----------------------------------------------------------------------------
// electron-vibrancy
// Copyright 2017 Levin Rickert, 2016 arkenthera
//
// MIT License
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice
// shall be included in all copies or substantial
// portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//----------------------------------------------------------------------------


#include "./VibrancyHelper.h"


#pragma comment(lib, "dwmapi.lib")

namespace Vibrancy {
    struct ACCENTPOLICY {
        int nAccentState;
        int nFlags;
        int nColor;
        int nAnimationId;
    };
    struct WINCOMPATTRDATA {
        int nAttribute;
        PVOID pData;
        ULONG ulDataSize;
    };

    enum AccentTypes {
        ACCENT_DISABLE = 0,
        ACCENT_ENABLE_GRADIENT = 1,
        ACCENT_ENABLE_TRANSPARENTGRADIENT = 2,
        ACCENT_ENABLE_BLURBEHIND = 3
    };

    bool IsWindows10() {
        OSVERSIONINFOA info;
        ZeroMemory(&info, sizeof(OSVERSIONINFOA));
        info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);

        GetVersionEx(&info);

        return info.dwMajorVersion == 10;
    }

    bool SetBlurBehind(HWND hwnd, bool state) {
        bool result = false;

        if (IsWindows10()) {
            const HINSTANCE hModule = LoadLibrary(TEXT("user32.dll"));
            if (hModule) {
                typedef BOOL(WINAPI*pSetWindowCompositionAttribute)(HWND,
                    WINCOMPATTRDATA*);
                const pSetWindowCompositionAttribute
                    SetWindowCompositionAttribute =
                    (pSetWindowCompositionAttribute)GetProcAddress(
                        hModule,
                        "SetWindowCompositionAttribute");

                // Only works on Win10
                if (SetWindowCompositionAttribute) {
                    ACCENTPOLICY policy =
                        { state ? ACCENT_ENABLE_BLURBEHIND
                            : ACCENT_DISABLE , 0, 0, 0 };
                    WINCOMPATTRDATA data = {19, &policy, sizeof(ACCENTPOLICY) };
                    result = SetWindowCompositionAttribute(hwnd, &data);
                }
                FreeLibrary(hModule);
            }
        }
        return result;
    }

    VibrancyHelper::VibrancyHelper() {
    }

    bool VibrancyHelper::DisableVibrancy(unsigned char* windowHandleBuffer) {
        uint32_t handle =
            *reinterpret_cast<uint32_t*>(windowHandleBuffer);
        HWND hwnd = (HWND)handle;
        return SetBlurBehind(hwnd, false);
    }

    bool VibrancyHelper::EnableVibrancy(unsigned char* windowHandleBuffer) {
        uint32_t handle =
            *reinterpret_cast<uint32_t*>(windowHandleBuffer);
        HWND hwnd = (HWND)handle;
        return SetBlurBehind(hwnd, true);
    }
}  // namespace Vibrancy
