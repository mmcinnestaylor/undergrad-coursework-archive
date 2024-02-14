/*
 * File:   CrazyRandomSword.h
 * Author: Marlan <mm05f@ny.fsu.edu>
 *
 * Created on February 3, 2019, 4:15 PM
 */

#include <string>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include "Weapon.h"

#ifndef CRAZYRANDOMSWORD_H
#define CRAZYRANDOMSWORD_H

/**
 * Defines the behavior of a crazy random sword (hitpoint = rand int 7-100,
 * ignores rand amount of  armor points 2 to .33(armor weapon hits))
 */
class CrazyRandomSword : public Weapon {

public:

    CrazyRandomSword() : Weapon("Crazy Random Sword", rand()%94 + 7) { //Calls Weapon(name, hitpoints) constructor with values Crazy Random Sword and rand()%94+7
    }

    virtual ~CrazyRandomSword() {};

    virtual double hit(double armor);

};

#endif /* CRAZYRANDOMSWORD_H */
