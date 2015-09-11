#  msi-keyboard.pro

#  (C) Copyright 2015, Brad Parker
#  All rights reserved.

#  License: 3-clause BSD. See COPYING

QT -= gui
SOURCES += main.cpp keyboard.cpp
HEADERS += keyboard.h

QMAKE_CXXFLAGS += -std=c++11

unix:LIBS += -lhidapi-libusb
