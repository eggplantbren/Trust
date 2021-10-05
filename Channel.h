#ifndef Trust_Channel_h
#define Trust_Channel_h

#include "Bytes.h"
#include <cstdint>
#include <tuple>

namespace Trust
{

class Channel
{
    private:
        Bytes claim_hash;
        std::uint64_t total_amount_deweys;
        double trust_score;

    public:

        Channel() = delete;

        // Construct from claim_hash and total dewey amount
        Channel(Bytes _claim_hash, std::uint64_t _total_amount_deweys);

        // Construct from RocksDB serialisation
        Channel(const Bytes& key, const Bytes& value);

        // Serialise for RocksDB
        std::tuple<Bytes, Bytes> serialise() const;
};

} // namespace


#endif
