QT -= gui
SOURCES += main.cpp keyboard.cpp
HEADERS += keyboard.h

unix:LIBS += -lhidapi-libusb
