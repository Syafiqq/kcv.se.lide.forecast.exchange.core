/*
 * This <core_kcv_se_lide_forcast_currency> project created by : 
 * Name         : syafiq
 * Date / Time  : 29 December 2016, 7:10 PM.
 * Email        : syafiq.rezpector@gmail.com
 * Github       : syafiqq
 */

#include "Dataset.h"

Dataset::Dataset(double *parameter, double actual, double predicted) : parameter(parameter), actual(actual),
                                                                        predicted(predicted)
{

}

double *Dataset::getParameter() const
{
    return this->parameter;
}

void Dataset::setParameter(double *parameter)
{
    Dataset::parameter = parameter;
}

double Dataset::getActual() const
{
    return this->actual;
}

void Dataset::setActual(double actual)
{
    Dataset::actual = actual;
}

double Dataset::getPredicted() const
{
    return this->predicted;
}

void Dataset::setPredicted(double predicted)
{
    Dataset::predicted = predicted;
}

Dataset::~Dataset()
{
}
