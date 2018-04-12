/* Copyright 2017 Colin T.A. Gray
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "xd75.h"
#include "rgblight.h"
#include <util/delay.h>
#include "keymap.h"

enum my_keycodes {
    // sticky keys
    STK_CTL = SAFE_RANGE,
    STK_ALT,
    STK_SHFT,
    STK_GUI,
    HYPER,

    // enter and reset
    ENT_SET,

    // layers
    GOTO_CM,
    GOTO_QW,
    GOTO_FN,

    // backlight toggle
    BKLT,

    // baby proofing
    LK_ANY,
    LK_2,
    LK_3,
    LK_1,

    // tap/hold buttons
    TH_PLAY,  // play / mute
    TH_PGUP,  // page up / home
    TH_PGDN,  // page down / end
    TH_1,     // 1 / F1
    TH_2,     // ...
    TH_3,
    TH_4,
    TH_5,
    TH_6,
    TH_7,
    TH_8,
    TH_9,
    TH_0,     // 0 / F10                   TH_LAST

    // normal macros
    MM_1,
    MM_2,
    MM_3,
    MM_4,
    MM_5,
    MM_6,
};

#define TH_EVENTS_COUNT 13
#define TH_FIRST TH_PLAY
#define TH_LAST TH_0
#define GOTO_LK LK_ANY

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* COLEMAK
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | `   ~  | 1   !  | 2   @  | 3   #  | 4   $  | 5   %  | KC_DEL | 6   ^  | 7   &  | 8   *  | 9   (  | 0   )  | -   _  | =   +  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | TAB    | Q      | W      | F      | P      | G      | BKSP   | J      | L      | U      | Y      | ;   :  | [   {  | ]   }  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------+--------|
 * |        | SHIFT  | A      | R      | S      | T      | D      | ENTER  | H      | N      | E      | I      | O      | '   "  | \   |  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------+--------+--------|
 * |        | CTRL   | Z      | X      | C      | V      | B      | GOTO_FN| K      | M      | ,   <  | .   >  | /   ?  | UP     | HYPER  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------|
 * |        | PLAY   |        | ALT    |        | GUI    |        |          SPACE           | PG. UP |PG. DOWN| LEFT   | DOWN   | RIGHT  |
 * '-----------/MUTE-----------------------------------------------------------------------------/HOME-----/END---------------------------'
 */

  [LAYER_COLEMAK] = KEYMAP(
     KC_ESC , KC_GRV , TH_1   , TH_2   , TH_3   , TH_4   , TH_5   , KC_DEL , TH_6   , TH_7   , TH_8   , TH_9   , TH_0   , KC_MINS, KC_EQL ,
      ___   , KC_TAB , KC_Q   , KC_W   , KC_F   , KC_P   , KC_G   , KC_BSPC, KC_J   , KC_L   , KC_U   , KC_Y   , KC_SCLN, KC_LBRC, KC_RBRC,
      ___   ,STK_SHFT, KC_A   , KC_R   , KC_S   , KC_T   , KC_D   , KC_ENT , KC_H   , KC_N   , KC_E   , KC_I   , KC_O   , KC_QUOT, KC_BSLS,
      ___   , STK_CTL, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , GOTO_FN, KC_K   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_UP  , HYPER  ,
      ___   , TH_PLAY,  ___   , STK_ALT,  ___   , STK_GUI,  ___   ,  ___   , KC_SPC  ,  ___   , TH_PGUP, TH_PGDN, KC_LEFT, KC_DOWN, KC_RGHT
  ),

/* QWERTY - Falls through to colemak for function keys, doesn't use sticky keys
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        |        | Q      | W      | E      | R      | T      |        | Y      | U      | I      | O      | P      |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------+--------|
 * |        | SHIFT  | A      | S      | D      | F      | G      |        | H      | J      | K      | L      | ;      |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------+--------+--------|
 * |        | CTRL   | Z      | X      | C      | V      | B      | GOTO_FN| N      | M      |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        | ALT    |        | GUI    |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [LAYER_QWERTY] = KEYMAP(
    ________,________,________,________,________,________,________,________,________,________,________,________,________,________,________,
    ________,________, KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,________, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   ,________,________,
    ________, KC_LSFT, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,________, KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN,________,________,
    ________, KC_LCTL, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , GOTO_FN, KC_N   , KC_M   ,________,________,________,________,________,
    ________,________,________, KC_LALT ,_______, KC_LGUI,________,________,________,________,________,________,________,________,________
  ),

/* FN LAYER - change layouts, media keys, function keys, reset
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | KC_SLEP| RESET  |   F1   |   F2   |   F3   |   F4   |   F5   |        |   F6   |   F7   |   F8   |   F9   |   F10  |   F11  |   F12  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        |        | QWERTY | MM_2   |        |        |        |        | MM_1   |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        |        |        |        | MM_5   | MM_4   |        | RESET  |        | MM_3   |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        |        |        | COLEMAK|        | VOL-   | GOTO_FN| VOL+   |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |          GOTO_LK         |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [LAYER_FN] = KEYMAP(
     KC_SLEP, RESET  , KC_F1  , KC_F2  , KC_F3  , KC_F4  ,  KC_F5 ,  ___   , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 ,
      ___   ,  ___   , GOTO_QW, MM_2   ,  ___   ,  ___   ,  ___   ,  ___   , MM_1   ,  ___   ,  ___   ,  ___   ,  ___   ,  ___   ,  ___   ,
      ___   , KC_LSFT,  ___   ,  ___   , MM_5   , MM_4   , KC_MRWD, ENT_SET, KC_MFFD, MM_3   , MM_6   ,  ___   ,  ___   ,  ___   ,  ___   ,
      ___   , KC_LCTL,  ___   ,  ___   , GOTO_CM,  ___   , KC_VOLD, GOTO_FN, KC_VOLU,  ___   ,  ___   ,  ___   ,  ___   ,  ___   , BKLT   ,
      ___   ,  ___   ,  ___   , KC_LALT,  ___   , KC_LGUI,  ___   ,  ___   , GOTO_LK,  ___   ,  ___   ,  ___   ,  ___   ,  ___   ,  ___
  ),

/* LOCK LAYER - baby proof layer, press keys 1/2/3 in order to unlock
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        |        |        |        |        |   2    |        |   1    |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |            3             |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [LAYER_LOCK] = KEYMAP(
     LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY ,
     LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY ,
     LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY ,
     LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY ,  LK_2  , LK_ANY ,  LK_1  , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY ,
     LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY ,  ___   ,  LK_3  ,  ___   , LK_ANY , LK_ANY , LK_ANY , LK_ANY , LK_ANY
     )
};

///
/// GLOBAL STATE VARS
///

/// previous layer refers to either QWERTY or Colemak; useful to "pop" back from the function layer
static uint32_t prev_layer_state;

/// Tap hold events - make sure the number of events matches TH_EVENTS_COUNT, and the TH_VOLD ... TH_0
/// keys must be sequential and in the same order.
static taphold_t th_events[] = {
    { .is_pressed = false, .timer = 0, .kc_tap = KC_MPLY, .kc_hold = KC_MUTE }, // TH_PLAY

    { .is_pressed = false, .timer = 0, .kc_tap = KC_PGUP, .kc_hold = KC_HOME }, // TH_PGUP
    { .is_pressed = false, .timer = 0, .kc_tap = KC_PGDN, .kc_hold = KC_END },  // TH_PGDN

    { .is_pressed = false, .timer = 0, .kc_tap = KC_1, .kc_hold = KC_F1 }, // TH_1
    { .is_pressed = false, .timer = 0, .kc_tap = KC_2, .kc_hold = KC_F2 }, // TH_2
    { .is_pressed = false, .timer = 0, .kc_tap = KC_3, .kc_hold = KC_F3 }, // TH_3
    { .is_pressed = false, .timer = 0, .kc_tap = KC_4, .kc_hold = KC_F4 }, // TH_4
    { .is_pressed = false, .timer = 0, .kc_tap = KC_5, .kc_hold = KC_F5 }, // TH_5
    { .is_pressed = false, .timer = 0, .kc_tap = KC_6, .kc_hold = KC_F6 }, // TH_6
    { .is_pressed = false, .timer = 0, .kc_tap = KC_7, .kc_hold = KC_F7 }, // TH_7
    { .is_pressed = false, .timer = 0, .kc_tap = KC_8, .kc_hold = KC_F8 }, // TH_8
    { .is_pressed = false, .timer = 0, .kc_tap = KC_9, .kc_hold = KC_F9 }, // TH_9
    { .is_pressed = false, .timer = 0, .kc_tap = KC_0, .kc_hold = KC_F10 } // TH_0
};

/// RGB KEYS
/// Store an rgblight_fadeout for each LED; these are turned on and fade out after every key press
static rgblight_fadeout lights[RGBLED_NUM];
static bool rgb_animations = true;

/// STICKY KEYS
// sticky key state - bit masks of MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT) | ...
// sticky_lock - same but stays on - double tap to activate
// hyper_state - override to allow "hyper" key
// taphold_down - taphold keys set this to true on event->pressed because those events shouldn't count
// as a key press until key up or hold timeout.
static uint8_t sticky_state = 0;
static uint8_t sticky_lock = 0;
static bool hyper_state = false;
static bool hyper_down = false;
static uint16_t sticky_auto_off_timer = 0;
static uint16_t sticky_lock_timer = 0;
static bool sticky_clear = false;
static bool taphold_down = false;
// actual "mod key pressed" state, which "overrides" the sticky state. "Sticky"
// state only lasts for one key press, but as long as the modifier key is held
// it will also continue to be active.
static uint8_t mods_down_state = 0;

/// FN layer
static bool bounce_fn_layer = false;

/// BABY PROOF
static uint8_t babycode = 0;

/// BACKLIGHT
static bool backlight_on = true;

void matrix_init_user(void) {
    rgblight_mode(1);
    rgblight_setrgb(0, 0, 0);
    rgblight_enable();
    gp100_led_on();
    capslock_led_on();
    keycaps_led_on();
    _delay_ms(250);
    gp100_led_off();
    capslock_led_off();

    for (uint8_t light_index = 0 ; light_index < RGBLED_NUM ; ++light_index ) {
        rgblight_fadeout *light = &lights[light_index];
        light->enabled = false;
    }

    rgblight_setrgb(0, 0, 0);
}

void matrix_scan_user(void) {
    scan_tap_hold(HELD);
    scan_rgblight_fadeout();
    scan_sticky_auto_off();
}

void scan_rgblight_fadeout(void) {
    if (!(rgb_animations && backlight_on)) { return; }

    bool litup = false;
    for (uint8_t light_index = 0 ; light_index < RGBLED_NUM ; ++light_index ) {
        if (lights[light_index].enabled && timer_elapsed(lights[light_index].timer) > 10) {
            rgblight_fadeout *light = &lights[light_index];
            rgblight_setrgb_at(light->r, light->g, light->b, light_index);
            litup = true;

            if (light->r || light->g || light->b) {
                light->life -= 1;
                light->r = light->r ? light->r - 1 : light->r;
                light->g = light->g ? light->g - 1 : light->g;
                light->b = light->b ? light->b - 1 : light->b;
                light->timer = timer_read();
            }
            else {
                light->enabled = false;
            }
        }
    }

    if (litup) {
        rgblight_set();
    }
}

void scan_sticky_auto_off(void) {
    if (sticky_auto_off_timer && timer_elapsed(sticky_auto_off_timer) > STICKY_AUTO_OFF) {
        uint8_t prev_mods = current_mods();
        sticky_state = 0;
        update_mods(prev_mods);
        sticky_auto_off_timer = 0;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool result = KBD_CONTINUE;

    result = process_record_user_rgb(keycode, record)         && result;
    result = process_record_user_sleep(keycode, record)       && result;
    result = process_record_user_reset(keycode, record)       && result;
    result = process_record_user_goto_layer(keycode, record)  && result;
    result = process_record_user_fnlayer(keycode, record)     && result;
    result = process_record_user_taphold(keycode, record)     && result;  // taphold must be BEFORE sticky
    result = process_record_user_sticky(keycode, record)      && result;
    result = process_record_user_macro(keycode, record)       && result;
    result = process_record_user_babyproof(keycode, record)   && result;
    result = process_record_user_keycap_leds(keycode, record) && result;

    return result;
}

bool process_record_user_rgb(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) { return KBD_CONTINUE; }

    switch (keycode) {
    case KC_A ... KC_SLASH:
    case KC_F1 ... KC_F12:
    case KC_INSERT ... KC_UP:
    case KC_KP_SLASH ... KC_KP_DOT:
    case KC_F13 ... KC_F24:
    case KC_AUDIO_MUTE ... KC_MEDIA_REWIND:
    case LK_ANY:
        start_rgb_light();
    }

    return KBD_CONTINUE;
}

bool process_record_user_reset(uint16_t keycode, keyrecord_t *record) {
    if (keycode != ENT_SET && keycode != RESET) { return KBD_CONTINUE; }

    if (record->event.pressed) {
        rgblight_setrgb(0xFF, 0xFF, 0);
        gp103_led_on();
        if (keycode == ENT_SET) {
            register_code(KC_ENT);
            unregister_code(KC_ENT);
        }
        reset_keyboard();
    }

    return KBD_HALT;
}

bool process_record_user_sleep(uint16_t keycode, keyrecord_t *record) {
    if (keycode != KC_SLEP) { return KBD_CONTINUE; }
    if (!record->event.pressed) { return KBD_HALT; }

    uint8_t ctrl_shift = MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSHIFT);
    uint8_t prev_mods = current_mods();
    sticky_state = 0;
    sticky_lock = 0;
    mods_down_state = ctrl_shift;
    update_mods(prev_mods);
    register_code(KC_POWER);
    unregister_code(KC_POWER);
    mods_down_state = 0;
    update_mods(ctrl_shift);

    layer_state_set(prev_layer_state);

    return KBD_HALT;
}

bool process_record_user_goto_layer(uint16_t keycode, keyrecord_t *record) {
    if ((keycode != GOTO_CM && keycode != GOTO_QW)) { return KBD_CONTINUE; }
    if (!record->event.pressed) { return KBD_HALT; }

    switch (keycode) {
    case GOTO_CM:
        layer_move(LAYER_COLEMAK);
        break;
    case GOTO_QW:
        layer_move(LAYER_QWERTY);
        break;
    }

    return KBD_HALT;
}

bool process_record_user_fnlayer(uint16_t keycode, keyrecord_t *record) {
    if (keycode != GOTO_FN && keycode != GOTO_LK) {
        if (layer_state_is(LAYER_FN)) {
            bounce_fn_layer = true;
        }
        return KBD_CONTINUE;
    }

    if (sticky_state || sticky_lock || hyper_state) {
        if (!record->event.pressed) {
            uint8_t prev_mods = current_mods();
            sticky_state = 0;
            sticky_lock = 0;
            hyper_state = false;
            update_mods(prev_mods);
        }
        return KBD_HALT;
    }

    if (keycode == GOTO_FN) {
        if (record->event.pressed) {
            if (layer_state_is(LAYER_FN)) {
                layer_state_set(prev_layer_state);
            }
            else {
                layer_move(LAYER_FN);
                bounce_fn_layer = false;
            }
        }
        else if (bounce_fn_layer) {
            layer_state_set(prev_layer_state);
            bounce_fn_layer = false;
        }
        return KBD_HALT;
    }

    if (!record->event.pressed) { return KBD_CONTINUE; }

    if (keycode == GOTO_LK) {
        keycaps_led_off();
        rgblight_setrgb(0, 0, 0);
        layer_move(LAYER_LOCK);
    }
    else if (layer_state_is(LAYER_COLEMAK) || layer_state_is(LAYER_QWERTY)) {
        prev_layer_state = layer_state & ((1UL << LAYER_COLEMAK) | (1UL << LAYER_QWERTY));
    }

    return KBD_CONTINUE;
}

bool process_record_user_taphold(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        scan_tap_hold(TAPPED);
    }

    if (keycode < TH_FIRST || keycode > TH_LAST) { return KBD_CONTINUE; }

    taphold_t *th_event = &th_events[keycode - TH_FIRST];

    if (record->event.pressed) {
        taphold_down = true;
        th_event->timer = timer_read();
        th_event->is_pressed = true;
        th_event->mods = current_mods();
    } else if (th_event->is_pressed) {
        scan_tap_hold(TAPPED);
    }

    return KBD_HALT;
}

void scan_tap_hold(taphold_state state) {
    bool any_activated = false;
    uint8_t original_mods = current_mods();
    uint8_t prev_mods = original_mods;
    for (uint8_t index = 0 ; index < TH_EVENTS_COUNT ; ++index ) {
        taphold_t *th_event = &th_events[index];
        if (!th_event->is_pressed) { continue; }

        if (state == TAPPED || timer_elapsed(th_event->timer) > LONGPRESS_DELAY) {
            uint16_t code = state == HELD ? th_event->kc_hold : th_event->kc_tap;
            bool should_update_mods = state == TAPPED && prev_mods != th_event->mods;
            if (should_update_mods) {
                set_current_mods(prev_mods, th_event->mods);
                prev_mods = th_event->mods;
            }
            register_code(code);
            unregister_code(code);
            th_event->is_pressed = false;
            any_activated = true;
        }
    }

    if (prev_mods != original_mods) {
        set_current_mods(prev_mods, original_mods);
    }

    if (any_activated) {
        process_record_after_sticky_clear();
    }
}

bool process_record_user_sticky(uint16_t keycode, keyrecord_t *record) {
    if (!layer_state_is(LAYER_COLEMAK)) { return KBD_CONTINUE; }

    uint8_t modkey_mask = 0;
    uint8_t prev_mods = current_mods();

    switch (keycode) {
    case STK_CTL:
        modkey_mask = MOD_BIT(KC_LCTL);
        break;
    case STK_ALT:
        modkey_mask = MOD_BIT(KC_LALT);
        break;
    case STK_GUI:
        modkey_mask = MOD_BIT(KC_LGUI);
        break;
    case STK_SHFT:
        modkey_mask = MOD_BIT(KC_LSHIFT);
        break;
    case HYPER:
        if (record->event.pressed) {
            hyper_state = !hyper_state;
        }
        hyper_down = record->event.pressed;
        break;
    default:
        if ((hyper_state || sticky_state) && record->event.pressed) {
            sticky_clear = true;
        }
        return KBD_CONTINUE;
    }

    if (modkey_mask) {
        if (record->event.pressed) {
            if (sticky_lock & modkey_mask) {
                sticky_state &= ~modkey_mask;
                sticky_lock  &= ~modkey_mask;
            }
            else if (sticky_state & modkey_mask) {
                 if (timer_elapsed(sticky_lock_timer) < STICKY_LOCK_DELAY) {
                    sticky_lock |= modkey_mask;
                }
                else {
                    sticky_state &= ~modkey_mask;
                }
            }
            else {
                sticky_state |= modkey_mask;
                sticky_lock_timer = timer_read();
                sticky_auto_off_timer = timer_read();
            }

            mods_down_state |= modkey_mask;
        }
        else {
            mods_down_state &= ~modkey_mask;

            if (!mods_down_state) {
                sticky_auto_off_timer = 0;
            }
        }
    }

    update_mods(prev_mods);
    return KBD_HALT;
}

bool process_record_user_macro(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) { return KBD_CONTINUE; }

    if (keycode == MM_1) {
        SEND_STRING(SENDSTRING_MM1);
    }
    else if (keycode == MM_2) {
        SEND_STRING(SENDSTRING_MM2);
    }
    else if (keycode == MM_3) {
        SEND_STRING(SENDSTRING_MM3);
    }
    else if (keycode == MM_4) {
        SEND_STRING(SENDSTRING_MM4);
    }
    else if (keycode == MM_5) {
        SEND_STRING(SENDSTRING_MM5);
    }
    else if (keycode == MM_6) {
        SEND_STRING(SENDSTRING_MM6);
    }
    else {
        return KBD_CONTINUE;
    }

    layer_state_set(prev_layer_state);
    return KBD_HALT;
}

bool process_record_user_babyproof(uint16_t keycode, keyrecord_t *record) {
    if (!layer_state_is(LAYER_LOCK) || record->event.pressed) { return KBD_CONTINUE; }

    uint8_t new_baby_code = 0;
    switch (keycode) {
    case LK_1:
        new_baby_code = 1;
        break;
    case LK_2:
        if (babycode == 1)  new_baby_code = 2;
        else new_baby_code = 0;
        break;
    case LK_3:
        if (babycode == 2)  new_baby_code = 3;
        else new_baby_code = 0;
        break;
    }

    if (new_baby_code == 3) {
        keycaps_led_set(backlight_on);
        layer_state_set(prev_layer_state);
    }
    else if (new_baby_code == 0 && babycode != 0) {
        rgblight_setrgb(0, 0, 0);
    }
    babycode = new_baby_code;

    return KBD_HALT;
}

bool process_record_user_keycap_leds(uint16_t keycode, keyrecord_t *record) {
    if (keycode != BKLT || !record->event.pressed) { return KBD_CONTINUE; }

    backlight_on = !backlight_on;
    keycaps_led_set(backlight_on);

    return KBD_HALT;
}

void start_rgb_light(void) {
    if (!(rgb_animations && backlight_on)) { return; }

    uint8_t indices[RGBLED_NUM];
    uint8_t indices_count = 0;
    uint8_t min_life = 0xFF;
    uint8_t min_life_index = -1;
    for (uint8_t index = 0 ; index < RGBLED_NUM ; ++index ) {
        if (lights[index].enabled) {
            if (min_life_index == -1 ||
                lights[index].life < min_life)
            {
                min_life = lights[index].life;
                min_life_index = index;
            }
            continue;
        }

        indices[indices_count] = index;
        ++indices_count;
    }

    uint8_t light_index;
    if (!indices_count) {
        light_index = min_life_index;
    }
    else {
        light_index = indices[rand() % indices_count];
    }

    rgblight_fadeout *light = &lights[light_index];
    light->enabled = true;
    light->timer = timer_read();
    light->life = 0xFF;

    light->r = rand() % 0xFF;
    light->g = rand() % 0xFF;
    light->b = rand() % 0xFF;

    rgblight_setrgb_at(light->r, light->g, light->b, light_index);
}

uint8_t current_mods(void) {
    if (hyper_state || hyper_down) {
        return MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LGUI);
    }
    return mods_down_state | sticky_state | sticky_lock;
}

void update_mods(uint8_t prev_mods) {
    set_current_mods(prev_mods, current_mods());
}

void set_current_mods(uint8_t prev_mods, uint8_t current_mods) {
    uint8_t mods[] = { KC_LCTL, KC_LALT, KC_LGUI, KC_LSHIFT };
    bool turned_off = false;
    for (uint8_t mod_index = 0; mod_index < 4; mod_index++ ) {
        uint8_t mod = mods[mod_index];
        uint8_t mask = MOD_BIT(mod);

        if ((mods_down_state & mask) && !((sticky_state | sticky_lock) & mask)) {
            turned_off = true;
        }

        if ( (prev_mods & mask) == (current_mods & mask)) {
            continue;
        }

        if (prev_mods & mask) {
            unregister_code(mod);
        }
        else {
            register_code(mod);
        }
    }

    set_mods(current_mods);

    bool hyper = hyper_state || hyper_down;
    if ((sticky_lock || turned_off) && !hyper) {
        gp100_led_on();
    }
    else {
        gp100_led_off();
    }

    if (sticky_state || sticky_lock || hyper_state) {
        capslock_led_on();
    }
    else {
        capslock_led_off();
    }
}

void process_record_after(keyrecord_t *record) {
    process_record_after_sticky_clear();
    process_record_after_rgb();
}

void process_record_after_rgb(void) {
    if (layer_state_is(LAYER_LOCK)) {
        switch (babycode) {
        case 0:
            rgb_animations = true;
            break;
        case 1:
            rgb_animations = false;
            rgblight_setrgb(0, 0xFF, 0);
            break;
        case 2:
            rgb_animations = false;
            rgblight_setrgb(0xFF, 0xFF, 0);
            break;
        }
    }
    else if (layer_state_is(LAYER_FN)) {
        rgb_animations = false;
        rgblight_setrgb(0xFF, 0xFF, 0xFF);
    }
    else if (!rgb_animations) {
        rgb_animations = true;
        rgblight_setrgb(0, 0, 0);
    }

    gp103_led_set(layer_state_is(LAYER_FN));
}

void process_record_after_sticky_clear(void) {
    if (taphold_down) {
        taphold_down = false;
        return;
    }

    if (sticky_clear) {
        uint8_t prev_mods = current_mods();
        hyper_state = false;
        sticky_state = 0;
        update_mods(prev_mods);
        sticky_clear = false;
    }
}
