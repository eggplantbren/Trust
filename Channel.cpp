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
,trust_score(soften(total_amount_deweys))
{
    assert(claim_hash.size() == Constants::CLAIM_HASH_SIZE);
}

// Construct from RocksDB serialisation
Channel::Channel(const Bytes& key, const Bytes& value)
{
    assert(key.size() == Constants::CLAIM_HASH_SIZE + 1);
    assert(value.size() == 2*8);

    // Unpack key
    claim_hash = key.substr(1);

    // Unpack value
    std::basic_stringstream<unsigned char> value_istream(value);
    value_istream.read((unsigned char*)(&total_amount_deweys),
                        sizeof(total_amount_deweys));
    value_istream.read((unsigned char*)(&trust_score),
                        sizeof(trust_score));
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


void Channel::print(std::ostream& out) const
{
    out << "Channel\n{\n";
    out << "  claim_hash = ";
    for(size_t i=0; i<claim_hash.size(); ++i)
        out << (unsigned int)claim_hash[i] << ' ';
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
