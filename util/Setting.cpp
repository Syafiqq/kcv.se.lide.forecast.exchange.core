//
// Created by syafiq on 12/22/16.
//

#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include "Setting.h"

Setting::Setting()
{
    this->setParameterCount(-1);
    this->setTestingCount(-1);
    this->setTrainingCount(-1);
    this->setFrom(-1);
    this->setTo(-1);
    this->setBiasMin(-1);
    this->setBiasMax(-1);
    this->setWeightMin(-1);
    this->setWeightMax(-1);
    this->setInputLayerCount(-1);
    this->setHiddenLayerCount(-1);
}

Setting::~Setting()
{

}

int Setting::getTrainingCount() const
{
    return this->trainingCount;
}

void Setting::setTrainingCount(int trainingCount)
{
    Setting::trainingCount = trainingCount;
}

int Setting::getParameterCount() const
{
    return this->parameterCount;
}

void Setting::setParameterCount(int parameterCount)
{
    Setting::parameterCount = parameterCount;
    Setting::inputLayerCount = parameterCount;
}

int Setting::getTestingCount() const
{
    return this->testingCount;
}

void Setting::setTestingCount(int testingCount)
{
    Setting::testingCount = testingCount;
}

int Setting::getFrom() const
{
    return this->from;
}

void Setting::setFrom(int from)
{
    Setting::from = from;
}

int Setting::getTo() const
{
    return this->to;
}

void Setting::setTo(int to)
{
    Setting::to = to;
}

const std::string &Setting::getDBHost() const
{
    return this->DBHost;
}

void Setting::setDBHost(const std::string &DBHost)
{
    Setting::DBHost = DBHost;
}

const std::string &Setting::getDBUsername() const
{
    return this->DBUsername;
}

void Setting::setDBUsername(const std::string &DBUsername)
{
    Setting::DBUsername = DBUsername;
}

const std::string &Setting::getDBPassword() const
{
    return this->DBPassword;
}

void Setting::setDBPassword(const std::string &DBPassword)
{
    Setting::DBPassword = DBPassword;
}

const std::string &Setting::getDBSchema() const
{
    return this->DBSchema;
}

void Setting::setDBSchema(const std::string &DBSchema)
{
    Setting::DBSchema = DBSchema;
}

double Setting::getBiasMin() const
{
    return this->biasMin;
}

void Setting::setBiasMin(double biasMin)
{
    Setting::biasMin = biasMin;
}

double Setting::getBiasMax() const
{
    return this->biasMax;
}

void Setting::setBiasMax(double biasMax)
{
    Setting::biasMax = biasMax;
}

double Setting::getWeightMin() const
{
    return this->weightMin;
}

void Setting::setWeightMin(double weightMin)
{
    Setting::weightMin = weightMin;
}

double Setting::getWeightMax() const
{
    return this->weightMax;
}

void Setting::setWeightMax(double weightMax)
{
    Setting::weightMax = weightMax;
}

int Setting::getInputLayerCount() const
{
    return this->inputLayerCount;
}

int Setting::getHiddenLayerCount() const
{
    return this->hiddenLayerCount;
}

void Setting::setHiddenLayerCount(int hiddenLayerCount)
{
    Setting::hiddenLayerCount = hiddenLayerCount;
}

void Setting::setInputLayerCount(int inputLayerCount)
{
    Setting::inputLayerCount = inputLayerCount;
}

bool Setting::isBiasEnable() const
{
    return this->biasEnable;
}

void Setting::setBiasEnable(bool biasEnable)
{
    Setting::biasEnable = biasEnable;
}

const arma::mat Setting::generateBias(arma::Mat<double> matrix, int hiddenSize, double lowerBound, double upperBound)
{
    int inputSize = 1;
    base_generator_type generator((const uint32_t &) (std::chrono::system_clock::now()).time_since_epoch().count());
    boost::uniform_real<> uni_dist(lowerBound, upperBound);
    boost::variate_generator<base_generator_type&, boost::uniform_real<> > uni(generator, uni_dist);

    if ((matrix.n_rows != inputSize) || (matrix.n_cols != hiddenSize))
    {
        matrix = arma::mat((const arma::uword) inputSize, (const arma::uword) hiddenSize, arma::fill::zeros);
    }

    for (int i = -1, is = inputSize, js = hiddenSize; ++i < is;)
    {
        for (int j = -1; ++j < js;)
        {
            matrix(i, j) = uni();
        }
    }

    return matrix;
}

const arma::mat Setting::generateMatrix(arma::Mat<double> matrix, int inputSize, int hiddenSize, double lowerBound,
                                        double upperBound)
{
    base_generator_type generator((const uint32_t &) (std::chrono::system_clock::now()).time_since_epoch().count());
    boost::uniform_real<> uni_dist(lowerBound, upperBound);
    boost::variate_generator<base_generator_type&, boost::uniform_real<> > uni(generator, uni_dist);

    if ((matrix.n_rows != inputSize) || (matrix.n_cols != hiddenSize))
    {
        matrix = arma::mat((const arma::uword) inputSize, (const arma::uword) hiddenSize, arma::fill::zeros);
    }

    for (int i = -1, is = inputSize, js = hiddenSize; ++i < is;)
    {
        for (int j = -1; ++j < js;)
        {
            matrix(i, j) = uni();
        }
    }

    return matrix;
}

void Setting::printFormatted(const std::vector<Dataset> value, int count)
{
    for(std::vector<Dataset>::const_iterator i = value.begin(), is = value.end(); i != is; ++i)
    {
        double *_v = (*i).getParameter();
        for(int j = -1, js = count; ++j < js;)
        {
            std::cout << _v[j] << " ";
        }
        std::cout << '{' << (*i).getActual() << ", " << (*i).getPredicted() << '}' << std::endl;
    }
}

std::vector<Dataset> Setting::formatValue(const std::vector<double> value, int count)
{
    std::vector<Dataset> result;
    for(int i = -1, is = (int) (value.size() - count); ++i < is;)
    {
        double* row = new double[count];
        for (int j = -1, js = count; ++j < js;)
        {
            row[j] = value.at((unsigned long) (i + (js - j)));
        }
        result.push_back(Dataset(row, value.at((unsigned long) i), -1));
    }
    return result;
}

const CurrencyBound Setting::generateNormalizationBound(CurrencyBound bound, const std::vector<double> &list, int bias)
{
    bound.setFromList(list);
    bound.setMin(bound.getMin() - bias);
    bound.setMax(bound.getMax() + bias);
    return bound;
}