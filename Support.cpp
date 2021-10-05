#include "Support.h"
#include "Constants.h"
#include <cassert>

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


} // namespace

