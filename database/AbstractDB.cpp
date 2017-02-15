//
// Created by syafiq on 12/22/16.
//

#include "AbstractDB.h"
#include "../util/Setting.h"

AbstractDB::AbstractDB()
{
    Setting &setting = Setting::getInstance();
    this->driver = sql::mysql::get_mysql_driver_instance();
    this->con = this->driver->connect(setting.getDBHost(), setting.getDBUsername(), setting.getDBPassword());
    this->con->setSchema(setting.getDBSchema());
}

bool AbstractDB::isValid()
{
    return this->con->isValid();
}

void AbstractDB::reconnect()
{
    this->con->reconnect();
}

AbstractDB::~AbstractDB()
{
    delete (this->con);
}

sql::Connection *AbstractDB::db()
{
    return this->con;
}


