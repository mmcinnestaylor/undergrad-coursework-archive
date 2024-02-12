// Bob Myers
// simple maze test program to help test Grid class

#include <iostream>
using namespace std;

#include "grid.h"


int main()
{
  // set up the initial grid

  Grid g(9,15,2,13,WEST);
  Grid h;
  h.Display();
  h.Grow(30, 30);
  h.Display();
  g.PutDown(2,1);

  for (int i = 0; i < 7; i++)
  {
     g.PlaceBlock(i,11);
     g.PlaceBlock(i,7);
     g.PlaceBlock(i,3);
     g.PlaceBlock(i+2,5);
     g.PlaceBlock(i+2,9);
  }
  //g.Grow(5, 5);
  g.Display();

  // now start moving

  g.TurnLeft();
  g.Move(5);
  g.Display();

  g.TurnLeft();
  g.TurnLeft();
  g.TurnLeft();
  g.Move(1);
  g.Display();  

  for (int i = 0; i < 2; i++)
  {
    g.Move(2);
    g.Display();

    g.TurnLeft();
    g.TurnLeft();
    g.TurnLeft();
    g.Move(6);
    g.Display();  

    g.PutDown();
    g.Display();  

    g.TurnLeft();
    g.Move(2);
    g.Display();

    g.TurnLeft();
    g.Move(6);
    g.Display();

    g.TurnLeft();
    g.TurnLeft();
    g.TurnLeft();
  }

  g.Move(3);
  g.Display();

  g.TurnLeft();
  g.TurnLeft();
  g.TurnLeft();
  g.Move(5);
  g.Display();

  g.PickUp();
  g.Display();

  g.TurnLeft();
  g.Move(1);
  g.Display();

  g.TogglePath();
  g.Display();
  g.TogglePath();
  g.Display();



}
