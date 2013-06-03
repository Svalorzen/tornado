#ifndef UTILS_HASHING_HEADER_FILE
#define UTILS_HASHING_HEADER_FILE

#include <utility>
#include <functional>

// Hashing multiple things
namespace Utils {
    template <class T>
    inline void hash_combine(std::size_t & seed, const T & v) {
        std::hash<T> hasher;
        seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
}

// std::pair hashing
namespace std {
    template<typename S, typename T>
    struct hash<pair<S, T>> {
        inline size_t operator()(const pair<S, T> & v) const {
            size_t seed = 0;
            Utils::hash_combine(seed, v.first);
            Utils::hash_combine(seed, v.second);
            return seed;
        }
    };
}

#endif
