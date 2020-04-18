// Created by Niels Marsman on 18-04-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_INPUT_H
#define SYNERGY_INPUT_H

#include <glm/glm.hpp>

#include "Synergy/Core.h"

namespace Synergy
{
    class SYNERGY_API Input
    {
    public:
        enum SYNERGY_API Key: uint16_t
        {
            UNKNOWN = 0x00,
            
            A = 0x04, // Keyboard a and A
            B = 0x05, // Keyboard b and B
            C = 0x06, // Keyboard c and C
            D = 0x07, // Keyboard d and D
            E = 0x08, // Keyboard e and E
            F = 0x09, // Keyboard f and F
            G = 0x0a, // Keyboard g and G
            H = 0x0b, // Keyboard h and H
            I = 0x0c, // Keyboard i and I
            J = 0x0d, // Keyboard j and J
            K = 0x0e, // Keyboard k and K
            L = 0x0f, // Keyboard l and L
            M = 0x10, // Keyboard m and M
            N = 0x11, // Keyboard n and N
            O = 0x12, // Keyboard o and O
            P = 0x13, // Keyboard p and P
            Q = 0x14, // Keyboard q and Q
            R = 0x15, // Keyboard r and R
            S = 0x16, // Keyboard s and S
            T = 0x17, // Keyboard t and T
            U = 0x18, // Keyboard u and U
            V = 0x19, // Keyboard v and V
            W = 0x1a, // Keyboard w and W
            X = 0x1b, // Keyboard x and X
            Y = 0x1c, // Keyboard y and Y
            Z = 0x1d, // Keyboard z and Z

            KEY_1 = 0x1e, // Keyboard 1 and !
            KEY_2 = 0x1f, // Keyboard 2 and @
            KEY_3 = 0x20, // Keyboard 3 and #
            KEY_4 = 0x21, // Keyboard 4 and $
            KEY_5 = 0x22, // Keyboard 5 and %
            KEY_6 = 0x23, // Keyboard 6 and ^
            KEY_7 = 0x24, // Keyboard 7 and &
            KEY_8 = 0x25, // Keyboard 8 and *
            KEY_9 = 0x26, // Keyboard 9 and (
            KEY_0 = 0x27, // Keyboard 0 and )
               
            RETURN      = 0x28, // Keyboard Return
            ESCAPE      = 0x29, // Keyboard Escape
            BACKSPACE   = 0x2a, // Keyboard Backspace
            TAB         = 0x2b, // Keyboard Tab
            SPACE       = 0x2c, // Keyboard Spacebar
            
            SUBTRACT        = 0x2d, // Keyboard - and _
            EQUALS          = 0x2e, // Keyboard = and +
            LEFT_BRACKET    = 0x2f, // Keyboard [ and {
            RIGHT_BRACKET   = 0x30, // Keyboard ] and }
            BACKSLASH       = 0x31, // Keyboard \ and |
            NONUS_HASH      = 0x32, // Keyboard # and ~
            SEMICOLON       = 0x33, // Keyboard ; and :
            APOSTROPHE      = 0x34, // Keyboard ' and "
            GRAVE           = 0x35, // Keyboard ` and ~
            COMMA           = 0x36, // Keyboard , and <
            PERIOD          = 0x37, // Keyboard . and >
            SLASH           = 0x38, // Keyboard / and ?
            
            CAPSLOCK = 0x39, // Keyboard Caps Lock
            
            F1  = 0x3a, // Keyboard F1
            F2  = 0x3b, // Keyboard F2
            F3  = 0x3c, // Keyboard F3
            F4  = 0x3d, // Keyboard F4
            F5  = 0x3e, // Keyboard F5
            F6  = 0x3f, // Keyboard F6
            F7  = 0x40, // Keyboard F7
            F8  = 0x41, // Keyboard F8
            F9  = 0x42, // Keyboard F9
            F10 = 0x43, // Keyboard F10
            F11 = 0x44, // Keyboard F11
            F12 = 0x45, // Keyboard F12
            F13 = 0x68, // Keyboard F13
            F14 = 0x69, // Keyboard F14
            F15 = 0x6a, // Keyboard F15
            F16 = 0x6b, // Keyboard F16
            F17 = 0x6c, // Keyboard F17
            F18 = 0x6d, // Keyboard F18
            F19 = 0x6e, // Keyboard F19
            F20 = 0x6f, // Keyboard F20
            F21 = 0x70, // Keyboard F21
            F22 = 0x71, // Keyboard F22
            F23 = 0x72, // Keyboard F23
            F24 = 0x73, // Keyboard F24
            F25 = 0x74, // Keyboard F25

            PRINTSCREEN = 0x46, // Keyboard Print Screen
            SCROLLLOCK  = 0x47, // Keyboard Scroll Lock
            PAUSE       = 0x48, // Keyboard Pause
            INSERT      = 0x49, // Keyboard Insert (Help on some Mac keyboards)
            HOME        = 0x4a, // Keyboard Home
            PAGEUP      = 0x4b, // Keyboard Page Up
            DELETE      = 0x4c, // Keyboard Delete Forward
            END         = 0x4d, // Keyboard End
            PAGEDOWN    = 0x4e, // Keyboard Page Down
            RIGHT       = 0x4f, // Keyboard Right Arrow
            LEFT        = 0x50, // Keyboard Left Arrow
            DOWN        = 0x51, // Keyboard Down Arrow
            UP          = 0x52, // Keyboard Up Arrow
            
            NUMLOCK = 0x53, // Keyboard Num Lock
            
            KEYPAD_DIVIDE               = 0x54, // Keypad /
            KEYPAD_MULTIPLY             = 0x55, // Keypad *
            KEYPAD_SUBTRACT             = 0x56, // Keypad -
            KEYPAD_ADD                  = 0x57, // Keypad +
            KEYPAD_RETURN               = 0x58, // Keypad ENTER
            KEYPAD_1                    = 0x59, // Keypad 1 and End
            KEYPAD_2                    = 0x5a, // Keypad 2 and Down Arrow
            KEYPAD_3                    = 0x5b, // Keypad 3 and PageDn
            KEYPAD_4                    = 0x5c, // Keypad 4 and Left Arrow
            KEYPAD_5                    = 0x5d, // Keypad 5
            KEYPAD_6                    = 0x5e, // Keypad 6 and Right Arrow
            KEYPAD_7                    = 0x5f, // Keypad 7 and Home
            KEYPAD_8                    = 0x60, // Keypad 8 and Up Arrow
            KEYPAD_9                    = 0x61, // Keypad 9 and Page Up
            KEYPAD_0                    = 0x62, // Keypad 0 and Insert
            KEYPAD_PERIOD               = 0x63, // Keypad . and Delete
            KEYPAD_EQUALS               = 0x67, // Keypad Equals
            KEYPAD_COMMA                = 0x85,
            KEYPAD_EQUALS_AS400         = 0x86,
            KEYPAD_00                   = 0xb0,
            KEYPAD_000                  = 0xb1,
            KEYPAD_THOUSANDSSEPARATOR   = 0xb2,
            KEYPAD_DECIMALSEPARATOR     = 0xb3,
            KEYPAD_CURRENCYUNIT         = 0xb4,
            KEYPAD_CURRENCYSUBUNIT      = 0xb5,
            KEYPAD_LEFTPAREN            = 0xb6,
            KEYPAD_RIGHTPAREN           = 0xb7,
            KEYPAD_LEFTBRACE            = 0xb8,
            KEYPAD_RIGHTBRACE           = 0xb9,
            KEYPAD_TAB                  = 0xba,
            KEYPAD_BACKSPACE            = 0xbb,
            KEYPAD_A                    = 0xbc,
            KEYPAD_B                    = 0xbd,
            KEYPAD_C                    = 0xbe,
            KEYPAD_D                    = 0xbf,
            KEYPAD_E                    = 0xc0,
            KEYPAD_F                    = 0xc1,
            KEYPAD_XOR                  = 0xc2,
            KEYPAD_POWER                = 0xc3,
            KEYPAD_PERCENT              = 0xc4,
            KEYPAD_LESS                 = 0xc5,
            KEYPAD_GREATER              = 0xc6,
            KEYPAD_AMPERSAND            = 0xc7,
            KEYPAD_DBLAMPERSAND         = 0xc8,
            KEYPAD_VERTICALBAR          = 0xc9,
            KEYPAD_DBLVERTICALBAR       = 0xca,
            KEYPAD_COLON                = 0xcb,
            KEYPAD_HASH                 = 0xcc,
            KEYPAD_SPACE                = 0xcd,
            KEYPAD_AT                   = 0xce,
            KEYPAD_EXCLAM               = 0xcf,
            KEYPAD_MEMSTORE             = 0xd0,
            KEYPAD_MEMRECALL            = 0xd1,
            KEYPAD_MEMCLEAR             = 0xd2,
            KEYPAD_MEMADD               = 0xd3,
            KEYPAD_MEMSUBTRACT          = 0xd4,
            KEYPAD_MEMMULTIPLY          = 0xd5,
            KEYPAD_MEMDIVIDE            = 0xd6,
            KEYPAD_PLUSMINUS            = 0xd7,
            KEYPAD_CLEAR                = 0xd8,
            KEYPAD_CLEARENTRY           = 0xd9,
            KEYPAD_BINARY               = 0xda,
            KEYPAD_OCTAL                = 0xdb,
            KEYPAD_DECIMAL              = 0xdc,
            KEYPAD_HEXADECIMAL          = 0xdd,
            
            NONUS_BACKSLASH = 0x64, // Keyboard Non-US \ and |
            
            APPLICATION = 0x65, // Keyboard Application (windows contextual menu, compose)
            POWER       = 0x66, // Keyboard Power
            EXECUTE     = 0x74, // Keyboard Execute
            HELP        = 0x75, // Keyboard Help
            MENU        = 0x76, // Keyboard Menu
            SELECT      = 0x77, // Keyboard Select
            STOP        = 0x78, // Keyboard Stop
            REDO        = 0x79, // Keyboard Redo / Again
            UNDO        = 0x7a, // Keyboard Undo
            CUT         = 0x7b, // Keyboard Cut
            COPY        = 0x7c, // Keyboard Copy
            PASTE       = 0x7d, // Keyboard Paste
            FIND        = 0x7e, // Keyboard Find
            MUTE        = 0x7f, // Keyboard Mute
            VOLUMEUP    = 0x80, // Keyboard Volume Up
            VOLUMEDOWN  = 0x81, // Keyboard Volume Down
            
            INTERNATIONAL1  = 0x87,
            INTERNATIONAL2  = 0x88,
            INTERNATIONAL3  = 0x89,
            INTERNATIONAL4  = 0x8a,
            INTERNATIONAL5  = 0x8b,
            INTERNATIONAL6  = 0x8c,
            INTERNATIONAL7  = 0x8d,
            INTERNATIONAL8  = 0x8e,
            INTERNATIONAL9  = 0x8f,
            LANG1           = 0x90,
            LANG2           = 0x91,
            LANG3           = 0x92,
            LANG4           = 0x93,
            LANG5           = 0x94,
            LANG6           = 0x95,
            LANG7           = 0x96,
            LANG8           = 0x97,
            LANG9           = 0x98,

            ALTERASE    = 0x99,
            SYSREQ      = 0x9a,
            CANCEL      = 0x9b,
            CLEAR       = 0x9c,
            PRIOR       = 0x9d,
            RETURN2     = 0x9e,
            SEPARATOR   = 0x9f,
            OUT         = 0xa0,
            OPER        = 0xa1,
            CLEARAGAIN  = 0xa2,
            CRSEL       = 0xa3,
            EXSEL       = 0xa4,
            
            LEFT_CTRL       = 0xe0, // Keyboard Left Control
            LEFT_SHIFT      = 0xe1, // Keyboard Left Shift
            LEFT_ALT        = 0xe2, // Keyboard Left Alt
            LEFT_PLATFORM   = 0xe3, // Keyboard Left Platform
            RIGHT_CTRL      = 0xe4, // Keyboard Right Control
            RIGHT_SHIFT     = 0xe5, // Keyboard Right Shift
            RIGHT_ALT       = 0xe6, // Keyboard Right Alt
            RIGHT_PLATFORM  = 0xe7, // Keyboard Right Platform
            
            AUDIONEXT           = 0x102,
            AUDIOPREV           = 0x103,
            AUDIOSTOP           = 0x104,
            AUDIOPLAY           = 0x105,
            AUDIOMUTE           = 0x106,
            AUDIOREWIND         = 0x11d,
            AUDIOFASTFORWARD    = 0x11e,
            
            MEDIASELECT         = 0x107,
            WWW                 = 0x108,
            MAIL                = 0x109,
            CALCULATOR          = 0x10a,
            COMPUTER            = 0x10b,
            ACTION_SEARCH       = 0x10c,
            ACTION_HOME         = 0x10d,
            ACTION_BACK         = 0x10e,
            ACTION_FORWARD      = 0x10f,
            ACTION_STOP         = 0x110,
            ACTION_REFRESH      = 0x111,
            ACTION_BOOKMARKS    = 0x112,
            
            BRIGHTNESSDOWN  = 0x113,
            BRIGHTNESSUP    = 0x114,
            DISPLAYSWITCH   = 0x115,
            KBDILLUMTOGGLE  = 0x116,
            KBDILLUMDOWN    = 0x117,
            KBDILLUMUP      = 0x118,
            EJECT           = 0x119,
            SLEEP           = 0x11a,
            APP1            = 0x11b,
            APP2            = 0x11c,

            COUNT
        };

        enum class SYNERGY_API Mouse: uint8_t
        {
            UKNOWN = 0x00,
            
            BUTTON_1  = 0x01,
            BUTTON_2  = 0x02,
            BUTTON_3  = 0x03,
            BUTTON_4  = 0x04,
            BUTTON_5  = 0x05,
            BUTTON_6  = 0x06,
            BUTTON_7  = 0x07,
            BUTTON_8  = 0x08,
            BUTTON_LEFT   = 0x00,
            BUTTON_RIGHT  = 0x01,
            BUTTON_MIDDLE = 0x02,
            
            COUNT
        };
        
        struct State
        {
            bool pressed = false;
            bool released = false;
            bool held = false;
        };
        
    private:
        static Input& Instance();
        
    public:
        Input(const Input&) = delete;
        Input& operator=(const Input&) = delete;
        
        static State Get(Key key);
        static State Get(Mouse button);
        
        static glm::vec2 GetMousePosition();
        
    private:
        Input() {}
        
        void UpdateState();
        
    private:
        bool keyboardPreviousState[256] { 0 };
        bool keyboardNextState[256] { 0 };
        State keyboardCurrentState[256] { 0 };
        
        bool mousePreviousState[8] { 0 };
        bool mouseNextState[8] { 0 };
        State mouseCurrentState[8] { 0 };
        
        glm::vec2 mousePositionCurrent = { 0, 0 };
        glm::vec2 mousePositionCache = { 0, 0 };
        
        friend class Platform;
    };
}

#endif
