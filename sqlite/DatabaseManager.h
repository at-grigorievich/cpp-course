#pragma once
#include <string>
#include <sqlite3.h>

namespace SQLite {
    class DatabaseManager
    {
    public:
        DatabaseManager(const std::string& dbPath);
        ~DatabaseManager();

        bool Open();
        void Close();

        bool InitializeTables();

    private:
        bool Execute(const std::string& sql);

    private:
        std::string _dbPath;
        sqlite3* _db;
    };
}