//
// Created by grish on 14.05.2020.
//

#ifndef WINDOWS_PTR_T_H
#define WINDOWS_PTR_T_H

#include "RAM.h"
#define null_ptr ptr_t{0}
namespace ptr {

    struct ptr_t {
        ptr_t() = default;

        ptr_t(uint16_t in) : index(in) {}


        template <typename T>
        operator T(){
            return reinterpret_cast<T>(&RAM[this->index]);
        }

    private:
        uint16_t index;

        friend ptr_t malloc(uint16_t);

        friend ptr_t calloc(uint16_t);

        friend void free(ptr_t);
    };

    ptr_t malloc(uint16_t size) {
        uint16_t index = 0;
        uint8_t required = size + 1;
        do {
            while (bitArray[index] && index < RAM_SIZE)
                index++;
            if (index != RAM_SIZE) {
                uint16_t j;
                for (j = index; j < required; ++j) {
                    if (bitArray[j]) {
                        j = 0;
                        break;
                    }
                }
                if (j != 0)
                    break;
            }
            ++index;
        } while (index < RAM_SIZE);
        if (index == RAM_SIZE)
            return null_ptr;
        ptr_t result(index);
        bitArray[index] = true;
        RAM[index] = size;
        for (uint8_t i = 0; i < required; ++i) {
            bitArray[index + i] = true;
        }
        return result;
    }

    ptr_t calloc(uint16_t size) {
        ptr_t result = malloc(size);
        for (uint8_t i = result.index + 1; i < size; ++i) {
            RAM[i] = 0;
        }
        return result;
    }

    void free(ptr_t ptr) {
        for (uint16_t i = ptr.index; i < RAM[ptr.index - 1]; ++i) {
            bitArray[i] = false;
        }
    }
} // namespace ptr
#endif //WINDOWS_PTR_T_H
