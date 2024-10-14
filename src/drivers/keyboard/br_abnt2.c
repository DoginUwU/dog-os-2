#include "br_abnt2.h"

KeyMapping layout_abnt_2[] = {
    {0x1E, 'a'},
    {0x30, 'b'},
};

KeyboardLayout keyboard_br_abnt2 = {layout_abnt_2,
                                    sizeof(layout_abnt_2) / sizeof(KeyMapping)};
