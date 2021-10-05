#include "Database.h"

namespace Trust
{

Database::Database()
{
    rocksdb::Options options;
    options.create_if_missing = true;
    rocksdb::Status status = rocksdb::DB::Open(options, "./channeldb", &db);
    assert(status.ok());
}

Database::~Database()
{
    delete db;
}

} // namespace
