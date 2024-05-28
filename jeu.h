#pragma once
#include"Guy.h"
#include <Imagine/Graphics.h>
#include <algorithm>
using namespace Imagine;

class jeu{
    //Le Guy du jeu
    Guy guy;

    //On crée un tableau pour les obstacles
    obstacle T[n_obstacle*5 + 5];
    obstacle Rect_haut;

    //On charge les images
    NativeBitmap my_native_bitmap_ville;
    NativeBitmap my_native_bitmap_triangle;
    NativeBitmap my_native_bitmap_rect;
    NativeBitmap my_native_bitmap_lava;
    NativeBitmap my_native_bitmap_sol;
    NativeBitmap my_native_bitmap;
    NativeBitmap my_native_bitmap_bis;
    NativeBitmap my_native_bitmap_boom;
    NativeBitmap my_native_bitmap_losange;
    NativeBitmap my_native_bitmap_rond;

public:
    jeu();
    void init();

    void dessin(int t) const;
    void dessin2(int t) const; //Pour le niveau 2

    void action(int t);
    int menu();

    bool collision(int t) const;
    bool collision2(int t) const;//Pour le niveau 2
};
