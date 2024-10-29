#include "querry.h"
#include <iostream>
#include <sstream>
#include <algorithm>

QueryProcessor::QueryProcessor(Storage* storageManager) : storage(storageManager) {}

QueryProcessor::ParsedQuery QueryProcessor::parseQuery(const std::string& query) {
    ParsedQuery pq;
    std::string upperQuery = query;
    std::transform(upperQuery.begin(), upperQuery.end(), upperQuery.begin(), ::toupper);
    
    if (upperQuery.find("CREATE TABLE") == 0) {
        pq.type = "CREATE";
    } else if (upperQuery.find("INSERT INTO") == 0) {
        pq.type = "INSERT";
    } else if (upperQuery.find("SELECT") == 0) {
        pq.type = "SELECT";
    } else if (upperQuery.find("DELETE FROM") == 0) {
        pq.type = "DELETE";
    }
    
    return pq;
}

bool QueryProcessor::processQuery(const std::string& query, const std::string& currentDb) {
    try {
        ParsedQuery pq = parseQuery(query);
        pq.database = currentDb;

        std::string upperQuery = query;
        std::transform(upperQuery.begin(), upperQuery.end(), upperQuery.begin(), ::toupper);

        if (upperQuery.find("CREATE DATABASE") == 0) {
            std::string dbName = query.substr(15);
            return storage->createDatabase(dbName);
        }
        
        if (pq.type == "CREATE") {
            return executeCreateTable(pq);
        } else if (pq.type == "INSERT") {
            return executeInsert(pq);
        } else if (pq.type == "SELECT") {
            return executeSelect(pq);
        } else if (pq.type == "DELETE") {
            return executeDelete(pq);
        }
        
        std::cerr << "Unknown query type" << std::endl;
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Query processing error: " << e.what() << std::endl;
        return false;
    }
}

bool QueryProcessor::isSystemQuery(const std::string& query) {
    std::string upperQuery = query;
    std::transform(upperQuery.begin(), upperQuery.end(), upperQuery.begin(), ::toupper);
    return upperQuery.find("CREATE DATABASE") == 0 || 
           upperQuery.find("USE") == 0 || 
           upperQuery.find("SHOW DATABASES") == 0;
}

bool QueryProcessor::executeCreateTable(const ParsedQuery& pq) {
    // Simple implementation
    std::cout << "Create table command received" << std::endl;
    return true;
}

bool QueryProcessor::executeInsert(const ParsedQuery& pq) {
    std::cout << "Insert command received" << std::endl;
    return true;
}

bool QueryProcessor::executeSelect(const ParsedQuery& pq) {
    std::cout << "Select command received" << std::endl;
    return true;
}

bool QueryProcessor::executeDelete(const ParsedQuery& pq) {
    std::cout << "Delete command received" << std::endl;
    return true;
}
