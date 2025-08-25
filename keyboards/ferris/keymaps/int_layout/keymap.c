// Copyright 2021 weteor | 2022 Conor Burns (@Conor-Burns)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _ALPHA_COLEMAK = 0,
    _SYM,
    _NAV,
    _NUM,
};

enum custom_keycodes {
    SEL_ROW = SAFE_RANGE,
};

// Process custom keycodes (standard QMK)
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SEL_ROW:
            if (record->event.pressed) {
                tap_code16(KC_END);
                tap_code16(LSFT(KC_HOME));
            }
            return false;
    }
    return true;
}

// Caps Word
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        case KC_SPC:
            return false;

        default:
            return false;  // Deactivate Caps Word.
    }
}

// Home row mods using standard QMK MT() macros
#define HR_A MT(MOD_LCTL, KC_A)
#define HR_R MT(MOD_RALT | MOD_RCTL | MOD_RGUI, KC_R)  // Hyper key (Alt + Ctrl + Gui)
#define HR_S MT(MOD_LGUI, KC_S)
#define HR_T MT(MOD_LSFT, KC_T)
#define HR_N MT(MOD_RSFT, KC_N)
#define HR_E MT(MOD_RGUI, KC_E)
#define HR_I MT(MOD_RALT | MOD_RCTL | MOD_RGUI, KC_I)  // Hyper key (Alt + Ctrl + Gui)
#define HR_O MT(MOD_RCTL, KC_O)

// Additional mod-taps for bottom row
#define HR_X MT(MOD_LALT, KC_X)     // Alt on hold
#define HR_DOT MT(MOD_RALT, KC_DOT) // Alt on hold

// Layer taps using standard QMK LT() macros
#define LT_SPC LT(_NUM, KC_SPC)
#define LT_TAB LT(_NAV, KC_TAB)
#define LT_ENT LT(_SYM, KC_ENT)

// Standard QMK home row mods and layer taps implementation

enum combo_events {
    // System combos
    COMBO_LOCK_DEVICE,
    COMBO_CLOSE_APP,
    COMBO_SCREENSHOT,
    
    // Text editing combos
    COMBO_CAPS_LOCK,
    COMBO_CAPS_WORD,
    COMBO_ENTER,
    COMBO_BACKSPACE,
    COMBO_ESC,
    
    // German umlaut combos
    COMBO_AE,
    COMBO_OE,
    COMBO_UE,
    COMBO_SS,
    
    COMBO_LENGTH
};

// System combos
const uint16_t PROGMEM combo_lock_device[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM combo_close_app[]   = {KC_W, KC_P, COMBO_END};
const uint16_t PROGMEM combo_screenshot[]  = {KC_C, KC_D, COMBO_END};

// Text editing combos
const uint16_t PROGMEM combo_caps_lock[]   = {KC_P, KC_L, COMBO_END};
const uint16_t PROGMEM combo_caps_word[]   = {HR_T, HR_N, COMBO_END};
const uint16_t PROGMEM combo_enter[]       = {HR_S, HR_T, COMBO_END};
const uint16_t PROGMEM combo_backspace[]   = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM combo_esc[]      = {HR_X, KC_D, COMBO_END};

// German umlaut combos
const uint16_t PROGMEM combo_ae[] = {HR_A, HR_R, COMBO_END};
const uint16_t PROGMEM combo_oe[] = {HR_I, HR_O, COMBO_END};
const uint16_t PROGMEM combo_ue[] = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM combo_ss[] = {KC_W, KC_F, COMBO_END};

/* OLD COMBO IMPLEMENTATION - KEEP COMMENTED FOR REFERENCE
combo_t key_combos[] = {
    // System combos
    COMBO(combo_lock_device, LCTL(RGUI(KC_Q))),
    COMBO(combo_close_app, RGUI(KC_Q)),
    COMBO(combo_screenshot, LGUI(LSFT(KC_4))),
    
    // Text editing comboss
    COMBO(combo_caps_lock, KC_CAPS),
    COMBO(combo_caps_word, QK_CAPS_WORD_TOGGLE),
    COMBO(combo_enter, KC_ENT),
    COMBO(combo_backspace, KC_BSPC),
    
    // German umlaut combos
    COMBO(combo_ae, KC_QUOT),
    COMBO(combo_oe, KC_SCLN),
    COMBO(combo_ue, KC_LBRC),
};
*/

combo_t key_combos[COMBO_LENGTH] = {
    [COMBO_LOCK_DEVICE] = COMBO_ACTION(combo_lock_device),
    [COMBO_CLOSE_APP] = COMBO_ACTION(combo_close_app),
    [COMBO_SCREENSHOT] = COMBO_ACTION(combo_screenshot),
    [COMBO_CAPS_LOCK] = COMBO_ACTION(combo_caps_lock),
    [COMBO_CAPS_WORD] = COMBO_ACTION(combo_caps_word),
    [COMBO_ENTER] = COMBO_ACTION(combo_enter),
    [COMBO_BACKSPACE] = COMBO_ACTION(combo_backspace),
    [COMBO_ESC] = COMBO_ACTION(combo_esc),
    [COMBO_AE] = COMBO_ACTION(combo_ae),
    [COMBO_OE] = COMBO_ACTION(combo_oe),
    [COMBO_UE] = COMBO_ACTION(combo_ue),
    [COMBO_SS] = COMBO_ACTION(combo_ss),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch(combo_index) {
        case COMBO_LOCK_DEVICE:
            if (pressed) {
                tap_code16(LCTL(RGUI(KC_Q)));
            }
            break;
        case COMBO_CLOSE_APP:
            if (pressed) {
                tap_code16(RGUI(KC_Q));
            }
            break;
        case COMBO_SCREENSHOT:
            if (pressed) {
                tap_code16(LGUI(LSFT(KC_4)));
            }
            break;
        case COMBO_CAPS_LOCK:
            if (pressed) {
                tap_code16(KC_CAPS);
            }
            break;
        case COMBO_CAPS_WORD:
            if (pressed) {
                caps_word_toggle();
            }
            break;
        case COMBO_ENTER:
            if (pressed) {
                tap_code16(KC_ENT);
            }
            break;
        case COMBO_BACKSPACE:
            if (pressed) {
                tap_code16(KC_BSPC);
            }
            break;
        case COMBO_ESC:
            if (pressed) {
                tap_code16(KC_ESC);
            }
            break;
        case COMBO_AE:
            if (pressed) {
                // Store current modifier state and check if shift was held
                uint8_t mods = get_mods();
                bool shift_held = mods & MOD_MASK_SHIFT;
                // Clear all modifiers so the dead key sequence works cleanly
                // The LALT(KC_U) dead key sequence gets interfered with by active modifiers
                clear_mods();
                // Send the dead key sequence for umlaut (Option+U on Mac, Alt+U elsewhere)
                tap_code16(LALT(KC_U));
                // Send the vowel (uppercase if shift was originally held)
                if (shift_held) {
                    tap_code16(LSFT(KC_A));  // Ä
                } else {
                    tap_code(KC_A);          // ä
                }
                // Restore the original modifier state
                set_mods(mods);
            }
            break;
        case COMBO_OE:
            if (pressed) {
                // Store current modifier state and check if shift was held
                uint8_t mods = get_mods();
                bool shift_held = mods & MOD_MASK_SHIFT;
                // Clear all modifiers so the dead key sequence works cleanly
                clear_mods();
                // Send the dead key sequence for umlaut
                tap_code16(LALT(KC_U));
                // Send the vowel (uppercase if shift was originally held)
                if (shift_held) {
                    tap_code16(LSFT(KC_O));  // Ö
                } else {
                    tap_code(KC_O);          // ö
                }
                // Restore the original modifier state
                set_mods(mods);
            }
            break;
        case COMBO_UE:
            if (pressed) {
                // Store current modifier state and check if shift was held
                uint8_t mods = get_mods();
                bool shift_held = mods & MOD_MASK_SHIFT;
                // Clear all modifiers so the dead key sequence works cleanly
                clear_mods();
                // Send the dead key sequence for umlaut
                tap_code16(LALT(KC_U));
                // Send the vowel (uppercase if shift was originally held)
                if (shift_held) {
                    tap_code16(LSFT(KC_U));  // Ü
                } else {
                    tap_code(KC_U);          // ü
                }
                // Restore the original modifier state
                set_mods(mods);
            }
            break;
        case COMBO_SS:
            if (pressed) {
                tap_code16(LALT(KC_S));
            }
            break;
    }
}

// end Combos

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off

    [_ALPHA_COLEMAK] = LAYOUT_split_3x5_2(
        KC_Q,     KC_W,    KC_F,    KC_P,    KC_B,                                                             KC_J,    KC_L,    KC_U,    KC_Y,    KC_MINS,
        HR_A,     HR_R,    HR_S,    HR_T,    KC_G,                                                             KC_M,    HR_N,    HR_E,    HR_I,    HR_O,
        KC_Z,     HR_X,    KC_C,    KC_D,    KC_V,                                                             KC_K,    KC_H,    KC_COMMA, HR_DOT,    KC_SLASH,
                LT_SPC, LT_TAB,                                                                             KC_BSPC, LT_ENT
    ),
    [_SYM] = LAYOUT_split_3x5_2(
        LSFT(KC_LBRC) , LSFT(KC_7),   LSFT(KC_8),  LSFT(KC_QUOT), LSFT(KC_EQUAL),                          KC_GRAVE, LSFT(KC_6), LSFT(KC_COMMA), LSFT(KC_DOT), XXXXXXX,
        KC_LBRC, LSFT(KC_4), LSFT(KC_2), KC_SLASH, KC_BACKSLASH,                                   KC_QUOTE, LSFT(KC_GRAVE), KC_SCLN, LSFT(KC_SCLN), XXXXXXX,
        LSFT(KC_SLASH), LSFT(KC_1), RSFT(KC_5), LSFT(KC_3), LSFT(KC_BACKSLASH),                      RALT(KC_E), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                LSFT(KC_9), LSFT(KC_0),                                                        XXXXXXX, XXXXXXX
    ),
    [_NAV] = LAYOUT_split_3x5_2(
        KC_ESC,  KC_F7, KC_F8, KC_F9, KC_F10,                                                                 QK_BOOT, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,
        LCTL_T(XXXXXXX), RALT_T(KC_F4),  LGUI_T(KC_F5),  LSFT_T(KC_F6),  KC_F11,                     KC_HOME, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT,
        XXXXXXX,  KC_F1,  KC_F2,  KC_F3,  KC_F12,                                                              XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END,
                   XXXXXXX, XXXXXXX,                                                                         KC_DEL, XXXXXXX
    ),
     [_NUM] = LAYOUT_split_3x5_2(
        KC_MUTE, KC_VOLD, LGUI(KC_F), KC_VOLU, XXXXXXX,                                                     LSFT(KC_EQUAL),  KC_7,  KC_8,  KC_9,  LSFT(KC_RBRC),
        RGUI(KC_A), RGUI(KC_X), RGUI(KC_C), RGUI(KC_V), RGUI(KC_Z),                                         KC_EQUAL,        KC_4,  KC_5,  KC_6,  KC_RBRC,
        SEL_ROW, KC_MPRV, KC_MPLY,    KC_MNXT, XXXXXXX,                                                     KC_BACKSLASH,   KC_1,  KC_2,  KC_3,  KC_DOT,
                  XXXXXXX, XXXXXXX,                                                                           KC_BSPC, KC_0
    ),
};