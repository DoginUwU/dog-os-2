#include <drivers/keyboard/br_abnt2.h>

key_mapping_t layout[] = {
    {0x02, '1'},
    {0x03, '2'},
    {0x04, '3'},
    {0x05, '4'},
    {0x06, '5'},
    {0x07, '6'},
    {0x08, '7'},
    {0x09, '8'},
    {0x0A, '9'},
    {0x0B, '0'},
    {0x0C, '-'},
    {0x0D, '='},
    /*{0x0E, '\0'}, Backspace */
    /*{0x0F, 'Tab'}, Tab */
    {0x10, 'q'},
    {0x11, 'w'},
    {0x12, 'e'},
    {0x13, 'r'},
    {0x14, 't'},
    {0x15, 'y'},
    {0x16, 'u'},
    {0x17, 'i'},
    {0x18, 'o'},
    {0x19, 'p'},
    /*{0x1A, '´'},*/
    {0x1B, '['},
    /*{0x1C, '\n'}, Enter */
    /*{0x1D, 'Ctrl'}, Ctrl */
    {0x1E, 'a'},
    {0x1F, 's'},
    {0x20, 'd'},
    {0x21, 'f'},
    {0x22, 'g'},
    {0x23, 'h'},
    {0x24, 'j'},
    {0x25, 'k'},
    {0x26, 'l'},
    /*{0x27, 'ç'},*/
    /*{0x28, '~'},*/
    {0x29, '\''},
    /*{0x2A, 'Shift'}, Shift */
    {0x2B, ']'},
    {0x2C, 'z'},
    {0x2D, 'x'},
    {0x2E, 'c'},
    {0x2F, 'v'},
    {0x30, 'b'},
    {0x31, 'n'},
    {0x32, 'm'},
    {0x33, ','},
    {0x34, '.'},
    {0x35, ';'},
    /*{0x36, 'R Shift'}, R Shift */
    {0x37, '*'},
    /*{0x38, 'Alt'}, Alt */
    {0x39, ' '},
};

keyboard_layout_t keyboard_br_abnt2 = {layout,
                                       sizeof(layout) / sizeof(key_mapping_t)};
