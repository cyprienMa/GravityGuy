#include "Guy.h"

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
        float x = 1-2*(t0-t)/(float)t_saut;
        h=h_saut*(1-x*x);
    }
    return h;
}



