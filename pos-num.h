#pragma once

#include "Arduino.h"
#include "M5Atom.h"

#include "matrix-number.h"

class POSNum
{
public:
    void SetBrightness(const uint8_t brightness);

    const bool DrawNumber(const uint8_t number);

    void Reset()
    {
        DrawNumber(0);
    }
};