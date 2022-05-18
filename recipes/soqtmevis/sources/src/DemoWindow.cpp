/*
 * Copyright (C) 2006 MeVis.  All Rights Reserved.
 * License: LGPL 2.1
 */

#include "DemoWindow.h"

#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/Qt/SoQtIcons.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/manips/SoTransformManip.h>

#include <QApplication>
#include <QCloseEvent>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QAction>
#include <QDebug>

DemoWindow::DemoWindow()
{
    m_viewer = new SoQtExaminerViewer (SoQtFullViewer::BUILD_ALL, SoQtViewer::BROWSER, this);
    m_viewer->setGLCursor (SoQtIcons::getCursor (SoQtIcons::CURSOR_VIEWING));
    m_viewer->setColorBitDepth (10);
    m_viewer->buildWidget();

    setCentralWidget(m_viewer);

    m_viewer->setSceneGraph (createDemoScene());
    m_viewer->viewAll();

    createActions();
    createMenus();
}

void DemoWindow::closeEvent (QCloseEvent* event)
{
    int colorDepth = m_viewer->getColorBitDepth();
    qDebug() << "The viewer had color depth: " << colorDepth;
    event->accept(); // always accept close
}

SoNode* DemoWindow::createDemoScene()
{
    SoSeparator* scene = new SoSeparator();
    scene->ref();
    SoTransformManip* manip = new SoTransformManip();
    scene->addChild (manip);
    //scene->addChild (new SoCube());
    scene->addChild (new SoCone());
    //scene->addChild (new SoSphere());

    return scene;
}

void DemoWindow::createActions()
{
    m_exitAction = new QAction(tr("Quit"), this);
    m_exitAction->setStatusTip(tr("Exit this application"));
    connect(m_exitAction, &QAction::triggered, qApp, &QApplication::quit);

    m_aboutAction = new QAction(tr("About"), this);
    m_aboutAction->setStatusTip(tr("Show the sample About box"));
    connect(m_aboutAction, &QAction::triggered, [this]() {
        QMessageBox::about(this, tr("About Application"),
                tr("The <b>Application</b> example demonstrates how to "
                   "write modern GUI applications using Qt."));
    });

    m_aboutQtAction = new QAction(tr("About &Qt"), this);
    m_aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
    connect(m_aboutAction, &QAction::triggered, qApp, &QApplication::aboutQt);
}

void DemoWindow::createMenus()
{
    auto fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(m_exitAction);

    menuBar()->addSeparator();

    auto helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(m_aboutAction);
    helpMenu->addAction(m_aboutQtAction);
}



