#include "Common.h"


// Variables needed by OLD style
#define BRIGHTNESS_START                  5
int brightness_set      =  BRIGHTNESS_START;
int brightness_err      =                 0;

void handle_brightness_old();
void handle_brightness_log();
void handle_brightness_exp();