#include "Soften.h"
#include <cmath>

namespace Trust
{

double soften(std::uint64_t amount_deweys)
{
    double lbc = 1.0E-8*amount_deweys;
    return sqrt(1.0 + lbc);
}

} // namespace
