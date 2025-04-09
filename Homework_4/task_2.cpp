#include <iostream>
#include <vector>
#include <algorithm>

struct Point
{
    int x, y;
};

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "( " << p.x << " , " << p.y << " )";
    return os;
}

bool PointsCompare(const Point& p1, const Point& p2) {
    if (p1.x == p2.x) {
        return p1.y < p2.y;
    }
    return p1.x < p2.x;
}

int main() {
    std::vector<Point> points;
    int N;
    std::cin >> N;
    for (int i = 0; i < N; i++) {
        int abscissa, ordinate;
        std::cin >> abscissa >> ordinate;
        points.push_back({abscissa, ordinate});
    }
    std::sort(points.begin(), points.end(), PointsCompare);

    for (int i = 0; i < N; i++) {
        std::cout << points[i] << "\n";
    }
}