#include <Windows.h>
#include <signal.h>

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
    HHOOK hookHandle = SetWindowsHookExW(
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

    // Use a message queue
    while (TRUE) {
        DWORD result = MsgWaitForMultipleObjects(0, NULL, FALSE, INFINITE, QS_ALLINPUT);
        if (result == WAIT_OBJECT_0) {
            MSG msg;
            while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        } else {
            // Handle other conditions, such as signaled events for shutdown
        }
    }

    // Cleanup
    if (hookHandle != NULL) {
        UnhookWindowsHookEx(hookHandle);
    }

    if (wmDll != NULL) {
        FreeLibrary(wmDll);
    }

    return 0;
}
