#ifndef Trust_Channel_h
#define Trust_Channel_h

#include <ostream>
#include <tuple>

namespace Trust
{

class Channel
{
    private:
        std::string claim_hash;
        std::uint64_t total_amount_deweys;
        double trust_score;

    public:

        Channel() = delete;

        // Construct from claim_hash and total dewey amount
        Channel(std::string _claim_hash, std::uint64_t _total_amount_deweys);

        // Construct from RocksDB serialisation
        Channel(const std::string& key, const std::string& value);

        // Serialise for RocksDB
        std::tuple<std::string, std::string> serialise() const;

        // Setter
        void increment_deweys(long long delta_deweys);

        // Print for human consumption
        void print(std::ostream& out) const;
};

std::ostream& operator << (std::ostream& out, const Channel& channel);

} // namespace


#endif
