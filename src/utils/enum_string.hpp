#ifndef ENUM_STRING_HEADER_FILE
#define ENUM_STRING_HEADER_FILE

#include <cstdlib>

struct entry {
    const char * name;
    int value;
};

template <typename T, size_t N>
constexpr size_t size_of(T (&)[N]) {
    return N;
}

constexpr bool same(const char * lhs, const char * rhs) {
    return !*lhs && !*rhs ? true : (*lhs == *rhs && same(lhs+1, rhs+1));
}

constexpr int value(char const * name, const entry * pair) {
    return same(pair->name, name) ? pair->value : value(name, pair+1);
}

#endif
