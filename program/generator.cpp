#include <vector>
#include <cstdint>
#include <ctime>
#include <random>
#include "head.h"

void edge_generator(std::vector<uint32_t>* E, uint32_t max,
                    uint32_t& edge_amount, uint32_t div)
{
    std::srand(time(0));
    uint32_t out_edges;
    for(uint32_t i = 0; i < max; ++i)
    {
        for(uint32_t j = 0; j < max; ++j)
            if((std::rand() % 101) < div)
            {
                ++edge_amount;
                E[i].push_back(j);
            }
    }
}
