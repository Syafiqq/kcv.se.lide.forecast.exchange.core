//
// Created by syafiq on 12/22/16.
//

#ifndef CORE_KCV_SE_LIDE_FORCAST_CURRENCY_EXCHANGE_H
#define CORE_KCV_SE_LIDE_FORCAST_CURRENCY_EXCHANGE_H


#include "core/AbstractModel.h"
#ifndef _SQL_PREPARED_STATEMENT_H_
    #include <cppconn/prepared_statement.h>
#endif
#include "vector"
#include "../entity/EExchange.h"
using namespace std;

class Exchange : AbstractModel
{
    public:
    static Exchange &getInstance()
    {
        static Exchange instance;
        return instance;
    }

    private:
    Exchange();

    public:
    Exchange(Exchange const &) = delete;
    void operator=(Exchange const &)  = delete;
    const vector<EExchange> getDataSortByDateDescLimitWithOffset(int from, int to, int limit, int offset);
    const int getMaxCountData(int from, int to);
};

#endif //CORE_KCV_SE_LIDE_FORCAST_CURRENCY_EXCHANGE_H
