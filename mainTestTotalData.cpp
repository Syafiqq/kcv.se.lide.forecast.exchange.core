/*
 * This <core_kcv_se_lide_forcast_currency> project created by : 
 * Name         : syafiq
 * Date / Time  : 30 December 2016, 11:30 AM.
 * Email        : syafiq.rezpector@gmail.com
 * Github       : syafiqq
 */

#include <iostream>
#include <armadillo>
#include <boost/chrono.hpp>
#include "model/Exchange.h"
#include "util/Setting.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include "model/Melm.h"
#include "dbConfig.h"

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

    boost::chrono::high_resolution_clock::time_point t1 ;
    boost::chrono::high_resolution_clock::time_point t2 ;

    for(int _data = 50, _dataMax = 1750; (_data += 50) <= _dataMax; )
    {
        for(int c = -1, cs = 10; ++c < cs;)
        {
            setting.setParameterCount(_data);

            const vector<EExchange> rrawTraining(rawTraining.begin(), rawTraining.end());
            const vector<EExchange> rrawTesting(rawTesting.begin(), rawTesting.end());

            const vector<double> valTraining = EExchange::sanitizeValue(rrawTraining);
            const vector<double> valTesting = EExchange::sanitizeValue(rrawTesting);

            vector<Dataset> formattedTraining = Setting::formatValue(valTraining, setting.getParameterCount());
            vector<Dataset> formattedTesting = Setting::formatValue(valTesting, setting.getParameterCount());

            const arma::mat weight = Setting::generateMatrix(arma::mat((const arma::uword) setting.getInputLayerCount(),
                                                                       (const arma::uword) setting.getHiddenLayerCount(),
                                                                       arma::fill::zeros),
                                                             setting.getInputLayerCount(),
                                                             setting.getHiddenLayerCount(),
                                                             setting.getWeightMin(),
                                                             setting.getWeightMax());
            const arma::mat bias = Setting::generateMatrix(arma::mat((const arma::uword) 1,
                                                                     (const arma::uword) setting.getHiddenLayerCount(),
                                                                     arma::fill::zeros),
                                                           1,
                                                           setting.getHiddenLayerCount(),
                                                           setting.getBiasMin(),
                                                           setting.getBiasMax());

            const CurrencyBound bound = Setting::generateNormalizationBound(CurrencyBound(), valTraining,  5000);

            Melm melm = Melm();
            melm.registerMetadata(setting.getParameterCount(), weight, bias, bound, setting.isBiasEnable());
            t1 = boost::chrono::high_resolution_clock::now();
            melm.learn(&formattedTraining);
            t2 = boost::chrono::high_resolution_clock::now();
            double accuracy = melm.testAccuracy(&formattedTesting);
            boost::this_thread::sleep(boost::posix_time::milliseconds(100));
            std::cout << std::fixed << _data << '\t' << accuracy << '\t' << (boost::chrono::duration_cast<boost::chrono::microseconds>(t2 - t1)) << std::endl;
        }
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
    assert((setting.getFrom() > 0) &&
                   (setting.getTo() > 0));
    const int dataCount = Exchange::getInstance().getMaxCountData(setting.getFrom(), setting.getTo());
    assert(dataCount > 2);

    setting.setParameterCount(30);
    setting.setTrainingCount(1815 - 30);
    setting.setTestingCount(1815 - 30);
    assert((setting.getParameterCount() > 0) && (setting.getTrainingCount() > 0) && (setting.getTestingCount() > 0));
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