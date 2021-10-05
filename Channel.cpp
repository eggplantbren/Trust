#include "Channel.h"
#include "Soften.h"

namespace Trust
{

Channel::Channel(Bytes _claim_hash, std::uint64_t _total_amount_deweys)
:claim_hash(std::move(_claim_hash))
,total_amount_deweys(_total_amount_deweys)
{


}


} // namespace
