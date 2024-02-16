#include <Windows.h>

/**
 * This is the hook procedure that will be called when a window event occurs.
 */

__declspec(dllexport) LRESULT CALLBACK hookProcedure(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HSHELL_WINDOWCREATED || nCode == HSHELL_WINDOWDESTROYED) {
        // Rearrange ALL the windows on the desktop vertically
        TileWindows(NULL, MDITILE_VERTICAL, NULL, NULL, NULL);
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
