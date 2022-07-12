/* Copyright 2021 Joe Maples <joe@maples.dev>
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

#include QMK_KEYBOARD_H

enum {
    TD_IPOD,
    TD_BRIG,
};

void on_ipod_finished(qk_tap_dance_state_t *state, void *user_data) {
    if(state->pressed) {
      layer_on(1);
      return;
    }

    switch (state->count){
        case 1:
            tap_code(KC_MEDIA_PLAY_PAUSE);
            break;
        case 2:
            tap_code(KC_MEDIA_NEXT_TRACK);
            break;
        case 3:
            tap_code(KC_MEDIA_PREV_TRACK);
        default:
            break;
    }
}

void on_ipod_reset(qk_tap_dance_state_t *state, void *user_data) {
    layer_off(1);
}

void on_brig_finished(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count){
        case 0:
            if(state->pressed) {
                layer_on(3);
                return;
            }

            break;
        case 1:
            if(state->pressed) {
                layer_on(3);
                return;
            }

            break;
        case 2:
            if(state->pressed) {
                layer_on(4);
                return;
            }

            tap_code(KC_F17);

            break;
        default:
            break;
    }
}

void on_brig_reset(qk_tap_dance_state_t *state, void *user_data) {
    layer_off(3);
    layer_off(4);
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_IPOD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, on_ipod_finished, on_ipod_reset),
    [TD_BRIG] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, on_brig_finished, on_brig_reset),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [4] = LAYOUT(KC_VOLD,     KC_VOLU,  _______      ),
    [3] = LAYOUT(KC_BRMD,     KC_BRMU,  _______      ),

    [2] = LAYOUT(_______,     _______,  QK_BOOTLOADER),
    [1] = LAYOUT(_______,     MO(2),    _______      ),

    [0] = LAYOUT(TD(TD_IPOD), KC_F18, TD(TD_BRIG)),
};
