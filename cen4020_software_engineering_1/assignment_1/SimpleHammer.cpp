/*
 * File:   SimpleHammer.cpp
 * Author: Marlan <mm05f@my.fsu.edu>
 *
 * Created on February 3, 2019, 3:50 PM
 */

#include "SimpleHammer.h"

double SimpleHammer::hit(double armor) {
    double damage = 0;
    if(armor < 30)
      damage = hitPoints;
    else
      damage = hitPoints - armor;

    if (damage < 0) {
        return 0;
    }
    return damage;
}
