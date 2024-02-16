#include <Windows.h>
#include <signal.h>

HHOOK hookHandle;

void handleCtrlC(int sig) {
    // Cleanup the hook
    UnhookWindowsHookEx((HHOOK)hookHandle);
    exit(0);
}

int main() {
    // Load the DLL
    HMODULE wmDll = LoadLibraryW(L"wm_dll.dll");

    if (wmDll == NULL) {
        printf("Failed to load DLL.\n");
        return 1;
    }

    // Get the address of the hook procedure
    FARPROC hookProcedure = GetProcAddress(wmDll, "hookProcedure");

    if (hookProcedure == NULL) {
        printf("Failed to get the address of the hook procedure.\n");
        return 1;
    }

    /**
     * We're interested in WH_SHELL because it tells us the type
     * of window event that occurred.
    */
    hookHandle = SetWindowsHookExW(
        WH_SHELL,
        // Pointer to the hook procedure. This needs to come from a separate DLL.
        (HOOKPROC)hookProcedure,
        // Handle to the DLL that contains the hook procedure.
        wmDll,
        // The identifier of the thread with which the hook procedure is to be associated.
        0
        );

    if (hookHandle == NULL) {
        printf("Failed to set the hook.\n");
        return 1;
    }

    // Detect if Crtl+C is pressed and handle it
    signal(SIGINT, handleCtrlC);

    // Wait for the user to press Ctrl+C. Until then, the hook procedure executes.
    while (1) {}

    return 0;
}
