/**
 * Icon source template
 * For use with the ugui python openiconic -> sprite generator
 * See build-iconic.py
 */

#include <stdint.h>

{{#icons}}
uint8_t icon_{{name}}_x{{scale}}[] = { {{data}} };
{{/icons}}
