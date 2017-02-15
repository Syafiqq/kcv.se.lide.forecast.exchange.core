/*
 * This <core_kcv_se_lide_forcast_currency> project created by : 
 * Name         : syafiq
 * Date / Time  : 29 December 2016, 3:40 PM.
 * Email        : syafiq.rezpector@gmail.com
 * Github       : syafiqq
 */

#ifndef CORE_KCV_SE_LIDE_FORCAST_CURRENCY_CURRENCYBOUND_H
#define CORE_KCV_SE_LIDE_FORCAST_CURRENCY_CURRENCYBOUND_H

#ifndef _GLIBCXX_VECTOR
    #include <vector>
#endif

class CurrencyBound
{
    private:
    double min, max, range;

    public:
    CurrencyBound();
    CurrencyBound(double min, double max);
    void validate();
    void setFromList(const std::vector<double> &list);
    double getMin() const;
    void setMin(double min);
    double getMax() const;
    void setMax(double max);
    double getRange() const;
    void calculateRange();
};


#endif //CORE_KCV_SE_LIDE_FORCAST_CURRENCY_CURRENCYBOUND_H
