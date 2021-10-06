#include "Database.h"
#include "Channel.h"
#include "Constants.h"
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
    rocksdb::Status status = db->Put(rocksdb::WriteOptions(), key, value);
    assert(status.ok());

    Support support(claim_hash, bid);
    std::tie(key, value) = support.serialise();
    status = db->Put(rocksdb::WriteOptions(), key, value);
    assert(status.ok());
}

void Database::channel_updated(const std::string& claim_hash,
                               long long bid_change)
{
    // Read existing channel data
    std::string key, value;
    key = Constants::CHANNEL_PREFIX + claim_hash;
    rocksdb::Status status = db->Get(rocksdb::ReadOptions(), key, &value);
    assert(status.ok());

    // Increment and save updated channel data
    Channel c(key, value);
    c.increment_deweys(bid_change);
    std::tie(key, value) = c.serialise();
    status = db->Put(rocksdb::WriteOptions(), key, value);
    assert(status.ok());

    // Read existing support data
    key = Constants::SUPPORT_PREFIX + claim_hash;
    status = db->Get(rocksdb::ReadOptions(), key, &value);
    assert(status.ok());

    // Increment and save updated support data
    Support s(key, value);
    s.increment_deweys(bid_change);
    std::tie(key, value) = s.serialise();
    status = db->Put(rocksdb::WriteOptions(), key, value);
    assert(status.ok());
}

} // namespace
