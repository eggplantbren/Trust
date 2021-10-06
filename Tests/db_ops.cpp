#include "Database.h"
#include <iostream>

using namespace Trust;

int main()
{
    // Prepare a claim hash
    std::string claim_hash;
    for(int i=0; i<20; ++i)
        claim_hash += (char)i;

    Database database;
    database.channel_created(claim_hash, 1000000);
    database.channel_updated(claim_hash, 100000000);
    std::cout << database << std::endl;

    return 0;
}
