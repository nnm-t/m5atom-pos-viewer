#pragma once

#include "Arduino.h"
#include "M5Atom.h"

#include "TM1637Display.h"

class POSPrice
{
    TM1637Display& _tm1637;
    int _num = 0;
    bool _leading_zero = false;

public:
    POSPrice(TM1637Display& tm1637) : _tm1637(tm1637)
    {

    }

    void SetBrightness(const uint8_t brightness, const bool is_on = true);

    void ShowNumberDec(const int num, const bool leading_zero = false);

    void Reset()
    {
        ShowNumberDec(0);
    }

    void Update();
};