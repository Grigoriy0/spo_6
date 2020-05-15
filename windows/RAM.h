
#ifndef WINDOWS_RAM_H
#define WINDOWS_RAM_H
#define uint16_t unsigned short
#define uint8_t unsigned char

#include <limits.h>
constexpr uint16_t RAM_SIZE = USHRT_MAX;
uint8_t RAM[RAM_SIZE];
static bool busyRAM[RAM_SIZE] = {};

#endif //WINDOWS_RAM_H
