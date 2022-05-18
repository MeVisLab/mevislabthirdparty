/*
 *
 *  Copyright (C) 2000 Silicon Graphics, Inc.  All Rights Reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  Further, this software is distributed without any warranty that it is
 *  free of the rightful claim of any third person regarding infringement
 *  or the like.  Any license provided herein, whether implied or
 *  otherwise, applies only to this software file.  Patent licenses, if
 *  any, provided herein do not apply to combinations of this program with
 *  other software, or any other product whatsoever.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,
 *  Mountain View, CA  94043, or:
 *
 *  http://www.sgi.com
 *
 *  For further information regarding this notice, see:
 *
 *  http://oss.sgi.com/projects/GenInfo/NoticeExplan/
 *
 */

/*
 * Copyright (C) 1990,91   Silicon Graphics, Inc.
 * Author(s): Alain Dumesny
 * Ported to Qt4 by MeVis (http://www.mevis.de), 2006
 */

#include <cmath>
#include <cstdio>
#include <cstdlib>

#include <Inventor/SbTypeDefs.h>
#include <Inventor/SoPickedPoint.h>
#include <Inventor/Qt/viewers/SoQtFullViewer.h>
#include <Inventor/Qt/SoQtIcons.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/errors/SoDebugError.h>

#include <QAbstractButton>
#include <QAction>
#include <QActionGroup>
#include <QBoxLayout>
#include <QButtonGroup>
#include <QCheckBox>
#include <QDialog>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QMenu>
#include <QMessageBox>
#include <QPushButton>
#include <QRadioButton>
#include <QSettings>
#include <QSlider>
#include <QTabWidget>
#include <QToolBar>
#include <QMetaMethod>
#include <Inventor/Qt/SoQtThumbWheel.h>


static QAction* findAction (QActionGroup* actionGroup, const QVariant& data)
{
    QList<QAction*> actions = actionGroup->actions();
    for (int i=0;i<actions.count();i++) {
        QAction* action = actions[i];
        if (action != nullptr && action->data() == data) {
            return action;
        }
    }
    return nullptr;
}

static void checkAction (QActionGroup* actionGroup, const QVariant& data)
{
    QAction* action = findAction (actionGroup, data);
    if (action != nullptr) {
        action->setChecked (true);
    } else {
        action = actionGroup->checkedAction();
        if (action != nullptr) {
            action->setChecked (false);
        }
    }
}

static void addActionGroupToMenu (QActionGroup* group, QMenu* menu)
{
    QList<QAction*> actions = group->actions();
    for (int i=0;i<actions.count();i++) {
        QAction* action = actions[i];
        action->setCheckable (true);
        menu->addAction (action);
    }
}



SoQtFullViewer::SoQtFullViewer(BuildFlag flag, Type type, QWidget* parent, Qt::WindowFlags f)
: SoQtViewer (type, parent, f)
, helpClientCount (0)
, nestingFlag (false)
{
    // init decoration vars
    // (decorations really are created all the time, they just are hidden if this flag is not set)
    decorationFlag = (flag & BUILD_DECORATION) != 0;

    initWidgets();
    clipNearWheelValue = 0.0;
    clipFarWheelValue = 0.0;
    seekDistWheelValue = 0.0;
    stereoWheelValue = 0.0;
    rightWheelValue = 0.0;
    bottomWheelValue = 0.0;
    leftWheelValue = 0.0;

    // (fri 20061015) that doesn't seem necessary, but merely causes resize problems with MeVisLab
    //setMinGLSize(360, 360);  // default size

    // (the popup menu is created when it is shown for the first time)
    setPopupMenuEnabled ((flag & BUILD_POPUP) != 0);
    zoomSldRange.setValue(1, 140);
    rightWheelName  = tr("Motion Z");
    bottomWheelName = tr("Motion X");
    leftWheelName   = tr("Motion Y");

    popupMenuTitle  = tr("Viewer Menu");
    prefSheetTitle  = tr("Viewer Preference Sheet");

    connect (this, SIGNAL(customContextMenuRequested(const QPoint&)),
             this, SLOT(showContextMenu(const QPoint&)));
}


SoQtFullViewer::~SoQtFullViewer()
{
}


void
SoQtFullViewer::initWidgets()
{
    appButtonForm = nullptr;
    rightWheelLabel = nullptr;
    bottomWheelLabel = nullptr;
    leftWheelLabel = nullptr;
    drawStyleStillGroup = nullptr;
    drawStyleInteractiveGroup = nullptr;
    bufferStyleGroup = nullptr;
    prefSheetDialog = nullptr;
    prefSheetContainer = nullptr;
    seekTimeInput = nullptr;
    seekModeGroup = nullptr;
    seekDistInput = nullptr;
    seekDistModeGroup = nullptr;
    zoomPrefSheet = nullptr;
    zoomSlider = nullptr;
    zoomInput = nullptr;
    zoomFromInput = nullptr;
    zoomToInput = nullptr;
    autoClippingToggle = nullptr;
    clipPlanesWidgets = nullptr;
    clipNearInput = nullptr;
    clipFarInput = nullptr;
    stereoViewingToggle = nullptr;
    stereoDistWidgets = nullptr;
    stereoDistInput = nullptr;
    leftTrimForm = nullptr;
    bottomTrimForm = nullptr;
    rightTrimForm = nullptr;
    leftWheel = nullptr;
    bottomWheel = nullptr;
    rightWheel = nullptr;

    // pre-create actions
    pickAction =
        new QAction (SoQtIcons::getIcon (SoQtIcons::ICON_PICK), tr("Pick mode"), this);
    connect (pickAction, SIGNAL (triggered(bool)), this, SLOT (setPickMode()));
    pickAction->setCheckable (true);

    viewAction =
        new QAction (SoQtIcons::getIcon (SoQtIcons::ICON_VIEW), tr("View mode"), this);
    connect (viewAction, SIGNAL (triggered(bool)), this, SLOT (setViewMode()));
    viewAction->setCheckable (true);

    QActionGroup* interactionGroup = new QActionGroup(this);
    interactionGroup->addAction (pickAction);
    interactionGroup->addAction (viewAction);

    pickAction->setChecked (!isViewing());
    viewAction->setChecked (isViewing());

    helpAction =
        new QAction (SoQtIcons::getIcon (SoQtIcons::ICON_HELP), tr("Help"), this);
    connect (helpAction, SIGNAL (triggered(bool)), this, SIGNAL (showHelp()));
    helpAction->setVisible (helpClientCount > 0);

    // second help action without icon
    helpAction2 = new QAction (tr("Help"), this);
    connect (helpAction2, SIGNAL (triggered(bool)), this, SIGNAL (showHelp()));
    helpAction2->setVisible (helpClientCount > 0);

    seekAction =
        new QAction (SoQtIcons::getIcon (SoQtIcons::ICON_SEEK), tr("Seek mode"), this);
    connect (seekAction, SIGNAL (triggered(bool)), this, SLOT (toggleSeekMode()));
    seekAction->setCheckable (true);
    seekAction->setChecked (isSeekMode());

    gotoHomeAction =
        new QAction (SoQtIcons::getIcon (SoQtIcons::ICON_HOME), tr("Goto home position"), this);
    connect (gotoHomeAction, SIGNAL (triggered(bool)), this, SLOT (resetToHomePositionSlot()));

    setHomeAction =
        new QAction (SoQtIcons::getIcon (SoQtIcons::ICON_SET_HOME), tr("Set home position"), this);
    connect (setHomeAction, SIGNAL (triggered(bool)), this, SLOT (saveHomePositionSlot()));

    viewAllAction =
        new QAction (SoQtIcons::getIcon (SoQtIcons::ICON_VIEW_ALL), tr("View all"), this);
    connect (viewAllAction, SIGNAL (triggered(bool)), this, SLOT (viewAllSlot()));

    viewingAction = new QAction (tr("Viewing"), this);
    connect (viewingAction, SIGNAL (triggered(bool)), this, SLOT (toggleViewing()));
    viewingAction->setCheckable (true);
    viewingAction->setChecked (isViewing());

    decorationAction = new QAction (tr("Decoration"), this);
    connect (decorationAction, SIGNAL (triggered(bool)), this, SLOT (toggleDecoration()));
    decorationAction->setCheckable (true);
    decorationAction->setChecked (decorationFlag);

    headlightAction = new QAction (tr("Headlight"),  this);
    connect (headlightAction, SIGNAL (triggered(bool)), this, SLOT (toggleHeadlight()));
    headlightAction->setCheckable (true);
    headlightAction->setChecked (isHeadlight());

}


void
SoQtFullViewer::setViewing (SbBool flag)
{
    if (flag == viewingFlag) { return; }

    // call the base class
    SoQtViewer::setViewing(flag);

    // update the push buttons
    viewAction->setChecked (viewingFlag);
    pickAction->setChecked (!viewingFlag);

    // update the popup menu entry
    viewingAction->setChecked (viewingFlag);
}


void
SoQtFullViewer::setHeadlight (SbBool flag)
{
    if (flag == isHeadlight()) {
        return;
    }

    // call base class routine
    SoQtViewer::setHeadlight (flag);

    // update the popup menu entry
    headlightAction->setChecked (isHeadlight());
}


void
SoQtFullViewer::setDrawStyle (SoQtViewer::DrawType type,
                              SoQtViewer::DrawStyle style)
{
    // call base class routine
    SoQtViewer::setDrawStyle(type, style);

    // update the popup menu entries
    if (drawStyleStillGroup) {
        QAction* a =
            findAction (drawStyleStillGroup, getDrawStyle(SoQtViewer::STILL));
        a->setChecked (true);
        a = findAction (drawStyleInteractiveGroup, getDrawStyle(SoQtViewer::INTERACTIVE));
        a->setChecked (true);
    }
}


void
SoQtFullViewer::setBufferingType (SoQtViewer::BufferType type)
{
    // call base class routine
    SoQtViewer::setBufferingType(type);

    // update the popup menu entries
    if (bufferStyleGroup) {
        QAction* action =
            findAction (bufferStyleGroup, getBufferingType());
        if (action != nullptr) {
            action->setChecked (true);
        }
    }
}


void
SoQtFullViewer::setCamera (SoCamera *newCamera, SbBool createdCamera)
{
    // call base class routine
    SoQtViewer::setCamera(newCamera, createdCamera);

    // check if the zoom slider needs to be enabled
    if (zoomPrefSheet != nullptr) {

        SbBool enable = camera != nullptr &&
                        camera->isOfType (SoPerspectiveCamera::getClassTypeId());
        zoomPrefSheet->setEnabled (enable);

        // update the UI if enabled
        if (enable) {
            double zoom = getCameraZoom();
            setZoomSliderPosition (zoom);
        }
    }
}


void
SoQtFullViewer::setDecoration (SbBool flag)
{
    if (flag == decorationFlag) {
        return;
    }
    decorationFlag = flag;

    if (leftTrimForm) {
        leftTrimForm->setVisible (decorationFlag);
    }
    if (rightTrimForm) {
        rightTrimForm->setVisible (decorationFlag);
    }
    if (bottomTrimForm) {
        bottomTrimForm->setVisible (decorationFlag);
    }

    // update the popup menu entry
    decorationAction->setChecked (decorationFlag);
}


void
SoQtFullViewer::setPopupMenuEnabled (bool flag)
{
    setContextMenuPolicy (flag ? Qt::CustomContextMenu : Qt::NoContextMenu);
}

bool
SoQtFullViewer::isPopupMenuEnabled()
{
    return (contextMenuPolicy() != Qt::NoContextMenu);
}

void
SoQtFullViewer::showContextMenu (const QPoint& pos)
{
    if (popupMenu == nullptr) {
        popupMenu = createPopupMenu();
    }
    if (popupMenu != nullptr) {
        popupMenu->popup (mapToGlobal (pos));
    }
}

void
SoQtFullViewer::showPreferences()
{
    if (prefSheetDialog == nullptr) {
        createPrefSheet();
    }
    if (prefSheetDialog != nullptr) {
        prefSheetDialog->show();
    }
}


void
SoQtFullViewer::addAppButton (QAbstractButton* newButton)
{
    // add the button to the end of the list
    appButtonList.append (newButton);
    if (appButtonForm != nullptr) {
        appButtonForm->layout()->addWidget (newButton);
    }
}


void
SoQtFullViewer::setPopupMenuTitle (const QString& str)
{
    popupMenuTitle = str;
    if (popupMenu != nullptr) {
        popupMenu->setTitle (str);
    }
}


void
SoQtFullViewer::setPrefSheetTitle (const QString& str)
{
    prefSheetTitle = str;
    if (prefSheetDialog != nullptr) {
        prefSheetDialog->setWindowTitle (str);
    }
}


void
SoQtFullViewer::setBottomWheelTitle (const QString& str)
{
    bottomWheelName = str;
    if (bottomWheelLabel) {
        bottomWheelLabel->setText (str);
    }
}


void
SoQtFullViewer::setLeftWheelTitle (const QString& str)
{
    leftWheelName = str;
    if (leftWheelLabel) {
        leftWheelLabel->setText (str);
    }
}


void
SoQtFullViewer::setRightWheelTitle (const QString& str)
{
    rightWheelName = str;
    if (rightWheelLabel) {
        rightWheelLabel->setText (str);
    }
}


QMenu*
SoQtFullViewer::createPopupMenu()
{
    QMenu* menu = new QMenu (popupMenuTitle, this);
    menu->addMenu (createFunctionsSubmenu());
    menu->addMenu (createDrawStyleSubmenu());
    menu->addAction (viewingAction);
    menu->addAction (decorationAction);
    menu->addAction (headlightAction);
    menu->addAction (tr("Preferences..."), this, SLOT (showPreferences()));
    return menu;
}


QMenu*
SoQtFullViewer::createFunctionsSubmenu()
{
    QMenu* submenu = new QMenu (tr("Functions"));

    submenu->addAction (helpAction2);
    submenu->addAction (tr("Home"),     this, SLOT (resetToHomePositionSlot()));
    submenu->addAction (tr("Set Home"), this, SLOT (saveHomePositionSlot()));
    submenu->addAction (tr("View All"), this, SLOT (viewAllSlot()));
    submenu->addAction (tr("Seek"),     this, SLOT (toggleSeekMode()));
    return submenu;
}

QMenu*
SoQtFullViewer::createDrawStyleSubmenu()
{
    QMenu* submenu = new QMenu (tr("Draw Style"));

    drawStyleStillGroup       = new QActionGroup (this);
    drawStyleInteractiveGroup = new QActionGroup (this);
    bufferStyleGroup          = new QActionGroup (this);
    drawStyleStillGroup->setExclusive (true);
    drawStyleInteractiveGroup->setExclusive (true);
    bufferStyleGroup->setExclusive (true);
    connect (drawStyleStillGroup, SIGNAL (triggered(QAction*)),
             this, SLOT (drawStyleStillPicked(QAction*)));
    connect (drawStyleInteractiveGroup, SIGNAL (triggered(QAction*)),
             this, SLOT (drawStyleInteractivePicked(QAction*)));
    connect (bufferStyleGroup, SIGNAL (triggered(QAction*)),
             this, SLOT (bufferStylePicked(QAction*)));

    QActionGroup* group = drawStyleStillGroup;
    group->addAction (tr("as is"))->setData (VIEW_AS_IS);
    group->addAction (tr("hidden line"))->setData (VIEW_HIDDEN_LINE);
    group->addAction (tr("no texture"))->setData (VIEW_NO_TEXTURE);
    group->addAction (tr("low resolution"))->setData (VIEW_LOW_COMPLEXITY);
    group->addAction (tr("wireframe"))->setData (VIEW_LINE);
    group->addAction (tr("points"))->setData (VIEW_POINT);
    group->addAction (tr("bounding box (no depth)"))->setData (VIEW_BBOX);
    addActionGroupToMenu (group, submenu);
    submenu->addSeparator();

    group = drawStyleInteractiveGroup;
    group->addAction (tr("move same as still"))->setData (VIEW_SAME_AS_STILL);
    group->addAction (tr("move no texture"))->setData (VIEW_NO_TEXTURE);
    group->addAction (tr("move low res"))->setData (VIEW_LOW_COMPLEXITY);
    group->addAction (tr("move wireframe"))->setData (VIEW_LINE);
    group->addAction (tr("move low res wireframe (no depth)"))->setData (VIEW_LOW_RES_LINE);
    group->addAction (tr("move points"))->setData (VIEW_POINT);
    group->addAction (tr("move low res points (no depth)"))->setData (VIEW_LOW_RES_POINT);
    group->addAction (tr("move bounding box (no depth)"))->setData (VIEW_BBOX);
    addActionGroupToMenu (group, submenu);
    submenu->addSeparator();

    // create the second part of this sub menu
    group = bufferStyleGroup;
    group->addAction (tr("single buffer"))->setData (BUFFER_SINGLE);
    group->addAction (tr("double buffer"))->setData (BUFFER_DOUBLE);
    group->addAction (tr("interactive buffer"))->setData (BUFFER_INTERACTIVE);
    addActionGroupToMenu (group, submenu);

    checkAction (drawStyleStillGroup, getDrawStyle(SoQtViewer::STILL));
    checkAction (drawStyleInteractiveGroup, getDrawStyle(SoQtViewer::INTERACTIVE));
    checkAction (bufferStyleGroup, getBufferingType());

    return submenu;
}


void
SoQtFullViewer::loadSettings (const QSettings& settings)
{
    // Decoration
    decorationFlag =
        settings.value ("decoration", decorationFlag).toBool();

    // seek...
    setSeekTime (
        settings.value ("seekAnimationTime", getSeekTime()).toDouble());

    setDetailSeek (
        settings.value ("seekTo", isDetailSeek()).toBool());

    seekDistAsPercentage =
        settings.value ("seekDistanceUsage", seekDistAsPercentage).toBool();

    // zoom slider...
    zoomSldRange[0] =
        settings.value ("zoomMin", zoomSldRange[0]).toDouble();
    zoomSldRange[1] =
        settings.value ("zoomMax", zoomSldRange[1]).toDouble();

    setAutoClipping (
        settings.value ("autoClipping", isAutoClipping()).toBool());

    // manual clipping planes...
    //??? what if camera is NULL? should we save the values somewhere?
    if (camera != nullptr) {
        camera->nearDistance =
            settings.value ("nearDistance",
                (double) camera->nearDistance.getValue()).toDouble();
        camera->farDistance =
            settings.value ("farDistance",
                (double) camera->farDistance.getValue()).toDouble();
    }
}


void
SoQtFullViewer::saveSettings (QSettings& settings)
{
    // Decoration
    settings.setValue ("decoration", decorationFlag);

    // seek...
    settings.setValue ("seekAnimationTime", getSeekTime());

    settings.setValue ("seekTo", isDetailSeek());

    settings.setValue ("seekDistanceUsage", seekDistAsPercentage);

    // zoom slider...
    settings.setValue ("zoomMin", zoomSldRange[0]);
    settings.setValue ("zoomMax", zoomSldRange[1]);

    settings.setValue ("autoClipping", isAutoClipping());

    // manual clipping planes...
    //??? what if camera is NULL? should we save the values somewhere?
    if (camera != nullptr) {
        settings.setValue ("nearDistance",
            (double) camera->nearDistance.getValue());
        settings.setValue ("farDistance",
            (double) camera->farDistance.getValue());
    }
}

void
SoQtFullViewer::createAppButtons (QWidget* /*parent*/)
{
    for (int i=0;i<appButtonList.count();i++) {
        QWidget* appButton = appButtonList[i];
        appButtonForm->layout()->addWidget (appButton);
    }
}


QWidget*
SoQtFullViewer::createLeftBorder (QWidget* parent)
{
    leftTrimForm = new QWidget (parent);
    QVBoxLayout* box = new QVBoxLayout();
    box->setMargin(2);
    leftTrimForm->setLayout (box);
    appButtonForm = new QWidget (leftTrimForm);
    QVBoxLayout* appButtonLayout = new QVBoxLayout();
    appButtonLayout->setMargin (0);
    appButtonLayout->setSpacing (2);
    appButtonForm->setLayout (appButtonLayout);
    createAppButtons (appButtonForm);
    box->addWidget (appButtonForm, 1);
    leftWheel = new SoQtThumbWheel (Qt::Vertical, leftTrimForm);
    leftWheel->setValue (leftWheelValue);
    connect (leftWheel, SIGNAL (valueChanged(double)), this, SLOT (leftWheelMotion(double)));
    connect (leftWheel, SIGNAL (dragStart(double)),    this, SLOT (leftWheelStart()));
    connect (leftWheel, SIGNAL (dragStop(double)),     this, SLOT (leftWheelFinish()));
    leftWheel->setAngleFactor (-2.0*M_PI);
    box->addWidget (leftWheel);
    box->setAlignment (leftWheel, Qt::AlignBottom | Qt::AlignHCenter);
    return leftTrimForm;
}


QWidget*
SoQtFullViewer::createLowerBorder (QWidget* parent)
{
    bottomTrimForm = new QWidget (parent);
    QHBoxLayout* box = new QHBoxLayout();
    box->setMargin(2);
    bottomTrimForm->setLayout (box);
    leftWheelLabel = new QLabel (leftWheelName, bottomTrimForm);
    box->addWidget (leftWheelLabel);
    bottomWheelLabel = new QLabel (bottomWheelName, bottomTrimForm);
    box->addWidget (bottomWheelLabel);
    bottomWheel = new SoQtThumbWheel (Qt::Horizontal, bottomTrimForm);
    bottomWheel->setValue (bottomWheelValue);
    connect (bottomWheel, SIGNAL (valueChanged(double)), this, SLOT (bottomWheelMotion(double)));
    connect (bottomWheel, SIGNAL (dragStart(double)),    this, SLOT (bottomWheelStart()));
    connect (bottomWheel, SIGNAL (dragStop(double)),     this, SLOT (bottomWheelFinish()));
    bottomWheel->setAngleFactor (2.0*M_PI);
    box->addWidget (bottomWheel);
    box->addStretch (1);
    rightWheelLabel = new QLabel (rightWheelName, bottomTrimForm);
    box->addWidget (rightWheelLabel);
    box->setAlignment (rightWheelLabel, Qt::AlignRight);
    return bottomTrimForm;
}


QWidget*
SoQtFullViewer::createRightBorder (QWidget* parent)
{
    rightTrimForm = new QWidget (parent);
    QVBoxLayout* box = new QVBoxLayout();
    box->setMargin(2);
    rightTrimForm->setLayout (box);
    viewerButtonBar = new QToolBar (rightTrimForm);
    viewerButtonBar->setOrientation (Qt::Vertical);
#if defined(MACOS)
    viewerButtonBar->setIconSize(QSize(26,26));
#endif
    createViewerButtons (viewerButtonBar);
    box->addWidget (viewerButtonBar, 1);
    rightWheel = new SoQtThumbWheel (Qt::Vertical, rightTrimForm);
    rightWheel->setValue (rightWheelValue);
    connect (rightWheel, SIGNAL (valueChanged(double)), this, SLOT (rightWheelMotion(double)));
    connect (rightWheel, SIGNAL (dragStart(double)),    this, SLOT (rightWheelStart()));
    connect (rightWheel, SIGNAL (dragStop(double)),     this, SLOT (rightWheelFinish()));
    rightWheel->setAngleFactor (-2.0*M_PI);
    box->addWidget (rightWheel);
    box->setAlignment (rightWheel, Qt::AlignBottom | Qt::AlignHCenter);
    return rightTrimForm;
}


void
SoQtFullViewer::createViewerButtons (QToolBar* parent)
{
    parent->addAction (pickAction);
    parent->addAction (viewAction);
    parent->addAction (helpAction);
    parent->addAction (gotoHomeAction);
    parent->addAction (setHomeAction);
    parent->addAction (viewAllAction);
    parent->addAction (seekAction);
}


QTabWidget*
SoQtFullViewer::createPrefSheet()
{
    prefSheetDialog = new QDialog (this);
    prefSheetDialog->setWindowTitle (prefSheetTitle);
    prefSheetDialog->setLayout (new QVBoxLayout());
    QTabWidget* tab = new QTabWidget ();
    tab->addTab (createSeekPrefSheetGuts(),     tr("Seek"));
    tab->addTab (createSeekDistPrefSheetGuts(), tr("Seek Distance"));
    tab->addTab (createZoomPrefSheetGuts(),     tr("Zoom"));
    tab->addTab (createClippingPrefSheetGuts(), tr("Clipping"));
    tab->addTab (createStereoPrefSheetGuts(),   tr("Stereo"));
    prefSheetDialog->layout()->addWidget (tab);
    prefSheetContainer = tab;
    return tab;
}

QWidget*
SoQtFullViewer::createSeekPrefSheetGuts ()
{
    QWidget* sheet = new QWidget();
    QGridLayout* grid = new QGridLayout();
    sheet->setLayout (grid);

    grid->addWidget (new QLabel (tr("Seek animation time:")), 0, 0);
    seekTimeInput = new QDoubleSpinBox();
    seekTimeInput->setRange (0.0, 60.0);
    seekTimeInput->setValue (getSeekTime());
    connect (seekTimeInput, SIGNAL (valueChanged(double)), this, SLOT (setSeekTime(double)));
    //-> SoQtFullViewer::seekPrefSheetFieldCB
    grid->addWidget (seekTimeInput, 0, 1);
    grid->addWidget (new QLabel (tr("seconds")), 0, 2);

    grid->addWidget (new QLabel (tr("Seek to:")), 1, 0);
    QAbstractButton* seekPointsButton = new QRadioButton (tr("point"));
    grid->addWidget (seekPointsButton, 1, 1);
    QAbstractButton* seekObjectsButton = new QRadioButton (tr("object"));
    grid->addWidget (seekObjectsButton, 1, 2);
    // make buttons mutually exclusive:
    QButtonGroup* group = new QButtonGroup (sheet);
    group->addButton (seekPointsButton, 1);
    group->addButton (seekObjectsButton, 0);
    group->button ((int) isDetailSeek())->setChecked (true);
    connect (group, SIGNAL (buttonClicked(int)), this, SLOT (setSeekDetailMode(int)));
    seekModeGroup = group;
    //-> SoQtFullViewer::seekPrefSheetToggle1CB
    //-> SoQtFullViewer::seekPrefSheetToggle2CB

    return sheet;
}


QWidget*
SoQtFullViewer::createSeekDistPrefSheetGuts ()
{
    QWidget* sheet = new QWidget();
    QGridLayout* grid = new QGridLayout();
    sheet->setLayout (grid);

    grid->addWidget (new QLabel (tr("Seek distance:")), 0, 0);
    SoQtThumbWheel* seekDistWheel = new SoQtThumbWheel (Qt::Horizontal);
    seekDistWheel->setValue (seekDistance);
    connect (seekDistWheel, SIGNAL (valueChanged(double)), this, SLOT (setSeekDistWheelValue(double)));
    //-> SoQtFullViewer::seekDistWheelCB
    grid->addWidget (seekDistWheel, 0, 1);
    seekDistInput = new QDoubleSpinBox();
    seekDistInput->setRange (0.0, 1000.0);
    seekDistInput->setValue (seekDistance);
    connect (seekDistInput, SIGNAL (valueChanged(double)), this, SLOT (setSeekDistance(double)));
    //-> SoQtFullViewer::seekDistInputCB
    grid->addWidget (seekDistInput, 0, 2);

    // create the second line
    QAbstractButton* seekDistPercButton = new QRadioButton (tr("percentage"));
    grid->addWidget (seekDistPercButton, 1, 1);
    QAbstractButton* seekDistAbsButton = new QRadioButton (tr("absolute"));
    grid->addWidget (seekDistAbsButton, 1, 2);

    // make buttons mutually exclusive:
    QButtonGroup* group = new QButtonGroup (sheet);
    group->addButton (seekDistPercButton, 1);
    group->addButton (seekDistAbsButton, 0);
    group->button ((int) seekDistAsPercentage)->setChecked (true);
    connect (group, SIGNAL (buttonClicked(int)), this, SLOT (setSeekDistMode(int)));
    seekDistModeGroup = group;
    //-> SoQtFullViewer::seekDistPercPrefSheetToggleCB
    //-> SoQtFullViewer::seekDistAbsPrefSheetToggleCB

    return sheet;
}


QWidget*
SoQtFullViewer::createZoomPrefSheetGuts ()
{
    QWidget* zoomPrefSheet = new QWidget();
    QGridLayout* grid = new QGridLayout();
    zoomPrefSheet->setLayout (grid);

    grid->addWidget (new QLabel (tr("Camera Zoom:")), 0, 0);
    zoomSlider = new QSlider (Qt::Horizontal);
    zoomSlider->setRange (0, 1000);
    setZoomSliderPosition (getCameraZoom());
    connect (zoomSlider, SIGNAL (valueChanged (int)), this, SLOT (setZoomSliderValue(int)));
    //-> SoQtFullViewer::zoomSliderCB
    grid->addWidget (zoomSlider, 0, 1);
    zoomInput = new QDoubleSpinBox();
    zoomInput->setRange (0, 1000);
    zoomInput->setValue (getCameraZoom());
    connect (zoomInput, SIGNAL (valueChanged(double)), this, SLOT (setZoomValue(double)));
    //-> SoQtFullViewer::zoomFieldCB
    grid->addWidget (zoomInput, 0,2);

    grid->addWidget (new QLabel (tr("Zoom slider ranges from:")), 1, 0);

    QHBoxLayout* box = new QHBoxLayout();

    zoomFromInput = new QDoubleSpinBox();
    zoomFromInput->setDecimals (1);
    zoomFromInput->setRange (0.0, 180.0);
    zoomFromInput->setValue (zoomSldRange[0]);
    connect (zoomFromInput, SIGNAL (valueChanged(double)), this, SLOT (setZoomMinValue(double)));
    //-> SoQtFullViewer::zoomPrefSheetMinFieldCB
    box->addWidget (zoomFromInput, 1);

    box->addWidget (new QLabel (tr("to:")));

    zoomToInput = new QDoubleSpinBox();
    zoomToInput->setDecimals (1);
    zoomToInput->setRange (0.0, 180.0);
    zoomToInput->setValue (zoomSldRange[1]);
    connect (zoomToInput, SIGNAL (valueChanged(double)), this, SLOT (setZoomMaxValue(double)));
    box->addWidget (zoomToInput, 1);

    grid->addLayout (box, 1, 1, 1, 2);

    bool enabled = (camera != nullptr && camera->isOfType(SoPerspectiveCamera::getClassTypeId()));
    zoomPrefSheet->setEnabled (enabled);

    return zoomPrefSheet;
}


QWidget*
SoQtFullViewer::createClippingPrefSheetGuts()
{
    QWidget* sheet = new QWidget();
    QBoxLayout* box = new QVBoxLayout();
    sheet->setLayout (box);

    autoClippingToggle = new QCheckBox(tr("Auto clipping planes"));
    autoClippingToggle->setEnabled (camera != nullptr);
    autoClippingToggle->setCheckState (isAutoClipping() ? Qt::Checked : Qt::Unchecked);
    connect (autoClippingToggle, SIGNAL (stateChanged(int)), this, SLOT (setAutoClippingState(int)));
    //-> SoQtFullViewer::clipPrefSheetToggleCB
    box->addWidget (autoClippingToggle);

    clipPlanesWidgets = new QWidget();
    QGridLayout* grid = new QGridLayout();
    clipPlanesWidgets->setLayout (grid);

    grid->addWidget (new QLabel (tr("near plane:")), 0, 0);

    double value = (camera != nullptr) ? camera->nearDistance.getValue() : 0.0;
    SoQtThumbWheel* clipNearWheel = new SoQtThumbWheel (Qt::Horizontal);
    connect (clipNearWheel, SIGNAL (valueChanged(double)), this, SLOT (setClipNearWheelValue(double)));
    //-> SoQtFullViewer::clipNearWheelCB
    grid->addWidget (clipNearWheel, 0, 1);

    clipNearInput = new QDoubleSpinBox();
    // clipNearInput>setDecimals (5);
    clipNearInput->setRange (0.0, 1000.0);
    clipNearInput->setValue (value);
    connect (clipNearInput, SIGNAL (valueChanged(double)), this, SLOT (setClipNearValue(double)));
    //-> SoQtFullViewer::clipFieldCB
    grid->addWidget (clipNearInput, 0, 2);

    grid->addWidget (new QLabel (tr("far plane:")), 1, 0);

    value = (camera != nullptr) ? camera->farDistance.getValue() : 0.0;
    SoQtThumbWheel* clipFarWheel = new SoQtThumbWheel (Qt::Horizontal);
    connect (clipFarWheel, SIGNAL (valueChanged(double)), this, SLOT (setClipFarWheelValue(double)));
    //-> SoQtFullViewer::clipFarWheelCB
    grid->addWidget (clipFarWheel, 1, 1);

    clipFarInput = new QDoubleSpinBox();
    // clipFarInput>setDecimals (5);
    clipFarInput->setRange (0.0, 1000.0);
    clipFarInput->setValue (value);
    connect (clipFarInput, SIGNAL (valueChanged(double)), this, SLOT (setClipFarValue(double)));
    //-> SoQtFullViewer::clipFieldCB
    grid->addWidget (clipFarInput, 1, 2);

    box->addWidget (clipPlanesWidgets);
    clipPlanesWidgets->setEnabled (!isAutoClipping());

    return sheet;
}



QWidget*
SoQtFullViewer::createStereoPrefSheetGuts()
{
    QWidget* sheet = new QWidget();
    QBoxLayout* box = new QVBoxLayout();
    sheet->setLayout (box);

    stereoViewingToggle = new QCheckBox(tr("Stereo Viewing"));
    stereoViewingToggle->setCheckState (isStereoViewing() ? Qt::Checked : Qt::Unchecked);
    connect (stereoViewingToggle, SIGNAL (stateChanged(int)), this, SLOT (setStereoViewingValue(int)));
    //-> SoQtFullViewer::stereoPrefSheetToggleCB
    box->addWidget (stereoViewingToggle);

    stereoDistWidgets = new QWidget (sheet);
    QBoxLayout* distBox = new QHBoxLayout();
    stereoDistWidgets->setLayout (distBox);
    distBox->addWidget (new QLabel (tr("camera rotation:")));
    SoQtThumbWheel* stereoDistWheel = new SoQtThumbWheel (Qt::Horizontal);
    connect (stereoDistWheel, SIGNAL (valueChanged(double)), this, SLOT (setStereoWheelValue(double)));
    //-> SoQtFullViewer::stereoWheelCB
    distBox->addWidget (stereoDistWheel);
    stereoDistInput = new QDoubleSpinBox();
    stereoDistInput->setDecimals (4);
    stereoDistInput->setRange (-100.0, 100.0);
    stereoDistInput->setValue (getStereoOffset());
    connect (stereoDistInput, SIGNAL (valueChanged(double)), this, SLOT (setStereoDistance(double)));
    //-> SoQtFullViewer::stereoFieldCB
    distBox->addWidget (stereoDistInput);
    stereoDistWidgets->setEnabled (isStereoViewing());
    box->addWidget (stereoDistWidgets, 1, Qt::AlignVCenter);

    return sheet;
}


QWidget*
SoQtFullViewer::createSpeedPrefSheetGuts()
{
    QWidget* sheet = new QWidget();
    QBoxLayout* box = new QVBoxLayout();
    sheet->setLayout (box);

    box->addWidget (new QLabel (tr("Viewer Speed:")));

    QPushButton* incSpeedButton = new QPushButton (tr("increase"));
    connect (incSpeedButton, SIGNAL (clicked(bool)), this, SLOT (increaseSpeed()));
    //-> SoQtFullViewer::speedIncPrefSheetButtonCB
    box->addWidget (incSpeedButton);

    QPushButton* decSpeedButton = new QPushButton (tr("decrease"));
    connect (decSpeedButton, SIGNAL (clicked(bool)), this, SLOT (decreaseSpeed()));
    //-> SoQtFullViewer::speedDecPrefSheetButtonCB
    box->addWidget (decSpeedButton);

    return sheet;
}

void
SoQtFullViewer::setSeekMode (SbBool onOrOff)
{
    SoQtViewer::setSeekMode (onOrOff);
    seekAction->setChecked (isSeekMode());
}

void
SoQtFullViewer::setDetailSeek(SbBool onOrOff)
{
    SoQtViewer::setDetailSeek (onOrOff);
    if (seekDistModeGroup) {
        seekDistModeGroup->button ((int) seekDistAsPercentage)->setChecked (true);
    }
}


void
SoQtFullViewer::setCameraZoom (double zoom)
{
    if (camera == nullptr) {
        return;
    } else if ( camera->isOfType (SoPerspectiveCamera::getClassTypeId()) ) {
        ((SoPerspectiveCamera *)camera)->heightAngle = zoom * M_PI / 180.0;
    } else if ( camera->isOfType (SoOrthographicCamera::getClassTypeId()) ) {
        ((SoOrthographicCamera *)camera)->height = zoom;
#if DEBUG
    } else {
        SoDebugError::post ("SoQtFullViewer::setCameraZoom",
                "unknown camera type");
#endif
    }
}


double
SoQtFullViewer::getCameraZoom()
{
    if (camera == nullptr) {
        return 0.0;
    } else if ( camera->isOfType (SoPerspectiveCamera::getClassTypeId()) ) {
        return ((SoPerspectiveCamera *)camera)->heightAngle.getValue() * 180.0 / M_PI;
    } else if ( camera->isOfType (SoOrthographicCamera::getClassTypeId()) ) {
        return ((SoOrthographicCamera *)camera)->height.getValue();
    } else {
#if DEBUG
        SoDebugError::post("SoQtFullViewer::getCameraZoom",
                            "unknown camera type");
#endif
        return 0.0;
    }
}


void
SoQtFullViewer::setZoomSliderPosition (double zoom)
{
    if (zoomSlider != nullptr) {
        // find the slider position, using a square root distance to make the
        // slider smoother and less sensitive when close to zero.
        double f = (zoom - zoomSldRange[0]) / (zoomSldRange[1] - zoomSldRange[0]);
        f = (f < 0.0) ? 0.0 : ((f > 1.0) ? 1.0 : f);
        f = sqrt (f);
        // finally position the slider
        zoomSlider->setValue (int (f * 1000));
    }
    if (zoomInput != nullptr) {
        zoomInput->setValue (zoom);
    }
}

void
SoQtFullViewer::setZoomValue (double zoom)
{
    if (nestingFlag) { return; }
    nestingFlag = true;
    if (zoom > 0.0) {
        // check for valid perspective camera range
        if ( camera != nullptr &&
            camera->isOfType(SoPerspectiveCamera::getClassTypeId()) ) {
            zoom = (zoom < 0.01) ? 0.01 : ((zoom > 179.99) ? 179.99 : zoom);
        }

        // check if the new value changed the slider range
        if (zoom < zoomSldRange[0]) {
            zoomSldRange[0] = zoom;
        } else if (zoom > zoomSldRange[1]) {
            zoomSldRange[1] = zoom;
        }
        setCameraZoom (zoom);
    } else {
        zoom = getCameraZoom();
    }

    setZoomSliderPosition (zoom);
    nestingFlag = false;
}

void
SoQtFullViewer::setZoomSliderValue (int value)
{
    // get the slider zoom value, taking the square value since we
    // are using the square root to make the slider smoother to use.
    double f = int(value) / 1000.0;
    f *= f;
    setZoomValue (zoomSldRange[0] + f * (zoomSldRange[1] - zoomSldRange[0]));
}


//
// Virtual thumb wheels methods which subclasses can redefine
//
void SoQtFullViewer::rightWheelStart()      { interactiveCountInc(); }
void SoQtFullViewer::bottomWheelStart()     { interactiveCountInc(); }
void SoQtFullViewer::leftWheelStart()       { interactiveCountInc(); }
void SoQtFullViewer::rightWheelFinish()     { interactiveCountDec(); }
void SoQtFullViewer::bottomWheelFinish()    { interactiveCountDec(); }
void SoQtFullViewer::leftWheelFinish()      { interactiveCountDec(); }

void SoQtFullViewer::rightWheelMotion(double v)    { rightWheelValue  = v; }
void SoQtFullViewer::bottomWheelMotion(double v)   { bottomWheelValue = v; }
void SoQtFullViewer::leftWheelMotion(double v)     { leftWheelValue   = v; }

void SoQtFullViewer::setLeftWheelValue (double v)
{
    leftWheelValue = v;
    if (leftWheel) {
        leftWheel->setValue (v);
    }
}

void SoQtFullViewer::setRightWheelValue (double v)
{
    rightWheelValue = v;
    if (rightWheel) {
        rightWheel->setValue (v);
    }
}

void SoQtFullViewer::setBottomWheelValue (double v)
{
    bottomWheelValue = v;
    if (bottomWheel) {
        bottomWheel->setValue (v);
    }
}

void
SoQtFullViewer::drawStyleStillPicked (QAction* action)
{
    if (action == nullptr) { return; }
    int mode = action->data().toInt();
    setDrawStyle(SoQtViewer::STILL, (SoQtViewer::DrawStyle)mode);
}

void
SoQtFullViewer::drawStyleInteractivePicked (QAction* action)
{
    if (action == nullptr) { return; }
    int mode = action->data().toInt();
    setDrawStyle(SoQtViewer::INTERACTIVE, (SoQtViewer::DrawStyle)mode);
}


void
SoQtFullViewer::bufferStylePicked (QAction* action)
{
    if (action == nullptr) { return; }
    int mode = action->data().toInt();
    setBufferingType ((SoQtViewer::BufferType)mode);
}


void
SoQtFullViewer::setAutoClippingState (int state)
{
    SoQtViewer::setAutoClipping (state == Qt::Checked);
    clipPlanesWidgets->setEnabled (!isAutoClipping());
}



void
SoQtFullViewer::setClipNearWheelValue (double value)
{
    if (camera == nullptr) { return; }

    // shorter/grow the near plane distance given the wheel rotation
    double dist = camera->nearDistance.getValue();
    dist *= pow (80.0, (value - clipNearWheelValue) / 360.0);
    clipNearWheelValue = value;

    setClipNearValue (dist);
}

void
SoQtFullViewer::setClipFarWheelValue (double value)
{
    if (camera == nullptr) { return; }

    // shorter/grow the near plane distance given the wheel rotation
    double dist = camera->farDistance.getValue();
    dist *= pow (80.0, (value - clipFarWheelValue) / 360.0);
    clipFarWheelValue = value;

    setClipFarValue (dist);
}

void
SoQtFullViewer::setClipNearValue (double value)
{
    if (camera == nullptr) { return; }
    if (nestingFlag) { return; }
    nestingFlag = true;

    if (value > 0.0 || camera->isOfType(SoOrthographicCamera::getClassTypeId())) {
        camera->nearDistance = value;
    }
    if (clipNearInput != nullptr) {
        clipNearInput->setValue (value);
    }
    nestingFlag = false;
}

void
SoQtFullViewer::setClipFarValue (double value)
{
    if (camera == nullptr) { return; }
    if (nestingFlag) { return; }
    nestingFlag = true;

    if (value > 0.0 || camera->isOfType(SoOrthographicCamera::getClassTypeId())) {
        camera->farDistance = value;
    }
    if (clipFarInput != nullptr) {
        clipFarInput->setValue (value);
    }
    nestingFlag = false;
}

void
SoQtFullViewer::setStereoViewingValue (int state)
{
    // checks to make sure stereo viewing can be set, else
    // grey the UI and bring and error message.
    SbBool toggleState = (state == Qt::Checked);
    if (toggleState != isStereoViewing()) {
        SoQtViewer::setStereoViewing (toggleState);
    }
    if (toggleState && !isStereoViewing()) {
        // we couldn't activate stereo viewing:
        stereoViewingToggle->setCheckState (Qt::Unchecked);
        stereoViewingToggle->setEnabled (false);
        QMessageBox::critical (stereoViewingToggle, tr("Stereo Error"),
                               tr("Stereo Viewing can't be set on this machine."));
        return;
    }

    // show/hide the eye spacing thumbwheel
    stereoDistWidgets->setEnabled (isStereoViewing());
}

void
SoQtFullViewer::setStereoWheelValue (double value)
{
    // shorter/grow the stereo camera offset
    setStereoDistance (getStereoOffset() * pow (80.0, value - stereoWheelValue) / 360.0);
    stereoWheelValue = value;
}

void
SoQtFullViewer::setStereoDistance (double value)
{
    // get text value from the label and update camera
    setStereoOffset(value);
    scheduleRedraw();
    if (stereoDistInput != nullptr) {
        stereoDistInput->setValue (value);
    }
}

void
SoQtFullViewer::setSeekDistWheelValue (double value)
{
    // shorter/grow the seek distance given the wheel rotation
    setSeekDistance (seekDistance *
                     pow (80.0, (value - seekDistWheelValue) / 360.0));
    seekDistWheelValue = value;
}

void
SoQtFullViewer::setSeekDistance (double value)
{
    seekDistance = value;
    if (seekDistInput != nullptr && !nestingFlag) {
        nestingFlag = true;
        seekDistInput->setValue (value);
        nestingFlag = false;
    }
}

void
SoQtFullViewer::setSeekTime (double value)
{
    SoQtViewer::setSeekTime (value);
    if (seekTimeInput != nullptr && !nestingFlag) {
        nestingFlag = true;
        seekTimeInput->setValue (value);
        nestingFlag = false;
    }
}

void
SoQtFullViewer::setZoomMinValue (double value)
{
    // check for valid perspective camera range
    if (camera != nullptr &&
        camera->isOfType(SoPerspectiveCamera::getClassTypeId())) {
        value = (value < 0.01) ? 0.01 : ((value > 178.99) ? 178.99 : value);

        // finally update the slider to reflect the changes
        zoomSldRange[0] = value;
        setZoomSliderPosition (getCameraZoom());
    }
}

void
SoQtFullViewer::setZoomMaxValue (double value)
{
    // check for valid perspective camera range
    if (camera != nullptr &&
        camera->isOfType(SoPerspectiveCamera::getClassTypeId())) {
        value = (value < 0.01) ? 0.01 : ((value > 178.99) ? 178.99 : value);

        // finally update the slider to reflect the changes
        zoomSldRange[1] = value;
        setZoomSliderPosition (getCameraZoom());
    }
}

void
SoQtFullViewer::hideEvent (QHideEvent* event)
{
    SoQtViewer::hideEvent (event);

    if (prefSheetDialog) {
        prefSheetDialog->hide();
    }
}

void SoQtFullViewer::connectNotify (const QMetaMethod& signal)
{
    if (signal == QMetaMethod::fromSignal(&SoQtFullViewer::showHelp)) {
        helpClientCount++;
        if (helpClientCount == 1) {
            helpAction->setVisible (true);
            helpAction2->setVisible (true);
        }
    }
    SoQtViewer::connectNotify (signal);
}

void SoQtFullViewer::disconnectNotify (const QMetaMethod& signal)
{
    if (signal == QMetaMethod::fromSignal(&SoQtFullViewer::showHelp)) {
        helpClientCount--;
        if (helpClientCount == 0) {
            helpAction->setVisible (false);
            helpAction2->setVisible (false);
        }
    }
    SoQtViewer::disconnectNotify (signal);
}

