#include "KeyBoardLock.h"

bool isKeyboardLocked = false;
HHOOK hKeyboardHook = NULL;  // Hook handle

// This function will block the keyboard input
LRESULT CALLBACK KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        // If a key is pressed or released, we block the input when the keyboard is locked
        if (isKeyboardLocked) {
            return 1;  // Block the keyboard event
        }
    }
    return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam); 
}

void ToggleLock() {
    if (isKeyboardLocked) {
        // Unblock keyboard input: Remove the hook
        if (hKeyboardHook != NULL) {
            UnhookWindowsHookEx(hKeyboardHook);
            hKeyboardHook = NULL;
        }
        isKeyboardLocked = false;
    } else {
        // Block keyboard input: Install the hook
        hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHookProc, NULL, 0);
        if (hKeyboardHook == NULL) {
            MessageBoxW(NULL, L"Failed to install keyboard hook!", L"Error", MB_OK);
        }
        isKeyboardLocked = true;
    }
}

