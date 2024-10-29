#pragma once
#include <string>
#include <vector>
#include <map>

struct Column {
    std::string name;
    std::string type;
    bool isNull;
    bool isPrimaryKey;
};

struct Table {
    std::string name;
    std::vector<Column> columns;
    std::vector<std::vector<std::string>> rows;
};

class Storage {
private:
    std::map<std::string, std::map<std::string, Table>> databases;
    std::string dataPath;

public:
    Storage();
    bool createDatabase(const std::string& dbName);
    bool createTable(const std::string& dbName, const std::string& tableName, const std::vector<Column>& columns);
    bool insertIntoTable(const std::string& dbName, const std::string& tableName, const std::vector<std::string>& values);
    std::vector<std::vector<std::string>> selectFromTable(const std::string& dbName, const std::string& tableName);
    bool databaseExists(const std::string& dbName) const;
    void listDatabases() const;
    bool saveToFile(const std::string& dbName);
    bool loadFromFile(const std::string& dbName);
};
