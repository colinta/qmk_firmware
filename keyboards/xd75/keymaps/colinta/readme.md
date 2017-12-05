# colinta's keymap for XD75

```
make xd75:colinta:dfu
```

The default layout is a Colemak keyboard with "sticky" keys assigned to the modifier keys.

    .--------------------------------------------------------------------------------------------------------------------------------------.
    | ESC    | 1   !  | 2   @  | 3   #  | 4   $  | 5   %  | KC_DEL | 6   ^  | 7   &  | 8   *  | 9   (  | 0   )  | -   _  | =   +  | `   ~  |
    |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    | TAB    | Q      | W      | F      | P      | G      | BKSP   | J      | L      | U      | Y      | ;   :  | [   {  | ]   }  | DM_1   |
    |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------+--------|
    | SHIFT  | A      | R      | S      | T      | D      | ENTER  | H      | N      | E      | I      | O      | '   "  | \   |  | DM_2   |
    |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------+--------+--------|
    | CTRL   | Z      | X      | C      | V      | B      | GOTO_FN| K      | M      | ,   <  | .   >  | /   ?  | UP     | HYPER  |PGUP/HOM|
    |--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------|
    |VOL-/BCK|PLY/MUTE|VOL+/FWD| ALT    | GUI    |          SPACE           | MM_3   | MM_4   | MENU   | LEFT   | DOWN   | RIGHT  |PGDN/END|
    '--------------------------------------------------------------------------------------------------------------------------------------'

I've implemented my own "tap/hold" feature, identical in spirit to "Space Cadet", but for generic use.  Tapping "1" sends a 1, but press and hold to send "F1".  Or, tap "VOL-" to turn the volume down, but press and hold for "previous track".

The function layer can be used to switch to Qwerty (so other people can use this keyboard - also turns off sticky keys) or to start recording/clear dynamic macros, or to put the keyboard in programming mode.

    .--------------------------------------------------------------------------------------------------------------------------------------.
    | KC_SLEP| RESET  |   F1   |   F2   |   F3   |   F4   |   F5   | QWERTY |   F6   |   F7   |   F8   |   F9   |   F10  |   F11  |   F12  |
    |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
    | REC 1  |        |        |        |        |        |        | COLEMAK|        |        |        |        |        |        |        |
    |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
    | REC 2  |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
    |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
    | CLEAR  |       |        |        |        |        |         | GOTO_FN|       |         |        |        |        |        |        |
    |--MACROS+-------+--------+--------+--------+--------+---------+--------+-------+---------+--------+--------+--------+--------+--------|
    | CLEAR  |       |        |        |        |        |           GOTO_LK        |         |        |        |        |        |        |
    '--MACROS------------------------------------------------------------------------------------------------------------------------------'

I implemented "stop recording" in a unique way; starting a macro recording sends the keyboard layer to a layer that has all the macro keys assigned to `DYN_REC_STOP`, and restores the layer to the default when recording is stopped.

For programming I use "enter and reset" which first sends the enter key, then puts the keyboard in programming mode.

Another odd feature: babyproof locks the keyboard until I type three keys in order.  This is specifically because I have a little toddler who loves to play on the keyboard, and who am I to stop her!?

I try to keep http://www.keyboard-layout-editor.com/#/gists/9169fb1b4be330385c4386a5e2e5b21e up to date with this key map.  I'm using DSA keycaps from [KBDFans DSA PBT](https://kbdfans.myshopify.com/collections/keycaps/products/dsa-pbt-145keys-keycaps-laser-etched-front-printed-legends) and [KBDFans DSA Blanks](https://kbdfans.myshopify.com/collections/keycaps/products/dsa-blank-keycaps-1).

## "secrets.h"

The macros I'm using are sensitive, and while I'm comfortable having them hardcoded onto my keyboard (no SSN or private GPG keys), they are not suitable for public viewing.  So I've put them in a header file that is excluded from the project.  This header file is included using `__has_include`, so if the file isn't present some blank defaults will be used instead.

If you would *also* like to take advantage of this feature, you'll first want to make sure your "secrets" file isn't included in the repo.  Open `.git/info/exclude` and add `secrets.h` to that file, below the comments.

###### .git/info/exclude
```
# git ls-files --others --exclude-from=.git/info/exclude
# Lines that start with '#' are comments.
# For a project mostly in C, the following would be a good set of
# exclude patterns (uncomment them if you want to use them):
# *.[oa]
# *~
/keyboards/xd75/keymaps/colinta/secrets.h
```

Then you can create this file and add your macro strings to it:

```
touch keyboards/xd75/keymaps/colinta/secrets.h
$EDITOR keyboards/xd75/keymaps/colinta/secrets.h
```

###### secrets.h
```
#define SENDSTRING_MM1 "shhhhh secret"
#define SENDSTRING_MM2 "stop saying pickle rick"
#define SENDSTRING_MM3 "abcd1234"
#define SENDSTRING_MM4 "HCF"
```

## Tap Hold

There is an array of `struct taphold_t`, and a list of `TH_n` keys in my custom keycodes.  They must be contiguous, because the keycode is used as an index for the `taphold_t` entry.

On key down the entry is updated with `.is_pressed = true, .timer = timer_read()`.  In `matrix_scan_user()` the entries are checked, and any entry where `is_pressed == true && timer > THRESHOLD` is considered a "hold" event, the hold key is sent (using `register_code/unregister_code`), and the entry is disabled (`is_pressed = false`).

If the key is released before the timer expires the event is considered a "tap" and the tap keypress is sent.

The use of `matrix_scan_user` makes for an immediate "hold" event, rather than checking the timer on key up.

## Sticky keys

I use sticky keys because of wrist issues, and my preferred logic is loosely based off of how Mac OS treats sticky keys, with my own "appropriate for a custom keyboard" modifications.

If you use macOS, I recommend that you use *my fork of* the "keycastr" app, with the "Svelte" theme: https://github.com/colinta/keycastr – my fork *only* shows the modifiers that are being pressed, and in a very small "always on top" window.

- press a modifier key once to turn it "on" for the next non-modifier key
- press and hold a modifier for more than .5 seconds will turn the sticky setting back OFF, this is to support cmd+click, ctrl+click.
- double tap a modifier to "lock" it (in mac os you just press the modifier key twice, but I prefer this to be on a timeout)
- pressing a non-modifier key turns the "sticky" setting off (but doesn't affect any locks or modifier keys still pressed)
- press the modifier again to turn it off

This behavior also works for press+hold events: on key down "sticky" is turned on, and on non-modifier key press sticky is turned off, but the modifier stays active as long as the modifier is held.

Another way to consider the modifier state is an `OR` of:

- currently pressed modifiers (`mods_down_state`)
- currently active sticky keys (`sticky_state`)
- currently active sticky locks (`sticky_lock`)

Any time I need to change the modifier keys, I use the following code:

```c
uint8_t prev_mods = current_mods();
... change the sticky state or update the currently pressed or locked state variables ...
update_mods(prev_mods);
```

`update_mods` will compare the two states and turn on/off the appropriate modifier settings and send the correct keys back to the OS.  So if you need to shift+click this will work as you intend, except the keyboard can't detect the mouse click (which would normally turn off the sticky key), so you need to tap shift again to manually turn it back off.

## LEDs

First, check out the awesome typing effects on the WS2812 RGB LEDs.  Every non-modifier key will turn on an LED and fade it out, pretty cool when you're typing quickly.

The "gp103" LED flashes at startup and when the `RESET` key is sent.

The WS2812s turn white when the function layer is active, and yellow when the keyboard is in "programmable" mode.

The caps lock and "gp100" LEDs are used to show sticky status:

- caps lock on means one or more sticky keys are active
- caps lock AND gp100 means there is one or more sticky locks
- caps lock OFF and gp100 ON means you have just turned off a sticky key or sticky lock

If you need to turn off sticky keys in a hurry, using the "goto function layer" key will turn off all sticky keys and locks.
