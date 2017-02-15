//
// Created by syafiq on 12/22/16.
//

#ifndef CORE_KCV_SE_LIDE_FORCAST_CURRENCY_ABSTRACTMODEL_H
#define CORE_KCV_SE_LIDE_FORCAST_CURRENCY_ABSTRACTMODEL_H


#include "../../database/AbstractDB.h"

class AbstractModel
{
    public:
    AbstractModel();


    private:
    AbstractDB *database = &AbstractDB::getInstance();

    protected:
    sql::Connection *db();
};


#endif //CORE_KCV_SE_LIDE_FORCAST_CURRENCY_ABSTRACTMODEL_H
