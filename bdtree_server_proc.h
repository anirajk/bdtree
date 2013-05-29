#pragma once
#include <stdint.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class DB {
public:
    virtual ~DB() {}
    virtual int read(const std::string& table,
                     const std::string& key,
                     const std::unordered_set<std::string>& fields,
                     std::unordered_map<std::string, std::string>& result) = 0;
    virtual int scan(const std::string& table,
                     const std::string& start_key,
                     int read_count,
                     const std::unordered_set<std::string>& fields,
                     std::vector<std::unordered_map<std::string, std::string> >& result) = 0;
    virtual int update(const std::string& table,
                       const std::string& key,
                       const std::unordered_map<std::string, std::string>& values) = 0;
    virtual int insert(const std::string& table,
                       const std::string& key,
                       const std::unordered_map<std::string, std::string>& values) = 0;
    virtual int remove(const std::string& table,
                       const std::string& key) = 0;
};

class server {
    int fd;
    DB& db;
    server(int fd, DB& db) : fd(fd), db(db) {}
    void exec();
    int32_t read_int();
    std::string read_string();
    std::unordered_set<std::string> read_fields();
    std::unordered_map<std::string, std::string> read_map();
    void send_int(int32_t i);
    void send_string(const std::string& s);
    void send_map(const std::unordered_map<std::string, std::string>& m);
    void send_vec(std::vector<std::unordered_map<std::string, std::string> >& v);
    void db_read();
    void db_scan();
    void db_update();
    void db_insert();
    void db_delete();
public:
    static void run(int fd, DB& db);
    ~server();
};