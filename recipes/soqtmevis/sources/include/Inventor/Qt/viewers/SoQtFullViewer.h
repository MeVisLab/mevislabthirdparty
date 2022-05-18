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
 * Copyright (C) 1990-93   Silicon Graphics, Inc.
 * Author(s): Alain Dumesny
 * Ported to Qt4 by MeVis (http://www.mevis.de), 2006
 */

#ifndef  _SO_QT_FULL_VIEWER_
#define  _SO_QT_FULL_VIEWER_

#include <Inventor/Qt/SoQtDLLInit.h>
#include <Inventor/Qt/viewers/SoQtViewer.h>
#include <Inventor/SbPList.h>

#include <QPointer>
#include <QList>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoQtFullViewer
//
//  The SoQtFullViewer component class is the abstract base class for all
//  viewers which include a decoration around the rendering area. The
//  decoration is made of thumbwheels, sliders and push/toggle buttons. There
//  is also a popup menu which includes all of the viewing options and methods.
//
//////////////////////////////////////////////////////////////////////////////

class QAbstractButton;
class QAction;
class QActionGroup;
class QButtonGroup;
class QCheckBox;
class QDoubleSpinBox;
class QLabel;
class QMenu;
class QSettings;
class QSlider;
class QTabWidget;
class QToolBar;
class SoQtThumbWheel;

class SOQT_MEVIS_EXPORT SoQtFullViewer : public SoQtViewer
{
    Q_OBJECT

public:
    //! This specifies what should be build by default in the constructor
    enum BuildFlag {
    BUILD_NONE          = 0x00,
    BUILD_DECORATION    = 0x01,
    BUILD_POPUP         = 0x02,
    BUILD_ALL           = 0xff
    };

    //! Constructor/Destructor
    SoQtFullViewer (BuildFlag flag, Type type = BROWSER, QWidget* parent = nullptr, Qt::WindowFlags f = nullptr);

    //! Show/hide the viewer component trims (default ON)
    void            setDecoration(SbBool onOrOff);
    SbBool          isDecoration()      { return decorationFlag; }

    //! Enable/disable the popup menu (default enabled)
    void            setPopupMenuEnabled (bool enable);
    bool            isPopupMenuEnabled();

    //! Add/remove push buttons for the application, which will be placed
    //! in the left hand side decoration trim.
    //! The add() method appends the button to the end of the list.
    void            addAppButton     (QAbstractButton* newButton);
    int             findAppButton    (QAbstractButton* oldButton)
                        { return appButtonList.indexOf (oldButton); }
    int             lengthAppButton()
                        { return appButtonList.count(); }

    // redefine these from the base class
    void    setCamera (SoCamera *cam, SbBool createdCamera) override;

    void loadSettings (const QSettings& settings);
    void saveSettings (QSettings& settings);


public slots:
    // redefine these from the base class, so we can keep our controls up-to-date
    void    setViewing(SbBool onOrOff) override;
    void    setHeadlight(SbBool onOrOff) override;
    void    setDrawStyle(SoQtViewer::DrawType type,
                        SoQtViewer::DrawStyle style) override;
    void    setBufferingType(SoQtViewer::BufferType type) override;

    //! change seek distance
    virtual void    setSeekDistance (double value);

    void    setDetailSeek(SbBool onOrOff) override;

    //! change seek time
    virtual void setSeekTime (double value);

    //! set zoom
    virtual void setZoomValue (double zoom);

    virtual void setCameraZoom (double zoom);
    double getCameraZoom();

    void showPreferences();

    //@{ access current decoration wheel position
    double getLeftWheelValue() const { return leftWheelValue; }
    double getRightWheelValue() const { return rightWheelValue; }
    double getBottomWheelValue() const { return bottomWheelValue; }
    //@}

    //@{ update decoration wheel position (without calling wheelMotion methods)
    void setLeftWheelValue (double v);
    void setRightWheelValue (double v);
    void setBottomWheelValue (double v);
    //@}

signals:
    // Subclasses SHOULD connect to showHelp() to show some kind of
    // help (called by push button and popup menu entry, only visible
    // if at least one slot was connected).
    void showHelp();

protected slots:
    //@{ these slots react to controls
    void toggleSeekMode()   { setSeekMode   (!isSeekMode()); }
    void toggleHeadlight()  { setHeadlight  (!isHeadlight()); }
    void toggleViewing()    { setViewing    (!isViewing()); }
    void toggleDecoration() { setDecoration (!decorationFlag); }
    void setSeekDetailMode (int mode) { setDetailSeek (mode != 0); }
    void setPickMode()      { setViewing    (false); }
    void setViewMode()      { setViewing    (true); }
    void increaseSpeed()    { viewerSpeed *= 2.0; }
    void decreaseSpeed()    { viewerSpeed /= 2.0; }
    void drawStyleStillPicked (QAction* action);
    void drawStyleInteractivePicked (QAction* action);
    void bufferStylePicked (QAction* action);
    //@}

    //! show context menu at requested local position - menu gets created
    //! when called for the first time
    void showContextMenu (const QPoint& pos);

protected:
    //! Destructor
    ~SoQtFullViewer() override;

    void    setSeekMode(SbBool onOrOff) override;

    //@{ access to thumb wheels for derived classes
    SoQtThumbWheel* getRightWheel()  { return rightWheel;  }
    SoQtThumbWheel* getBottomWheel() { return bottomWheel; }
    SoQtThumbWheel* getLeftWheel()   { return leftWheel;   }
    //@}

    //@{ access to thumb wheel labels for derived classes
    QLabel*         getRightWheelLabel()  { return rightWheelLabel;  }
    QLabel*         getBottomWheelLabel() { return bottomWheelLabel; }
    QLabel*         getLeftWheelLabel()   { return leftWheelLabel;   }
    //@}

    // general decoration vars
    QWidget*        leftTrimForm;
    QWidget*        bottomTrimForm;
    QWidget*        rightTrimForm;

    // thumb wheel vars
    SoQtThumbWheel*     rightWheel;
    SoQtThumbWheel*     bottomWheel;
    SoQtThumbWheel*     leftWheel;

    // The button widget should be used as the parent widget
    // when creating new application buttons
    QWidget*        getButtonWidget() const { return appButtonForm; }

    // popup menu vars
    QPointer<QMenu> popupMenu;

    // Build decoration routines
    QWidget*  createLeftBorder  (QWidget* parent) override;
    QWidget*  createLowerBorder (QWidget* parent) override;
    QWidget*  createRightBorder (QWidget* parent) override;

    // This method is called by createLeftBorder,
    // default is to add the widgets that have been added by addAppButton.
    virtual void    createAppButtons    (QWidget* parent);

    // This method is called by createRightBorder
    virtual void    createViewerButtons (QToolBar* parent);

    // viewer toolbar actions
    QAction*        pickAction;
    QAction*        viewAction;
    QAction*        seekAction;
    QAction*        helpAction;
    QAction*        gotoHomeAction;
    QAction*        setHomeAction;
    QAction*        viewAllAction;

    // popup menu build routines
    void            setPopupMenuTitle (const QString& str);
    virtual QMenu*  createPopupMenu();
    QMenu*          createFunctionsSubmenu();
    QMenu*          createDrawStyleSubmenu();

    // Preference sheet build routines
    void            setPrefSheetTitle (const QString& str);
    virtual QTabWidget* createPrefSheet();
    QWidget*        createSeekPrefSheetGuts();
    QWidget*        createSeekDistPrefSheetGuts();
    QWidget*        createZoomPrefSheetGuts();
    QWidget*        createClippingPrefSheetGuts();
    QWidget*        createStereoPrefSheetGuts();
    QWidget*        createSpeedPrefSheetGuts();

    //! hide preferences dialog when the viewer is hidden
    void    hideEvent (QHideEvent* event) override;

    //@{ monitor connections to showHelp signal
    void    connectNotify (const QMetaMethod& signal) override;
    void    disconnectNotify (const QMetaMethod& signal) override;
    //@}

    // derived classes may use this variables to store the current
    // value of the decoration wheels:
    double          rightWheelValue;
    double          bottomWheelValue;
    double          leftWheelValue;

protected slots:
    // Subclasses SHOULD redefine these to do viewer specific tasks
    // since these do nothing in the base class. those routines are
    // called by the thumb wheels whenever they rotate.
    virtual void    rightWheelMotion (double);
    virtual void    bottomWheelMotion (double);
    virtual void    leftWheelMotion (double);

    // Subclasses can redefine these to add viewer functionality. They
    // by default call start and finish interactive viewing methods.
    // (defined in the base class).
    virtual void    rightWheelStart();
    virtual void    bottomWheelStart();
    virtual void    leftWheelStart();
    virtual void    rightWheelFinish();
    virtual void    bottomWheelFinish();
    virtual void    leftWheelFinish();

    // Subclasses SHOULD set those wheel string to whatever functionality
    // name they are redefining the thumb wheels to do. Default names are
    // "Motion X, "Motion Y" and "Motion Z" for bottom, left and right wheels.
    void            setBottomWheelTitle (const QString& name);
    void            setLeftWheelTitle   (const QString& name);
    void            setRightWheelTitle  (const QString& name);

private slots:
    //! translate zoom slider value with dynamic scale, calls setZoomValue
    void setZoomSliderValue (int value);

    //! auto clipping toggle changed in pref sheet
    void setAutoClippingState (int state);

    //! near clipping plane changed in pref sheet via thumb wheel
    void setClipNearWheelValue (double value);

    //! far clipping plane changed in pref sheet via thumb wheel
    void setClipFarWheelValue (double value);

    //! near clipping plane changed in pref sheet via spin box
    void setClipNearValue (double value);

    //! far clipping plane changed in pref sheet via spin box
    void setClipFarValue (double value);

    //! stereo viewing toggle changed in pref sheet
    void setStereoViewingValue (int state);

    //! stereo viewing offset changed in pref sheet via thumb wheel
    void setStereoWheelValue (double value);

    //! stereo viewing offset changed in pref sheet via spin box
    void setStereoDistance (double value);

    //! seek distance mode changed in pref sheet via radio buttons
    void setSeekDistMode (int mode) { seekDistAsPercentage = (bool) mode; }

    //! seek distance changed in pref sheet via thumb wheel
    void setSeekDistWheelValue (double value);

    //! set minimum value for zoom
    void setZoomMinValue (double value);

    //! set maximum value for zoom
    void setZoomMaxValue (double value);

private:
    //! set position of zoom slider with dynamic scale
    void setZoomSliderPosition (double zoom);

    //! set widget pointers to null
    void initWidgets();

private:
    SbBool          decorationFlag;
    SbVec2f         zoomSldRange;
    double          clipNearWheelValue;
    double          clipFarWheelValue;
    double          seekDistWheelValue;
    double          stereoWheelValue;

    // thumb wheel names
    QString         rightWheelName;
    QString         bottomWheelName;
    QString         leftWheelName;
    QLabel*         rightWheelLabel;
    QLabel*         bottomWheelLabel;
    QLabel*         leftWheelLabel;

    // app button vars
    QWidget*        appButtonForm;
    QList<QAbstractButton*> appButtonList;

    // viewer button container
    QToolBar*       viewerButtonBar;

    // popup menu entries
    QActionGroup*   drawStyleStillGroup;
    QActionGroup*   drawStyleInteractiveGroup;
    QActionGroup*   bufferStyleGroup;
    QAction*        viewingAction;
    QAction*        decorationAction;
    QAction*        headlightAction;
    QAction*        helpAction2; // help action without icon
    QString         popupMenuTitle;

    // pref sheet dialog
    QDialog*        prefSheetDialog;
    QTabWidget*     prefSheetContainer;
    QString         prefSheetTitle;

    // seek pref sheet
    QDoubleSpinBox* seekTimeInput;
    QButtonGroup*   seekModeGroup;
    QDoubleSpinBox* seekDistInput;
    QButtonGroup*   seekDistModeGroup;

    // zoom pref sheet
    QWidget*        zoomPrefSheet;
    QSlider*        zoomSlider;
    QDoubleSpinBox* zoomInput;
    QDoubleSpinBox* zoomFromInput;
    QDoubleSpinBox* zoomToInput;

    // clipping pref sheet
    QCheckBox*      autoClippingToggle;
    QWidget*        clipPlanesWidgets;
    QDoubleSpinBox* clipNearInput;
    QDoubleSpinBox* clipFarInput;

    // stereo pref sheet
    QCheckBox*      stereoViewingToggle;
    QWidget*        stereoDistWidgets;
    QDoubleSpinBox* stereoDistInput;

    int             helpClientCount; // number of slots connected to showHelp

    // nesting flag to guard against recursion through signals
    bool            nestingFlag;
};


#endif  /* _SO_QT_FULL_VIEWER_ */
