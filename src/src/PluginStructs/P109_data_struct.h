#ifndef PLUGINSTRUCTS_P109_DATA_STRUCT_H
#define PLUGINSTRUCTS_P109_DATA_STRUCT_H

#include "../../_Plugin_Helper.h"
#ifdef USES_P109

# include "../Globals/ESPEasyWiFiEvent.h"
# include "../Helpers/OLed_helper.h"

# include "SSD1306.h"
# include "SH1106Wire.h"
# include "Dialog_Plain_12_font.h" // Part of the OLED library
# include "Dialog_Plain_18_font.h"

# define P109_Nlines            1
# define P109_Nchars            32

const char flameimg[] PROGMEM = {
  0x00, 0x20, 0x00, 0x00, 0x70, 0x00,
  0x00, 0x78, 0x00, 0x00, 0x7c, 0x00,
  0x00, 0x7c, 0x00, 0x80, 0x7f, 0x00,
  0xc0, 0xff, 0x00, 0xc0, 0xff, 0x00,
  0xe0, 0xff, 0x04, 0xe0, 0xff, 0x05,
  0xf0, 0xff, 0x0f, 0xf0, 0xff, 0x0f,
  0xf8, 0xff, 0x0f, 0xf8, 0xff, 0x1f,
  0xf8, 0xff, 0x1f, 0xf8, 0xff, 0x3f,
  0xf8, 0xff, 0x3f, 0xf8, 0xf3, 0x3f,
  0xf8, 0xf1, 0x3f, 0xf8, 0xf1, 0x3f,
  0xf8, 0xe1, 0x3f, 0xf0, 0x21, 0x3f,
  0xf0, 0x01, 0x1f, 0xe0, 0x01, 0x0f,
  0xc0, 0x01, 0x0f, 0x80, 0x01, 0x07,
  0x00, 0x03, 0x01
};

# define P109_WIFI_STATE_UNSET          -2
# define P109_WIFI_STATE_NOT_CONNECTED  -1
# define P109_TEMP_STATE_UNSET          99.0f
# define P109_SETPOINT_STATE_UNSET      0.0f
# define P109_SETPOINT_STATE_INITIAL    19.0f
# define P109_TIMEOUT_STATE_UNSET       32768.0f
# define P109_HEATING_STATE_UNSET       255
# define P109_MODE_STATE_UNSET          255
# define P109_MODE_STATE_INITIAL        1
# define P109_BUTTON_DEBOUNCE_TIME_MS   300

# define P109_CONFIG_I2CADDRESS         PCONFIG(0)
# define P109_CONFIG_ROTATION           PCONFIG(1)
# define P109_CONFIG_DISPLAYTYPE        PCONFIG(2)
# define P109_CONFIG_CONTRAST           PCONFIG(3)
# define P109_CONFIG_RELAYPIN           PCONFIG(4)
# define P109_CONFIG_HYSTERESIS         PCONFIG_FLOAT(0)

struct P109_data_struct : public PluginTaskData_base {
  P109_data_struct();
  ~P109_data_struct();

  bool plugin_init(struct EventStruct *event);
  bool plugin_exit(struct EventStruct *event);
  bool plugin_ten_per_second(struct EventStruct *event);
  bool plugin_once_a_second(struct EventStruct *event);
  bool plugin_read(struct EventStruct *event);
  bool plugin_write(struct EventStruct *event,
                    String            & string);
  bool plugin_webform_load(struct EventStruct *event);
  bool plugin_webform_save(struct EventStruct *event);

private:

  OLEDDisplay *_display = nullptr;

  uint32_t _lastsavetime = 0;
  uint32_t _buttons[3];

  float _prev_temp     = P109_TEMP_STATE_UNSET;
  float _prev_setpoint = P109_SETPOINT_STATE_UNSET;
  float _prev_timeout  = P109_TIMEOUT_STATE_UNSET;

  int8_t  _lastWiFiState = P109_WIFI_STATE_UNSET;
  uint8_t _prev_heating  = P109_HEATING_STATE_UNSET;
  uint8_t _prev_mode     = P109_MODE_STATE_UNSET;
  uint8_t _taskIndex     = 0;
  uint8_t _varIndex      = 0;
  uint8_t _changed       = 0;
  uint8_t _saveneeded    = 0;
  int8_t  _relaypin      = -1;

  char _deviceTemplate[P109_Nlines][P109_Nchars];

  bool _initialized  = false;
  bool _showWiFiName = true;

  void display_header();
  void display_time();
  void display_title(const String& title);
  bool display_wifibars();
  void display_current_temp();
  void display_setpoint_temp(const uint8_t& force = 0);
  void display_timeout();
  void display_mode();
  void display_heat();
  void display_page();
  void setSetpoint(const String& sptemp);
  void setHeatRelay(const uint8_t& state);
  void setHeater(const String& heater);
  void setMode(const String& amode,
               const String& atimeout);
};

#endif // ifdef USES_P109
#endif // ifndef PLUGINSTRUCTS_P109_DATA_STRUCT_H
