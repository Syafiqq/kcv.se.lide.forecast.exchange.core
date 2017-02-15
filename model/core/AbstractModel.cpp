//
// Created by syafiq on 12/22/16.
//

#include "AbstractModel.h"

AbstractModel::AbstractModel()
{

}

sql::Connection *AbstractModel::db()
{
    return this->database->db();
}
