/*
 * This <core_kcv_se_lide_forcast_currency> project created by : 
 * Name         : syafiq
 * Date / Time  : 30 December 2016, 10:38 AM.
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

    int tests[] = {
            3,
            3,
            3,
            3,
            3,
            3,
            3,
            3,
            3,
            3,
            4,
            4,
            4,
            4,
            4,
            4,
            4,
            4,
            4,
            4,
            5,
            5,
            5,
            5,
            5,
            5,
            5,
            5,
            5,
            5,
            6,
            6,
            6,
            6,
            6,
            6,
            6,
            6,
            6,
            6,
            7,
            7,
            7,
            7,
            7,
            7,
            7,
            7,
            7,
            7,
            8,
            8,
            8,
            8,
            8,
            8,
            8,
            8,
            8,
            8,
            9,
            9,
            9,
            9,
            9,
            9,
            9,
            9,
            9,
            9,
            10,
            10,
            10,
            10,
            10,
            10,
            10,
            10,
            10,
            10,
            11,
            11,
            11,
            11,
            11,
            11,
            11,
            11,
            11,
            11,
            12,
            12,
            12,
            12,
            12,
            12,
            12,
            12,
            12,
            12,
            13,
            13,
            13,
            13,
            13,
            13,
            13,
            13,
            13,
            13,
            14,
            14,
            14,
            14,
            14,
            14,
            14,
            14,
            14,
            14,
            15,
            15,
            15,
            15,
            15,
            15,
            15,
            15,
            15,
            15,
            16,
            16,
            16,
            16,
            16,
            16,
            16,
            16,
            16,
            16,
            17,
            17,
            17,
            17,
            17,
            17,
            17,
            17,
            17,
            17,
            18,
            18,
            18,
            18,
            18,
            18,
            18,
            18,
            18,
            18,
            19,
            19,
            19,
            19,
            19,
            19,
            19,
            19,
            19,
            19,
            20,
            20,
            20,
            20,
            20,
            20,
            20,
            20,
            20,
            20,
            21,
            21,
            21,
            21,
            21,
            21,
            21,
            21,
            21,
            21,
            22,
            22,
            22,
            22,
            22,
            22,
            22,
            22,
            22,
            22,
            23,
            23,
            23,
            23,
            23,
            23,
            23,
            23,
            23,
            23,
            24,
            24,
            24,
            24,
            24,
            24,
            24,
            24,
            24,
            24,
            25,
            25,
            25,
            25,
            25,
            25,
            25,
            25,
            25,
            25,
            26,
            26,
            26,
            26,
            26,
            26,
            26,
            26,
            26,
            26,
            27,
            27,
            27,
            27,
            27,
            27,
            27,
            27,
            27,
            27,
            28,
            28,
            28,
            28,
            28,
            28,
            28,
            28,
            28,
            28,
            29,
            29,
            29,
            29,
            29,
            29,
            29,
            29,
            29,
            29,
            30,
            30,
            30,
            30,
            30,
            30,
            30,
            30,
            30,
            30,
            31,
            31,
            31,
            31,
            31,
            31,
            31,
            31,
            31,
            31,
            32,
            32,
            32,
            32,
            32,
            32,
            32,
            32,
            32,
            32,
            33,
            33,
            33,
            33,
            33,
            33,
            33,
            33,
            33,
            33,
            34,
            34,
            34,
            34,
            34,
            34,
            34,
            34,
            34,
            34,
            35,
            35,
            35,
            35,
            35,
            35,
            35,
            35,
            35,
            35,
            36,
            36,
            36,
            36,
            36,
            36,
            36,
            36,
            36,
            36,
            37,
            37,
            37,
            37,
            37,
            37,
            37,
            37,
            37,
            37,
            38,
            38,
            38,
            38,
            38,
            38,
            38,
            38,
            38,
            38,
            39,
            39,
            39,
            39,
            39,
            39,
            39,
            39,
            39,
            39,
            40,
            40,
            40,
            40,
            40,
            40,
            40,
            40,
            40,
            40,
            41,
            41,
            41,
            41,
            41,
            41,
            41,
            41,
            41,
            41,
            42,
            42,
            42,
            42,
            42,
            42,
            42,
            42,
            42,
            42,
            43,
            43,
            43,
            43,
            43,
            43,
            43,
            43,
            43,
            43,
            44,
            44,
            44,
            44,
            44,
            44,
            44,
            44,
            44,
            44,
            45,
            45,
            45,
            45,
            45,
            45,
            45,
            45,
            45,
            45,
            46,
            46,
            46,
            46,
            46,
            46,
            46,
            46,
            46,
            46,
            47,
            47,
            47,
            47,
            47,
            47,
            47,
            47,
            47,
            47,
            48,
            48,
            48,
            48,
            48,
            48,
            48,
            48,
            48,
            48,
            49,
            49,
            49,
            49,
            49,
            49,
            49,
            49,
            49,
            49,
            50,
            50,
            50,
            50,
            50,
            50,
            50,
            50,
            50,
            50,
            51,
            51,
            51,
            51,
            51,
            51,
            51,
            51,
            51,
            51,
            52,
            52,
            52,
            52,
            52,
            52,
            52,
            52,
            52,
            52,
            53,
            53,
            53,
            53,
            53,
            53,
            53,
            53,
            53,
            53,
            54,
            54,
            54,
            54,
            54,
            54,
            54,
            54,
            54,
            54,
            55,
            55,
            55,
            55,
            55,
            55,
            55,
            55,
            55,
            55,
            56,
            56,
            56,
            56,
            56,
            56,
            56,
            56,
            56,
            56,
            57,
            57,
            57,
            57,
            57,
            57,
            57,
            57,
            57,
            57,
            58,
            58,
            58,
            58,
            58,
            58,
            58,
            58,
            58,
            58,
            59,
            59,
            59,
            59,
            59,
            59,
            59,
            59,
            59,
            59,
            60,
            60,
            60,
            60,
            60,
            60,
            60,
            60,
            60,
            60,
            61,
            61,
            61,
            61,
            61,
            61,
            61,
            61,
            61,
            61,
            62,
            62,
            62,
            62,
            62,
            62,
            62,
            62,
            62,
            62,
            63,
            63,
            63,
            63,
            63,
            63,
            63,
            63,
            63,
            63,
            64,
            64,
            64,
            64,
            64,
            64,
            64,
            64,
            64,
            64,
            65,
            65,
            65,
            65,
            65,
            65,
            65,
            65,
            65,
            65,
            66,
            66,
            66,
            66,
            66,
            66,
            66,
            66,
            66,
            66,
            67,
            67,
            67,
            67,
            67,
            67,
            67,
            67,
            67,
            67,
            68,
            68,
            68,
            68,
            68,
            68,
            68,
            68,
            68,
            68,
            69,
            69,
            69,
            69,
            69,
            69,
            69,
            69,
            69,
            69,
            70,
            70,
            70,
            70,
            70,
            70,
            70,
            70,
            70,
            70,
            71,
            71,
            71,
            71,
            71,
            71,
            71,
            71,
            71,
            71,
            72,
            72,
            72,
            72,
            72,
            72,
            72,
            72,
            72,
            72,
            73,
            73,
            73,
            73,
            73,
            73,
            73,
            73,
            73,
            73,
            74,
            74,
            74,
            74,
            74,
            74,
            74,
            74,
            74,
            74,
            75,
            75,
            75,
            75,
            75,
            75,
            75,
            75,
            75,
            75,
            76,
            76,
            76,
            76,
            76,
            76,
            76,
            76,
            76,
            76,
            77,
            77,
            77,
            77,
            77,
            77,
            77,
            77,
            77,
            77,
            78,
            78,
            78,
            78,
            78,
            78,
            78,
            78,
            78,
            78,
            79,
            79,
            79,
            79,
            79,
            79,
            79,
            79,
            79,
            79,
            80,
            80,
            80,
            80,
            80,
            80,
            80,
            80,
            80,
            80,
            81,
            81,
            81,
            81,
            81,
            81,
            81,
            81,
            81,
            81,
            82,
            82,
            82,
            82,
            82,
            82,
            82,
            82,
            82,
            82,
            83,
            83,
            83,
            83,
            83,
            83,
            83,
            83,
            83,
            83,
            84,
            84,
            84,
            84,
            84,
            84,
            84,
            84,
            84,
            84,
            85,
            85,
            85,
            85,
            85,
            85,
            85,
            85,
            85,
            85,
            86,
            86,
            86,
            86,
            86,
            86,
            86,
            86,
            86,
            86,
            87,
            87,
            87,
            87,
            87,
            87,
            87,
            87,
            87,
            87,
            88,
            88,
            88,
            88,
            88,
            88,
            88,
            88,
            88,
            88,
            89,
            89,
            89,
            89,
            89,
            89,
            89,
            89,
            89,
            89,
            90,
            90,
            90,
            90,
            90,
            90,
            90,
            90,
            90,
            90
    };

    for(int _feature : tests)
    {
        setting.setParameterCount(_feature);

        const vector<EExchange> rrawTraining(rawTraining.begin(), rawTraining.end());
        const vector<EExchange> rrawTesting(rawTesting.begin(), rawTesting.end());

        const vector<double> valTraining = EExchange::sanitizeValue(rrawTraining);
        const vector<double> valTesting = EExchange::sanitizeValue(rrawTesting);

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
        t1 = boost::chrono::high_resolution_clock::now();
        melm.learn(&formattedTraining);
        t2 = boost::chrono::high_resolution_clock::now();
        double accuracy = melm.testAccuracy(&formattedTesting);
        boost::this_thread::sleep(boost::posix_time::milliseconds(100));
        std::cout << std::fixed << _feature << '\t' << accuracy << '\t' << (boost::chrono::duration_cast<boost::chrono::milliseconds>(t2 - t1)) << std::endl;
    }
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