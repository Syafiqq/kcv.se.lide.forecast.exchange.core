//
// Created by syafiq on 12/22/16.
//
#include "Exchange.h"
#include "../entity/EExchange.h"

Exchange::Exchange()
{

}

const vector<EExchange> Exchange::getDataSortByDateDescLimitWithOffset(int from = 2, int to = 1, int limit = 1, int offset = 0)
{
    sql::PreparedStatement  *prep_stmt;
    vector<EExchange> result;

    prep_stmt = this->db()->prepareStatement("SELECT `base` AS 'from', `to`, `date`, `value`, coalesce(`predicted`, -1) AS 'predicted' FROM `exchange` WHERE `base` = ? AND `to` = ? AND `value` IS NOT NULL ORDER BY `date` DESC LIMIT ? OFFSET ?");

    prep_stmt->setInt(1, from);
    prep_stmt->setInt(2, to);
    prep_stmt->setInt(3, limit);
    prep_stmt->setInt(4, offset);
    sql::ResultSet *res = prep_stmt->executeQuery();
    while (res->next()) {
        result.push_back(EExchange(res->getInt("from"),
                                   res->getInt("to"),
                                   res->getString("date"),
                                   res->getInt("value"),
                                   res->getInt("predicted")));
    }
    delete res;
    delete prep_stmt;
    return result;
}

const int Exchange::getMaxCountData(int from, int to)
{
    sql::PreparedStatement  *prep_stmt;
    int result = -1;

    prep_stmt = this->db()->prepareStatement("SELECT COUNT(`value`) AS 'count' FROM `exchange` WHERE `base` = ? AND `to` = ? AND `value` IS NOT NULL LIMIT 1");

    prep_stmt->setInt(1, from);
    prep_stmt->setInt(2, to);
    sql::ResultSet *res = prep_stmt->executeQuery();
    while (res->next()) {
        result = res->getInt("count");
    }
    delete res;
    delete prep_stmt;
    return result;
}

