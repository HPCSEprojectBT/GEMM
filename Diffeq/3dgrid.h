#include <iostream>
#include <vector>

using namespace std;

template<class T>
class grid3d {
private:
    size_t width, height, depth;
    std::vector<std::vector<std::vector<T> > > data;
public:
    grid3d(size_t N)
    : width(N), height(N), depth(N), data(N, vector< vector<T> > (N, vector<T> (N)))
    { }
    
    T& operator()(size_t i, size_t j, size_t k) {
        return data[i][j][k];
    }
    
    const T& operator()(size_t i, size_t j, size_t k) const {
        return data[i][j][k];
    }
};

