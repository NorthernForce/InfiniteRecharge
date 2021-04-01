#include "Constants.h"
namespace CPlane {
    class Point {
    public:
        double x,y;
        Point(double x=0, double y=0)
        : x(x), y(y) {}
    };

    const Point up = Point(0,Constants::obstacleDistance);
    const Point right = Point(Constants::obstacleDistance,0);
    const Point down = Point(0,-Constants::obstacleDistance);
    const Point left = Point(-Constants::obstacleDistance,0);

    const Point A1 = Point(30,150);
    const Point A2 = Point(60,150);
    const Point A3 = Point(90,150);
    const Point A4 = Point(120,150);
    const Point A5 = Point(150,150);
    const Point A6 = Point(180,150);
    const Point A7 = Point(210,150);
    const Point A8 = Point(240,150);
    const Point A9 = Point(270,150);
    const Point A10 = Point(300,150);
    const Point A11 = Point(330,150);

    const Point B1 = Point(30,120);
    const Point B2 = Point(60,120);
    const Point B3 = Point(90,120);
    const Point B4 = Point(120,120);
    const Point B5 = Point(150,120);
    const Point B6 = Point(180,120);
    const Point B7 = Point(210,120);
    const Point B8 = Point(240,120);
    const Point B9 = Point(270,120);
    const Point B10 = Point(300,120);
    const Point B11 = Point(330,120);

    const Point C1 = Point(30,90);
    const Point C2 = Point(60,90);
    const Point C3 = Point(90,90);
    const Point C4 = Point(120,90);
    const Point C5 = Point(150,90);
    const Point C6 = Point(180,90);
    const Point C7 = Point(210,90);
    const Point C8 = Point(240,90);
    const Point C9 = Point(270,90);
    const Point C10 = Point(300,90);
    const Point C11 = Point(330,90);

    const Point D1 = Point(30,60);
    const Point D2 = Point(60,60);
    const Point D3 = Point(90,60);
    const Point D4 = Point(120,60);
    const Point D5 = Point(150,60);
    const Point D6 = Point(180,60);
    const Point D7 = Point(210,60);
    const Point D8 = Point(240,60);
    const Point D9 = Point(270,60);
    const Point D10 = Point(300,60);
    const Point D11 = Point(330,60);

    const Point E1 = Point(30,30);
    const Point E2 = Point(60,30);
    const Point E3 = Point(90,30);
    const Point E4 = Point(120,30);
    const Point E5 = Point(150,30);
    const Point E6 = Point(180,30);
    const Point E7 = Point(210,30);
    const Point E8 = Point(240,30);
    const Point E9 = Point(270,30);
    const Point E10 = Point(300,30);
    const Point E11 = Point(330,30);
}