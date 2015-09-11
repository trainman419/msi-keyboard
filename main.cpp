/*
  main.cpp

  (C) Copyright 2015, Brad Parker
  All rights reserved.

  License: 3-clause BSD. See COPYING
*/

#include <QCoreApplication>
#include <QCommandLineParser>
#include <iostream>
#include "keyboard.h"

enum CommandLineParseResult
{
  CommandLineOk,
  CommandLineError,
  CommandLineVersionRequested,
  CommandLineHelpRequested
};


CommandLineParseResult parseCommandLine(QCommandLineParser &parser, QString *errorMessage) {
  QCommandLineOption helpOption = parser.addHelpOption();
  QCommandLineOption versionOption = parser.addVersionOption();

  QCommandLineOption mode(QStringList() << "m" << "mode", "set color mode: normal, gaming, breathe, demo, wave");
  QCommandLineOption color(QStringList() << "c" << "color", "set a color using the format: region,color,intensity");

  parser.addOption(mode);
  parser.addOption(color);

  if(!parser.parse(QCoreApplication::arguments())) {
    *errorMessage = parser.errorText();
    return CommandLineError;
  }

  if(parser.isSet(versionOption))
    return CommandLineVersionRequested;

  if(parser.isSet(helpOption))
    return CommandLineHelpRequested;

  return CommandLineOk;
}

int main(int argc, char *argv[]) {
  QCoreApplication app(argc, argv);
  app.setApplicationName("msi-keyboard");
  app.setApplicationVersion("1.0");

  QCommandLineParser parser;
  parser.setApplicationDescription("Keyboard color changer for MSI steelseries keyboards");

  QString errorMessage;

  switch(parseCommandLine(parser, &errorMessage)) {
    case CommandLineOk:
      break;
    case CommandLineError:
      fputs(qPrintable(errorMessage), stderr);
      fputs("\n\n", stderr);
      fputs(qPrintable(parser.helpText()), stderr);
      return 1;
    case CommandLineVersionRequested:
      printf("%s %s\n", qPrintable(QCoreApplication::applicationName()),
             qPrintable(QCoreApplication::applicationVersion()));
      return 0;
    case CommandLineHelpRequested:
    {
      std::cout << qPrintable(parser.helpText()) << std::endl;

      QStringList regions = QStringList() << "left" << "middle" << "right";
      QStringList colors = QStringList() << "off" << "red" << "orange" << "yellow" << "green" << "sky" << "blue" << "purple" << "white";
      QStringList intensities = QStringList() << "high" << "medium" << "low" << "light";

      QString colorHelp = QString(R"(Available regions:

%1

Available colors:

%2

Available intensities:

%3

Example:

%4
)").arg(regions.join('\n')).arg(colors.join('\n')).arg(intensities.join('\n')).arg(QString(argv[0]) + " -m normal -c left,red,high -c middle,purple,high -c right,sky,high");

      std::cout << qPrintable(colorHelp) << std::endl;

      return 0;
    }
  }

  Keyboard k;
  k.setMode(MODE_NORMAL);
  k.setColor(REGION_LEFT, COLOR_RED, INTENSITY_HIGH);
  k.setColor(REGION_MIDDLE, COLOR_PURPLE, INTENSITY_HIGH);
  k.setColor(REGION_RIGHT, COLOR_SKY, INTENSITY_HIGH);

  return 0;
  //return app.exec();
}

