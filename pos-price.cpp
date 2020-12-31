#include "pos-price.h"

void POSPrice::SetBrightness(const uint8_t brightness, const bool is_on)
{
    _tm1637.setBrightness(brightness, is_on);
}

void POSPrice::ShowNumberDec(const int num, const bool leading_zero)
{
    _num = num;
    _leading_zero = leading_zero;
}

void POSPrice::Update()
{
    _tm1637.showNumberDec(_num, _leading_zero);
}