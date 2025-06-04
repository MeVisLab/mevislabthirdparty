/*************************************************************************************
**
** Copyright 2014, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/
#ifndef _INVENTORBASE_H
#define _INVENTORBASE_H

#include <PythonQt.h>
#include <stdexcept>
#include <QObject>
#include <Inventor/misc/SoBase.h>
#include <Inventor/fields/SoField.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoMFVec2f.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFVec4f.h>
#include <Inventor/fields/SoMFVec2d.h>
#include <Inventor/fields/SoMFVec3d.h>
#include <Inventor/fields/SoMFVec4d.h>
#include <Inventor/fields/SoMFColor.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoMFUInt32.h>
#include <Inventor/fields/SoMFDouble.h>
#include <Inventor/fields/SoFieldContainer.h>
#include <Inventor/engines/SoEngine.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoCallback.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/nodes/SoSelection.h>
#include <QVariantList>
#include <Inventor/SbLineard.h>
#include <Inventor/SbColor.h>

#include <Inventor/actions/SoCallbackAction.h>

class HelperSFEnum : public SoSFEnum
{
public:
  // Number of enumeration values
  int     getNumEnums() {return numEnums;}
  // Enumeration values
  int     getEnumValue(int i) { return enumValues[i];}
  // Mnemonic names of values
  const char* getEnumName(int i) { return enumNames[i].getString();}
};

class SbMatrixDecomposeResult : public QObject
{
  Q_OBJECT

  public:

    SbMatrixDecomposeResult(const SbMatrix& matrix, const SbVec3f& center)
    {
      matrix.getTransform(_translation, _rotation, _scaling, _scaleOrientation, center);
    }

  public Q_SLOTS:
    SbVec3f    py_get_translation() { return _translation; }
    SbRotation py_get_rotation() { return _rotation; }
    SbVec3f    py_get_scaling() { return _scaling; }
    SbRotation py_get_scaleOrientation() { return _scaleOrientation; }

  private:
    SbVec3f    _translation;
    SbRotation _rotation;
    SbVec3f    _scaling;
    SbRotation _scaleOrientation;
};

class SbMatrixdDecomposeResult : public QObject
{
  Q_OBJECT

public:

  SbMatrixdDecomposeResult(const SbMatrixd& matrix, const SbVec3d& center)
  {
    matrix.getTransform(_translation, _rotation, _scaling, _scaleOrientation, center);
  }

public Q_SLOTS:
  SbVec3d    py_get_translation() { return _translation; }
  SbRotationd py_get_rotation() { return _rotation; }
  SbVec3d    py_get_scaling() { return _scaling; }
  SbRotationd py_get_scaleOrientation() { return _scaleOrientation; }

private:
  SbVec3d    _translation;
  SbRotationd _rotation;
  SbVec3d    _scaling;
  SbRotationd _scaleOrientation;
};

class InventorBaseDecorator : public QObject
{
  Q_OBJECT

public Q_SLOTS:
  SoField*  py_dynamic_get_attrib(SoFieldContainer* container, const QByteArray& name);
  PyObject* py_dynamic_get_attrib(SoEngine* engine, const QByteArray& name );

  PyObject* py_dynamic_dict(SoFieldContainer* container);
  PyObject* py_dynamic_dict(SoEngine* container);

  SbMatrix*    new_SbMatrix(const QVariantList& values);
  void         setValue(SbMatrix* matrix, const QVariantList& values);
  QVariantList getValue(SbMatrix* matrix);
  void         __setitem__(SbMatrix* matrix, int index, QList<float> values);
  void         __setitem__(SbMatrix* matrix, QPair<int,int> index, float value);
  QList<float> __getitem__(SbMatrix* matrix, int index);
  float        __getitem__(SbMatrix* matrix, QPair<int,int> index);
  PythonQtPassOwnershipToPython<QObject*> getTransform(SbMatrix* matrix, const SbVec3f& center = SbVec3f(0.,0.,0.));

  SbMatrixd*    new_SbMatrixd(const QVariantList& values);
  void         setValue(SbMatrixd* matrix, const QVariantList& values);
  QVariantList getValue(SbMatrixd* matrix);
  void         __setitem__(SbMatrixd* matrix, int index, QList<double> values);
  void         __setitem__(SbMatrixd* matrix, QPair<int,int> index, double value);
  QList<double> __getitem__(SbMatrixd* matrix, int index);
  double        __getitem__(SbMatrixd* matrix, QPair<int,int> index);
  PythonQtPassOwnershipToPython<QObject*> getTransform(SbMatrixd* matrix, const SbVec3d& center = SbVec3d(0., 0., 0.));

  SbMatrix toMatrix(SbMatrixd* matrix);
  SbMatrixd toMatrixd(SbMatrix* matrix);

  SbPlaned toPlaned(SbPlane* plane);
  SbPlane  toPlane(SbPlaned* plane);

  SbRotationd toRotationd(SbRotation* rot);
  SbRotation  toRotation(SbRotationd* rot);

  QList<double> getQuaternion(SbRotation* rot);
  QList<double> getQuaternion(SbRotationd* rot);

  QString py_toString(SbVec2s* vec) {
    return QString("SbVec2s (%1, %2)").arg((*vec)[0]).arg((*vec)[1]);
  }
  QString py_toString(SbVec2f* vec) {
    return QString("SbVec2f (%1, %2)").arg((*vec)[0]).arg((*vec)[1]);
  }
  QString py_toString(SbVec2d* vec) {
    return QString("SbVec2d (%1, %2)").arg((*vec)[0]).arg((*vec)[1]);
  }
  QString py_toString(SbVec3s* vec) {
    return QString("SbVec3s (%1, %2, %3)").arg((*vec)[0]).arg((*vec)[1]).arg((*vec)[2]);
  }
  QString py_toString(SbVec3f* vec) {
    return QString("SbVec3f (%1, %2, %3)").arg((*vec)[0]).arg((*vec)[1]).arg((*vec)[2]);
  }
  QString py_toString(SbVec3d* vec) {
    return QString("SbVec3d (%1, %2, %3)").arg((*vec)[0]).arg((*vec)[1]).arg((*vec)[2]);
  }
  QString py_toString(SbVec4f* vec) {
    return QString("SbVec4f (%1, %2, %3, %4)").arg((*vec)[0]).arg((*vec)[1]).arg((*vec)[2]).arg((*vec)[3]);
  }
  QString py_toString(SbVec4d* vec) {
    return QString("SbVec4d (%1, %2, %3, %4)").arg((*vec)[0]).arg((*vec)[1]).arg((*vec)[2]).arg((*vec)[3]);
  }

  QString py_toString(SbColor* vec) {
    return QString("SbColor (%1, %2, %3)").arg((*vec)[0]).arg((*vec)[1]).arg((*vec)[2]);
  }

  QString py_toString(SbPlane* vec) {
    return QString("SbPlane (%1, %2, %3, %4)").arg(vec->getNormal()[0]).arg(vec->getNormal()[1]).arg(vec->getNormal()[2]).arg(vec->getDistanceFromOrigin());
  }
  QString py_toString(SbPlaned* vec) {
    return QString("SbPlaned (%1, %2, %3, %4)").arg(vec->getNormal()[0]).arg(vec->getNormal()[1]).arg(vec->getNormal()[2]).arg(vec->getDistanceFromOrigin());
  }

  QString py_toString(SbRotation* vec) {
    return QString("SbRotation ((%1, %2, %3), %4)").arg(vec->getAxis()[0]).arg(vec->getAxis()[1]).arg(vec->getAxis()[2]).arg(vec->getAngle());
  }
  QString py_toString(SbRotationd* vec) {
    return QString("SbRotationd ((%1, %2, %3), %4)").arg(vec->getAxis()[0]).arg(vec->getAxis()[1]).arg(vec->getAxis()[2]).arg(vec->getAngle());
  }


  PyObject*  intersect(SbPlaned* theWrappedObject, const SbLined&  l) const {
    SbVec3d* intersection =  new SbVec3d();
    bool ok = theWrappedObject->intersect(l, *intersection);
    if (ok) {
      static const QByteArray type = "SbVec3d";
      PythonQtInstanceWrapper* wrapper = (PythonQtInstanceWrapper*) PythonQt::priv()->wrapPtr(intersection, type, /*passOwnership = */ true);
      return (PyObject*)wrapper;
    } else {
      Py_INCREF(Py_None);
      return Py_None;
    }
  }

  PyObject*  intersect(SbPlane* theWrappedObject, const SbLine&  l) const {
    SbVec3f* intersection =  new SbVec3f();
    bool ok = theWrappedObject->intersect(l, *intersection);
    if (ok) {
      static const QByteArray type = "SbVec3f";
      return PythonQt::priv()->wrapPtr(intersection, type, /*passOwnership = */ true);
    } else {
      delete intersection;
      Py_INCREF(Py_None);
      return Py_None;
    }
  }

  PyObject* intersect(SbSphere* sphere, const SbLine& line) const
  {
    SbVec3f* entry = new SbVec3f();
    SbVec3f* exit = new SbVec3f();
    if (sphere->intersect(line, *entry, *exit)) {
      static const QByteArray type = "SbVec3f";
      PyObject* tuple = PyTuple_New(2);
      // SET_ITEM steal the references, so we are good:
      PyTuple_SET_ITEM(tuple, 0, PythonQt::priv()->wrapPtr(entry, type, /*passOwnership = */ true));
      PyTuple_SET_ITEM(tuple, 1, PythonQt::priv()->wrapPtr(exit, type, /*passOwnership = */ true));
      return tuple;
    } else {
      delete entry;
      delete exit;
      Py_INCREF(Py_None);
      return Py_None;
    }
  }

  PyObject* intersect(SbSphered* sphere, const SbLined& line) const
  {
    SbVec3d* entry = new SbVec3d();
    SbVec3d* exit = new SbVec3d();
    if (sphere->intersect(line, *entry, *exit)) {
      static const QByteArray type = "SbVec3d";
      PyObject* tuple = PyTuple_New(2);
      // SET_ITEM steal the references, so we are good:
      PyTuple_SET_ITEM(tuple, 0, PythonQt::priv()->wrapPtr(entry, type, /*passOwnership = */ true));
      PyTuple_SET_ITEM(tuple, 1, PythonQt::priv()->wrapPtr(exit, type, /*passOwnership = */ true));
      return tuple;
    } else {
      delete entry;
      delete exit;
      Py_INCREF(Py_None);
      return Py_None;
    }
  }

  PyObject* intersect(SbCylinder* cyl, const SbLine& line) const
  {
    SbVec3f* entry = new SbVec3f();
    SbVec3f* exit = new SbVec3f();
    if (cyl->intersect(line, *entry, *exit)) {
      static const QByteArray type = "SbVec3f";
      PyObject* tuple = PyTuple_New(2);
      // SET_ITEM steal the references, so we are good:
      PyTuple_SET_ITEM(tuple, 0, PythonQt::priv()->wrapPtr(entry, type, /*passOwnership = */ true));
      PyTuple_SET_ITEM(tuple, 1, PythonQt::priv()->wrapPtr(exit, type, /*passOwnership = */ true));
      return tuple;
    } else {
      delete entry;
      delete exit;
      Py_INCREF(Py_None);
      return Py_None;
    }
  }

  PyObject* intersect(SbCylinderd* cyl, const SbLined& line) const
  {
    SbVec3d* entry = new SbVec3d();
    SbVec3d* exit = new SbVec3d();
    if (cyl->intersect(line, *entry, *exit)) {
      static const QByteArray type = "SbVec3d";
      PyObject* tuple = PyTuple_New(2);
      // SET_ITEM steal the references, so we are good:
      PyTuple_SET_ITEM(tuple, 0, PythonQt::priv()->wrapPtr(entry, type, /*passOwnership = */ true));
      PyTuple_SET_ITEM(tuple, 1, PythonQt::priv()->wrapPtr(exit, type, /*passOwnership = */ true));
      return tuple;
    } else {
      delete entry;
      delete exit;
      Py_INCREF(Py_None);
      return Py_None;
    }
  }

  void fullPathPop(SoPath* o) {
    return ((SoFullPath*)o)->pop();
  }
  SoNode* fullPathGetTail(SoPath* o) {
    return ((SoFullPath*)o)->getTail();
  }
  SoNode* fullPathGetNodeFromTail(SoPath* o, int i) {
    return ((SoFullPath*)o)->getNodeFromTail(i);
  }
  int fullPathGetIndexFromTail(SoPath* o, int i) {
    return ((SoFullPath*)o)->getIndexFromTail(i);
  }
  int fullPathGetLength(SoPath* o) {
    return ((SoFullPath*)o)->getLength();
  }

  QString get(SoField* theWrappedObject) {
    SbString value;
    theWrappedObject->get(value);
    return QString::fromUtf8(value.getString());
  }

  QString get1(SoMField* theWrappedObject, int  index) {
    SbString value;
    theWrappedObject->get1(index, value);
    return QString::fromUtf8(value.getString());
  }

  SoEngineOutput* getConnectedEngine(SoField* theWrappedObject) const
  {
    SoEngineOutput* engineOutput;
    if (theWrappedObject->getConnectedEngine(engineOutput)) {
      return engineOutput;
    } else {
      return nullptr;
    }
  }

  SoField* getConnectedField(SoField* theWrappedObject) const
  {
    SoField* field;
    if (theWrappedObject->getConnectedField(field)) {
      return field;
    } else {
      return nullptr;
    }
  }

  SbName getFieldName(SoFieldContainer* cont, const SoField* field) {
    SbName name;
    if (cont->getFieldName(field, name)) {
      return name;
    } else {
      return SbName("");
    }
  }

  SbName getOutputName(SoEngine* engine, const SoEngineOutput* out) {
    SbName name;
    if (engine->getOutputName(out, name)) {
      return name;
    } else {
      return SbName("");
    }
  }

  QHash<int, QString> getEnumValues(SoSFEnum* field) {
    QHash<int, QString> result;
    HelperSFEnum* helper = (HelperSFEnum*)field;
    for (int i = 0;i<helper->getNumEnums(); i++) {
      result.insert(helper->getEnumValue(i), QString::fromUtf8(helper->getEnumName(i)));
    }
    return result;
  }

  PyObject * getMaterial(SoCallbackAction* action, const int index = 0) {
    SbColor* ambient = new SbColor;
    SbColor* diffuse = new SbColor;
    SbColor* specular = new SbColor;
    SbColor* emission = new SbColor;
    float shininess, transparency;

    action->getMaterial(*ambient, *diffuse, *specular, *emission, shininess, transparency, index);

    static const QByteArray colorType("SbColor");
    return Py_BuildValue("(OOOOff)",
      PythonQt::priv()->wrapPtr(ambient, colorType, true),
      PythonQt::priv()->wrapPtr(diffuse, colorType, true),
      PythonQt::priv()->wrapPtr(specular, colorType, true),
      PythonQt::priv()->wrapPtr(emission, colorType, true),
      shininess,
      transparency);
  }

  void addPreCallback(SoCallbackAction* action, SoType type, PyObject* callable) {
    if (PyCallable_Check(callable)) {
      action->addPreCallback(type, PySoCallbackActionCB, callable);
    } else {
      throw std::invalid_argument("SoCallbackAction::addPreCallback requires a callable");
    }
  }
  void addPostCallback(SoCallbackAction* action, SoType type, PyObject* callable) {
    if (PyCallable_Check(callable)) {
      action->addPostCallback(type, PySoCallbackActionCB, callable);
    } else {
      throw std::invalid_argument("SoCallbackAction::addPostCallback requires a callable");
    }
  }
  void addPreTailCallback(SoCallbackAction* action, PyObject* callable) {
    if (PyCallable_Check(callable)) {
      action->addPreTailCallback(PySoCallbackActionCB, callable);
    } else {
      throw std::invalid_argument("SoCallbackAction::addPreTailCallback requires a callable");
    }
  }
  void addPostTailCallback(SoCallbackAction* action, PyObject* callable) {
    if (PyCallable_Check(callable)) {
      action->addPostTailCallback(PySoCallbackActionCB, callable);
    } else {
      throw std::invalid_argument("SoCallbackAction::addPostTailCallback requires a callable");
    }
  }

  void addLineSegmentCallback(SoCallbackAction* action, SoType type, PyObject* callable) {
    if (PyCallable_Check(callable)) {
      action->addLineSegmentCallback(type, PySoLineSegmentCB, callable);
    } else {
      throw std::invalid_argument("SoCallbackAction::addLineSegmentCallback requires a callable");
    }
  }
  void addPointCallback(SoCallbackAction* action, SoType type, PyObject* callable) {
    if (PyCallable_Check(callable)) {
      action->addPointCallback(type, PySoPointCB, callable);
    } else {
      throw std::invalid_argument("SoCallbackAction::addPointCallback requires a callable");
    }
  }
  void addTriangleCallback(SoCallbackAction* action, SoType type, PyObject* callable) {
    if (PyCallable_Check(callable)) {
      action->addTriangleCallback(type, PySoTriangleCB, callable);
    } else {
      throw std::invalid_argument("SoCallbackAction::addTriangleCallback requires a callable");
    }
  }

  void setCallback(SoCallback* cb, PyObject* callable) {
    if (PyCallable_Check(callable)) {
      cb->setCallback(PySoCallbackCB, callable);
    } else {
      if (callable == Py_None) {
        cb->setCallback(nullptr,nullptr);
      }
      throw std::invalid_argument("SoCallback::setCallback requires a callable");
    }
  }

  void addEventCallback(SoEventCallback* cb, SoType eventType, PyObject* callable) {
    if (PyCallable_Check(callable)) {
      cb->addEventCallback(eventType, PySoEventCallbackCB, callable);
    } else {
      throw std::invalid_argument("SoEventCallback::addEventCallback requires a callable");
    }
  }
  void removeEventCallback(SoEventCallback* cb, SoType eventType, PyObject* callable) {
    if (PyCallable_Check(callable)) {
      cb->removeEventCallback(eventType, PySoEventCallbackCB, callable);
    } else {
      throw std::invalid_argument("SoEventCallback::removeEventCallback requires a callable");
    }
  }

  void addSelectionCallback(SoSelection* sel, PyObject* callable) {
    if (PyCallable_Check(callable)) {
      sel->addSelectionCallback(PySoSelectionPathCB, callable);
    } else {
      throw std::invalid_argument("SoSelection::addSelectionCallback requires a callable");
    }
  }
  void removeSelectionCallback(SoSelection* sel, PyObject* callable) {
    if (PyCallable_Check(callable)) {
      sel->removeSelectionCallback(PySoSelectionPathCB, callable);
    } else {
      throw std::invalid_argument("SoSelection::removeSelectionCallback requires a callable");
    }
  }
  void addDeselectionCallback(SoSelection* sel, PyObject* callable) {
    if (PyCallable_Check(callable)) {
      sel->addDeselectionCallback(PySoSelectionPathCB, callable);
    } else {
      throw std::invalid_argument("SoSelection::addDeselectionCallback requires a callable");
    }
  }
  void removeDeselectionCallback(SoSelection* sel, PyObject* callable) {
    if (PyCallable_Check(callable)) {
      sel->removeDeselectionCallback(PySoSelectionPathCB, callable);
    } else {
      throw std::invalid_argument("SoSelection::removeDeselectionCallback requires a callable");
    }
  }

  void addStartCallback(SoSelection* sel, PyObject* callable) {
    if (PyCallable_Check(callable)) {
      sel->addStartCallback(PySoSelectionClassCB, callable);
    } else {
      throw std::invalid_argument("SoSelection::addStartCallback requires a callable");
    }
  }
  void removeStartCallback(SoSelection* sel, PyObject* callable) {
    if (PyCallable_Check(callable)) {
      sel->removeStartCallback(PySoSelectionClassCB, callable);
    } else {
      throw std::invalid_argument("SoSelection::removeStartCallback requires a callable");
    }
  }
  void addFinishCallback(SoSelection* sel, PyObject* callable) {
    if (PyCallable_Check(callable)) {
      sel->addFinishCallback(PySoSelectionClassCB, callable);
    } else {
      throw std::invalid_argument("SoSelection::addFinishCallback requires a callable");
    }
  }
  void removeFinishCallback(SoSelection* sel, PyObject* callable) {
    if (PyCallable_Check(callable)) {
      sel->removeFinishCallback(PySoSelectionClassCB, callable);
    } else {
      throw std::invalid_argument("SoSelection::removeFinishCallback requires a callable");
    }
  }

  //! Set the values starting at offset start from the given array.
  //! This supports numpy arrays of type float and double with 3 components.
  void setValues(SoMFColor* field, int start, PyObject* array);
  //! Returns a writable numpy array. Don't forget to call finishEditing() and
  //! don't keep a reference to the returned object after finishEditing().
  PyObject* startEditing(SoMFColor* field);
  //! Returns a read-only numpy array with a direct memory reference to the contained values.
  //! Make sure to copy the values if you want to keep them longer than they exist in C++.
  PyObject* getValues(SoMFColor* field);

  //! Set the values starting at offset start from the given array.
  //! This supports numpy arrays of type float and double with 3 components.
  void setValues(SoMFVec4f* field, int start, PyObject* array);
  //! Returns a writable numpy array. Don't forget to call finishEditing() and
  //! don't keep a reference to the returned object after finishEditing().
  PyObject* startEditing(SoMFVec4f* field);
  //! Returns a read-only numpy array with a direct memory reference to the contained values.
  //! Make sure to copy the values if you want to keep them longer than they exist in C++.
  PyObject* getValues(SoMFVec4f* field);

  //! Set the values starting at offset start from the given array.
  //! This supports numpy arrays of type float and double with 3 components.
  void setValues(SoMFVec3f* field, int start, PyObject* array);
  //! Returns a writable numpy array. Don't forget to call finishEditing() and
  //! don't keep a reference to the returned object after finishEditing().
  PyObject* startEditing(SoMFVec3f* field);
  //! Returns a read-only numpy array with a direct memory reference to the contained values.
  //! Make sure to copy the values if you want to keep them longer than they exist in C++.
  PyObject* getValues(SoMFVec3f* field);

  //! Set the values starting at offset start from the given array.
  //! This supports numpy arrays of type float and double with 3 components.
  void setValues(SoMFVec2f* field, int start, PyObject* array);
  //! Returns a writable numpy array. Don't forget to call finishEditing() and
  //! don't keep a reference to the returned object after finishEditing().
  PyObject* startEditing(SoMFVec2f* field);
  //! Returns a read-only numpy array with a direct memory reference to the contained values.
  //! Make sure to copy the values if you want to keep them longer than they exist in C++.
  PyObject* getValues(SoMFVec2f* field);

  //! Set the values starting at offset start from the given array.
  //! This supports numpy arrays of type float and double with 3 components.
  void setValues(SoMFVec2d* field, int start, PyObject* array);
  //! Returns a writable numpy array. Don't forget to call finishEditing() and
  //! don't keep a reference to the returned object after finishEditing().
  PyObject* startEditing(SoMFVec2d* field);
  //! Returns a read-only numpy array with a direct memory reference to the contained values.
  //! Make sure to copy the values if you want to keep them longer than they exist in C++.
  PyObject* getValues(SoMFVec2d* field);

  //! Set the values starting at offset start from the given array.
  //! This supports numpy arrays of type float and double with 3 components.
  void setValues(SoMFVec3d* field, int start, PyObject* array);
  //! Returns a writable numpy array. Don't forget to call finishEditing() and
  //! don't keep a reference to the returned object after finishEditing().
  PyObject* startEditing(SoMFVec3d* field);
  //! Returns a read-only numpy array with a direct memory reference to the contained values.
  //! Make sure to copy the values if you want to keep them longer than they exist in C++.
  PyObject* getValues(SoMFVec3d* field);

  //! Set the values starting at offset start from the given array.
  //! This supports numpy arrays of type float and double with 3 components.
  void setValues(SoMFVec4d* field, int start, PyObject* array);
  //! Returns a writable numpy array. Don't forget to call finishEditing() and
  //! don't keep a reference to the returned object after finishEditing().
  PyObject* startEditing(SoMFVec4d* field);
  //! Returns a read-only numpy array with a direct memory reference to the contained values.
  //! Make sure to copy the values if you want to keep them longer than they exist in C++.
  PyObject* getValues(SoMFVec4d* field);

  //! Set the values starting at offset start from the given array.
  //! This supports numpy arrays of type float and double with 3 components.
  void setValues(SoMFFloat* field, int start, PyObject* array);
  //! Returns a writable numpy array. Don't forget to call finishEditing() and
  //! don't keep a reference to the returned object after finishEditing().
  PyObject* startEditing(SoMFFloat* field);
  //! Returns a read-only numpy array with a direct memory reference to the contained values.
  //! Make sure to copy the values if you want to keep them longer than they exist in C++.
  PyObject* getValues(SoMFFloat* field);

  //! Set the values starting at offset start from the given array.
  //! This supports numpy arrays of type float and double with 3 components.
  void setValues(SoMFDouble* field, int start, PyObject* array);
  //! Returns a writable numpy array. Don't forget to call finishEditing() and
  //! don't keep a reference to the returned object after finishEditing().
  PyObject* startEditing(SoMFDouble* field);
  //! Returns a read-only numpy array with a direct memory reference to the contained values.
  //! Make sure to copy the values if you want to keep them longer than they exist in C++.
  PyObject* getValues(SoMFDouble* field);

  //! Set the values starting at offset start from the given array.
  //! This supports numpy arrays of type float and double with 3 components.
  void setValues(SoMFUInt32* field, int start, PyObject* array);
  //! Returns a writable numpy array. Don't forget to call finishEditing() and
  //! don't keep a reference to the returned object after finishEditing().
  PyObject* startEditing(SoMFUInt32* field);
  //! Returns a read-only numpy array with a direct memory reference to the contained values.
  //! Make sure to copy the values if you want to keep them longer than they exist in C++.
  PyObject* getValues(SoMFUInt32* field);

  //! Set the values starting at offset start from the given array.
  //! This supports numpy arrays of type float and double with 3 components.
  void setValues(SoMFInt32* field, int start, PyObject* array);
  //! Returns a writable numpy array. Don't forget to call finishEditing() and
  //! don't keep a reference to the returned object after finishEditing().
  PyObject* startEditing(SoMFInt32* field);
  //! Returns a read-only numpy array with a direct memory reference to the contained values.
  //! Make sure to copy the values if you want to keep them longer than they exist in C++.
  PyObject* getValues(SoMFInt32* field);

public:
  static
#if PY_MAJOR_VERSION >= 3
  void*
#else
  void
#endif
  init_numpy();

protected:
  static void PySoSelectionPathCB(void *userData, SoPath *path);
  static void PySoSelectionClassCB(void *userData, SoSelection *sel);

  static void PySoEventCallbackCB(void *userData, SoEventCallback *node);

  static void PySoCallbackCB(void *userData, SoAction *action);

  static SoCallbackAction::Response PySoCallbackActionCB(void *userData, SoCallbackAction *action, const SoNode *node);

  static void PySoTriangleCB(void *userData,
    SoCallbackAction *action,
    const SoPrimitiveVertex *v1,
    const SoPrimitiveVertex *v2,
    const SoPrimitiveVertex *v3);

  static void PySoLineSegmentCB(void *userData, SoCallbackAction *action,
    const SoPrimitiveVertex *v1,
    const SoPrimitiveVertex *v2);

  static void PySoPointCB(void *userData, SoCallbackAction *action,
    const SoPrimitiveVertex *v);


  static void         setValueHelper(SbMatrix* matrix, const QVariantList& values);
  static void         setValueHelper(SbMatrixd* matrix, const QVariantList& values);

  static void addFieldsToDict( SoFieldContainer* container, PyObject* dict );

};


#endif
