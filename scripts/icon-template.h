/**
 * Icon header template
 * For use with the ugui python open-iconic -> sprite generator
 * See build-iconic.py
 *
 * Template: {{template}}
 * Scale: {{scale}}
 */

#include <stdint.h>

#ifndef ICONS_{{scale}}X_H
#define ICONS_{{scale}}X_H

{{#icons}}
uint8_t icon_{{name}}[{{size}}];
{{/icons}}

#endif
