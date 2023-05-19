#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

template <typename T>
struct Vect;

template <typename T>
auto operator*(Vect<T>, T);

template <typename T>
auto operator*(Vect<T>, Vect<T>);

/*! \class Vect
    \brief 2D geometry vector
    \brief x,y - coordinaes
    \brief supports common vector operations
*/
template <typename T>
struct Vect {
    /// \brief x coordinate
    T x = 0;
    /// \brief y coordinate
    T y = 0;
    /// \brief multiplying by a scalar
    /// \param left - scalar
    auto& operator*=(T left) {
        *this = *this * left;
        return *this;
    }
    /// \brief dividing by a scalar
    /// \param left - scalar
    auto& operator/=(T left) {
        *this = *this / left;
        return *this;
    }
    /// \brief adding Vect
    /// \param left - Vect
    auto& operator+=(Vect<T> left) {
        *this = *this + left;
        return *this;
    }
    /// \brief subtracting Vect
    /// \param left - Vect
    auto& operator-=(Vect<T> left) {
        *this = *this - left;
        return *this;
    }
    /// \brief inverse
    Vect operator-() const {
        return {-x, -y};
    }
    /// \brief module squared
    auto SqAbs() {
        return x * x + y * y;
    }
};

/// \brief reading coordinates
/// \param stream - stream to read from
/// \param vect - place where to read
template <typename T>
auto& operator>>(std::istream& stream, Vect<T>& vect) {
    stream >> vect.x >> vect.y;
    return stream;
}

/// \brief scalar product of vectors
/// \param left - left multipler
/// \param right - right multipler
template <typename T>
auto operator*(Vect<T> left, Vect<T> right) {
    return left.x * right.x + left.y * right.y;
}

/// \brief cross product of vectors
/// \param left - left multipler
/// \param right - right multipler
template <typename T>
auto operator/(Vect<T> left, Vect<T> right) {
    return left.x * right.y - left.y * right.x;
}

/// \brief multiplying by a scalar
/// \param left - Vect
/// \param right - scalar
template <typename T>
auto operator*(Vect<T> q, T e) {
    return Vect{q.x * e , q.y * e};
}

/// \brief dividing by a scalar
/// \param left - Vect
/// \param right - scalar
template <typename T>
auto operator/(Vect<T> q, T e) {
    return Vect{q.x / e , q.y / e};
}

/// \brief multiplying by a scalar
/// \param left - scalar
/// \param right - Vect
template <typename T>
auto operator*(T q, Vect<T> e) {
    return Vect{q * e.x , q * e.y};
}

/// \brief adding
/// \param left - Vect
/// \param right - Vect
template <typename T>
auto operator+(Vect<T> left, Vect<T> right) {
    return Vect{left.x + right.x, left.y + right.y};
}

/// \brief subtracting
/// \param left - Vect
/// \param right - Vect
template <typename T>
auto operator-(Vect<T> left, Vect<T> right) {
    return Vect<T>{left.x - right.x, left.y - right.y};
}

/// \brief get -1 or 0 or 1 depending on sign of a number
/// \param num - number
auto Sign(auto num) {
    return (0 < num) - (num < 0);
}

/// @brief get abs of a number
/// @param num - number
auto Abs(auto num) {
    return num < 0 ? -num : num;
}

/// \brief return convex hull
/// \details side effect: shuffles dots
/// \param dots - dots
template<typename T>
auto ConvexHull(std::vector<Vect<T>>&dots){
    std::sort(dots.begin(), dots.end(), [&](auto q, auto e) { return std::make_tuple(q.x, q.y) < std::make_tuple(e.x, e.y); });
    std::sort(dots.begin() + 1, dots.end(), [&](auto q, auto e) {
        auto w = (q - dots[0]) / (e - dots[0]);
        if (w == 0) {
            w = ((q - dots[0]).SqAbs() - (e - dots[0]).SqAbs());
        }
        return w < 0;
    });
    std::vector<Vect<std::int64_t>> poly({dots[0], dots[1]});
    std::rotate(dots.begin(), dots.begin() + 1, dots.end());
    for (std::size_t q = 1; q < dots.size(); ++q) {
        while (poly.size() > 1 and (poly.end()[-2] - poly.end()[-1]) / (poly.end()[-1] - dots[q]) >= 0) {
            poly.pop_back();
        }
        poly.push_back(dots[q]);
    }
    poly.pop_back();
    return poly;
}

/// \brief return convex hull
/// \details side effect: shuffles dots
/// \param poly - polygon
template<typename T>
auto DoubledArea(std::vector<Vect<T>>&poly){
    int64_t d = 0;
    for (size_t q = 2; q < poly.size(); ++q) {
        d += (poly[q - 1] - poly[0]) / (poly[q] - poly[q - 1]);
    }
    d = Abs(d);
    return d;
}

int main() {
    size_t n;
    std::cin>>n;
    std::vector<Vect<std::int64_t>> dots(n);
    for (auto&w:dots){
        std::cin>>w;
    }
    auto poly=ConvexHull(dots);
    std::cout << poly.size() << std::endl;
    for (auto w : poly) {
        std::cout << w.x << " " << w.y << "\n";
    }
    auto d_area=DoubledArea(poly);
    std::cout << d_area / 2 << (d_area % 2 ? ".5" : ".0") << std::endl;
}
