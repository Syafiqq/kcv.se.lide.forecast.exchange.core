/*
 * This <core_kcv_se_lide_forcast_currency> project created by : 
 * Name         : syafiq
 * Date / Time  : 29 December 2016, 3:40 PM.
 * Email        : syafiq.rezpector@gmail.com
 * Github       : syafiqq
 */

#include <cassert>
#include <algorithm>
#include "CurrencyBound.h"

CurrencyBound::CurrencyBound(double min, double max) : min(min), max(max)
{
    this->calculateRange();
}

double CurrencyBound::getRange() const
{
    return this->range;
}

double CurrencyBound::getMin() const
{
    return this->min;
}

void CurrencyBound::setMin(double min)
{
    this->min = min;
    this->calculateRange();
}

double CurrencyBound::getMax() const
{
    return this->max;
}

void CurrencyBound::setMax(double max)
{
    this->max = max;
    this->calculateRange();
}

void CurrencyBound::calculateRange()
{
    this->range = this->max - this->min;
}

void CurrencyBound::setFromList(const std::vector<double> &list)
{
    std::vector<double>::const_iterator val = std::min_element(std::begin(list), std::end(list), [](double x, double y)
    {
        return x < y;
    });
    if (std::end(list) != val )
    {
        this->setMin(*val);
    }

    val = std::max_element(std::begin(list), std::end(list), [](double x, double y)
    {
        return x < y;
    });
    if (std::end(list) != val )
    {
        this->setMax(*val);
    }

    this->validate();
}

CurrencyBound::CurrencyBound() : min(0), max(0)
{

}

void CurrencyBound::validate()
{
    assert (this->max >= this->min);
}
