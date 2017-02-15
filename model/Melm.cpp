/*
 * This <core_kcv_se_lide_forcast_currency> project created by : 
 * Name         : syafiq
 * Date / Time  : 29 December 2016, 4:14 PM.
 * Email        : syafiq.rezpector@gmail.com
 * Github       : syafiqq
 */

#include "Melm.h"
#include <cassert>

void Melm::registerMetadata(int feature, const arma::Mat<double> &weight, const arma::Mat<double> &bias,
                            const CurrencyBound bound, bool isBiasEnable)
{
    this->feature = feature;
    this->w = weight;
    this->b = bias;
    this->bound = bound;
    this->biasEnable = isBiasEnable;
}

void Melm::learn(const std::vector<Dataset> *data)
{
    std::cout << '\n' << "===BEGIN TRAINING===" << std::endl;
    const std::vector<Dataset> norm = this->generateNormalization(data);
    std::cout << "Normalize Training" << std::endl;
    this->__printVector3(norm);
    this->calculateELMTraining(&norm);
}

double Melm::testAccuracy(std::vector<Dataset> *data)
{
    std::cout << '\n' << "===BEGIN TESTING===" << std::endl;
    const std::vector<Dataset> norm = this->generateNormalization(data);
    std::cout << "Normalize Testing" << std::endl;
    this->__printVector3(norm);
    arma::mat _y = this->calculateELMTesting(&norm);
    //this->assignPrediction(data, &_y);
    return this->calculateAccuracy(&norm, &_y);
}

arma::mat Melm::calculateELMTraining(const std::vector<Dataset> *data)
{
    arma::mat X = this->generateDataMatrix(data);
    arma::mat y = this->generateActualClass(data);
    arma::mat H = this->calculateH(&X);
    arma::mat MPPI = arma::pinv(H);
    std::cout << "M-P PI" << '\n' << MPPI << std::endl;
    std::cout << "y" << '\n' << y << std::endl;
    //this->betaTopi = (inv(H.t() * H) * H.t()) * y;
    this->betaTopi = MPPI * y;
    std::cout << "Beta Topi" << '\n' << this->betaTopi << std::endl;
    return H;
}

arma::mat Melm::calculateELMTesting(const std::vector<Dataset> *data)
{
    arma::mat X = this->generateDataMatrix(data);
    arma::mat _y = this->calculateH(&X) * this->betaTopi;
    std::cout << "Nilai Prediksi" << '\n' << _y << std::endl;
    return _y;
}

arma::mat Melm::generateDataMatrix(const std::vector<Dataset> *data)
{
    arma::mat matrix((*data).size(), (const arma::uword) this->feature);
    int _c = -1;
    for(std::vector<Dataset>::const_iterator i = (*data).begin(), is = (*data).end(); i != is; ++i )
    {
        ++_c;
        double *param = (*i).getParameter();
        for(int j = -1, js = this->feature; ++j < js;)
        {
            matrix(_c, j) = param[j];
        }
    }
    return matrix;
}

std::vector<Dataset> Melm::generateNormalization(const std::vector<Dataset> *data)
{
    std::vector<Dataset> norm;
    const double range = this->bound.getRange();
    const double min = this->bound.getMin();
    for(std::vector<Dataset>::const_iterator i = (*data).begin(), is = (*data).end(); i != is; ++i )
    {
        double *param = (*i).getParameter();
        double *tmpparam = new double[this->feature];
        for(int j = -1, js = this->feature; ++j < js;)
        {
            tmpparam[j] = (param[j] - this->bound.getMin()) / this->bound.getRange();
        }
        norm.push_back(Dataset(tmpparam,
                               ((*i).getActual() - min) / range,
                               (*i).getPredicted()
        ));
    }
    return norm;
}

arma::mat Melm::generateActualClass(const std::vector<Dataset> *data)
{
    arma::mat matrix((*data).size(), 1);
    int _c = -1;
    for(std::vector<Dataset>::const_iterator i = (*data).begin(), is = (*data).end(); i != is; ++i )
    {
        matrix(++_c, 0) = (*i).getActual();
    }
    return matrix;
}

arma::mat Melm::calculateH(const arma::Mat<double> *dataset)
{
    arma::mat hInit = (*dataset) * this->w;
    std::cout << '\n' << "Perhitungan H" << std::endl;
    std::cout << "H_Init" << '\n' << hInit << std::endl;
    if(this->biasEnable)
    {
        arma::mat _bias = arma::ones(dataset->n_rows, 1) * this->b;
        std::cout << "Bias" << '\n' << _bias << std::endl;
        hInit += _bias;
    }
    hInit.each_row([this](arma::rowvec &a)
                   {
                       int _c = -1;
                       for (arma::rowvec::col_iterator i = a.begin(), is = a.end(); i != is; ++i)
                       {
                           (*i) = (1.0 / (1.0 + exp(-(*i))));
                       }
                   });
    std::cout << "H" << '\n' << hInit << std::endl;
    return hInit;
}

void Melm::assignPrediction(std::vector<Dataset> *dataset, arma::mat *_y)
{
    assert ((*dataset).size() == (*_y).size());
    int _c = -1;
    double range = this->bound.getRange();
    double min = this->bound.getMin();
    for(std::vector<Dataset>::iterator i = (*dataset).begin() -1, is = (*dataset).end(); ++i < is; )
    {
        (*i).setPredicted(((*_y)(++_c, 0) * range) + min);
    }
}

double Melm::calculateAccuracy(const std::vector<Dataset> *normDataset, arma::mat *_y)
{
    std::cout << "Akurasi" << std::endl;

    assert ((*normDataset).size() == (*_y).size());
    double accuracy = 0.0;
    int _c = -1;
    for(std::vector<Dataset>::const_iterator i = (*normDataset).begin() -1, is = (*normDataset).end(); ++i < is; )
    {
        const double actual = (*i).getActual();
        double __val = (abs((((*_y)(++_c, 0) - actual) / actual) * 100));
        std::cout << __val << '\t';
        accuracy += __val;
    }
    std::cout << std::endl << "Akurasi" << '\t' << accuracy << '\t' << (_c + 1) << "\t=\t";
    accuracy /= ++_c;
    std::cout << accuracy << std::endl;
    return accuracy;
}

void Melm::__printVector3(const std::vector<Dataset> data)
{
    int no = 0;
    for (std::vector<Dataset>::const_iterator i = data.begin(); i != data.end(); i++)
    {

        std::cout << ++no
                  << '\t';
        for (int j = -1, js = this->feature; ++j < js;)
        {
            std::cout << i->getParameter()[j]
                      << '\t';
        }
        std::cout << '\t'
                  << i->getActual()
                  << '\t'
                  << i->getPredicted()
                  << std::endl;
    }
}
