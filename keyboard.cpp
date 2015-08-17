#include "keyboard.h"
#include <iostream>
#include <QTimer>
#include <QCoreApplication>

#define BUFSIZ 8

Keyboard::Keyboard() :
  m_dev(NULL)
{
  m_dev = hid_open(0x1770, 0xff00, 0);

  if(!m_dev) {
    std::cout << "cannot open usb device" << std::endl;
    QTimer::singleShot(0, qApp, SLOT(quit()));
    return;
  }
}

Keyboard::~Keyboard() {
  if(m_dev) {
    hid_close(m_dev);
    std::cout << "closed usb device" << std::endl;
  }
}

void Keyboard::setMode(Mode mode) {
  if(!m_dev)
    return;

  unsigned char buf[BUFSIZ] = {0};

  buf[0] = 1;
  buf[1] = 2;
  buf[2] = 65;
  buf[3] = static_cast<unsigned int>(mode);
  buf[4] = 0;
  buf[5] = 0;
  buf[6] = 0;
  buf[7] = 236;

  hid_send_feature_report(m_dev, buf, BUFSIZ);
}

void Keyboard::setColor(Region region, Color color, Intensity intensity) {
  if(!m_dev)
    return;

  unsigned char buf[BUFSIZ] = {0};

  buf[0] = 1;
  buf[1] = 2;
  buf[2] = 66;
  buf[3] = static_cast<unsigned int>(region);
  buf[4] = static_cast<unsigned int>(color);
  buf[5] = static_cast<unsigned int>(intensity);
  buf[6] = 0;
  buf[7] = 236;

  hid_send_feature_report(m_dev, buf, BUFSIZ);
}

