#pragma once
#include <string>
#include "storage.h"
#include "querry.h"

class DBMS {
private:
    Storage* storage;
    QueryProcessor* queryProcessor;
    std::string currentDatabase;

public:
    DBMS();
    ~DBMS();
    
    bool createDatabase(const std::string& dbName);
    bool useDatabase(const std::string& dbName);
    bool executeQuery(const std::string& query);
    void showDatabases();
    bool isDatabaseSelected() const;
    std::string getCurrentDatabase() const;
};