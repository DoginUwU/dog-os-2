#include <drivers/keyboard/br_abnt2.h>

key_mapping_t layout[] = {
    {0x1E, 'a'},
};

keyboard_layout_t keyboard_br_abnt2 = {layout,
                                       sizeof(layout) / sizeof(key_mapping_t)};
