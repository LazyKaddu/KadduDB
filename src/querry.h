#pragma once
#include <string>
#include "storage.h"

class QueryProcessor {
private:
    Storage* storage;
    
    struct ParsedQuery {
        std::string type;
        std::string database;
        std::string table;
        std::vector<Column> columns;
        std::vector<std::string> values;
        std::string condition;
    };

public:
    explicit QueryProcessor(Storage* storageManager);
    bool processQuery(const std::string& query, const std::string& currentDb);
    bool isSystemQuery(const std::string& query);
    
private:
    ParsedQuery parseQuery(const std::string& query);
    bool executeCreateTable(const ParsedQuery& pq);
    bool executeInsert(const ParsedQuery& pq);
    bool executeSelect(const ParsedQuery& pq);
    bool executeDelete(const ParsedQuery& pq);
};
