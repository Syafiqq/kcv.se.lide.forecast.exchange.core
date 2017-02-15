//
// Created by syafiq on 12/22/16.
//

#ifndef CORE_KCV_SE_LIDE_FORCAST_CURRENCY_ABSTARCTDB_H
#define CORE_KCV_SE_LIDE_FORCAST_CURRENCY_ABSTARCTDB_H

#include <mysql_driver.h>
#include <cppconn/connection.h>

class AbstractDB
{
    public:
    static AbstractDB &getInstance()
    {
        static AbstractDB instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

    private:
    AbstractDB();// Constructor? (the {} brackets) are needed here.
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;

    public:
    virtual ~AbstractDB();
    // C++ 11
    // =======
    // We can use the better technique of deleting the methods
    // we don't want.
    public:
    AbstractDB(AbstractDB const &) = delete;

    void operator=(AbstractDB const &)  = delete;

    bool isValid();

    void reconnect();

    sql::Connection *db();

    // Note: Scott Meyers mentions in his Effective Modern
    //       C++ book, that deleted functions should generally
    //       be public as it results in better error messages
    //       due to the compilers behavior to check accessibility
    //       before deleted status
};

#endif //CORE_KCV_SE_LIDE_FORCAST_CURRENCY_ABSTARCTDB_H
