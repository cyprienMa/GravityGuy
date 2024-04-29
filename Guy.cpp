#include "Guy.h"
#include <Imagine/Graphics.h>
#include <algorithm>
using namespace Imagine;

//On initialise un Guy au sol
Guy::Guy() {
    t = -t_saut;
}

//On actualise la valeur de t quand le Guy saute
void Guy::saut(int t0) {
    t = t0;
}

//On vérifie si le Guy est en train de sauter
bool Guy::check_saut(int t0) const {
    return t<=t0 && t0<=t+t_saut;
}

//Si le Guy est en train de sauter, alors on calcule sa hauteur
int Guy::hauteur(int t0) const {
    float h = 0;
    if(check_saut(t0)) {
        float x = 1-2*(t0-t)/(float)t_saut;  //La trajectoire du Guy suit une parabole ce qui nous donne sa hauteur
        h=h_saut*(1-x*x);
    }
    return h;
}

void obstacle::set(int t, int x) {
    tInit=t;
    xInit=x;
}
//On initialise les paramètres de l'obstacle: t=0 et x=10001
obstacle::obstacle() {
    set(0, 1000);
}

//Renvoie le centre de l'obstacle_1
int obstacle::center(int t) const {
    return xInit-(t-tInit)*vitesse;
}



