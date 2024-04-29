// Project Gravity Guy
// Author: Cyprien MALGOYRE and Hind TANOUTI

#include <Imagine/Graphics.h>
#include <iostream>
using namespace Imagine;
using namespace std;
#include "Guy.h"
#include "jeu.h"

int main(){
    openWindow(w,h);
    jeu J;
    int t=0;
    for(t=0; true; t++) {
        J.dessin(t);
        milliSleep(20);
        J.action(t);
    }
    endGraphics();
    return 0;
}

