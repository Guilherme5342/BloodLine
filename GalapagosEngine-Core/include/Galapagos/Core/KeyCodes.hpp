#pragma once
#include "SDL2/SDL_keycode.h"
#include "SDL2/SDL_mouse.h"

enum class MouseButton : std::int32_t {
    Left = SDL_BUTTON_LEFT,
    Middle = SDL_BUTTON_MIDDLE,
    Right = SDL_BUTTON_RIGHT,
    X1 = SDL_BUTTON_X1,
    X2 = SDL_BUTTON_X2
};

enum class Key : std::int32_t
{
    Unknown = SDLK_UNKNOWN,
    Return = SDLK_RETURN,
    Escape = SDLK_ESCAPE,
    Backspace = SDLK_BACKSPACE,
    Tab = SDLK_TAB,
    Space = SDLK_SPACE,
    Exclaim = SDLK_EXCLAIM,
    Quotedbl = SDLK_QUOTEDBL,
    Hash = SDLK_HASH,
    Percent = SDLK_PERCENT,
    Dollar = SDLK_DOLLAR,
    Ampersand = SDLK_AMPERSAND,
    Quote = SDLK_QUOTE,
    Leftparen = SDLK_LEFTPAREN,
    Rightparen = SDLK_RIGHTPAREN,
    Asterisk = SDLK_ASTERISK,
    Plus = SDLK_PLUS,
    Comma = SDLK_COMMA,
    Minus = SDLK_MINUS,
    Period = SDLK_PERIOD,
    Slash = SDLK_SLASH,
    Num_0 = SDLK_0,
    Num_1 = SDLK_1,
    Num_2 = SDLK_2,
    Num_3 = SDLK_3,
    Num_4 = SDLK_4,
    Num_5 = SDLK_5,
    Num_6 = SDLK_6,
    Num_7 = SDLK_7,
    Num_8 = SDLK_8,
    Num_9 = SDLK_9,
    Colon = SDLK_COLON,
    Semicolon = SDLK_SEMICOLON,
    Less = SDLK_LESS,
    Equals = SDLK_EQUALS,
    Greater = SDLK_GREATER,
    Question = SDLK_QUESTION,
    At = SDLK_AT,
    Leftbracket = SDLK_LEFTBRACKET,
    Backslash = SDLK_BACKSLASH,
    Rightbracket = SDLK_RIGHTBRACKET,
    Caret = SDLK_CARET,
    Underscore = SDLK_UNDERSCORE,
    Backquote = SDLK_BACKQUOTE,
    A = SDLK_a,
    B = SDLK_b,
    C = SDLK_c,
    D = SDLK_d,
    E = SDLK_e,
    F = SDLK_f,
    G = SDLK_g,
    H = SDLK_h,
    I = SDLK_i,
    J = SDLK_j,
    K = SDLK_k,
    L = SDLK_l,
    M = SDLK_m,
    N = SDLK_n,
    O = SDLK_o,
    P = SDLK_p,
    Q = SDLK_q,
    R = SDLK_r,
    S = SDLK_s,
    T = SDLK_t,
    U = SDLK_u,
    V = SDLK_v,
    W = SDLK_w,
    X = SDLK_x,
    Y = SDLK_y,
    Z = SDLK_z,
    Capslock = SDLK_CAPSLOCK,
    F1 = SDLK_F1,
    F2 = SDLK_F2,
    F3 = SDLK_F3,
    F4 = SDLK_F4,
    F5 = SDLK_F5,
    F6 = SDLK_F6,
    F7 = SDLK_F7,
    F8 = SDLK_F8,
    F9 = SDLK_F9,
    F10 = SDLK_F10,
    F11 = SDLK_F11,
    F12 = SDLK_F12,
    Printscreen = SDLK_PRINTSCREEN,
    Scrolllock = SDLK_SCROLLLOCK,
    Pause = SDLK_PAUSE,
    Insert = SDLK_INSERT,
    Home = SDLK_HOME,
    Pageup = SDLK_PAGEUP,
    Delete = SDLK_DELETE,
    End = SDLK_END,
    Pagedown = SDLK_PAGEDOWN,
    ArrowRight = SDLK_RIGHT,
    ArrowLeft = SDLK_LEFT,
    ArrowDown = SDLK_DOWN,
    ArrowUp = SDLK_UP,
    Numlockclear = SDLK_NUMLOCKCLEAR,
    Numpad_divide = SDLK_KP_DIVIDE,
    Numpad_multiply = SDLK_KP_MULTIPLY,
    Numpad_minus = SDLK_KP_MINUS,
    Numpad_plus = SDLK_KP_PLUS,
    Numpad_enter = SDLK_KP_ENTER,
    Numpad_1 = SDLK_KP_1,
    Numpad_2 = SDLK_KP_2,
    Numpad_3 = SDLK_KP_3,
    Numpad_4 = SDLK_KP_4,
    Numpad_5 = SDLK_KP_5,
    Numpad_6 = SDLK_KP_6,
    Numpad_7 = SDLK_KP_7,
    Numpad_8 = SDLK_KP_8,
    Numpad_9 = SDLK_KP_9,
    Numpad_0 = SDLK_KP_0,
    Numpad_period = SDLK_KP_PERIOD,
    Application = SDLK_APPLICATION,
    Power = SDLK_POWER,
    Numpad_equals = SDLK_KP_EQUALS,
    F13 = SDLK_F13,
    F14 = SDLK_F14,
    F15 = SDLK_F15,
    F16 = SDLK_F16,
    F17 = SDLK_F17,
    F18 = SDLK_F18,
    F19 = SDLK_F19,
    F20 = SDLK_F20,
    F21 = SDLK_F21,
    F22 = SDLK_F22,
    F23 = SDLK_F23,
    F24 = SDLK_F24,
    Execute = SDLK_EXECUTE,
    Help = SDLK_HELP,
    Menu = SDLK_MENU,
    Select = SDLK_SELECT,
    Stop = SDLK_STOP,
    Again = SDLK_AGAIN,
    Undo = SDLK_UNDO,
    Cut = SDLK_CUT,
    Copy = SDLK_COPY,
    Paste = SDLK_PASTE,
    Find = SDLK_FIND,
    Mute = SDLK_MUTE,
    Volumeup = SDLK_VOLUMEUP,
    Volumedown = SDLK_VOLUMEDOWN,
    Numpad_comma = SDLK_KP_COMMA,
    Numpad_equalsas400 = SDLK_KP_EQUALSAS400,
    Alterase = SDLK_ALTERASE,
    Sysreq = SDLK_SYSREQ,
    Cancel = SDLK_CANCEL,
    Clear = SDLK_CLEAR,
    Prior = SDLK_PRIOR,
    Return2 = SDLK_RETURN2,
    Separator = SDLK_SEPARATOR,
    Out = SDLK_OUT,
    Oper = SDLK_OPER,
    Clearagain = SDLK_CLEARAGAIN,
    Crsel = SDLK_CRSEL,
    Exsel = SDLK_EXSEL,
    Numpad_00 = SDLK_KP_00,
    Numpad_000 = SDLK_KP_000,
    Thousandsseparator = SDLK_THOUSANDSSEPARATOR,
    Decimalseparator = SDLK_DECIMALSEPARATOR,
    Currencyunit = SDLK_CURRENCYUNIT,
    Currencysubunit = SDLK_CURRENCYSUBUNIT,
    Numpad_leftparen = SDLK_KP_LEFTPAREN,
    Numpad_rightparen = SDLK_KP_RIGHTPAREN,
    Numpad_leftbrace = SDLK_KP_LEFTBRACE,
    Numpad_rightbrace = SDLK_KP_RIGHTBRACE,
    Numpad_tab = SDLK_KP_TAB,
    Numpad_backspace = SDLK_KP_BACKSPACE,
    Numpad_a = SDLK_KP_A,
    Numpad_b = SDLK_KP_B,
    Numpad_c = SDLK_KP_C,
    Numpad_d = SDLK_KP_D,
    Numpad_e = SDLK_KP_E,
    Numpad_f = SDLK_KP_F,
    Numpad_xor = SDLK_KP_XOR,
    Numpad_power = SDLK_KP_POWER,
    Numpad_percent = SDLK_KP_PERCENT,
    Numpad_less = SDLK_KP_LESS,
    Numpad_greater = SDLK_KP_GREATER,
    Numpad_ampersand = SDLK_KP_AMPERSAND,
    Numpad_dblampersand = SDLK_KP_DBLAMPERSAND,
    Numpad_verticalbar = SDLK_KP_VERTICALBAR,
    Numpad_dblverticalbar = SDLK_KP_DBLVERTICALBAR,
    Numpad_colon = SDLK_KP_COLON,
    Numpad_hash = SDLK_KP_HASH,
    Numpad_space = SDLK_KP_SPACE,
    Numpad_at = SDLK_KP_AT,
    Numpad_exclam = SDLK_KP_EXCLAM,
    Numpad_memstore = SDLK_KP_MEMSTORE,
    Numpad_memrecall = SDLK_KP_MEMRECALL,
    Numpad_memclear = SDLK_KP_MEMCLEAR,
    Numpad_memadd = SDLK_KP_MEMADD,
    Numpad_memsubtract = SDLK_KP_MEMSUBTRACT,
    Numpad_memmultiply = SDLK_KP_MEMMULTIPLY,
    Numpad_memdivide = SDLK_KP_MEMDIVIDE,
    Numpad_plusminus = SDLK_KP_PLUSMINUS,
    Numpad_clear = SDLK_KP_CLEAR,
    Numpad_clearentry = SDLK_KP_CLEARENTRY,
    Numpad_binary = SDLK_KP_BINARY,
    Numpad_octal = SDLK_KP_OCTAL,
    Numpad_decimal = SDLK_KP_DECIMAL,
    Numpad_hexadecimal = SDLK_KP_HEXADECIMAL,
    Lctrl = SDLK_LCTRL,
    Lshift = SDLK_LSHIFT,
    Lalt = SDLK_LALT,
    Lgui = SDLK_LGUI,
    Rctrl = SDLK_RCTRL,
    Rshift = SDLK_RSHIFT,
    Ralt = SDLK_RALT,
    Rgui = SDLK_RGUI,
    Mode = SDLK_MODE,
    Audionext = SDLK_AUDIONEXT,
    Audioprev = SDLK_AUDIOPREV,
    Audiostop = SDLK_AUDIOSTOP,
    Audioplay = SDLK_AUDIOPLAY,
    Audiomute = SDLK_AUDIOMUTE,
    Mediaselect = SDLK_MEDIASELECT,
    Www = SDLK_WWW,
    Mail = SDLK_MAIL,
    Calculator = SDLK_CALCULATOR,
    Computer = SDLK_COMPUTER,
    Ac_search = SDLK_AC_SEARCH,
    Ac_home = SDLK_AC_HOME,
    Ac_back = SDLK_AC_BACK,
    Ac_forward = SDLK_AC_FORWARD,
    Ac_stop = SDLK_AC_STOP,
    Ac_refresh = SDLK_AC_REFRESH,
    Ac_bookmarks = SDLK_AC_BOOKMARKS,
    Brightnessdown = SDLK_BRIGHTNESSDOWN,
    Brightnessup = SDLK_BRIGHTNESSUP,
    Displayswitch = SDLK_DISPLAYSWITCH,
    Kbdillumtoggle = SDLK_KBDILLUMTOGGLE,
    Kbdillumdown = SDLK_KBDILLUMDOWN,
    Kbdillumup = SDLK_KBDILLUMUP,
    Eject = SDLK_EJECT,
    Sleep = SDLK_SLEEP,
    App1 = SDLK_APP1,
    App2 = SDLK_APP2,
    Audiorewind = SDLK_AUDIOREWIND,
    Audiofastforward = SDLK_AUDIOFASTFORWARD
};