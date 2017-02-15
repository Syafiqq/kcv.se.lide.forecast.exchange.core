//
// Created by syafiq on 12/22/16.
//

#ifndef CORE_KCV_SE_LIDE_FORCAST_CURRENCY_SETTING_H
#define CORE_KCV_SE_LIDE_FORCAST_CURRENCY_SETTING_H

#include <string>
#include <vector>
#include <armadillo>
#include <boost/random/linear_congruential.hpp>
#include "../model/Dataset.h"
#include "../model/util/CurrencyBound.h"

class Setting
{
    public:
    static Setting &getInstance()
    {
        static Setting instance;
        return instance;
    }

    public:
    static std::vector<Dataset> formatValue(const std::vector<double> value, int count);
    static void printFormatted(const std::vector<Dataset> vector, int count);
    static const arma::mat generateWeight(arma::Mat<double> matrix, int inputSize, int hiddenSize, double lowerBound,
                                          double upperBound);
    static const arma::mat generateBias(arma::Mat<double> matrix, int hiddenSize, double lowerBound, double upperBound);
    static const CurrencyBound generateNormalizationBound(CurrencyBound bound, const std::vector<double> &list,
                                                          int bias);
    double getBiasMin() const;
    void setBiasMin(double biasMin);
    double getBiasMax() const;
    void setBiasMax(double biasMax);
    double getWeightMin() const;
    void setWeightMin(double weightMin);
    double getWeightMax() const;
    void setWeightMax(double weightMax);
    const std::string &getDBHost() const;
    void setDBHost(const std::string &DBHost);
    const std::string &getDBUsername() const;
    void setDBUsername(const std::string &DBUsername);
    const std::string &getDBPassword() const;
    void setDBPassword(const std::string &DBPassword);
    const std::string &getDBSchema() const;
    void setDBSchema(const std::string &DBSchema);
    int getFrom() const;
    void setFrom(int from);
    int getTo() const;
    void setTo(int to);
    int getTestingCount() const;
    void setTestingCount(int testingCount);
    int getTrainingCount() const;
    void setTrainingCount(int trainingCount);
    int getParameterCount() const;
    void setParameterCount(int parameterCount);
    virtual ~Setting();
    Setting(Setting const &) = delete;
    void operator=(Setting const &)  = delete;
    int getInputLayerCount() const;
    int getHiddenLayerCount() const;
    void setHiddenLayerCount(int hiddenLayerCount);

    private:
    typedef boost::minstd_rand base_generator_type;
    Setting();
    void setInputLayerCount(int inputLayerCount);
    int trainingCount;
    int testingCount;
    int parameterCount;
    int from;
    int to;
    double biasMin;
    double biasMax;
    bool biasEnable;
    public:
    bool isBiasEnable() const;
    void setBiasEnable(bool biasEnable);
    private:
    double weightMin;
    double weightMax;
    int inputLayerCount;
    int hiddenLayerCount;
    std::string DBHost;
    std::string DBUsername;
    std::string DBPassword;
    std::string DBSchema;
};


#endif //CORE_KCV_SE_LIDE_FORCAST_CURRENCY_SETTING_H
