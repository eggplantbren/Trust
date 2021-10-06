#include "Database.h"
#include "Channel.h"

namespace Trust
{

Database::Database()
{
    rocksdb::Options options;
    options.create_if_missing = true;
    rocksdb::Status status = rocksdb::DB::Open(options, "./db", &db);
    assert(status.ok());
}

Database::~Database()
{
    delete db;
}

void Database::channel_created(const std::string& claim_hash, std::uint64_t bid)
{
    Channel c(claim_hash, bid);
    auto [key, value] = c.serialise();
    rocksdb::Status s = db->Put(rocksdb::WriteOptions(), key, value);
    assert(s.ok());
}

} // namespace
