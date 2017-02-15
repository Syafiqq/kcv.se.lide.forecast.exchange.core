//
// Created by syafiq on 12/22/16.
//

#ifndef CORE_KCV_SE_LIDE_FORCAST_CURRENCY_EEXCHANGE_H
#define CORE_KCV_SE_LIDE_FORCAST_CURRENCY_EEXCHANGE_H

#include <iostream>
#include <vector>

class EExchange
{
    public:
    EExchange(int base, int to, const std::string date, double value, double predicted);

    int getBase() const;
    void setBase(int base);
    int getTo() const;
    void setTo(int to);
    const std::string &getDate() const;
    void setDate(const std::string &date);
    double getValue() const;
    void setValue(double value);
    double getPredicted() const;
    void setPredicted(double predicted);
    static const std::vector<double> sanitizeValue(const std::vector<EExchange> value);

    private:
    int base, to;
    std::string date;
    double value, predicted;
};


#endif //CORE_KCV_SE_LIDE_FORCAST_CURRENCY_EEXCHANGE_H
