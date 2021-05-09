static char     keylog_str[6] = {};
static uint16_t log_timer = 0;
static const char code_to_name[60] = {' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\', '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

// #define PREP_FRAMES 1 // uncomment if >1

#define TAP_FRAMES 2
#define TAP_SPEED 60 // above this wpm value typing animation to triggere

#define ANIM_FRAME_DURATION 200 // how long each frame lasts in ms
#define ANIM_SIZE 636 // number of bytes in array, minimize for adequate firmware size, max is 1024

uint32_t anim_timer = 0;
uint8_t current_tap_frame = 0;
bool is_idle = true;

// Images credit j-inc(/James Incandenza) and pixelbenny. Credit to obosob for initial animation approach.
static const char PROGMEM tap[TAP_FRAMES][ANIM_SIZE] = {
    {
    0,  0,126,126, 24, 60,102, 66,  0, 12, 28,112,112, 28, 12,  0,116,116, 20, 20,124,104,  0,124,124,  0,112,120, 44, 36,124,124,0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,  0,  0,  0,  0,  0,128, 64, 64, 32, 32, 32, 32, 16, 16, 16, 16,  8,  4,  2,  1,  1,  2, 12, 48, 64,128,  0,  0,  0,  0,  0,  0,  0,248,248,248,248,  0,  0,  0,  0,  0,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,128,
    0,  0,  0,  0,192, 96, 48, 24, 12,132,198, 98, 35, 51, 17,145,113,241,113,145, 17, 51, 35, 98,198,132, 12, 24, 48, 96,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,225,  0,  0,  1,  1,  2,  2,129,128,128,  0,  0,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0, 48, 48,  0,  0,  1,  1,  2,  4,  8, 16, 32, 67,135,  7,  1,  0,184,188,190,159, 95, 95, 79, 76, 32, 32, 32, 32, 16, 16, 16, 16,  8,  8,  8,  8,  8,196,  4,196,  4,196,  2,194,  2,194,  1,  1,  1,  1,  0,  0,  0,
    0,  0,252, 15,  1,  0,248, 14, 31,109,140,148,148,164,166,249,224,255,224,249,166,164,148,148,140,109, 31, 14,248,  0,  1, 15,252,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,112, 12,  3,  0,  0, 24,  6,  5,152,153,132, 67,124, 65, 65, 64, 64, 32, 33, 34, 18, 17, 17, 17,  9,  8,  8,  8,  8,  4,  4,  8,  8, 16, 16, 16, 16, 16, 17, 15,  1, 61,124,252,252,252,252,252, 60, 12,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,170,170,255,255,195,191,127,  3,127,191,195,255,255,170,170,  0,  0,  0,  0,
    0,  0, 31,120,192,  0, 15, 56,124,219,152, 20, 20, 18, 50,207,  3,255,  3,207, 50, 18, 20, 20,152,219,124, 56, 15,  0,192,120, 63, 16, 16, 16, 16,  8,  8,  8,  8,  8,  4,  4,  4,  4,  4,  2,  3,  2,  2,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  3,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,130,135, 31,  7,159,  7, 28,  7,159,  7,159,  7,  2,130,  0,  0,  0,  0,
    32, 16, 16, 16, 17, 11, 14, 12, 24, 16, 49, 35, 98,102, 68, 68, 71, 71, 71, 68, 68,102, 98, 35, 49, 16, 24, 12,  6,  3,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  8,  8, 23,  0, 15,  1,  2,  1, 15,  0, 15,  2,  5,  8
    },
    {
    0,  0,126,126, 24, 60,102, 66,  0, 12, 28,112,112, 28, 12,  0,116,116, 20, 20,124,104,  0,124,124,  0,112,120, 44, 36,124,124,0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,  0,  0,  0,  0,  0,128, 64, 64, 32, 32, 32, 32, 16, 16, 16, 16,  8,  4,  2,  1,  1,  2, 12, 48, 64,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,128,
    0,  0,  0,  0,192, 96, 48, 24, 12,132,198, 98, 35, 51, 17,145,113,241,113,145, 17, 51, 35, 98,198,132, 12, 24, 48, 96,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,225,  0,  0,  1,  1,  2,  2,  1,  0,  0,  0,  0,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0, 48, 48,  0,  0,  1,225, 26,  6,  9, 49, 53,  1,138,124,  0,  0,128,128,128,128, 64, 64, 64, 64, 32, 32, 32, 32, 16, 16, 16, 16,  8,  8,  8,  8,  8,196,  4,196,  4,196,  2,194,  2,194,  1,  1,  1,  1,  0,  0,  0,
    0,  0,252, 15,  1,  0,248, 14, 31,109,140,148,148,164,166,249,224,255,224,249,166,164,148,148,140,109, 31, 14,248,  0,  1, 15,252,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,112, 12,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0, 64,160, 33, 34, 18, 17, 17, 17,  9,  8,  8,  8,  8,  4,  4,  4,  4,  4,  4,  2,  2,  2,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,170,170,255,255,195,191,127,  3,127,191,195,255,255,170,170,  0,  0,  0,  0,
    0,  0, 31,120,192,  0, 15, 56,124,219,152, 20, 20, 18, 50,207,  3,255,  3,207, 50, 18, 20, 20,152,219,124, 56, 15,  0,192,120, 31, 16, 16, 16, 16,  8,  8,  8,  8,  8,  4,  4,  4,  4,  4,  2,  3,122,122,121,121,121,121, 57, 49,  2,  2,  4,  4,  8,  8,  8,136,136,135,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,130,135, 31,  7,159,  7, 28,  7,159,  7,159,  7,  2,130,  0,  0,  0,  0,
    32, 16, 16, 16, 17, 11, 14, 12, 24, 16, 49, 35, 98,102, 68, 68, 71, 71, 71, 68, 68,102, 98, 35, 49, 16, 24, 12,  6,  3,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48,120,124,254,255, 63,  7,  0,  0,  0,  0,255,255,127,127, 63, 62, 28, 24,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  8,  8, 23,  0, 15,  1,  2,  1, 15,  0, 15,  2,  5,  8
    },
};
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_master) {
    return OLED_ROTATION_270;
  } else {
    return rotation;
  }
}

void add_keylog(uint16_t keycode) {
  if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
    keycode = keycode & 0xFF;
  }

  for (uint8_t i = 4; i > 0; --i) {
    keylog_str[i] = keylog_str[i - 1];
  }

  if (keycode < 60) {
    keylog_str[0] = code_to_name[keycode];
  }

  log_timer = timer_read();
}

void update_log(void) {
  if (timer_elapsed(log_timer) > 750) {
    add_keylog(0);
  }
}

void render_bootmagic_status(void) {
  if (copy_mode_osx) {
  // if (keymap_config.swap_lalt_lgui) {
    oled_write_P(PSTR("<Mac>"), false);
  } else {
    oled_write_P(PSTR("<Lin>"), false);
  }
}

void render_default_layer_state(void) {
  oled_write_P(PSTR("Base:"), false);
  switch (biton32(default_layer_state)) {
    case _QW:
      oled_write_P(PSTR(" QRTY"), false);
      break;
    case _DH:
      oled_write_P(PSTR(" COLE"), false);
      break;
    case _DV:
      oled_write_P(PSTR(" DVRK"), false);
      break;
  }
}

void render_layer_state(void) {
  oled_write_P(PSTR("Layr:"), false);
  switch (biton32(layer_state)) {
    case 0:
      oled_write_P(PSTR(" DEF "), false);
      break;
    case _RA:
      oled_write_P(PSTR(" RAI "), false);
      break;
    case _LO:
      oled_write_P(PSTR(" LOW "), false);
      break;
    case _AD:
      oled_write_P(PSTR(" ADJ "), false);
      break;
    case _EM:
      oled_write_P(PSTR(" EMO "), false);
      break;
    default:
      oled_write_P(PSTR(" UNK "), false);
      break;
  }
}

void render_keylock_status(uint8_t led_usb_state) {
  oled_write_P(PSTR("Lock:"), false);
  oled_write_P(PSTR(" "), false);
  oled_write_P(PSTR("NUM "), led_usb_state & (1 << USB_LED_NUM_LOCK));
  oled_write_P(PSTR(" "), false);
  oled_write_P(PSTR("CAPS"), led_usb_state & (1 << USB_LED_CAPS_LOCK));
  oled_write_P(PSTR(" "), false);
  oled_write_P(PSTR("SCRL"), led_usb_state & (1 << USB_LED_SCROLL_LOCK));
}

void render_mod_status(uint8_t modifiers) {
  oled_write_P(PSTR("Mods:"), false);
  oled_write_P(PSTR(" "), false);
  oled_write_P(PSTR("SHFT"), (modifiers & MOD_MASK_SHIFT));
  oled_write_P(PSTR(" "), false);
  oled_write_P(PSTR("CTRL"), (modifiers & MOD_MASK_CTRL));
  oled_write_P(PSTR(" "), false);
  oled_write_P(PSTR("GUI "), (modifiers & MOD_MASK_GUI));
  oled_write_P(PSTR(" "), false);
  oled_write_P(PSTR("ALT "), (modifiers & MOD_MASK_ALT));
}

void render_keylogger_status(void) {
  oled_write_P(PSTR("Log: "), false);
  oled_write(keylog_str, false);
}

//assumes 1 frame prep stage
void animation_phase(void) {
  current_tap_frame = (current_tap_frame + 1) % TAP_FRAMES;
  oled_write_raw_P(tap[abs((TAP_FRAMES-1)-current_tap_frame)], ANIM_SIZE);
}


void render_anim(void) {
  if (is_idle) {
    oled_write_P(tap[1], false);
  } else {
    if(anim_timer == 0 || timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
        anim_timer = timer_read32();
        animation_phase();
    }
  }
}


void render_status_main(void) {
  render_bootmagic_status();
  render_default_layer_state();
  render_layer_state();
  render_keylock_status(host_keyboard_leds());
  render_mod_status(get_mods()|get_oneshot_mods());
  render_keylogger_status();
}

void render_status_secondary(void) {
  if (idle_timer == 0) {
    is_idle = true;
  } else if (timer_elapsed(idle_timer) < IDLE_TIMEOUT) {
    is_idle = false;
  } else {
    if (!is_idle) {
      is_idle = true;
      anim_timer = 0;
      current_tap_frame = 0;
    }
  }
  render_anim();
  oled_set_cursor(0,6);
}

void oled_task_user(void) {
  if (idle_timer == 0 || timer_elapsed(idle_timer) > IDLE_SLEEP) {
    if (is_oled_on()) {
      oled_off();
      idle_timer = 0;
    }
    return;
  }

  if (!is_oled_on()) {
    oled_on();
  }

  update_log();
  if (is_master) {
    render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
  } else {
    render_status_secondary();
  }
}