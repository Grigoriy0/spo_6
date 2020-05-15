//
// Created by grish on 14.05.2020.
//

#ifndef WINDOWS_PTR_T_H
#define WINDOWS_PTR_T_H

#include <string.h>
#include <stdio.h>

#include "RAM.h"
namespace ptr {

#define null_ptr ptr_t{}
    struct ptr_t {

    private:
        uint16_t index;
        explicit ptr_t(uint16_t in) : index(in) {}

        friend ptr_t malloc(uint16_t);

        friend ptr_t calloc(uint16_t, uint8_t);

        friend ptr_t realloc(ptr_t oldptr, uint16_t newsize);

        friend void free(ptr_t);

    public:
        ptr_t(){
            index = 0;
        };

        ptr_t(const ptr_t& other){
            index = other.index;
        }

        template <typename T>
        operator T(){
            return reinterpret_cast<T>(&RAM[index]);
        }

        bool operator==(const ptr_t &other) const{
            return index == other.index;
        }

        bool operator!=(const ptr_t &other) const{
            return index != other.index;
        }

        void info() const{
            printf("0x%x:%u\n", index, RAM[index - 1] - 1);
        }

    };

    ptr_t malloc(uint16_t size) {
        if (size == 0)
            return null_ptr;
        uint16_t index = 1;
        ++size;
        do {
            while (busyRAM[index] && index < RAM_SIZE)
                index++;
            if (index < RAM_SIZE) {
                uint16_t j;
                bool busy = false;
                for (j = index; j < size; ++j) {
                    if (busyRAM[j]) {
                        busy = true;
                        break;
                    }
                    if (j == RAM_SIZE)
                        return null_ptr;
                }
                if (busy)
                    index++;
                else break;
            }
        } while (index < RAM_SIZE);
        if (index == RAM_SIZE)
            return null_ptr;
        index++;
        RAM[index - 1] = size;
        for (uint8_t i = 0; i < size - 1; ++i) {
            busyRAM[index + i] = true;
        }
        ptr_t result(index);
        return result;
    }

    ptr_t calloc(uint16_t size, uint8_t count) {
        ptr_t result = malloc(size * count);
        if (result == null_ptr)
            return null_ptr;
        memset(&RAM[result.index], 0, size * count);
        return result;
    }

    ptr_t realloc(ptr_t oldptr, uint16_t newsize) {
        uint16_t index = oldptr.index + RAM[oldptr.index - 1];
        newsize++;
        do {
            while (busyRAM[index] && index < RAM_SIZE)
                index++;
            if (index < RAM_SIZE) {
                uint16_t j;
                bool busy = false;
                for (j = index; j < newsize; ++j) {
                    if (busyRAM[j]) {
                        busy = true;
                        break;
                    }
                    if (j == RAM_SIZE)
                        return null_ptr;
                }
                if (busy)
                    index++;
                else break;
            }
        } while (index < RAM_SIZE);
        if (index == RAM_SIZE)
            return null_ptr;
        memcpy(&RAM[index + 1], &RAM[oldptr.index], RAM[oldptr.index - 1]);
        free(oldptr);
        RAM[index] = newsize;
        for (uint8_t i = 0; i < newsize; ++i) {
            busyRAM[index + i] = true;
        }
        return ptr_t(index + 1);
    }


    void free(ptr_t ptr) {
        if (ptr == null_ptr)return;
        for (uint16_t i = ptr.index; i < RAM[ptr.index - 1]; ++i) {
            busyRAM[i] = false;
        }
    }

} // namespace ptr
#endif //WINDOWS_PTR_T_H
