#include QMK_KEYBOARD_H
#include "keymap.h"

// layers:
// - colemak
// - brackets
// - fn
// - lock
#define LAYER_COLEMAK 0
#define LAYER_BRACKET 1
#define LAYER_FN 2
#define LAYER_LOCK 8

// #define MY_SPC LT(LAYER_BRACKET, KC_SPC)

enum my_keycodes {
    SLEEP = SAFE_RANGE,

    // sticky keys
    STK_CTL,
    STK_ALT,
    STK_SHFT,
    STK_GUI,
    HYPER,

    // enter and reset
    ENT_SET,

    // layers
    GOTO_CM,
    GOTO_FN,
    GOTO_BRK,

    // baby proofing
    GOTO_LK,
    LK_2,
    LK_3,
    LK_1,

    // tap/hold buttons
    TH_PLAY,  // play / mute
    TH_VOLU,
    TH_VOLD,

    // normal macros
    MM_1,
    MM_2,
    MM_3,
    MM_4,
    MM_5,
    MM_6,
};

#define TH_EVENTS_COUNT 3
#define TH_FIRST TH_PLAY
#define TH_LAST TH_VOLD
#define MM_LAST MM_6

#define LAYER_BASE 0

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[LAYER_COLEMAK] = LAYOUT( \
    MM_1 ,   __   , KC_ESC ,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 ,  KC_F5 ,  KC_F6      ,      KC_F7 ,  KC_F8 ,  KC_F9 , KC_F10 , KC_F11 , KC_F12 , TH_VOLD, TH_PLAY, TH_VOLU, \
    MM_2 ,   __   , KC_GRV ,  KC_1  ,  KC_2  ,  KC_3  ,  KC_4  ,  KC_5  , KC_DEL      ,     KC_DEL ,  KC_6  ,  KC_7  ,  KC_8  ,  KC_9  ,  KC_0  , KC_MINS, KC_EQL , KC_MUTE, \
    MM_3 ,   __   , KC_TAB ,  KC_Q  ,  KC_W  ,  KC_F  ,  KC_P  ,  KC_G  , KC_BSPC     ,     KC_BSPC,  KC_J  ,  KC_L  ,  KC_U  ,  KC_Y  , KC_SCLN, KC_LBRC, KC_RBRC, KC_HOME, \
    MM_4 ,   __   ,STK_SHFT,  KC_A  ,  KC_R  ,  KC_S  ,  KC_T  ,  KC_D  , KC_ENT      ,     KC_ENT ,  KC_H  ,  KC_N  ,  KC_E  ,  KC_I  ,  KC_O  , KC_QUOT, KC_PGUP, KC_PGDN, \
    MM_5 ,   __   , STK_CTL,  KC_Z  ,  KC_X  ,  KC_C  ,  KC_V  ,  KC_B  , GOTO_FN     ,     GOTO_FN,  KC_K  ,  KC_M  , KC_COMM, KC_DOT , KC_SLSH, KC_BSLS,  KC_UP , KC_END , \
     __  ,   __   ,   __   ,  HYPER ,   __   , STK_ALT,   __   , STK_GUI,   __        ,       __   , KC_SPC ,   __   ,GOTO_BRK,   __   ,   __   , KC_LEFT, KC_DOWN, KC_RGHT  \
),

[LAYER_BRACKET] = LAYOUT( \
    __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __        ,       __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   , \
    __   ,   __   ,   __   ,   __   , KC_DLR , KC_LPRN, KC_RPRN,   __   ,   __        ,       __   ,   __   , KC_LPRN, KC_RPRN,   __   ,   __   ,   __   ,   __   ,   __   , \
    __   ,   __   ,   __   ,   __   , KC_DLR , KC_LCBR, KC_RCBR,   __   ,   __        ,       __   ,   __   , KC_LCBR, KC_RCBR,   __   ,   __   ,   __   ,   __   ,   __   , \
    __   ,   __   ,STK_SHFT,   __   , KC_BSLS, KC_LPRN, KC_RPRN,   __   ,   __        ,       __   ,   __   , KC_LBRC, KC_RBRC,   __   ,   __   ,   __   ,   __   ,   __   , \
    __   ,   __   , STK_CTL,   __   , KC_PERC, KC_LCBR, KC_RCBR,   __   ,   __        ,       __   ,   __   , KC_LABK, KC_RABK,   __   ,   __   ,   __   ,   __   ,   __   , \
    __   ,   __   ,   __   ,  HYPER ,   __   , STK_ALT,   __   , STK_GUI,   __        ,       __   ,   __   ,   __   ,GOTO_BRK,   __   ,   __   ,   __   ,   __   ,   __     \
),

[LAYER_FN] = LAYOUT( \
   SLEEP ,   __   , GOTO_LK,   __   ,   __   ,   __   ,   __   ,   __   ,   __        ,       __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   , \
   SLEEP ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __        ,       __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   , \
   SLEEP ,   __   ,   __   ,   __   ,  MM_2  ,   __   ,   __   ,   __   , RESET       ,     RESET  ,  MM_1  ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   , \
   SLEEP ,   __   ,   __   ,   __   ,   __   ,  MM_5  ,  MM_4  ,   __   , ENT_SET     ,     ENT_SET,   __   ,  MM_3  ,  MM_6  ,   __   ,   __   ,   __   ,   __   ,   __   , \
   SLEEP ,   __   ,   __   ,   __   ,   __   , GOTO_CM,   __   , KC_VOLD, GOTO_FN     ,     GOTO_FN, KC_VOLU,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   , \
    __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __        ,       __   , KC_MUTE,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __     \
),

[LAYER_LOCK] = LAYOUT( \
    __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __        ,       __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   , \
    __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __        ,       __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   , \
    __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __        ,       __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   , \
    __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __        ,       __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   , \
    __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,  LK_2  ,   __        ,       __   ,  LK_1  ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   , \
    __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __        ,       __   ,  LK_3  ,   __   ,   __   ,   __   ,   __   ,   __   ,   __   ,   __     \
)
};

///
/// GLOBAL STATE VARS
///

/// previous layer always refers to Colemak, until one day when I might use two layers?
static uint32_t prev_layer_state = LAYER_COLEMAK;

/// Tap hold events - make sure the number of events matches TH_EVENTS_COUNT, and the TH_VOLD ... TH_0
/// keys must be sequential and in the same order.
static taphold_t th_events[] = {
    { .is_pressed = false, .timer = 0, .kc_tap = KC_MPLY, .kc_hold = KC_MUTE }, // TH_PLAY
    { .is_pressed = false, .timer = 0, .kc_tap = KC_VOLU, .kc_hold = KC_MFFD }, // TH_VOLU
    { .is_pressed = false, .timer = 0, .kc_tap = KC_VOLD, .kc_hold = KC_MRWD }  // TH_VOLD
};

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

/// "restore" previous layer after a key press in the function layer
static bool bounce_fn_layer = false;

/// macro (press twice to activate macro)
static uint16_t macro = 0;

/// reset (press twice to reset)
static bool reset = false;

/// BABY PROOF
static uint8_t babycode = 0;

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
    scan_tap_hold(HELD);
    scan_sticky_auto_off();
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

void scan_sticky_auto_off(void) {
    if (sticky_auto_off_timer && timer_elapsed(sticky_auto_off_timer) > STICKY_AUTO_OFF) {
        clear_sticky_mods();
        sticky_auto_off_timer = 0;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool result = KBD_CONTINUE;

    result = process_record_user_reset(keycode, record)       && result;
    result = process_record_user_sleep(keycode, record)       && result;
    result = process_record_user_goto_colemak(keycode, record)&& result;
    result = process_record_user_goto_bracket(keycode, record)     && result;
    result = process_record_user_goto_fn(keycode, record)   && result;
    result = process_record_user_goto_lock(keycode, record)     && result;  // taphold must be BEFORE sticky
    result = process_record_user_taphold(keycode, record)      && result;
    result = process_record_user_sticky(keycode, record)       && result;
    result = process_record_user_macro(keycode, record)   && result;
    result = process_record_user_babyproof(keycode, record)   && result;

    return result;
}

bool process_record_user_reset(uint16_t keycode, keyrecord_t *record) {
    if (keycode != ENT_SET && keycode != RESET) {
        reset = false;
        return KBD_CONTINUE;
    }

    if (record->event.pressed) {
        if (!reset) {
            reset = true;
            return KBD_HALT;
        }

        if (keycode == ENT_SET) {
            register_code(KC_ENT);
            unregister_code(KC_ENT);
        }
        reset_keyboard();
    }

    return KBD_HALT;
}

bool process_record_user_sleep(uint16_t keycode, keyrecord_t *record) {
    if (keycode != SLEEP) { return KBD_CONTINUE; }
    if (!record->event.pressed) { return KBD_HALT; }

    uint8_t ctrl_super = MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI);
    uint8_t ctrl_shift = MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSHIFT);
    uint8_t prev_mods = current_mods();
    sticky_state = 0;
    sticky_lock = 0;

    mods_down_state = ctrl_super;
    update_mods(prev_mods);
    register_code(KC_Q);
    unregister_code(KC_Q);

    mods_down_state = ctrl_shift;
    update_mods(prev_mods);
    register_code(KC_POWER);
    unregister_code(KC_POWER);

    mods_down_state = 0;
    update_mods(ctrl_shift);

    layer_state_set(prev_layer_state);

    return KBD_HALT;
}

bool process_record_user_goto_colemak(uint16_t keycode, keyrecord_t *record) {
    if ((keycode != GOTO_CM)) { return KBD_CONTINUE; }

    if (record->event.pressed) {
        prev_layer_state = LAYER_COLEMAK;
        layer_move(LAYER_COLEMAK);
    }

    return KBD_HALT;
}

bool process_record_user_goto_bracket(uint16_t keycode, keyrecord_t *record) {
    if (keycode != GOTO_BRK) { return KBD_CONTINUE; }

    if (record->event.pressed) {
        layer_move(LAYER_BRACKET);
    }
    else {
        layer_move(LAYER_COLEMAK);
    }

    return KBD_HALT;
}

bool process_record_user_goto_fn(uint16_t keycode, keyrecord_t *record) {
    if (keycode != GOTO_FN) {
        if (layer_state_is(LAYER_FN)) {
            bounce_fn_layer = true;
        }
        return KBD_CONTINUE;
    }

    if (sticky_state || sticky_lock || hyper_state) {
        return KBD_HALT;
    }

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

bool process_record_user_goto_lock(uint16_t keycode, keyrecord_t *record) {
    if (keycode != GOTO_LK) { return KBD_CONTINUE; }

    if (record->event.pressed) {
        layer_move(LAYER_LOCK);
    }

    return KBD_HALT;
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
    for (uint8_t mod_index = 0; mod_index < 4; mod_index++ ) {
        uint8_t mod = mods[mod_index];
        uint8_t mask = MOD_BIT(mod);

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
}

void clear_sticky_mods(void) {
    uint8_t prev_mods = current_mods();
    sticky_state = 0;
    sticky_lock = 0;
    hyper_state = false;
    update_mods(prev_mods);
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
            sticky_state = 0;
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
    if (keycode < MM_1 || keycode > MM_LAST) {
        macro = 0;
        return KBD_CONTINUE;
    }
    if (!record->event.pressed) { return KBD_CONTINUE; }

    if (macro == keycode) {
        switch (macro) {
        case MM_1:
            send_string(SENDSTRING_MM1);
            break;
        case MM_2:
            send_string(SENDSTRING_MM2);
            break;
        case MM_3:
            send_string(SENDSTRING_MM3);
            break;
        case MM_4:
            send_string(SENDSTRING_MM4);
            break;
        case MM_5:
            send_string(SENDSTRING_MM5);
            break;
        case MM_6:
            send_string(SENDSTRING_MM6);
            break;
        }

        layer_state_set(prev_layer_state);
        macro = 0;
    }
    else {
        macro = keycode;
    }

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
        layer_state_set(prev_layer_state);
    }
    babycode = new_baby_code;

    return KBD_HALT;
}

void process_record_after(keyrecord_t *record) {
    process_record_after_sticky_clear();
}

void process_record_after_sticky_clear(void) {
    if (taphold_down) {
        taphold_down = false;
        return;
    }

    if (sticky_clear) {
        clear_sticky_mods();
        sticky_clear = false;
    }
}
