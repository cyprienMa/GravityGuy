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

    Img img;
    if (!load(img,srcPath("ville.jpg")))
        return 0;

    Window gameWindow = openWindow(w, h);
    display(img);

    int t=0;
    for(t=0; true; t++){
        J.dessin(t);
        milliSleep(20);
        J.action(t);
        if(J.collision(t)){
            break;
        }
    }
    endGraphics();
    return 0;
}

