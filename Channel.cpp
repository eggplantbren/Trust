#include "Channel.h"
#include "Constants.h"
#include "Soften.h"
#include <cassert>
#include <sstream>

namespace Trust
{

Channel::Channel(Bytes _claim_hash, std::uint64_t _total_amount_deweys)
:claim_hash(std::move(_claim_hash))
,total_amount_deweys(_total_amount_deweys)
{
    assert(claim_hash.size() == Constants::CLAIM_HASH_SIZE);
}


// Serialise for RocksDB
std::tuple<Bytes, Bytes> Channel::serialise() const
{
    // Pack key
    std::basic_stringstream<unsigned char> key_ostream;
    key_ostream << Constants::CHANNEL_PREFIX;
    key_ostream << claim_hash;

    // Pack value
    std::basic_stringstream<unsigned char> value_ostream;
    value_ostream.write((const unsigned char*)(&total_amount_deweys),
                        sizeof(total_amount_deweys));
    value_ostream.write((const unsigned char*)(&trust_score),
                        sizeof(trust_score));

    return { key_ostream.str(), value_ostream.str() };
}


} // namespace
