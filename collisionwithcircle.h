#ifndef COLLISIONWITHCIRCLE_H
#define COLLISIONWITHCIRCLE_H
//碰撞检测算法
#include <QtMath>
inline bool CollisionWithCircle(QPoint PointA, int RadiusA, QPoint PointB, int RadiusB)
{
    const int X_Distance= PointA.x() - PointB.x();
    const int Y_Distance = PointA.y() - PointB.y();
    const int Distance = qSqrt(X_Distance*X_Distance+Y_Distance*Y_Distance);

    if (Distance <= RadiusA + RadiusB)
        return true;
    else
        return false;
}


#endif // COLLISIONWITHCIRCLE_H
