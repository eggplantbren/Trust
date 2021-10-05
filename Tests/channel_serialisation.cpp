#include "Channel.h"
#include <iostream>

using namespace Trust;

int main()
{
    // Prepare a claim hash
    Bytes claim_hash;
    for(int i=0; i<20; ++i)
        claim_hash += (unsigned char)0;

    // Create and print channel
    Channel c1(claim_hash, 100000000);
    std::cout << c1 << std::endl;

    // Serialise channel
    auto [key, value] = c1.serialise();
    std::cout << "Key is " << key.size() << " bytes long." << std::endl;
    std::cout << "Value is " << value.size() << " bytes long." << std::endl;
//    Channel c2(key, value);
//    std::cout << c2 << std::endl;


    return 0;
}
