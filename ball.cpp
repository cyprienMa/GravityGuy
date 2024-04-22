#include "ball.h"
#include "tools.h"

void DisplayBall(Ball D) {
    fillCircle(D.p.x, D.p.y, D.r, D.col);
}

void EraseBall(Ball D) {
    fillCircle(D.p.x, D.p.y, D.r, WHITE);
}

void MoveBall(Ball &D){
    D.p = D.p + D.v*dt;
}
void Acceleration(Ball &D){
    D.v.y = D.v.y + 0.0005*dt;
}

void Gravitation(Ball &D, Ball S){
    Vector R0 = D.p - S.p;
    double R = norm2(R0);
    if (R >= D.r + S.r){
        Vector A = {-G*S.m*R0.x / (R*R*R), -G*S.m*R0.y / (R*R*R)};
        D.v = D.v + A*dt;
    }
}

void shockSimple(Ball &D, Ball &S){
    shockSimple(D.p.x, D.p.y, D.v.x, D.v.y, D.m, S.p.x, S.p.y, S.v.x, S.v.y);
}

bool collision(Ball &D, Ball &S){
    return collision(D.p.x, D.p.y, D.v.x, D.v.y, D.r, S.p.x, S.p.y, S.v.x, S.v.y, S.r);
}

void shock(Ball &B1, Ball &B2){
    return shock(B1.p.x,  B1.p.y,  B1.v.x, B1.v.y, B1.m, B2.p.x,  B2.p.y,  B2.v.x, B2.v.y, B2.m);
}
