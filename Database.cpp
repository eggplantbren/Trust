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
    Channel c(key, value);

    // Read existing support data
    key = Constants::SUPPORT_PREFIX + claim_hash;
    status = db->Get(rocksdb::ReadOptions(), key, &value);
    assert(status.ok());
    Support s(key, value);

    // Update values (not trust score, yet)
    c.increment_deweys(bid_change);
    s.increment_deweys(bid_change);   

    // Save updated data
    std::tie(key, value) = c.serialise();
    status = db->Put(rocksdb::WriteOptions(), key, value);
    assert(status.ok());
    std::tie(key, value) = s.serialise();
    status = db->Put(rocksdb::WriteOptions(), key, value);
    assert(status.ok());
}

void Database::print(std::ostream& out) const
{
    rocksdb::Iterator* it = db->NewIterator(rocksdb::ReadOptions());
    for(it->SeekToFirst(); it->Valid(); it->Next())
    {
        std::string key   = it->key().ToString();
        std::string value = it->value().ToString();
        if(key[0] == Constants::CHANNEL_PREFIX)
            out << Channel{key, value} << std::endl;
        else if(key[0] == Constants::SUPPORT_PREFIX)
            out << Support{key, value} << std::endl;
        else
        {
            out << "Unknown " << it->key().ToString() << ": ";
            out << it->value().ToString() << std::endl;
        }
    }
    assert(it->status().ok()); // Check for any errors found during the scan
    delete it;
}

std::ostream& operator << (std::ostream& out, const Database& database)
{
    database.print(out);
    return out;
}

} // namespace
