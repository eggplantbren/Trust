#ifndef Trust_Support_h
#define Trust_Support_h

#include <cstdint>
#include <ostream>
#include <optional>
#include <tuple>

namespace Trust
{

class Support
{
    private:
        std::string supported_channel;
        std::uint64_t total_amount_deweys;
        std::optional<std::string> supporting_channel;

    public:

        Support() = delete;

        // Construct from given stuff
        Support(std::string _supported_channel,
                std::uint64_t _total_amount_deweys,
                std::optional<std::string> _supporting_channel = {});

        // Construct from RocksDB serialisation
        Support(const std::string& key, const std::string& value);

        // Serialise for RocksDB
        std::tuple<std::string, std::string> serialise() const;

        // Print for human consumption
        void print(std::ostream& out) const;
};

std::ostream& operator << (std::ostream& out, const Support& support);

} // namespace


#endif
