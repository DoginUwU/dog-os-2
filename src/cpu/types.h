#ifndef TYPES_H
#define TYPES_H

/*typedef unsigned long long uint64_t;*/
/*typedef long long int64_t;*/
typedef unsigned int uint32_t;
typedef signed int int32_t;
typedef unsigned short uint16_t;
typedef signed short int16_t;
typedef unsigned char uint8_t;
typedef signed char int8_t;

typedef typeof(sizeof(0)) size_t;

#define low_16(address) (uint16_t)((address) & 0xFFFF)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

#define low_8(address) (uint8_t)((address) & 0xFF)
#define high_8(address) (uint8_t)(((address) >> 8) & 0xFF)

#endif
