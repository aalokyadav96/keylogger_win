#include <windows.h>
#include <iostream>
HHOOK _k_hook;
LRESULT __stdcall k_Callback1(int nCode, WPARAM wParam, LPARAM lParam)
{
    PKBDLLHOOKSTRUCT key = (PKBDLLHOOKSTRUCT)lParam;
    //a key was pressed
    if (wParam == WM_KEYDOWN && nCode == HC_ACTION)
    {
        switch (key->vkCode)
        {
        case 'A':
            puts("A pressed");
            break;
        case 'B':
            puts("B pressed");
            break;
        case 'C':
            puts("C pressed");
            break;
        case 'D':
            puts("D pressed");
            break;
        case 'E':
            puts("E pressed");
            break;
        case 'F':
            puts("F pressed");
            break;
        case 'G':
            puts("G pressed");
            break;
        case 'H':
            puts("H pressed");
            break;
        case 'I':
            puts("I pressed");
            break;
        case 'J':
            puts("J pressed");
            break;
        case 'K':
            puts("K pressed");
            break;
        case 'L':
            puts("L pressed");
            break;
        case 'M':
            puts("M pressed");
            break;
        case 'N':
            puts("N pressed");
            break;
        case 'O':
            puts("O pressed");
            break;
        case 'P':
            puts("P pressed");
            break;
        case 'Q':
            puts("Q pressed");
            break;
        case 'R':
            puts("R pressed");
            break;
        case 'S':
            puts("S pressed");
            break;
        case 'T':
            puts("T pressed");
            break;
        case 'U':
            puts("U pressed");
            break;
        case 'V':
            puts("V pressed");
            break;
        case 'W':
            puts("W pressed");
            break;
        case 'X':
            puts("X pressed");
            break;
        case 'Y':
            puts("Y pressed");
            break;
        case 'Z':
            puts("Z pressed");
            break;
        case VK_LMENU:
            puts("Left Alt pressed");
            break;
        case VK_RMENU:
            puts("Right Alt pressed");
            break;
        case VK_ESCAPE:
            puts("ESC pressed");
            break;
        case VK_TAB:
            puts("TAB pressed");
            break;
        case VK_RETURN:
            puts("RETURN pressed");
            break;
        case VK_LBUTTON:
            puts("LBUTTON pressed");
            break;
        case VK_RBUTTON:
            puts("RBUTTON pressed");
            break;
        case VK_MBUTTON:
            puts("MBUTTON pressed");
            break;
        case VK_BACK:
            puts("BACK pressed");
            break;
        case VK_SHIFT:
            puts("SHIFT pressed");
            break;
        case VK_RSHIFT:
            puts("RSHIFT pressed");
            break;
        case VK_LSHIFT:
            puts("LSHIFT pressed");
            break;
        case VK_CONTROL:
            puts("CONTROL pressed");
            break;
        case VK_LCONTROL:
            puts("LCONTROL pressed");
            break;
        case VK_RCONTROL:
            puts("RCONTROL pressed");
            break;
        case VK_CAPITAL:
            puts("CAPITAL pressed");
            break;
        case VK_SPACE:
            puts("SPACE pressed");
            break;
        case VK_PRIOR:
            puts("Page Up pressed");
            break;
        case VK_NEXT:
            puts("Page Down pressed");
            break;
        case VK_HOME:
            puts("HOME pressed");
            break;
        case VK_END:
            puts("END pressed");
            break;
        case VK_DOWN:
            puts("DOWN pressed");
            break;
        case VK_UP:
            puts("UP pressed");
            break;
        case VK_LEFT:
            puts("LEFT pressed");
            break;
        case VK_RIGHT:
            puts("RIGHT pressed");
            break;
        case VK_INSERT:
            puts("INSERT pressed");
            break;
        case VK_DELETE:
            puts("DELETE pressed");
            break;
        case VK_LWIN:
            puts("LWin pressed");
            break;
        case VK_SLEEP:
            puts("Sleep pressed");
            break;
        case VK_MULTIPLY:
            puts("MULTIPLY pressed");
            break;
        case VK_ADD:
            puts("ADD pressed");
            break;
        case VK_SUBTRACT:
            puts("SUBTRACT pressed");
            break;
        case VK_DECIMAL:
            puts("DECIMAL pressed");
            break;
        case VK_DIVIDE:
            puts("DIVIDE pressed");
            break;
        case VK_F1:
            puts("F1 pressed");
            break;
        case VK_F2:
            puts("F2 pressed");
            break;
        case VK_F3:
            puts("F3 pressed");
            break;
        case VK_F4:
            puts("F4 pressed");
            break;
        case VK_F5:
            puts("F5 pressed");
            break;
        case VK_F6:
            puts("F6 pressed");
            break;
        case VK_F7:
            puts("F7 pressed");
            break;
        case VK_F8:
            puts("F8 pressed");
            break;
        case VK_F9:
            puts("F9 pressed");
            break;
        case VK_F10:
            puts("F10 pressed");
            break;
        case VK_F11:
            puts("F11 pressed");
            break;
        case VK_F12:
            puts("F12 pressed");
            break;
        case VK_NUMLOCK:
            puts("NUMLOCK pressed");
            break;
        case VK_SCROLL:
            puts("SCROLL pressed");
            break;
        case VK_VOLUME_MUTE:
            puts("VK_VOLUME_MUTE pressed");
            break;
        case VK_VOLUME_DOWN:
            puts("VK_VOLUME_DOWN pressed");
            break;
        case VK_VOLUME_UP:
            puts("VK_VOLUME_UP pressed");
            break;
        case VK_MEDIA_PLAY_PAUSE:
            puts("VK_MEDIA_PLAY_PAUSE pressed");
            break;
        case VK_MEDIA_NEXT_TRACK:
            puts("VK_MEDIA_NEXT_TRACK pressed");
            break;
        case VK_MEDIA_PREV_TRACK:
            puts("VK_MEDIA_PREV_TRACK pressed");
            break;
        case VK_OEM_COMMA:
            puts("VK_OEM_COMMA pressed");
            break;
        case VK_NUMPAD0:
            puts("NUMPAD0 pressed");
            break;
        case VK_NUMPAD1:
            puts("NUMPAD1 pressed");
            break;
        case VK_NUMPAD2:
            puts("NUMPAD2 pressed");
            break;
        case VK_NUMPAD3:
            puts("NUMPAD3 pressed");
            break;
        case VK_NUMPAD4:
            puts("NUMPAD4 pressed");
            break;
        case VK_NUMPAD5:
            puts("NUMPAD5 pressed");
            break;
        case VK_NUMPAD6:
            puts("NUMPAD6 pressed");
            break;
        case VK_NUMPAD7:
            puts("NUMPAD7 pressed");
            break;
        case VK_NUMPAD8:
            puts("NUMPAD8 pressed");
            break;
        case VK_NUMPAD9:
            puts("NUMPAD9 pressed");
            break;
        case 0x30:
					puts("0");
					break;
				case 0x31:
					puts("1");
					break;
				case 0x32:
					puts("2");
					break;
				case 0x33:
					puts("3");
					break;
				case 0x34:
					puts("4");
					break;
				case 0x35:
					puts("5");
					break;
				case 0x36:
					puts("6");
					break;
				case 0x37:
					puts("7");
					break;
				case 0x38:
					puts("8");
					break;
				case 0x39:
					puts("9");
					break;
				case 0xBB:
					puts("=");
					break;
				case 0xBE:
					puts(".");
					break;
				case 0xBD:
					puts("-");
					break;
				case 0xE2:
					puts("<");
					break;

			case VK_OEM_3:
				puts(" ` ");
				break;
			case VK_OEM_4:
				puts(" [ ");
				break;
			case VK_OEM_6:
				puts(" ] ");
				break;
			case VK_OEM_1:
				puts(" ; ");
				break;
			case VK_OEM_8:
				puts(" \\ ");
				break;
			case VK_OEM_7:
				puts(" ' ");
				break;
        default:
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

