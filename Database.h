#ifndef Trust_Database_h
#define Trust_Database_h

#include <rocksdb/db.h>
#include <cstdint>
#include <ostream>

namespace Trust
{

class Database
{
    private:
        rocksdb::DB* db;

    public:
        Database();
        ~Database();

        // Events that can occur on the blockchain that should trigger
        // something to occur in the trust database.

        // A channel was created
        void channel_created(const std::string& claim_hash, std::uint64_t bid);

        // A channel was updated and its bid changed
        void channel_updated(const std::string& claim_hash, long long bid_change);

        // A channel was abandoned
        void channel_abandoned(const std::string& claim_hash);

/*        void channel_abandoned(const std::string& _claim_hash);*/

        // This could be a claim_create, or a claim_update that moved the claim
        // into the channel when it wasn't previously
/*        void claim_added_to_channel(const std::string& _claim_hash, std::uint64_t amount);*/
/*        void claim_removed_from_channel(const std::string& _claim_hash, std::uint64_t amount);*/

        void print(std::ostream& out) const;
};

std::ostream& operator << (std::ostream& out, const Database& database);

} // namespace

#endif
