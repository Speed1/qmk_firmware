// Copyright 2021 weteor | 2022 Conor Burns (@Conor-Burns)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _ALPHA_COLEMAK = 0,
//    _ALPHA_QWERTY,
    _SYM,
    _NAV,
    _NUM,
//    _CFG,
};

// start SM Tap Dance (sm_td or smtd for short) user library for QMK

enum custom_keycodes {
    CKC_R = SAFE_RANGE,
    CKC_I,
    CKC_NA,
    CKC_NR,
    CKC_NS,
    CKC_NT,
    CKC_NZ,
};

#include "sm_td.h"

// Process tap dance records
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t smtd_last_pressed_keycode = KC_NO;
    if (record->event.pressed) {
        smtd_last_pressed_keycode = keycode;
    } else if (keycode == smtd_last_pressed_keycode) {
        smtd_last_pressed_keycode = KC_NO;
    }
    if (!process_smtd(keycode, record)) {
        return false;
    }
    return true;
}

smtd_resolution on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) {
    switch (keycode) {
        // Modifier keys
        SMTD_MT(KC_A, KC_LEFT_CTRL)
        case CKC_R: {
            switch (action) {
                case SMTD_ACTION_TOUCH:
                    return SMTD_RESOLUTION_UNCERTAIN;
                case SMTD_ACTION_TAP:
                    if (is_caps_word_on()) {
                        tap_code16(LSFT(KC_R)); // Capital R when caps word is on
                    } else {
                        tap_code(KC_R);      // Normal r otherwise
                    }
                    return SMTD_RESOLUTION_DETERMINED;
                case SMTD_ACTION_HOLD:
                    switch (tap_count) {
                        case 0:
                        case 1:
                            register_mods(MOD_BIT(KC_LEFT_ALT) | MOD_BIT(KC_LEFT_CTRL) | MOD_BIT(KC_LEFT_GUI));
                            break;
                    }
                    return SMTD_RESOLUTION_DETERMINED;
                case SMTD_ACTION_RELEASE:
                    switch (tap_count) {
                        case 0:
                        case 1:
                            unregister_mods(MOD_BIT(KC_LEFT_ALT) | MOD_BIT(KC_LEFT_CTRL) | MOD_BIT(KC_LEFT_GUI));
                            break;
                    }
                    return SMTD_RESOLUTION_DETERMINED;
            }
        }
        SMTD_MT(KC_S, KC_LEFT_GUI)
        SMTD_MT(KC_T, KC_LSFT)
        SMTD_MT(KC_X, KC_LEFT_ALT)
        SMTD_MT(KC_N, KC_RSFT)
        SMTD_MT(KC_E, KC_RIGHT_GUI)
        case CKC_I: {
            switch (action) {
                case SMTD_ACTION_TOUCH:
                    return SMTD_RESOLUTION_UNCERTAIN;
                case SMTD_ACTION_TAP:
                    if (is_caps_word_on()) {
                        tap_code16(LSFT(KC_I)); // Capital I when caps word is on
                    } else {
                        tap_code(KC_I);      // Normal i otherwise
                    }
                    return SMTD_RESOLUTION_DETERMINED;
                case SMTD_ACTION_HOLD:
                    switch (tap_count) {
                        case 0:
                        case 1:
                            register_mods(MOD_BIT(KC_LEFT_ALT) | MOD_BIT(KC_LEFT_CTRL) | MOD_BIT(KC_LEFT_GUI));
                            break;
                    }
                    return SMTD_RESOLUTION_DETERMINED;
                case SMTD_ACTION_RELEASE:
                    switch (tap_count) {
                        case 0:
                        case 1:
                            unregister_mods(MOD_BIT(KC_LEFT_ALT) | MOD_BIT(KC_LEFT_CTRL) | MOD_BIT(KC_LEFT_GUI));
                            break;
                    }
                    return SMTD_RESOLUTION_DETERMINED;
            }
        }
        SMTD_MT(KC_O, KC_RIGHT_CTRL)
        case KC_DOT: {
            switch (action) {
                case SMTD_ACTION_TOUCH:
                    return SMTD_RESOLUTION_UNCERTAIN;
                case SMTD_ACTION_TAP:
                    if (tap_count == 0) {
                        tap_code16(KC_DOT);
                    } else if (tap_count == 1) {
                        // Double-tap: ':'
                        tap_code16(LSFT(KC_SCLN));
                    } else {
                        // triple-tap or more: '...'
                        tap_code16(KC_DOT);
                        tap_code16(KC_DOT);
                        tap_code16(KC_DOT);
                    }
                    return SMTD_RESOLUTION_DETERMINED;
                case SMTD_ACTION_HOLD:
                    switch (tap_count) {
                        case 0:
                        case 1:
                            register_mods(MOD_BIT(KC_RIGHT_ALT));
                            send_keyboard_report();
                            break;
                    }
                    return SMTD_RESOLUTION_DETERMINED;
                case SMTD_ACTION_RELEASE:
                    switch (tap_count) {
                        case 0:
                        case 1:
                            unregister_mods(MOD_BIT(KC_RIGHT_ALT));
                            send_keyboard_report();
                            break;
                    }
                    return SMTD_RESOLUTION_DETERMINED;
            }
        }
        case KC_COMMA: {
            switch (action) {
                case SMTD_ACTION_TOUCH:
                    return SMTD_RESOLUTION_UNCERTAIN;
                case SMTD_ACTION_TAP:
                    if (tap_count == 0) {
                        tap_code16(KC_COMMA);
                    } else {
                        // Double-tap: ';'
                        tap_code16(KC_SCLN);
                    }
                    return SMTD_RESOLUTION_DETERMINED;
                case SMTD_ACTION_HOLD:
                case SMTD_ACTION_RELEASE:
                    return SMTD_RESOLUTION_DETERMINED;
            }
        }
        // Num layer copy/paste
        SMTD_MT_ON_MKEY(CKC_NA, RGUI(KC_A), KC_LEFT_CTRL)
        SMTD_MT_ON_MKEY(CKC_NR, RGUI(KC_X), KC_LEFT_ALT)
        SMTD_MT_ON_MKEY(CKC_NS, RGUI(KC_C), KC_LEFT_GUI)
        SMTD_MT_ON_MKEY(CKC_NT, RGUI(KC_V), KC_LSFT)
        // select entire row
        case CKC_NZ: {
            switch (action) {
                case SMTD_ACTION_TOUCH:
                    return SMTD_RESOLUTION_UNCERTAIN;
                case SMTD_ACTION_TAP:
                    tap_code16(KC_END);
                    tap_code16(LSFT(KC_HOME));
                    return SMTD_RESOLUTION_DETERMINED;
                default:
                    return SMTD_RESOLUTION_UNHANDLED;
            }
        }
        // Layer toggles
        //SMTD_LT(KC_ESC, _CFG)
        SMTD_LT(KC_SPC, _NUM)
        SMTD_LT(KC_TAB, _NAV)
        SMTD_LT(KC_ENT, _SYM)
    }

    return SMTD_RESOLUTION_UNHANDLED;
}

uint32_t get_smtd_timeout(uint16_t keycode, smtd_timeout timeout) {
    switch (keycode) {
        case KC_SPC:
            if (timeout == SMTD_TIMEOUT_TAP) return 350;
        case KC_DOT:
        case KC_COMMA:
            if (timeout == SMTD_TIMEOUT_SEQUENCE) return 200; // longer double-tap window
    }

    return get_smtd_timeout_default(timeout);
}

bool smtd_feature_enabled(uint16_t keycode, smtd_feature feature) {
    if (feature == SMTD_FEATURE_AGGREGATE_TAPS) {
        switch (keycode) {
            case KC_DOT:
            case KC_COMMA:
                return true; // Wait for sequence end to decide single vs double tap
        }
    }
    return false;
}
// end SM Tap Dance (sm_td or smtd for short) user library for QMK

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
const uint16_t PROGMEM combo_caps_word[]   = {KC_T, KC_N, COMBO_END};
const uint16_t PROGMEM combo_enter[]       = {KC_S, KC_T, COMBO_END};
const uint16_t PROGMEM combo_backspace[]   = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM combo_esc[]      = {KC_X, KC_D, COMBO_END};

// German umlaut combos
const uint16_t PROGMEM combo_ae[] = {KC_A, CKC_R, COMBO_END};
const uint16_t PROGMEM combo_oe[] = {CKC_I, KC_O, COMBO_END};
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
        KC_A, CKC_R, KC_S, KC_T, KC_G,                                                                         KC_M, KC_N, KC_E, CKC_I, KC_O,
        KC_Z, KC_X, KC_C, KC_D, KC_V,                                                                           KC_K,    KC_H,    KC_COMMA, KC_DOT,  KC_SLASH,
                KC_SPC, KC_TAB,                                                                             KC_BSPC, KC_ENT
    ),
/*    [_ALPHA_QWERTY] = LAYOUT_split_3x5_3(
        KC_Q,         KC_W,    KC_E,    KC_R,    KC_T,                                                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        LCTL_T(KC_A), LALT_T(KC_S), LGUI_T(KC_D), LSFT_T(KC_F), KC_G,                                KC_H, RSFT_T(KC_J), RGUI_T(KC_K), RALT_T(KC_L), RCTL_T(KC_SCLN),
        KC_Z, KC_X,    KC_C,    KC_V,    KC_B,                                                                 KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
             LT(_CFG,KC_ESCAPE), LT(_NUM,KC_SPC), LT(_NAV, KC_TAB),                                      KC_BSPC, LT(_SYM, KC_ENT), KC_DEL
    ),*/
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
        KC_MUTE, KC_VOLD, LGUI(KC_F), KC_VOLU, LGUI(KC_I),                                                     LSFT(KC_EQUAL),  KC_7,  KC_8,  KC_9,  LSFT(KC_RBRC),
        CKC_NA, CKC_NR, CKC_NS, CKC_NT, RGUI(KC_Z),                                                               KC_EQUAL,  KC_4,  KC_5,  KC_6, KC_RBRC,
        CKC_NZ, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX,                                                         KC_BACKSLASH,  KC_1,  KC_2,  KC_3, KC_DOT,
                  XXXXXXX, XXXXXXX,                                                                           KC_BSPC, KC_0
    ),
 /*       [_CFG] = LAYOUT_split_3x5_3(
        RALT(RGUI(RCTL(KC_Q))), XXXXXXX, XXXXXXX, RALT(RGUI(RCTL(KC_P))), RALT(RGUI(RCTL(KC_B))),                                     XXXXXXX, XXXXXXX, KC_LBRC,DF(_ALPHA_COLEMAK), DF(_ALPHA_QWERTY),
        RALT(RGUI(RCTL(KC_A))), XXXXXXX, RALT(RGUI(RCTL(KC_S))), RALT(RGUI(RCTL(KC_T))), RALT(RGUI(RCTL(KC_G))),                 XXXXXXX, RSFT_T(XXXXXXX), XXXXXXX, XXXXXXX, KC_SCLN,
        RALT(RGUI(RCTL(KC_Y))), XXXXXXX, RALT(RGUI(RCTL(KC_C))),  RALT(RGUI(RCTL(KC_D))), RALT(RGUI(RCTL(KC_V))),                XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                XXXXXXX, XXXXXXX, XXXXXXX,                                                                                                                     XXXXXXX, XXXXXXX, QK_BOOT
    )*/
    // clang-format on
};