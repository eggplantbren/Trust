#include "Support.h"
#include "Constants.h"
#include <cassert>
#include <sstream>

namespace Trust
{

Support::Support(Bytes _supported_channel,
                 std::uint64_t _total_amount_deweys,
                 std::optional<Bytes> _supporting_channel)
:supported_channel(std::move(_supported_channel))
,total_amount_deweys(_total_amount_deweys)
,supporting_channel(std::move(_supporting_channel))
{
    assert(supported_channel.size() == Constants::CLAIM_HASH_SIZE);
    if(supporting_channel.has_value())
        assert(supporting_channel->size() == Constants::CLAIM_HASH_SIZE);
}

// Construct from RocksDB serialisation
Support::Support(const Bytes& key, const Bytes& value)
{
    assert(key.size() == Constants::CLAIM_HASH_SIZE + 1 ||
           key.size() == 2*Constants::CLAIM_HASH_SIZE + 1);
    assert(value.size() == 8);

    // Unpack key
    supported_channel = key.substr(1, Constants::CLAIM_HASH_SIZE+1);
    if(key.size() == 2*Constants::CLAIM_HASH_SIZE + 1)
        supporting_channel = key.substr(Constants::CLAIM_HASH_SIZE+1);

    // Unpack value
    std::basic_stringstream<unsigned char> value_istream(value);
    value_istream.read((unsigned char*)(&total_amount_deweys),
                        sizeof(total_amount_deweys));
}

std::tuple<Bytes, Bytes> Support::serialise() const
{
    // Pack key
    std::basic_stringstream<unsigned char> key_ostream;
    key_ostream << Constants::SUPPORT_PREFIX;
    key_ostream << supported_channel;
    if(supporting_channel.has_value())
        key_ostream << (*supporting_channel);

    // Pack value
    std::basic_stringstream<unsigned char> value_ostream;
    value_ostream.write((const unsigned char*)(&total_amount_deweys),
                        sizeof(total_amount_deweys));

    return { key_ostream.str(), value_ostream.str() };
}

// Print for human consumption
void Support::print(std::ostream& out) const
{
    out << "Support\n{\n";
    out << "  supported_channel = ";
    for(size_t i=0; i<supported_channel.size(); ++i)
        out << (unsigned int)supported_channel[i] << ' ';
    out << '\n';
    out << "  total_amount_deweys = " << total_amount_deweys << '\n';
    out << "  supporting_channel = ";
    if(supporting_channel.has_value())
        for(size_t i=0; i<supporting_channel->size(); ++i)
            out << (unsigned int)(*supporting_channel)[i] << ' ';
    else
        out << "null";
    out << '\n';
    out << '}';
}

std::ostream& operator << (std::ostream& out, const Support& support)
{
    support.print(out);
    return out;
}

} // namespace

