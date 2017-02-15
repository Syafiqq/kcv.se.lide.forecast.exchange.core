cmake_minimum_required(VERSION 3.6)
project(core_kcv_se_lide_forcast_currency)

set(CMAKE_CXX_STANDARD 11)

find_package(Armadillo REQUIRED) # <<<
if (Armadillo_FOUND)
    include_directories(${ARMADILLO_INCLUDE_DIRS}) # <<<

    set(Boost_USE_STATIC_LIBS OFF)
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_USE_STATIC_RUNTIME OFF)
    find_package(Boost 1.62.0 REQUIRED COMPONENTS system timer chrono thread)

    if (Boost_FOUND)
        include_directories(${Boost_INCLUDE_DIRS})

        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -larmadillo -lboost_thread -lboost_system -lboost_timer -lboost_chrono -lmysqlcppconn -lrt")
        set(CORE_DEPENDENCY database/AbstractDB.cpp database/AbstractDB.h model/core/AbstractModel.cpp model/core/AbstractModel.h model/Exchange.cpp model/Exchange.h entity/EExchange.cpp entity/EExchange.h util/Setting.cpp util/Setting.h model/util/CurrencyBound.cpp model/util/CurrencyBound.h model/Melm.cpp model/Melm.h model/Dataset.cpp model/Dataset.h dbConfig.h)

        add_executable(core_kcv_se_lide_forcast_currency main.cpp ${CORE_DEPENDENCY})
        target_link_libraries(core_kcv_se_lide_forcast_currency ${ARMADILLO_LIBRARIES} ${Boost_LIBRARIES} mysqlcppconn) # <<<

        add_executable(test_w_and_b mainTestWandB.cpp ${CORE_DEPENDENCY})
        target_link_libraries(test_w_and_b ${ARMADILLO_LIBRARIES} ${Boost_LIBRARIES} mysqlcppconn) # <<<

        add_executable(test_feature mainTestFeature.cpp ${CORE_DEPENDENCY})
        target_link_libraries(test_feature ${ARMADILLO_LIBRARIES} ${Boost_LIBRARIES} mysqlcppconn) # <<<

        add_executable(test_hidden_node mainTestHiddenNode.cpp ${CORE_DEPENDENCY})
        target_link_libraries(test_hidden_node ${ARMADILLO_LIBRARIES} ${Boost_LIBRARIES} mysqlcppconn) # <<<

        add_executable(test_total_data_training mainTestTotalData.cpp ${CORE_DEPENDENCY})
        target_link_libraries(test_total_data_training ${ARMADILLO_LIBRARIES} ${Boost_LIBRARIES} mysqlcppconn) # <<<
    endif ()
endif ()