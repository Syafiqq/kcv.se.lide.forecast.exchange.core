#include <iostream>
#include <armadillo>
#include "model/Exchange.h"
#include "util/Setting.h"
#include "model/Melm.h"
#include "dbConfig.h"

void _setELMParam();
void _setDBParam();

void __printVector1(const vector<EExchange> data);
void __printVector2(vector<Dataset> data);
const arma::mat generateMatrix(arma::Mat<double> matrix, const double *data, int count, int layerCount);
Setting &setting = Setting::getInstance();

int main()
{
    _setDBParam();
    _setELMParam();
    Exchange &exchange = Exchange::getInstance();
    const vector<EExchange> rawTraining = exchange.getDataSortByDateDescLimitWithOffset(setting.getFrom(),
                                                                                        setting.getTo(),
                                                                                        setting.getTrainingCount() +
                                                                                                setting.getParameterCount(),
                                                                                        0);
    const vector<EExchange> rawTesting = exchange.getDataSortByDateDescLimitWithOffset(setting.getFrom(),
                                                                                       setting.getTo(),
                                                                                       setting.getTestingCount() +
                                                                                               setting.getParameterCount(),
                                                                                       0);

    std::cout << "Raw Training" << std::endl;
    __printVector1(rawTraining);
    std::cout << "Raw Testing" << std::endl;
    __printVector1(rawTesting);

    const vector<double> valTraining = EExchange::sanitizeValue(rawTraining);
    const vector<double> valTesting = EExchange::sanitizeValue(rawTesting);

    vector<Dataset> formattedTraining = Setting::formatValue(valTraining, setting.getParameterCount());
    vector<Dataset> formattedTesting = Setting::formatValue(valTesting, setting.getParameterCount());

    std::cout << "Format Training" << std::endl;
    __printVector2(formattedTraining);
    std::cout << "Format Testing" << std::endl;
    __printVector2(formattedTesting);


/*    const arma::mat weight = Setting::generateWeight(arma::mat((const arma::uword) setting.getHiddenLayerCount(),
                                                               (const arma::uword) setting.getInputLayerCount(),
                                                               arma::fill::zeros),
                                                     setting.getInputLayerCount(),
                                                     setting.getHiddenLayerCount(),
                                                     setting.getWeightMin(),
                                                     setting.getWeightMax());
    const arma::mat bias = Setting::generateBias(arma::mat((const arma::uword) setting.getHiddenLayerCount(),
                                                           (const arma::uword)1,
                                                           arma::fill::zeros),
                                                 setting.getHiddenLayerCount(),
                                                 setting.getBiasMin(),
                                                 setting.getBiasMax());*/
    const double _weight[setting.getHiddenLayerCount()][setting.getInputLayerCount()] = {
            {0.221,  0.416,  0.229,  0.086},
            {0.499,  0.037,  -0.302, -0.154},
            {-0.435, -0.291, -0.436, 0.232},
            {0.430,  -0.389, 0.344,  -0.496},
            {0.398,  0.274,  -0.489, -0.446},
            {-0.301, -0.393, -0.419, 0.173},
            {0.308,  -0.286, 0.230,  0.237},
            {-0.024, -0.077, 0.147,  -0.316}
    };

    const double _bias[setting.getHiddenLayerCount()][1] = {
            {0.930},
            {0.997},
            {0.064},
            {0.039},
            {0.012},
            {0.582},
            {0.993},
            {0.087}
    };

    arma::mat weight = arma::mat((const arma::uword) setting.getHiddenLayerCount(),
                                 (const arma::uword) setting.getInputLayerCount(), arma::fill::zeros);
    for (int i = -1, is = setting.getHiddenLayerCount(), js = setting.getInputLayerCount(); ++i < is;)
    {
        for (int j = -1; ++j < js;)
        {
            weight(i, j) = _weight[i][j];
        }
    }
    arma::mat bias = arma::mat((const arma::uword) setting.getHiddenLayerCount(), (const arma::uword) 1,
                               arma::fill::zeros);
    for (int i = -1, is = setting.getHiddenLayerCount(), js = 1; ++i < is;)
    {
        for (int j = -1; ++j < js;)
        {
            bias(i, j) = _bias[i][j];
        }
    }

    const CurrencyBound bound = Setting::generateNormalizationBound(CurrencyBound(), valTraining,  5000);

    std::cout << "Weight" << std::endl;
    std::cout << weight << std::endl;

    std::cout << "Bias" << std::endl;
    std::cout << bias << std::endl;

    std::cout << "Normalization" << std::endl;
    std::cout << bound.getMin() << '\t' << bound.getMax() << std::endl;

    Melm melm = Melm();
    melm.registerMetadata(setting.getParameterCount(), weight, bias, bound, setting.isBiasEnable());
    melm.learn(&formattedTraining);
    double accuracy = melm.testAccuracy(&formattedTesting);
    std::cout << accuracy << std::endl;
}

const arma::mat generateMatrix(arma::Mat<double> matrix, const double *data[], int count, int layerCount)
{
    return arma::mat();
}

void __printVector2(vector<Dataset> data)
{
    int no = 0;
    for (vector<Dataset>::const_iterator i = data.begin(); i != data.end(); i++)
    {

        std::cout << ++no
                  << '\t';
        for (int j = -1, js = setting.getParameterCount(); ++j < js;)
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

void __printVector1(const vector<EExchange> data)
{
    int no = 0;
    for (vector<EExchange>::const_iterator i = data.begin(); i != data.end(); i++)
    {
        std::cout << ++no
                  << '\t'
                  << i->getBase()
                  << '\t'
                  << i->getTo()
                  << '\t'
                  << i->getDate()
                  << '\t'
                  << i->getValue()
                  << '\t'
                  << i->getPredicted()
                  << std::endl;
    }
}

void _setDBParam()
{
    setting.setDBHost(DB_CONFIG_HOST);
    setting.setDBUsername(DB_CONFIG_USERNAME);
    setting.setDBPassword(DB_CONFIG_PASSWORD);
    setting.setDBSchema(DB_CONFIG_SCHEMA);
    assert(AbstractDB::getInstance().isValid());
}

void _setELMParam()
{
    setting.setFrom(2);
    setting.setTo(1);
    assert ((setting.getFrom() > 0) &&
                    (setting.getTo() > 0));
    const int dataCount = Exchange::getInstance().getMaxCountData(setting.getFrom(), setting.getTo());
    assert(dataCount > 2);

    setting.setParameterCount(4);
    setting.setTrainingCount(12 - 4);
    setting.setTestingCount(12 - 4);
    assert ((setting.getParameterCount() > 0) && (setting.getTrainingCount() > 0) && (setting.getTestingCount() > 0));
    assert((setting.getParameterCount() < dataCount));
    assert(((setting.getParameterCount() + setting.getTrainingCount()) <= dataCount));
    assert(((setting.getParameterCount() + setting.getTestingCount()) <= dataCount));

    setting.setBiasMin(0.0);
    setting.setBiasMax(1.0);
    setting.setWeightMin(-0.5);
    setting.setWeightMax(0.5);
    setting.setBiasEnable(true);
    assert(setting.getBiasMin() != setting.getBiasMax());
    assert(setting.getBiasMin() < setting.getBiasMax());
    assert(setting.getWeightMin() != setting.getWeightMax());
    assert(setting.getWeightMin() < setting.getWeightMax());

    setting.setHiddenLayerCount(8);
    assert(setting.getHiddenLayerCount() > 0);
}
