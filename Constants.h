#ifndef Trust_Constants_h
#define Trust_Constants_h

#include "Bytes.h"

namespace Trust
{

namespace Constants
{

static const Bytes CHANNEL_PREFIX = {0};
static const Bytes SUPPORT_PREFIX = {1};
static constexpr int CLAIM_HASH_SIZE = 20;

} // namespace Constants

} // namespace

#endif
