#include "dbms.h"
#include <iostream>

DBMS::DBMS() {
    storage = new Storage();
    queryProcessor = new QueryProcessor(storage);
    currentDatabase = "";
}

DBMS::~DBMS() {
    delete storage;
    delete queryProcessor;
}

bool DBMS::createDatabase(const std::string& dbName) {
    return storage->createDatabase(dbName);
}

bool DBMS::useDatabase(const std::string& dbName) {
    if (storage->databaseExists(dbName)) {
        currentDatabase = dbName;
        return true;
    }
    return false;
}

bool DBMS::executeQuery(const std::string& query) {
    if (currentDatabase.empty() && !queryProcessor->isSystemQuery(query)) {
        std::cerr << "Error: No database selected. Use 'USE database_name';" << std::endl;
        return false;
    }
    return queryProcessor->processQuery(query, currentDatabase);
}

void DBMS::showDatabases() {
    storage->listDatabases();
}

bool DBMS::isDatabaseSelected() const {
    return !currentDatabase.empty();
}

std::string DBMS::getCurrentDatabase() const {
    return currentDatabase;
}
