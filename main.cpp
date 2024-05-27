// Project Gravity Guy
// Author: Cyprien MALGOYRE and Hind TANOUTI

#include <Imagine/Graphics.h>
#include <Imagine/Images.h>
#include <iostream>

using namespace Imagine;
using namespace std;
typedef Image<byte> Img;

#include "Guy.h"
#include "jeu.h"


int main(){
    jeu J;
    J.menu();
    Window gameWindow = openWindow(w, h);

    int t=0;
    for(t=0; true; t++){
        J.dessin(t);
        milliSleep(20);
        J.action(t);
        if(J.collision(t)){
            std::cout<< t<<std::endl;
            break;
        }
    }
    endGraphics();
    return 0;
}

