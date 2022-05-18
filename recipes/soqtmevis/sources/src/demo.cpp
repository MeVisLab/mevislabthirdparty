/*
 * Copyright (C) 2006 MeVis.  All Rights Reserved.
 * License: LGPL 2.1
 */

// test program for the MeVis SoQt library
// which provides viewers for an OpenInventor scene

#include "DemoWindow.h"

#include <Inventor/Qt/SoQt.h>
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QApplication::setQuitOnLastWindowClosed(true);

    SoQt::init("demo");

    DemoWindow mainWin;
    mainWin.show();

    return app.exec();
}
