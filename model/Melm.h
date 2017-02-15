/*
 * This <core_kcv_se_lide_forcast_currency> project created by : 
 * Name         : syafiq
 * Date / Time  : 29 December 2016, 4:14 PM.
 * Email        : syafiq.rezpector@gmail.com
 * Github       : syafiqq
 */

#ifndef CORE_KCV_SE_LIDE_FORCAST_CURRENCY_MELM_H
#define CORE_KCV_SE_LIDE_FORCAST_CURRENCY_MELM_H

#include <armadillo>
#include "util/CurrencyBound.h"
#include "Dataset.h"

class Melm
{
    public :
    void registerMetadata(int feature, const arma::Mat<double> &weight, const arma::Mat<double> &bias, const CurrencyBound bound, bool isBiasEnable);
    void learn(const std::vector<Dataset> *data);
    double testAccuracy(std::vector<Dataset> *data);

    private:
    int feature;
    arma::mat w;
    arma::mat b;
    arma::mat betaTopi;
    CurrencyBound bound;
    bool biasEnable;

    arma::mat calculateELMTraining(const std::vector<Dataset> *vector);
    std::vector<Dataset> generateNormalization(const std::vector<Dataset> *data);
    arma::mat generateDataMatrix(const std::vector<Dataset> *vector);
    arma::mat generateActualClass(const std::vector<Dataset> *data);
    arma::mat calculateH(const arma::Mat<double> *dataset);
    arma::mat calculateELMTesting(const std::vector<Dataset> *data);
    void assignPrediction(std::vector<Dataset> *dataset, arma::mat *_y);
    double calculateAccuracy(const std::vector<Dataset> *normDataset, arma::mat *_y);
    void __printVector3(const std::vector<Dataset> vector);
};


#endif //CORE_KCV_SE_LIDE_FORCAST_CURRENCY_MELM_H
