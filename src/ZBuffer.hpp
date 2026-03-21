#ifndef ZBUFFER_HPP
#define ZBUFFER_HPP
#include <vector>
#include <algorithm>

class ZBuffer {
public:
    explicit ZBuffer(int width) : buf_(width, 1e30), width_(width) {}

    void reset() { std::fill(buf_.begin(), buf_.end(), 1e30); }
    void set(int col, double dist) { buf_[col] = dist; }
    double get(int col) const { return buf_[col]; }
    int width() const { return width_; }
    const double* data() const { return buf_.data(); }

private:
    std::vector<double> buf_;
    int width_;
};

#endif
