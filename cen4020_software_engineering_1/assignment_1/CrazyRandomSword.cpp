/*
 * File:   CrazyRandomSword.cpp
 * Author: Marlan <mm05f@my.fsu.edu>
 *
 * Created on February 3, 2019, 4:15 PM
 */

#include "CrazyRandomSword.h"

double CrazyRandomSword::hit(double armor) {
    double damage = 0;

    if(armor <= 6)
      damage = hitPoints - (armor - 2);
    else
      damage = hitPoints - (armor - (rand()%((int)ceil(armor * .3) - 2) + 2));
    if (damage < 0) {
        return 0;
    }
    return damage;
}
