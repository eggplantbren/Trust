#include "Database.h"
#include "Channel.h"
#include "Support.h"

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

    Support support(claim_hash, bid);
    auto [key2, value2] = support.serialise();
    s = db->Put(rocksdb::WriteOptions(), key2, value2);

    assert(s.ok());
}

void Database::channel_updated(const std::string& _claim_hash,
                               std::uint64_t old_bid,
                               std::uint64_t new_bid)
{
    // TODO
}

} // namespace
