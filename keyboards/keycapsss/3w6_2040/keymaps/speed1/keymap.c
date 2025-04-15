// Copyright 2021 weteor | 2022 Conor Burns (@Conor-Burns)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_german_mac_iso.h"

enum layers {
    _ALPHA_COLEMAK = 0,
    _ALPHA_QWERTY,
    _SYM,
    _NAV,
    _NUM,
    _CFG,
};

// start SM Tap Dance (sm_td or smtd for short) user library for QMK

enum custom_keycodes {
    SMTD_KEYCODES_BEGIN = SAFE_RANGE,
    CKC_A, // reads as C(ustom) + KC_A, but you may give any name here
    CKC_R,
    CKC_S,
    CKC_T,
    CKC_N,
    CKC_E,
    CKC_I,
    CKC_O,
    CKC_NA,
    CKC_NR,
    CKC_NS,
    CKC_NT,
    CKC_ESC,
    CKC_SPC,
    CKC_TAB,
    CKC_ENT,
    SMTD_KEYCODES_END,
};

#include "sm_td.h"

// Process tap dance records
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_smtd(keycode, record)) {
        return false;
    }
    return true;
}

void on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) {
    switch (keycode) {
        // Modifier keys
        SMTD_MT(CKC_A, KC_A, KC_LEFT_CTRL)
        case CKC_R: {
            switch (action) {
                case SMTD_ACTION_TOUCH:
                    break;
                case SMTD_ACTION_TAP:
                    tap_code(KC_R);
                    break;
                case SMTD_ACTION_HOLD:
                    switch (tap_count) {
                        case 0:
                        case 1:
                            register_mods(MOD_BIT(KC_LEFT_ALT) | MOD_BIT(KC_LEFT_CTRL) | MOD_BIT(KC_LEFT_GUI));
                            break;
                    }
                    break;
                case SMTD_ACTION_RELEASE:
                    switch (tap_count) {
                        case 0:
                        case 1:
                            unregister_mods(MOD_BIT(KC_LEFT_ALT) | MOD_BIT(KC_LEFT_CTRL) | MOD_BIT(KC_LEFT_GUI));
                            break;
                    }
                    break;
            }
            break;
        }
        SMTD_MT(CKC_S, KC_S, KC_LEFT_GUI)
        SMTD_MT(CKC_T, KC_T, KC_LSFT)
        SMTD_MT(CKC_N, KC_N, KC_RSFT)
        SMTD_MT(CKC_E, KC_E, KC_RIGHT_GUI)
        SMTD_MT(CKC_I, KC_I, KC_RIGHT_ALT)
        SMTD_MT(CKC_O, KC_O, KC_RIGHT_CTRL)
        // Num layer copy/paste
        SMTD_MT(CKC_NA, RGUI(KC_A), KC_LEFT_CTRL)
        SMTD_MT(CKC_NR, RGUI(KC_X), KC_LEFT_ALT)
        SMTD_MT(CKC_NS, RGUI(KC_C), KC_LEFT_GUI)
        SMTD_MT(CKC_NT, RGUI(KC_V), KC_LSFT)
        // Layer toggles
        SMTD_LT(CKC_ESC, KC_ESC, _CFG)
        SMTD_LT(CKC_SPC, KC_SPC, _NUM)
        SMTD_LT(CKC_TAB, KC_TAB, _NAV)
        SMTD_LT(CKC_ENT, KC_ENT, _SYM)
    }
}

// end SM Tap Dance (sm_td or smtd for short) user library for QMK

// System combos
const uint16_t PROGMEM combo_lock_device[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM combo_close_app[]   = {KC_W, KC_P, COMBO_END};
const uint16_t PROGMEM combo_screenshot[]  = {KC_C, KC_D, COMBO_END};

// Text editing combos
const uint16_t PROGMEM combo_caps_lock[]   = {KC_P, KC_L, COMBO_END};
const uint16_t PROGMEM combo_caps_word[]   = {CKC_T, CKC_N, COMBO_END};
const uint16_t PROGMEM combo_enter[]       = {CKC_S, CKC_T, COMBO_END};
const uint16_t PROGMEM combo_backspace[]   = {KC_F, KC_P, COMBO_END};

// German umlaut combos
const uint16_t PROGMEM combo_ae[] = {CKC_A, CKC_R, COMBO_END};
const uint16_t PROGMEM combo_oe[] = {CKC_I, CKC_O, COMBO_END};
const uint16_t PROGMEM combo_ue[] = {KC_U, KC_Z, COMBO_END};

combo_t key_combos[] = {
    // System combos
    COMBO(combo_lock_device, LCTL(RGUI(KC_Q))),
    COMBO(combo_close_app, RGUI(KC_Q)),
    COMBO(combo_screenshot, LGUI(LSFT(KC_4))),
    
    // Text editing combos
    COMBO(combo_caps_lock, KC_CAPS),
    COMBO(combo_caps_word, QK_CAPS_WORD_TOGGLE),
    COMBO(combo_enter, KC_ENT),
    COMBO(combo_backspace, KC_BSPC),
    
    // German umlaut combos
    COMBO(combo_ae, KC_QUOT),
    COMBO(combo_oe, KC_SCLN),
    COMBO(combo_ue, KC_LBRC),
};

// end Combos

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off

    [_ALPHA_COLEMAK] = LAYOUT_split_3x5_3(
        KC_Q,     KC_W,    KC_F,    KC_P,    KC_B,                                                             KC_J,    KC_L,    KC_U,    KC_Z,    KC_MINS,
        CKC_A, CKC_R, CKC_S, CKC_T, KC_G,                                                                     KC_M, CKC_N, CKC_E, CKC_I, CKC_O,
        KC_Y, KC_X, KC_C, KC_D, KC_V,                                                                           KC_K,    KC_H,    KC_COMMA, KC_DOT,  KC_SLASH,
                CKC_ESC, CKC_SPC, CKC_TAB,                                                                         KC_BSPC, CKC_ENT, KC_DEL
    ),
    [_ALPHA_QWERTY] = LAYOUT_split_3x5_3(
        KC_Q,         KC_W,    KC_E,    KC_R,    KC_T,                                                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        LCTL_T(KC_A), LALT_T(KC_S), LGUI_T(KC_D), LSFT_T(KC_F), KC_G,                                KC_H, RSFT_T(KC_J), RGUI_T(KC_K), RALT_T(KC_L), RCTL_T(KC_SCLN),
        KC_Z, KC_X,    KC_C,    KC_V,    KC_B,                                                                 KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
             LT(_CFG,KC_ESCAPE), LT(_NUM,KC_SPC), LT(_NAV, KC_TAB),                                      KC_BSPC, LT(_SYM, KC_ENT), KC_DEL
    ),
    [_SYM] = LAYOUT_split_3x5_3(
        RALT(KC_8) , LSFT(KC_6),   LSFT(KC_RBRC),  LSFT(KC_2), XXXXXXX,                          RSFT(KC_EQUAL), KC_NONUS_BACKSLASH, KC_GRAVE, RSFT(KC_GRAVE), XXXXXXX,
        RALT(KC_5), LSFT(KC_4), RALT(KC_L), LSFT(KC_7), KC_RBRC,                                   RSFT(KC_NONUS_HASH), RALT(DE_N), XXXXXXX, XXXXXXX, XXXXXXX,
        LSFT(KC_MINUS), LSFT(KC_1), RSFT(KC_5), KC_NONUS_HASH, RALT(KC_7),                      KC_EQUAL, XXXXXXX, KC_MINS, XXXXXXX, XXXXXXX,
                LSFT(KC_8), LSFT(KC_9), LSFT(KC_SLASH),                                                       XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [_NAV] = LAYOUT_split_3x5_3(
        XXXXXXX,  KC_F7, KC_F8, KC_F9, KC_F10,                                                                 XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,
        LCTL_T(XXXXXXX), RALT_T(KC_F4),  LGUI_T(KC_F5),  LSFT_T(KC_F6),  KC_F11,                     KC_HOME, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT,
        XXXXXXX,  KC_F1,  KC_F2,  KC_F3,  KC_F12,                                                              XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END,
                  XXXXXXX, XXXXXXX, XXXXXXX,                                                                         XXXXXXX, MO(_CFG), XXXXXXX
    ),
     [_NUM] = LAYOUT_split_3x5_3(
        KC_MUTE, KC_VOLD, LGUI(KC_F), KC_VOLU, XXXXXXX,                                                     KC_RBRC,  KC_7,  KC_8,  KC_9,  RALT(KC_9),
        CKC_NA, CKC_NR, CKC_NS, CKC_NT, RGUI(KC_Y),                                                               RSFT(KC_0),  KC_4,  KC_5,  KC_6, RALT(KC_6),
        XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX,                                                         RSFT(RALT(DE_7)),  KC_1,  KC_2,  KC_3, KC_DOT,
                  XXXXXXX, XXXXXXX, XXXXXXX,                                                                           KC_BSPC, KC_0, KC_PENT
    ),
        [_CFG] = LAYOUT_split_3x5_3(
        RALT(RGUI(RCTL(KC_Q))), XXXXXXX, XXXXXXX, RALT(RGUI(RCTL(KC_P))), RALT(RGUI(RCTL(KC_B))),                                     XXXXXXX, XXXXXXX, KC_LBRC,DF(_ALPHA_COLEMAK), DF(_ALPHA_QWERTY),
        RALT(RGUI(RCTL(KC_A))), XXXXXXX, RALT(RGUI(RCTL(KC_S))), RALT(RGUI(RCTL(KC_T))), RALT(RGUI(RCTL(KC_G))),                 XXXXXXX, RSFT_T(XXXXXXX), XXXXXXX, XXXXXXX, KC_SCLN,
        RALT(RGUI(RCTL(KC_Y))), XXXXXXX, RALT(RGUI(RCTL(KC_C))),  RALT(RGUI(RCTL(KC_D))), RALT(RGUI(RCTL(KC_V))),                XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                XXXXXXX, XXXXXXX, XXXXXXX,                                                                                                                     XXXXXXX, XXXXXXX, QK_BOOT
    )
    // clang-format on
};
