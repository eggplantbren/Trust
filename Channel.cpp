#include "Channel.h"
#include "Constants.h"
#include "Soften.h"
#include <cassert>
#include <sstream>

namespace Trust
{

Channel::Channel(std::string _claim_hash, std::uint64_t _total_amount_deweys)
:claim_hash(std::move(_claim_hash))
,total_amount_deweys(_total_amount_deweys)
,trust_score(soften(total_amount_deweys))
{
    assert(claim_hash.size() == Constants::CLAIM_HASH_SIZE);
}

// Construct from RocksDB serialisation
Channel::Channel(const std::string& key, const std::string& value)
{
    assert(key.size() == Constants::CLAIM_HASH_SIZE + 1);
    assert(value.size() == 2*8);

    // Unpack key
    claim_hash = key.substr(1);

    // Unpack value
    std::stringstream value_istream(value);
    value_istream.read((char*)(&total_amount_deweys),
                        sizeof(total_amount_deweys));
    value_istream.read((char*)(&trust_score),
                        sizeof(trust_score));
}

// Serialise for RocksDB
std::tuple<std::string, std::string> Channel::serialise() const
{
    // Pack key
    std::stringstream key_ostream;
    key_ostream << Constants::CHANNEL_PREFIX;
    key_ostream << claim_hash;

    // Pack value
    std::stringstream value_ostream;
    value_ostream.write((const char*)(&total_amount_deweys),
                        sizeof(total_amount_deweys));
    value_ostream.write((const char*)(&trust_score),
                        sizeof(trust_score));

    return { key_ostream.str(), value_ostream.str() };
}

void Channel::increment_deweys(long long delta_deweys)
{
    total_amount_deweys += delta_deweys;
}


void Channel::print(std::ostream& out) const
{
    out << "Channel\n{\n";
    out << "  claim_hash = ";
    for(size_t i=0; i<claim_hash.size(); ++i)
        out << (int)claim_hash[i] << ' ';
    out << '\n';
    out << "  total_amount_deweys = " << total_amount_deweys << '\n';
    out << "  trust_score = " << trust_score << '\n';
    out << '}';
}

std::ostream& operator << (std::ostream& out, const Channel& channel)
{
    channel.print(out);
    return out;
}


} // namespace
