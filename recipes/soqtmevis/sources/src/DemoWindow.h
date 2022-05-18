/*
 * Copyright (C) 2006 MeVis.  All Rights Reserved.
 * License: LGPL 2.1
 */

#include <QMainWindow>

class QMenu;
class SoNode;
class SoQtViewer;

class DemoWindow : public QMainWindow
{
    Q_OBJECT

public:
    DemoWindow();

protected:
    void closeEvent(QCloseEvent* event);

    SoNode* createDemoScene();

private:
    void createActions();
    void createMenus();

private:
    SoQtViewer* m_viewer = nullptr;
    QAction *m_exitAction = nullptr;
    QAction *m_aboutAction = nullptr;
    QAction *m_aboutQtAction = nullptr;
};

