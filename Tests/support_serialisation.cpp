#include "Support.h"
#include <iostream>

using namespace Trust;

int main()
{
    // Prepare a claim hash
    std::string claim_hash;
    for(int i=0; i<20; ++i)
        claim_hash += (char)i;

    // Create and print support
    Support s1(claim_hash, 100000000);
    std::cout << s1 << std::endl;

    // Serialise support
    auto [key, value] = s1.serialise();
    std::cout << "Key is " << key.size() << " bytes long." << std::endl;
    std::cout << "Value is " << value.size() << " bytes long." << std::endl;
    Support s2(key, value);
    std::cout << s2 << std::endl;

    // Now redo with signed support
    std::string temp;
    for(int i=0; i<20; ++i)
        temp += (char)(i + 20);
    Support s3(claim_hash, 12345678, temp);
    std::cout << s3 << std::endl;
    auto [key3, value3] = s3.serialise();
    std::cout << Support{key3, value3} << std::endl;

    return 0;
}
