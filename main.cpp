/*
  main.cpp

  (C) Copyright 2015, Brad Parker
  All rights reserved.

  License: 3-clause BSD. See COPYING
*/

#include <QCoreApplication>
#include "keyboard.h"

int main(int argc, char *argv[]) {
  QCoreApplication app(argc, argv);

  Keyboard k;
  k.setMode(MODE_NORMAL);
  k.setColor(REGION_LEFT, COLOR_RED, INTENSITY_HIGH);
  k.setColor(REGION_MIDDLE, COLOR_PURPLE, INTENSITY_HIGH);
  k.setColor(REGION_RIGHT, COLOR_SKY, INTENSITY_HIGH);

  return 0;
  //return app.exec();
}

