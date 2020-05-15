//
// Created by grish on 14.05.2020.
//

#ifndef WINDOWS_RAM_H
#define WINDOWS_RAM_H
#define uint16_t unsigned short
#define uint8_t unsigned char

#include <limits.h>
constexpr uint16_t RAM_SIZE = USHRT_MAX;
uint8_t RAM[RAM_SIZE];
bool bitArray[RAM_SIZE] = {};

#endif //WINDOWS_RAM_H
