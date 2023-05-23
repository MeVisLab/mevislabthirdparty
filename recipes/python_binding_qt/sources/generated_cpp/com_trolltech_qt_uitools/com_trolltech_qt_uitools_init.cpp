/*************************************************************************************
**
** Copyright 2022, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/
#include <PythonQt.h>
#include <PythonQtConversion.h>
#include "com_trolltech_qt_uitools0.h"



void PythonQt_init_QtUiTools(PyObject* module) {
PythonQt::priv()->registerClass(&QUiLoader::staticMetaObject, "QtUiTools", PythonQtCreateObject<PythonQtWrapper_QUiLoader>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_QUiLoader>, module, 0);


}
