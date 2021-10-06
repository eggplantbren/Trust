#include "Support.h"
#include "Constants.h"
#include <cassert>
#include <sstream>

namespace Trust
{

Support::Support(std::string _destination,
                 std::uint64_t _total_amount_deweys,
                 std::optional<std::string> _source)
:destination(std::move(_destination))
,total_amount_deweys(_total_amount_deweys)
,source(std::move(_source))
{
    assert(destination.size() == Constants::CLAIM_HASH_SIZE);
    if(source.has_value())
        assert(source->size() == Constants::CLAIM_HASH_SIZE);
}

// Construct from RocksDB serialisation
Support::Support(const std::string& key, const std::string& value)
{
    assert(key[0] == Constants::SUPPORT_PREFIX);
    assert(key.size() == Constants::CLAIM_HASH_SIZE + 1 ||
           key.size() == 2*Constants::CLAIM_HASH_SIZE + 1);
    assert(value.size() == 8);

    // Unpack key
    destination = key.substr(1, Constants::CLAIM_HASH_SIZE+1);
    if(key.size() == 2*Constants::CLAIM_HASH_SIZE + 1)
        source = key.substr(Constants::CLAIM_HASH_SIZE+1);

    // Unpack value
    std::stringstream value_istream(value);
    value_istream.read((char*)(&total_amount_deweys),
                        sizeof(total_amount_deweys));
}

void Support::increment_deweys(long long delta)
{
    total_amount_deweys += delta;
}

std::tuple<std::string, std::string> Support::serialise() const
{
    // Pack key
    std::stringstream key_ostream;
    key_ostream << Constants::SUPPORT_PREFIX;
    key_ostream << destination;
    if(source.has_value())
        key_ostream << (*source);

    // Pack value
    std::stringstream value_ostream;
    value_ostream.write((const char*)(&total_amount_deweys),
                        sizeof(total_amount_deweys));

    return { key_ostream.str(), value_ostream.str() };
}

// Print for human consumption
void Support::print(std::ostream& out) const
{
    out << "Support\n{\n";
    out << "  destination = ";
    for(size_t i=0; i<destination.size(); ++i)
        out << (int)destination[i] << ' ';
    out << '\n';
    out << "  total_amount_deweys = " << total_amount_deweys << '\n';
    out << "  source = ";
    if(source.has_value())
        for(size_t i=0; i<source->size(); ++i)
            out << (int)(*source)[i] << ' ';
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

