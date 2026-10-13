/*

This supplies missing Arduino print features required by Adafruit GFX.
The small Print class provides print(), println(), and write() functions used for drawing text.
The pgm_read_* macros let Adafruit GFX read font and image data from memory.

*/



#ifndef WPROGRAM_H
#define WPROGRAM_H

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <string>

using String = std::string;

class __FlashStringHelper;

typedef uint8_t byte;
typedef bool boolean;

#ifndef PROGMEM
#define PROGMEM
#endif

#ifndef pgm_read_byte
#define pgm_read_byte(address) (*(const uint8_t *)(address))
#endif

#ifndef pgm_read_word
#define pgm_read_word(address) (*(const uint16_t *)(address))
#endif

#ifndef pgm_read_dword
#define pgm_read_dword(address) (*(const uint32_t *)(address))
#endif

// #ifndef pgm_read_pointer
// #define pgm_read_pointer(address) (*(const void *const *)(address))
// #endif

class Print {
public:
    virtual ~Print() = default;

    virtual size_t write(uint8_t value) = 0;

    size_t write(const uint8_t *buffer, size_t size)
    {
        size_t written = 0;

        while (size--) {
            written += write(*buffer++);
        }

        return written;
    }

    size_t write(const char *text)
    {
        if (text == nullptr) {
            return 0;
        }

        return write(
            reinterpret_cast<const uint8_t *>(text),
            strlen(text)
        );
    }

    size_t print(const char *text)
    {
        return write(text);
    }

    size_t println(const char *text)
    {
        size_t written = print(text);
        written += write(static_cast<uint8_t>('\r'));
        written += write(static_cast<uint8_t>('\n'));
        return written;
    }
};

inline float radians(float degrees)
{
    return degrees * 0.01745329251994329577f;
}

#endif