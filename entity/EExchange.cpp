//
// Created by syafiq on 12/22/16.
//

#include "EExchange.h"

EExchange::EExchange(int base, int to, const std::string date, double value, double predicted): base(base), to(to),
                                                                                           date(date), value(value),
                                                                                           predicted(predicted)
{

}

int EExchange::getBase() const
{
    return this->base;
}

void EExchange::setBase(int base)
{
    EExchange::base = base;
}

int EExchange::getTo() const
{
    return this->to;
}

void EExchange::setTo(int to)
{
    EExchange::to = to;
}

const std::string &EExchange::getDate() const
{
    return this->date;
}

void EExchange::setDate(const std::string &date)
{
    EExchange::date = date;
}

double EExchange::getValue() const
{
    return this->value;
}

void EExchange::setValue(double value)
{
    EExchange::value = value;
}

double EExchange::getPredicted() const
{
    return this->predicted;
}

void EExchange::setPredicted(double predicted)
{
    EExchange::predicted = predicted;
}

const std::vector<double> EExchange::sanitizeValue(const std::vector<EExchange> value)
{
    std::vector<double> result;
    for(std::vector<EExchange>::const_iterator i = value.begin(), is = value.end(); i != is; ++i)
    {
        result.push_back(i->getValue());
    }
    return result;
}
