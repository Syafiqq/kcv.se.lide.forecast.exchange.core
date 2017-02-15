#include <iostream>
#include <armadillo>
#include "model/Exchange.h"
#include "util/Setting.h"
#include "model/Melm.h"

void _setELMParam();
void _setDBParam();

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
    const vector<double> valTraining = EExchange::sanitizeValue(rawTraining);
    const vector<double> valTesting = EExchange::sanitizeValue(rawTesting);

    vector<Dataset> formattedTraining = Setting::formatValue(valTraining, setting.getParameterCount());
    vector<Dataset> formattedTesting = Setting::formatValue(valTesting, setting.getParameterCount());

    const arma::mat weight = Setting::generateWeight(arma::mat((const arma::uword) setting.getHiddenLayerCount(),
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
                                                 setting.getBiasMax());

    const CurrencyBound bound = Setting::generateNormalizationBound(CurrencyBound(), valTraining,  5000);

    Melm melm = Melm();
    melm.registerMetadata(setting.getParameterCount(), weight, bias, bound, setting.isBiasEnable());
    melm.learn(&formattedTraining);
    double accuracy = melm.testAccuracy(&formattedTesting);
    std::cout << accuracy << std::endl;
}

void _setDBParam()
{
    setting.setDBHost("tcp://127.0.0.1:3306");
    setting.setDBUsername("root");
    setting.setDBPassword("Muhammad_Syafiq");
    setting.setDBSchema("core.kcv.se.lide.forcast.currency");
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

    setting.setParameterCount(30);
    setting.setTrainingCount(1815 - 30);
    setting.setTestingCount(1815 - 30);
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

    setting.setHiddenLayerCount(setting.getParameterCount());
    assert(setting.getHiddenLayerCount() > 0);
}
