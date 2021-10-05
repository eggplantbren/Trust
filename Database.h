#ifndef Trust_Database_h
#define Trust_Database_h

#include <rocksdb/db.h>

namespace Trust
{

class Database
{
    private:
        rocksdb::DB* db;

    public:
        Database();
        ~Database();

};

} // namespace

#endif
