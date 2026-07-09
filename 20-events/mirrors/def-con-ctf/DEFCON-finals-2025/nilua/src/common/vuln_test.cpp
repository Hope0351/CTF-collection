#include <iostream>
#include "common/string_storage.h"
#include "common/vector.h"
#include "common/artwork.h"

int main()
{
    VulnVector<Bid> vec;
    StringStorage storage;

    for (int i = 0; i < 256; i++) {
        StringHandle handle = storage.allocate("bid");
        if (i < 256) {
            vec.push_back(Bid(i, handle, 10.0));
        } else {
            auto pos = &vec[i - 1 + 2];
            vec.insert(pos, Bid(i, handle, 10.0));
            std::cout << "Inserted " << i << " at " << pos << std::endl;
        }
    }

    auto pos = &vec[257];
    StringHandle handle = storage.allocate("bid");
    vec.insert(pos, Bid(257, handle, 10.0));
    std::cout << vec[257].artwork_id << " " << vec[257].bidder << " " << vec[257].amount << std::endl;
    std::cout << "Inserted " << 257 << " at " << pos << std::endl;

    StringHandle handle_0 = storage.allocate("larger");
    StringHandle handle_1 = storage.allocate("vector");
    StringHandle handle_2 = storage.allocate("string");
    storage.allocate("dafuck");
    storage.allocate("mofuck");
    storage.allocate("fuck00");
    storage.allocate("fuck01");
    storage.allocate("fuck02");

    std::cout << handle_0 << ": " << storage.get(handle_0) << std::endl;
    std::cout << handle_1 << ": " << storage.get(handle_1) << std::endl;
    std::cout << handle_2 << ": " << storage.get(handle_2) << std::endl;

    std::cout << vec[257].artwork_id << " " << vec[257].bidder << " " << vec[257].amount << " " 
        << vec[257].success_callback << std::endl;
    vec[257].bid_succeeded(storage);
    return 0;
}