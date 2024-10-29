#include "storage.h"
#include <iostream>
#include <fstream>
#include <filesystem>

Storage::Storage() {
    dataPath = "data/";
    std::filesystem::create_directory(dataPath);
}

bool Storage::createDatabase(const std::string& dbName) {
    if (databases.find(dbName) != databases.end()) {
        std::cerr << "Database '" << dbName << "' already exists." << std::endl;
        return false;
    }
    
    databases[dbName] = std::map<std::string, Table>();
    std::filesystem::create_directory(dataPath + dbName);
    std::cout << "Database created successfully." << std::endl;
    return true;
}

bool Storage::createTable(const std::string& dbName, const std::string& tableName, 
                         const std::vector<Column>& columns) {
    if (databases[dbName].find(tableName) != databases[dbName].end()) {
        std::cerr << "Table '" << tableName << "' already exists." << std::endl;
        return false;
    }
    
    Table newTable;
    newTable.name = tableName;
    newTable.columns = columns;
    databases[dbName][tableName] = newTable;
    std::cout << "Table created successfully." << std::endl;
    return saveToFile(dbName);
}

bool Storage::insertIntoTable(const std::string& dbName, const std::string& tableName, 
                            const std::vector<std::string>& values) {
    if (databases[dbName].find(tableName) == databases[dbName].end()) {
        std::cerr << "Table '" << tableName << "' does not exist." << std::endl;
        return false;
    }
    
    Table& table = databases[dbName][tableName];
    if (values.size() != table.columns.size()) {
        std::cerr << "Column count mismatch." << std::endl;
        return false;
    }
    
    table.rows.push_back(values);
    std::cout << "1 row inserted successfully." << std::endl;
    return saveToFile(dbName);
}

std::vector<std::vector<std::string>> Storage::selectFromTable(const std::string& dbName, 
                                                             const std::string& tableName) {
    if (databases[dbName].find(tableName) == databases[dbName].end()) {
        std::cerr << "Table '" << tableName << "' does not exist." << std::endl;
        return {};
    }
    
    return databases[dbName][tableName].rows;
}

bool Storage::databaseExists(const std::string& dbName) const {
    return databases.find(dbName) != databases.end();
}

void Storage::listDatabases() const {
    std::cout << "\nDatabases:\n";
    for (const auto& db : databases) {
        std::cout << "- " << db.first << std::endl;
    }
}

bool Storage::saveToFile(const std::string& dbName) {
    // Simple file storage implementation
    std::ofstream file(dataPath + dbName + "/schema.txt");
    if (!file) return false;
    
    for (const auto& table : databases[dbName]) {
        file << "TABLE " << table.first << "\n";
        for (const auto& col : table.second.columns) {
            file << col.name << " " << col.type << "\n";
        }
        file << "END\n";
    }
    return true;
}

bool Storage::loadFromFile(const std::string& dbName) {
    std::ifstream file(dataPath + dbName + "/schema.txt");
    if (!file) return false;
    
    // Simple implementation
    return true;
}
