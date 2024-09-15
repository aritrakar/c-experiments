#include <Windows.h>

BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData) {
    MONITORINFOEX miex;
    miex.cbSize = sizeof(miex);
    if (GetMonitorInfo(hMonitor, &miex)) {
        printf("Monitor Name: %s\n", miex.szDevice);
        printf("Monitor Area: %ld x %ld\n", lprcMonitor->right - lprcMonitor->left, lprcMonitor->bottom - lprcMonitor->top);
    }
    return TRUE;
}

void EnumerateAndHandleMonitors() {
    EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, 0);
}

int main() {
    EnumerateAndHandleMonitors();
    return 0;
}