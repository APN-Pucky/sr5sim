#include <string>
using namespace std;

template <typename T>
std::string tos( const T & t );

void pppp();

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}
