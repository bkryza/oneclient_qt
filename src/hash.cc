#include "hash.h"

#include <boost/uuid/sha1.hpp>


std::string Hash::hash(const std::string& input) {
    boost::uuids::detail::sha1 sha1;
    sha1.process_bytes(input.c_str(), input.size());
    unsigned hash[5] = {0};
    sha1.get_digest(hash);

    // Back to string
    char buf[41] = {0};

    for (int i = 0; i < 5; i++)
    {
        std::sprintf(buf + (i << 3), "%08x", hash[i]);
    }

    return buf;
}
