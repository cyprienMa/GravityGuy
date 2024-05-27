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
    int Level = J.menu();

    Window gameWindow = openWindow(w, h);
    if (Level==1){
        int t=0;
        for(t=0; true; t++){
            J.dessin(t);
            milliSleep(20);
            J.action(t);
            if(J.collision(t)){
                break;
            }
        }
    }

    if (Level==2){
        int t=0;
        for(t=0; true; t++){
            J.dessin2(t);
            milliSleep(20);
            J.action(t);
            if(J.collision2(t)){
                break;
            }
        }
    }
    endGraphics();
    return 0;
}

