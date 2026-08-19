#include QMK_KEYBOARD_H
#include <stdio.h>

/* ==========================================================================
   1. DEFINIÇÃO DAS CAMADAS (LAYERS)
   ========================================================================== */
enum sofle_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

/* ==========================================================================
   2. MAPA DE TECLAS PADRÃO DO SOFLE PICO
   ========================================================================== */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_MUTE,  KC_MPLY, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                    KC_LALT, KC_LCTL, LOWER,   KC_ENT, KC_SPC,   RAISE,   KC_RGUI, KC_DEL
),

[_LOWER] = LAYOUT(
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
  _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_EQL,
  _______, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                    _______, _______, _______, _______, _______, _______, _______, _______
),

[_RAISE] = LAYOUT(
  _______, KC_F11,  KC_F12,  _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  _______, KC_PLUS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                    _______, _______, _______, _______, _______, _______, _______, _______
),

[_ADJUST] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                    _______, _______, _______, _______, _______, _______, _______, _______
)

};

// Configuração do Encoders (Rotary Encoders)
#if defined(ENCODER_ENABLE)
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { // Encoder Esquerdo: Volume
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) { // Encoder Direito: Scroll Vertical
        if (clockwise) {
            tap_code(KC_MS_WH_DOWN);
        } else {
            tap_code(KC_MS_WH_UP);
        }
    }
    return true;
}
#endif

/* ==========================================================================
   3. CÓDIGO E MATRIZES DE IMAGEM DO BONGO CAT (OLED 128x32)
   ========================================================================== */
#if defined(OLED_ENABLE)

// Matrizes de bytes para os quadros do Bongo Cat (Inerte, Pata Esquerda, Pata Direita, Ambas)
static const char PROGMEM bongo_idle[] = {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0xfe,0x01,0x01,0x01,0x01,0xfe,0x00,0x00,0x00,0x00,0xfe,0x01,0x01,0xfe,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfe,0x01,0x01,0xfe,0x00,0x00,0x00
};

static const char PROGMEM bongo_tap_left[] = {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0xfe,0x01,0x01,0x01,0x01,0xfe,0x00,0x00,0x00,0x00,0xfe,0x01,0x01,0xfe,
    0x00,0x00,0xfe,0x01,0x01,0xfe,0x00,0x00,0x00,0xfe,0x01,0x01,0xfe,0x00,0x00,0x00
};

static const char PROGMEM bongo_tap_right[] = {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0xfe,0x01,0x01,0x01,0x01,0xfe,0x00,0x00,0xfe,0x01,0x01,0xfe,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfe,0x01,0x01,0xfe,0x00,0x00,0x00
};

// Renderiza a animação do Bongo Cat baseando-se no ritmo de digitação (WPM)
static void render_anim_bongocat(void) {
    uint8_t wpm = get_current_wpm();

    if (wpm == 0) {
        oled_write_raw_P(bongo_idle, sizeof(bongo_idle));
    } else if (wpm < 40) {
        if ((timer_read() / 150) % 2 == 0) {
            oled_write_raw_P(bongo_tap_left, sizeof(bongo_tap_left));
        } else {
            oled_write_raw_P(bongo_tap_right, sizeof(bongo_tap_right));
        }
    } else {
        if ((timer_read() / 75) % 2 == 0) {
            oled_write_raw_P(bongo_tap_left, sizeof(bongo_tap_left));
        } else {
            oled_write_raw_P(bongo_tap_right, sizeof(bongo_tap_right));
        }
    }
}

/* ==========================================================================
   4. TAREFA PRINCIPAL DO DISPLAY OLED (LADO MESTRE E ESCRAVO)
   ========================================================================== */
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // --- LADO MESTRE (Com o cabo USB conectado) ---
        
        // 1. Escreve a velocidade de digitação (WPM)
        char wpm_str[16];
        snprintf(wpm_str, sizeof(wpm_str), "WPM: %03d\n", get_current_wpm());
        oled_write(wpm_str, false);

        // 2. Desenha a animação do Bongo Cat
        render_anim_bongocat();

    } else {
        // --- LADO ESCRAVO (Conectado pelo cabo TRRS) ---
        
        oled_write_P(PSTR("SOFLE PICO\n"), false);
        oled_write_P(PSTR("----------\n"), false);

        // Exibe o nome da camada (Layer) ativa
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state)) {
            case _QWERTY:
                oled_write_P(PSTR("QWERTY\n"), false);
                break;
            case _LOWER:
                oled_write_P(PSTR("LOWER\n"), false);
                break;
            case _RAISE:
                oled_write_P(PSTR("RAISE\n"), false);
                break;
            case _ADJUST:
                oled_write_P(PSTR("ADJUST\n"), false);
                break;
            default:
                oled_write_P(PSTR("UNKNOWN\n"), false);
                break;
        }

        // Animação/Texto decorativo para o lado secundário
        if (get_current_wpm() == 0) {
            oled_write_P(PSTR("\n Cat: Zzz.."), false);
        } else {
            oled_write_P(PSTR("\n Cat: Work!"), false);
        }
    }
    return false;
}

#endif
