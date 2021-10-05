#ifndef Trust_Support_h
#define Trust_Support_h

#include "Bytes.h"
#include <cstdint>
#include <ostream>
#include <optional>
#include <tuple>

namespace Trust
{

class Support
{
    private:
        Bytes supported_channel;
        std::uint64_t total_amount_deweys;
        std::optional<Bytes> supporting_channel;

    public:

        Support() = delete;

        // Construct from given stuff
        Support(Bytes _supported_channel,
                std::uint64_t _total_amount_deweys,
                std::optional<Bytes> _supporting_channel = {});

        // Construct from RocksDB serialisation
        Support(const Bytes& key, const Bytes& value);

        // Serialise for RocksDB
        std::tuple<Bytes, Bytes> serialise() const;

        // Print for human consumption
        void print(std::ostream& out) const;
};

std::ostream& operator << (std::ostream& out, const Support& support);

} // namespace


#endif
