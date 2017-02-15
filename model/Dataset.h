/*
 * This <core_kcv_se_lide_forcast_currency> project created by : 
 * Name         : syafiq
 * Date / Time  : 29 December 2016, 7:10 PM.
 * Email        : syafiq.rezpector@gmail.com
 * Github       : syafiqq
 */

#ifndef CORE_KCV_SE_LIDE_FORCAST_CURRENCY_DATASET_H
#define CORE_KCV_SE_LIDE_FORCAST_CURRENCY_DATASET_H



class Dataset
{
    public:
    Dataset(double *parameter, double actual, double predicted);
    virtual ~Dataset();

    double *getParameter() const;
    void setParameter(double *parameter);
    double getActual() const;
    void setActual(double actual);
    double getPredicted() const;
    void setPredicted(double predicted);

    private :
    double * parameter;
    double actual;
    double predicted;
};


#endif //CORE_KCV_SE_LIDE_FORCAST_CURRENCY_DATASET_H
