/*************************************************************************************
**
** Copyright 2014, MeVis Medical Solutions AG
**
** GNU LESSER GENERAL PUBLIC LICENSE Version 2.1, February 1999
**
**************************************************************************************/

#include "InventorBase.h"

#include "PythonQt.h"
#include "PythonQtConversion.h"
#include <QModelIndex>
#include <QList>
#include <Inventor/SbString.h>
#include <Inventor/misc/SoBase.h>
#include <QString>

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

#include <numpy/arrayobject.h>

#include <sstream>

PyObject* ConvertSbStringToPython(const void* inObject, int /*metaTypeId*/)
{
  return PythonQtConv::QStringToPyObject(QString::fromUtf8(((const SbString*)inObject)->getString()));
}

bool ConvertPythonToSbString(PyObject* inObject, void* outObject, int /*metaTypeId*/, bool strict)
{
  bool ok;
  QString string = PythonQtConv::PyObjGetString(inObject, strict, ok);
  if (ok) {
    *((SbString*)outObject) = SbString(string.toUtf8().constData());
  }
  return ok;
}

PyObject* ConvertSbNameToPython(const void* inObject, int /*metaTypeId*/)
{
  return PythonQtConv::QStringToPyObject(QString::fromUtf8(((const SbName*)inObject)->getString()));
}

bool ConvertPythonToSbName(PyObject* inObject, void* outObject, int /*metaTypeId*/, bool strict)
{
  bool ok;
  QString string = PythonQtConv::PyObjGetString(inObject, strict, ok);
  if (ok) {
    *((SbName*)outObject) = SbName(string.toUtf8().constData());
  }
  return ok;
}

static void* polymorphicHandler_SoBase(const void *ptr, const char **class_name)
{
  static QHash<QByteArray, QByteArray> names;
  SoBase *object = (SoBase*)ptr;
  QByteArray name = object->getTypeId().getName().getString();
  QByteArray resultName = names.value(name);
  if (resultName.isEmpty()) {
    QByteArray fullName = name;
    if (!fullName.startsWith("So")) {
      fullName = "So" + name;
    }
    names[name] = fullName;
    resultName = fullName;
  }
  PythonQtClassInfo* info = PythonQt::priv()->getClassInfo(resultName);
  if (!info) {
    // if the class is not yet known to PythonQt, register the whole parent hierachy...
    SoType type = object->getTypeId();
    do {
      QByteArray name = type.getName().getString();

      if (!name.startsWith("So")) {
        name = "So" + name;
      }
      SoType parent = type.getParent();
      QByteArray parentName = parent.getName().getString();
      if (!parentName.startsWith("So")) {
        parentName = "So" + parentName;
      }
      // check if the parent class is already registered before calling registerCPPClass(),
      // because it creates the parent class info without registering it completely
      PythonQtClassInfo* info = PythonQt::priv()->getClassInfo(parentName);
      PythonQt::priv()->registerCPPClass(name, parentName);
      type = parent;
      if (info) {
        static bool inventorNodesImported   = false;
        static bool inventorEnginesImported = false;
        // If the original type wasn't known, but SoNode is known, perhaps
        // somebody imported Inventor.base, but not Inventor.nodes. Try to fix this.
        if (!inventorNodesImported && (parentName == "SoNode" || parentName == "SoShape" || parentName == "SoFieldContainer")) {
          inventorNodesImported = true;
          Py_XDECREF(PyImport_ImportModule("Inventor.nodes"));
        }
        // The same for Inventor.engines (stuff like SoCalculator)
        if (!inventorEnginesImported && parentName == "SoEngine") {
          inventorEnginesImported = true;
          Py_XDECREF(PyImport_ImportModule("Inventor.engines"));
        }
        // stop because parent class was already known
        break;
      }
    } while (!type.isBad() && QByteArray(type.getName().getString()) != "Base");
  }
  *class_name = resultName.constData();
  return object;
}

void PythonQt_init_InventorBase(PyObject*);

static PyMethodDef NoMethods[] = {
    {nullptr, nullptr, 0, nullptr}        /* Sentinel */
};

Q_DECLARE_METATYPE(SbString)
Q_DECLARE_METATYPE(SbName)

static void SoBaseRefCB(void* object) {
  //std::cout << "ref: " << static_cast<SoBase*>(object)->getTypeId().getName().getString() << std::endl;
  static_cast<SoBase*>(object)->ref();
}

static void SoBaseUnrefCB(void* object) {
  //std::cout << "unref: " << static_cast<SoBase*>(object)->getTypeId().getName().getString() << std::endl;
  static_cast<SoBase*>(object)->unref();
}

static PyModuleDef baseModuleDef = {
  PyModuleDef_HEAD_INIT,
  "base",
  nullptr,
  -1,
  NoMethods,
  nullptr,
  nullptr,
  nullptr,
  nullptr
};

#define PyInitModFunc(name) PyInit_##name(void)
  #define PyModuleInit(name) PyModule_Create(&baseModuleDef)

#ifdef UNIX
PyMODINIT_FUNC
PyInitModFunc(base) ML_LIBRARY_EXPORT_ATTRIBUTE ;
#endif

PyMODINIT_FUNC
PyInitModFunc(base)
{
  // Initialize PythonQt if not yet done, to support e.g. pylint
  if (!PythonQt::self()) {
    PythonQt::init(PythonQt::IgnoreSiteModule, "_PythonQt");
  }

  PyObject* module = PyModuleInit("base");
  PythonQt_init_InventorBase(module);

  PythonQt::priv()->getClassInfo("SoBase")->setReferenceCounting(SoBaseRefCB, SoBaseUnrefCB);

  int typeId = qRegisterMetaType<SbString>();
  PythonQtConv::registerPythonToMetaTypeConverter(typeId, ConvertPythonToSbString);
  PythonQtConv::registerMetaTypeToPythonConverter(typeId, ConvertSbStringToPython);

  typeId = qRegisterMetaType<SbName>();
  PythonQtConv::registerPythonToMetaTypeConverter(typeId, ConvertPythonToSbName);
  PythonQtConv::registerMetaTypeToPythonConverter(typeId, ConvertSbNameToPython);

  PythonQt::self()->addPolymorphicHandler("SoBase", polymorphicHandler_SoBase);
  PythonQt::self()->addPolymorphicHandler("SoNode", polymorphicHandler_SoBase);
  PythonQt::self()->addPolymorphicHandler("SoShape", polymorphicHandler_SoBase);
  PythonQt::self()->addPolymorphicHandler("SoFieldContainer", polymorphicHandler_SoBase);

  PythonQt::self()->addDecorators(new InventorBaseDecorator());

  return module;
}



SoField* InventorBaseDecorator::py_dynamic_get_attrib(SoFieldContainer* container, const QByteArray& name )
{
  SoField* field = container->getField(SbName(name.constData()));
  if (!field) {
    throw std::invalid_argument("");
  }
  return field;
}

PyObject* InventorBaseDecorator::py_dynamic_get_attrib(SoEngine* engine, const QByteArray& name )
{
  SoField* field = engine->getField(SbName(name.constData()));
  if (field) {
    return PythonQt::priv()->wrapPtr(field, "SoField");
  } else {
    SoEngineOutput* output = engine->getOutput(SbName(name.constData()));
    if (output) {
      return PythonQt::priv()->wrapPtr(output, "SoEngineOutput");
    } else {
      throw std::invalid_argument("");
    }
  }
  return nullptr;
}

PyObject* InventorBaseDecorator::py_dynamic_dict( SoFieldContainer* container )
{
  PyObject* dict = PyDict_New();
  addFieldsToDict(container, dict);
  return dict;
}


void InventorBaseDecorator::addFieldsToDict( SoFieldContainer* container, PyObject* dict )
{
  SoFieldList fields;
  container->getFields(fields);
  for (int i = 0;i<fields.getLength(); i++) {
    SoField* field = fields[i];
    SbName fieldName;
    if (container->getFieldName(field, fieldName))
    {
      PyObject* object = PythonQt::priv()->wrapPtr(field, "SoField");
      PyDict_SetItemString(dict, fieldName.getString(), object);
      // dictionary ref counts the item, we need to decref:
      Py_XDECREF(object);
    }
  }
}

PyObject* InventorBaseDecorator::py_dynamic_dict( SoEngine* engine )
{
  PyObject* dict = PyDict_New();

  addFieldsToDict(engine, dict);

  SoEngineOutputList fields;
  engine->getOutputs(fields);
  for (int i = 0;i<fields.getLength(); i++) {
    SoEngineOutput* field = fields[i];
    SbName fieldName;
    if (engine->getOutputName(field, fieldName))
    {
      PyObject* object = PythonQt::priv()->wrapPtr(field, "SoEngineOutput");
      PyDict_SetItemString(dict, fieldName.getString(), object);
      // dictionary ref counts the item, we need to decref:
      Py_DECREF(object);
    }
  }

  return dict;
}

//----------------------------------------------------------------------------------

QVariantList InventorBaseDecorator::getValue( SbMatrix* matrix )
{
  QVariantList r;
  for (int i=0;i<4;i++) {
    QVariantList r2;
    for (int j=0;j<4;j++) {
      r2 << (*matrix)[i][j];
    }
    r << QVariant(r2);
  }
  return r;
}

SbMatrix* InventorBaseDecorator::new_SbMatrix( const QVariantList& values )
{
  SbMatrix* mat = new SbMatrix();
  setValueHelper(mat, values);
  return mat;
}

void InventorBaseDecorator::setValue( SbMatrix* matrix, const QVariantList& values )
{
  setValueHelper(matrix, values);
}

void InventorBaseDecorator::__setitem__( SbMatrix* matrix, int index, QList<float> values )
{
  if (index < 0 || index >= 4) {
    throw std::range_error("SbMatrix::__setitem__: out of range");
  }
  if (values.length()!=4) {
    throw std::range_error("SbMatrix::__setitem__: wrong number of values");
  }
  for (int i = 0;i<4;i++) {
    (*matrix)[index][i] = values[i];
  }
}

void InventorBaseDecorator::__setitem__( SbMatrix* matrix, QPair<int,int> index, float value )
{
  if (index.first < 0 || index.first >= 4 ||
    index.second < 0 || index.second >= 4) {
      throw std::range_error("SbMatrix::__setitem__: out of range");
  }
  for (int i = 0;i<4;i++) {
    (*matrix)[index.first][index.second] = value;
  }
}

QList<float> InventorBaseDecorator::__getitem__( SbMatrix* matrix, int index )
{
  if (index < 0 || index >= 4) {
    throw std::range_error("SbMatrix::__getitem__: out of range");
  }
  QList<float> r;
  for (int i = 0;i<4;i++) {
    r << (*matrix)[index][i];
  }
  return r;
}

float InventorBaseDecorator::__getitem__( SbMatrix* matrix, QPair<int,int> index )
{
  if (index.first < 0 || index.first >= 4 ||
    index.second < 0 || index.second >= 4) {
      throw std::range_error("SbMatrix::__setitem__: out of range");
  }
  return (*matrix)[index.first][index.second];
}

PythonQtPassOwnershipToPython<QObject*> InventorBaseDecorator::getTransform(SbMatrix* matrix, const SbVec3f& center)
{
  return new SbMatrixDecomposeResult(*matrix, center);
}

PythonQtPassOwnershipToPython<QObject*> InventorBaseDecorator::getTransform(SbMatrixd* matrix, const SbVec3d& center)
{
  return new SbMatrixdDecomposeResult(*matrix, center);
}

void InventorBaseDecorator::setValueHelper( SbMatrix* matrix, const QVariantList& values )
{
  bool ok = true;
  if (values.size() != 4) {
    throw std::range_error("SbMatrix::setValue: Wrong array length");
  }
  for (int i=0;i<4;i++) {
    QVariantList l = values[i].toList();
    if (l.size() != 4) {
      throw std::range_error("SbMatrix::setValue: Wrong array length");
    }
    for (int j=0;j<4;j++) {
      (*matrix)[i][j] = l.at(j).toFloat(&ok);
      if (!ok) {
        throw std::range_error("SbMatrix::setValue: Can not convert to double.");
      }
    }
  }
}

//----------------------------------------------------------------------------------

QVariantList InventorBaseDecorator::getValue( SbMatrixd* matrix )
{
  QVariantList r;
  for (int i=0;i<4;i++) {
    QVariantList r2;
    for (int j=0;j<4;j++) {
      r2 << (*matrix)[i][j];
    }
    r << QVariant(r2);
  }
  return r;
}

SbMatrixd* InventorBaseDecorator::new_SbMatrixd( const QVariantList& values )
{
  SbMatrixd* mat = new SbMatrixd();
  setValueHelper(mat, values);
  return mat;
}

void InventorBaseDecorator::setValue( SbMatrixd* matrix, const QVariantList& values )
{
  setValueHelper(matrix, values);
}

void InventorBaseDecorator::__setitem__( SbMatrixd* matrix, int index, QList<double> values )
{
  if (index < 0 || index >= 4) {
    throw std::range_error("SbMatrixd::__setitem__: out of range");
  }
  if (values.length()!=4) {
    throw std::range_error("SbMatrixd::__setitem__: wrong number of values");
  }
  for (int i = 0;i<4;i++) {
    (*matrix)[index][i] = values[i];
  }
}

void InventorBaseDecorator::__setitem__( SbMatrixd* matrix, QPair<int,int> index, double value )
{
  if (index.first < 0 || index.first >= 4 ||
    index.second < 0 || index.second >= 4) {
      throw std::range_error("SbMatrixd::__setitem__: out of range");
  }
  for (int i = 0;i<4;i++) {
    (*matrix)[index.first][index.second] = value;
  }
}

QList<double> InventorBaseDecorator::__getitem__( SbMatrixd* matrix, int index )
{
  if (index < 0 || index >= 4) {
    throw std::range_error("SbMatrixd::__getitem__: out of range");
  }
  QList<double> r;
  for (int i = 0;i<4;i++) {
    r << (*matrix)[index][i];
  }
  return r;
}

double InventorBaseDecorator::__getitem__( SbMatrixd* matrix, QPair<int,int> index )
{
  if (index.first < 0 || index.first >= 4 ||
    index.second < 0 || index.second >= 4) {
      throw std::range_error("SbMatrixd::__setitem__: out of range");
  }
  return (*matrix)[index.first][index.second];
}

void InventorBaseDecorator::setValueHelper( SbMatrixd* matrix, const QVariantList& values )
{
  bool ok = true;
  if (values.size() != 4) {
    throw std::range_error("SbMatrixd::setValue: Wrong array length");
  }
  for (int i=0;i<4;i++) {
    QVariantList l = values[i].toList();
    if (l.size() != 4) {
      throw std::range_error("SbMatrixd::setValue: Wrong array length");
    }
    for (int j=0;j<4;j++) {
      (*matrix)[i][j] = l.at(j).toDouble(&ok);
      if (!ok) {
        throw std::range_error("SbMatrixd::setValue: Can not convert to double.");
      }
    }
  }
}


SbMatrix InventorBaseDecorator::toMatrix( SbMatrixd* matrix )
{
  SbMatrix m;
  for (int i = 0;i<4;i++) {
    for (int j = 0;j<4;j++) {
      m[i][j] = (*matrix)[i][j];
    }
  }
  return m;
}

SbMatrixd InventorBaseDecorator::toMatrixd( SbMatrix* matrix )
{
  SbMatrixd m;
  for (int i = 0;i<4;i++) {
    for (int j = 0;j<4;j++) {
      m[i][j] = (*matrix)[i][j];
    }
  }
  return m;
}

SbPlaned InventorBaseDecorator::toPlaned( SbPlane* plane )
{
  const SbVec3f& normal = plane->getNormal();
  return SbPlaned(SbVec3d(normal[0], normal[1], normal[2]), plane->getDistanceFromOrigin());
}

SbPlane InventorBaseDecorator::toPlane( SbPlaned* plane )
{
  const SbVec3d& normal = plane->getNormal();
  return SbPlane(SbVec3f(normal[0], normal[1], normal[2]), plane->getDistanceFromOrigin());
}

SbRotationd InventorBaseDecorator::toRotationd( SbRotation* rot )
{
  float q0, q1, q2, q3;
  rot->getValue(q0,q1,q2,q3);
  return SbRotationd(q0,q1,q2,q3);
}

SbRotation InventorBaseDecorator::toRotation( SbRotationd* rot )
{
  double q0, q1, q2, q3;
  rot->getValue(q0,q1,q2,q3);
  return SbRotation(q0,q1,q2,q3);
}

QList<double> InventorBaseDecorator::getQuaternion(SbRotation* rot)
{
  QList<double> result;
  float x, y, z, w;
  rot->getValue(x, y, z, w);
  result << x << y << z << w;
  return result;
}

QList<double> InventorBaseDecorator::getQuaternion(SbRotationd* rot)
{
  QList<double> result;
  double x, y, z, w;
  rot->getValue(x, y, z, w);
  result << x << y << z << w;
  return result;
}

SoCallbackAction::Response InventorBaseDecorator::PySoCallbackActionCB( void *userData, SoCallbackAction *action, const SoNode *node )
{
  PYTHONQT_GIL_SCOPE;
  PyObject* callable = (PyObject*)userData;
  PyObject* tuple = PyTuple_New(2);
  PyTuple_SET_ITEM(tuple, 0, PythonQt::priv()->wrapPtr(action, "SoCallbackAction"));
  PyTuple_SET_ITEM(tuple, 1, PythonQt::priv()->wrapPtr((void*)node, "SoNode"));
  PyObject* result = PyObject_CallObject(callable, tuple);
  Py_DECREF(tuple);
  if (result) {
    bool ok;
    int value = PythonQtConv::PyObjGetInt(result, false, ok);
    Py_DECREF(result);
    return (SoCallbackAction::Response)value;
  } else {
    PythonQt::self()->handleError();
    return SoCallbackAction::ABORT;
  }
}

void InventorBaseDecorator::PySoTriangleCB( void *userData, SoCallbackAction *action, const SoPrimitiveVertex *v1, const SoPrimitiveVertex *v2, const SoPrimitiveVertex *v3 )
{
  PYTHONQT_GIL_SCOPE;
  PyObject* callable = (PyObject*)userData;
  PyObject* tuple = PyTuple_New(4);
  PyTuple_SET_ITEM(tuple, 0, PythonQt::priv()->wrapPtr(action, "SoCallbackAction"));
  PyTuple_SET_ITEM(tuple, 1, PythonQt::priv()->wrapPtr((void*)v1, "SoPrimitiveVertex"));
  PyTuple_SET_ITEM(tuple, 2, PythonQt::priv()->wrapPtr((void*)v2, "SoPrimitiveVertex"));
  PyTuple_SET_ITEM(tuple, 3, PythonQt::priv()->wrapPtr((void*)v3, "SoPrimitiveVertex"));
  PyObject* result = PyObject_CallObject(callable, tuple);
  if (!result) {
    PythonQt::self()->handleError();
  }
  Py_DECREF(tuple);
  Py_XDECREF(result);
}

void InventorBaseDecorator::PySoLineSegmentCB( void *userData, SoCallbackAction *action, const SoPrimitiveVertex *v1, const SoPrimitiveVertex *v2 )
{
  PYTHONQT_GIL_SCOPE;
  PyObject* callable = (PyObject*)userData;
  PyObject* tuple = PyTuple_New(3);
  PyTuple_SET_ITEM(tuple, 0, PythonQt::priv()->wrapPtr(action, "SoCallbackAction"));
  PyTuple_SET_ITEM(tuple, 1, PythonQt::priv()->wrapPtr((void*)v1, "SoPrimitiveVertex"));
  PyTuple_SET_ITEM(tuple, 2, PythonQt::priv()->wrapPtr((void*)v2, "SoPrimitiveVertex"));
  PyObject* result = PyObject_CallObject(callable, tuple);
  if (!result) {
    PythonQt::self()->handleError();
  }
  Py_DECREF(tuple);
  Py_XDECREF(result);
}

void InventorBaseDecorator::PySoPointCB( void *userData, SoCallbackAction *action, const SoPrimitiveVertex *v )
{
  PYTHONQT_GIL_SCOPE;
  PyObject* callable = (PyObject*)userData;
  PyObject* tuple = PyTuple_New(2);
  PyTuple_SET_ITEM(tuple, 0, PythonQt::priv()->wrapPtr(action, "SoCallbackAction"));
  PyTuple_SET_ITEM(tuple, 1, PythonQt::priv()->wrapPtr((void*)v, "SoPrimitiveVertex"));
  PyObject* result = PyObject_CallObject(callable, tuple);
  if (!result) {
    PythonQt::self()->handleError();
  }
  Py_DECREF(tuple);
  Py_XDECREF(result);
}

void InventorBaseDecorator::PySoCallbackCB( void *userData, SoAction *action )
{
  PYTHONQT_GIL_SCOPE;
  PyObject* callable = (PyObject*)userData;
  PyObject* tuple = PyTuple_New(1);
  PyTuple_SET_ITEM(tuple, 0, PythonQt::priv()->wrapPtr(action, "SoAction"));
  PyObject* result = PyObject_CallObject(callable, tuple);
  if (!result) {
    PythonQt::self()->handleError();
  }
  Py_DECREF(tuple);
  Py_XDECREF(result);
}

void InventorBaseDecorator::PySoEventCallbackCB( void *userData, SoEventCallback *node )
{
  PYTHONQT_GIL_SCOPE;
  PyObject* callable = (PyObject*)userData;
  PyObject* tuple = PyTuple_New(1);
  PyTuple_SET_ITEM(tuple, 0, PythonQt::priv()->wrapPtr(node, "SoEventCallback"));
  PyObject* result = PyObject_CallObject(callable, tuple);
  if (!result) {
    PythonQt::self()->handleError();
  }
  Py_DECREF(tuple);
  Py_XDECREF(result);
}

void InventorBaseDecorator::PySoSelectionPathCB( void *userData, SoPath *path )
{
  PYTHONQT_GIL_SCOPE;
  PyObject* callable = (PyObject*)userData;
  PyObject* tuple = PyTuple_New(1);
  PyTuple_SET_ITEM(tuple, 0, PythonQt::priv()->wrapPtr(path, "SoPath"));
  PyObject* result = PyObject_CallObject(callable, tuple);
  if (!result) {
    PythonQt::self()->handleError();
  }
  Py_DECREF(tuple);
  Py_XDECREF(result);
}

void InventorBaseDecorator::PySoSelectionClassCB( void *userData, SoSelection *sel )
{
  PYTHONQT_GIL_SCOPE;
  PyObject* callable = (PyObject*)userData;
  PyObject* tuple = PyTuple_New(1);
  PyTuple_SET_ITEM(tuple, 0, PythonQt::priv()->wrapPtr(sel, "SoSelection"));
  PyObject* result = PyObject_CallObject(callable, tuple);
  if (!result) {
    PythonQt::self()->handleError();
  }
  Py_DECREF(tuple);
  Py_XDECREF(result);
}

void* InventorBaseDecorator::init_numpy()
{
  static bool initialized = false;
  if (!initialized) {
    initialized = true;
    import_array();
  }
#if PY_MAJOR_VERSION >= 3
  return nullptr;
#endif
}

template<class FIELD, class VECTOR, int SIZE, int mainNumpyType, class mainType, class conversionType>
void setVectorValuesHelper( FIELD* field, int start, PyObject* obj, PyTypeObject* wrapperType )
{
  InventorBaseDecorator::init_numpy();
  PythonQtObjectPtr scopedArray;
  // check if it isn't a numpy array
  if (!PyArray_Check(obj)) {
    // if it is a sequence, check if it is a sequence of VECTOR
    if (PySequence_Check(obj)) {
      bool sequenceOfVectors = false;
      int count = PySequence_Size(obj);
      if (count > 0) {
        sequenceOfVectors = true;
        PyObject* value;
        for (int i = 0;i<count && sequenceOfVectors;i++) {
          value = PySequence_GetItem(obj,i);
          if (wrapperType != Py_TYPE(value)) {
            sequenceOfVectors = false;
          }
          Py_XDECREF(value);
        }
        if (sequenceOfVectors) {
          field->setNum(start + count);
          VECTOR* values = field->startEditing();
          values += start;
          for (int i = 0; i<count; i++) {
            value = PySequence_GetItem(obj,i);
            PythonQtInstanceWrapper* ptr = (PythonQtInstanceWrapper*)value;
            *values = *((VECTOR*)ptr->_wrappedPtr);
            Py_XDECREF(value);
            values++;
          }
          field->finishEditing();
          return;
        }
      }
    }
    // not a sequence of vectors, so we use PyArray_FromAny to convert to a numpy array
    PyObject* float_array = PyArray_FromAny(obj,PyArray_DescrFromType(mainNumpyType), 2,2,0,nullptr);
    // this takes care of the ref counting...
    scopedArray.setNewRef(float_array);
    obj = float_array;
  }
  if (obj) {
    PyArrayObject*  contiguousArray = PyArray_GETCONTIGUOUS((PyArrayObject*)obj);
    // we use a PythonQtObjectPtr to handle the ownership of contiguousArray
    scopedArray.setNewRef((PyObject*)contiguousArray);
    if (PyArray_NDIM(contiguousArray) != 2) {
      throw std::invalid_argument("Expecting a numpy array of dimension 2");
    }
    if (PyArray_DIMS(contiguousArray)[1] != SIZE) {
      std::stringstream str;
      str << "Expecting a numpy array of size " << SIZE << " in dimension 0";
      throw std::invalid_argument(str.str());
    }
    int type = PyArray_DESCR(contiguousArray)->type_num;
    if (type != NPY_DOUBLE && type != NPY_FLOAT) {
      throw std::invalid_argument("Expecting a numpy array of type float or double");
    }
    int numValues = PyArray_DIMS(contiguousArray)[0];
    if (type == mainNumpyType) {
      typedef mainType vec[SIZE];
      field->setValues(start, numValues, (const vec*)PyArray_DATA(contiguousArray));
    } else {
      conversionType* npValues = (conversionType*)PyArray_DATA(contiguousArray);
      field->setNum(start + numValues);
      VECTOR* values = field->startEditing();
      values += start;
      for (int i = 0; i<numValues; i++) {
        mainType value[SIZE];
        for (int j = 0;j<SIZE;j++) {
          value[j] = static_cast<mainType>(npValues[j]);
        }
        values->setValue(value);
        npValues += SIZE;
        values++;
      }
      field->finishEditing();
    }
  } else {
    throw std::invalid_argument("Expecting a numpy array or something that is convertible using fromAny()");
  }
}

void InventorBaseDecorator::setValues( SoMFVec2f* field, int start, PyObject* obj )
{
  PYTHONQT_GIL_SCOPE;
  static PyTypeObject* wrapperType = (PyTypeObject*)PythonQt::priv()->getClassInfo("SbVec2f")->pythonQtClassWrapper();
  setVectorValuesHelper<SoMFVec2f, SbVec2f, 2, NPY_FLOAT, float, double>(field, start, obj, wrapperType);
}

PyObject* InventorBaseDecorator::startEditing( SoMFVec2f* field )
{
  PYTHONQT_GIL_SCOPE;
  init_numpy();
  npy_intp size[2] = {field->getNum(), 2};
  PyObject* obj = PyArray_New(&PyArray_Type, 2, size, NPY_FLOAT, nullptr,
    (float*)field->startEditing(), 0, NPY_ARRAY_CARRAY, nullptr);
  return obj;
}

PyObject* InventorBaseDecorator::getValues( SoMFVec2f* field )
{
  PYTHONQT_GIL_SCOPE;
  init_numpy();
  npy_intp size[2] = {field->getNum(), 2};
  // return a read-only version
  PyObject* obj = PyArray_New(&PyArray_Type, 2, size, NPY_FLOAT, nullptr,
    (float*)field->getValues(0), 0, NPY_ARRAY_C_CONTIGUOUS | NPY_ARRAY_BEHAVED, nullptr);
  return obj;
}

void InventorBaseDecorator::setValues( SoMFVec3f* field, int start, PyObject* obj )
{
  PYTHONQT_GIL_SCOPE;
  static PyTypeObject* wrapperType = (PyTypeObject*)PythonQt::priv()->getClassInfo("SbVec3f")->pythonQtClassWrapper();
  setVectorValuesHelper<SoMFVec3f, SbVec3f, 3, NPY_FLOAT, float, double>(field, start, obj, wrapperType);
}

PyObject* InventorBaseDecorator::startEditing( SoMFVec3f* field )
{
  PYTHONQT_GIL_SCOPE;
  init_numpy();
  npy_intp size[2] = {field->getNum(), 3};
  PyObject* obj = PyArray_New(&PyArray_Type, 2, size, NPY_FLOAT, nullptr,
                              (float*)field->startEditing(), 0, NPY_ARRAY_CARRAY, nullptr);
  return obj;
}

PyObject* InventorBaseDecorator::getValues( SoMFVec3f* field )
{
  PYTHONQT_GIL_SCOPE;
  init_numpy();
  npy_intp size[2] = {field->getNum(), 3};
  // return a read-only version
  PyObject* obj = PyArray_New(&PyArray_Type, 2, size, NPY_FLOAT, nullptr,
    (float*)field->getValues(0), 0, NPY_ARRAY_C_CONTIGUOUS | NPY_ARRAY_BEHAVED, nullptr);
  return obj;
}

void InventorBaseDecorator::setValues( SoMFColor* field, int start, PyObject* obj )
{
  PYTHONQT_GIL_SCOPE;
  static PyTypeObject* wrapperType = (PyTypeObject*)PythonQt::priv()->getClassInfo("SbColor")->pythonQtClassWrapper();
  setVectorValuesHelper<SoMFColor, SbColor, 3, NPY_FLOAT, float, double>(field, start, obj, wrapperType);
}

PyObject* InventorBaseDecorator::startEditing( SoMFColor* field )
{
  PYTHONQT_GIL_SCOPE;
  init_numpy();
  npy_intp size[2] = {field->getNum(), 3};
  PyObject* obj = PyArray_New(&PyArray_Type, 2, size, NPY_FLOAT, nullptr,
    (float*)field->startEditing(), 0, NPY_ARRAY_CARRAY, nullptr);
  return obj;
}

PyObject* InventorBaseDecorator::getValues( SoMFColor* field )
{
  PYTHONQT_GIL_SCOPE;
  init_numpy();
  npy_intp size[2] = {field->getNum(), 3};
  // return a read-only version
  PyObject* obj = PyArray_New(&PyArray_Type, 2, size, NPY_FLOAT, nullptr,
    (float*)field->getValues(0), 0, NPY_ARRAY_C_CONTIGUOUS | NPY_ARRAY_BEHAVED, nullptr);
  return obj;
}

void InventorBaseDecorator::setValues( SoMFVec4f* field, int start, PyObject* obj )
{
  PYTHONQT_GIL_SCOPE;
  static PyTypeObject* wrapperType = (PyTypeObject*)PythonQt::priv()->getClassInfo("SbVec4f")->pythonQtClassWrapper();
  setVectorValuesHelper<SoMFVec4f, SbVec4f, 4, NPY_FLOAT, float, double>(field, start, obj, wrapperType);
}

PyObject* InventorBaseDecorator::startEditing( SoMFVec4f* field )
{
  PYTHONQT_GIL_SCOPE;
  init_numpy();
  npy_intp size[2] = {field->getNum(), 4};
  PyObject* obj = PyArray_New(&PyArray_Type, 2, size, NPY_FLOAT, nullptr,
    (float*)field->startEditing(), 0, NPY_ARRAY_CARRAY, nullptr);
  return obj;
}

PyObject* InventorBaseDecorator::getValues( SoMFVec4f* field )
{
  PYTHONQT_GIL_SCOPE;
  init_numpy();
  npy_intp size[2] = {field->getNum(), 4};
  // return a read-only version
  PyObject* obj = PyArray_New(&PyArray_Type, 2, size, NPY_FLOAT, nullptr,
    (float*)field->getValues(0), 0, NPY_ARRAY_C_CONTIGUOUS | NPY_ARRAY_BEHAVED, nullptr);
  return obj;
}

//------------------------------------------------------------------------------------------------

void InventorBaseDecorator::setValues( SoMFVec2d* field, int start, PyObject* obj )
{
  PYTHONQT_GIL_SCOPE;
  static PyTypeObject* wrapperType = (PyTypeObject*)PythonQt::priv()->getClassInfo("SbVec2d")->pythonQtClassWrapper();
  setVectorValuesHelper<SoMFVec2d, SbVec2d, 2, NPY_DOUBLE, double, float>(field, start, obj, wrapperType);
}

PyObject* InventorBaseDecorator::startEditing( SoMFVec2d* field )
{
  PYTHONQT_GIL_SCOPE;
  init_numpy();
  npy_intp size[2] = {field->getNum(), 2};
  PyObject* obj = PyArray_New(&PyArray_Type, 2, size, NPY_DOUBLE, nullptr,
    (double*)field->startEditing(), 0, NPY_ARRAY_CARRAY, nullptr);
  return obj;
}

PyObject* InventorBaseDecorator::getValues( SoMFVec2d* field )
{
  PYTHONQT_GIL_SCOPE;
  init_numpy();
  npy_intp size[2] = {field->getNum(), 2};
  // return a read-only version
  PyObject* obj = PyArray_New(&PyArray_Type, 2, size, NPY_DOUBLE, nullptr,
    (double*)field->getValues(0), 0, NPY_ARRAY_C_CONTIGUOUS | NPY_ARRAY_BEHAVED, nullptr);
  return obj;
}

void InventorBaseDecorator::setValues( SoMFVec3d* field, int start, PyObject* obj )
{
  PYTHONQT_GIL_SCOPE;
  static PyTypeObject* wrapperType = (PyTypeObject*)PythonQt::priv()->getClassInfo("SbVec3d")->pythonQtClassWrapper();
  setVectorValuesHelper<SoMFVec3d, SbVec3d, 3, NPY_DOUBLE, double, float>(field, start, obj, wrapperType);
}

PyObject* InventorBaseDecorator::startEditing( SoMFVec3d* field )
{
  PYTHONQT_GIL_SCOPE;
  init_numpy();
  npy_intp size[2] = {field->getNum(), 3};
  PyObject* obj = PyArray_New(&PyArray_Type, 2, size, NPY_DOUBLE, nullptr,
    (double*)field->startEditing(), 0, NPY_ARRAY_CARRAY, nullptr);
  return obj;
}

PyObject* InventorBaseDecorator::getValues( SoMFVec3d* field )
{
  PYTHONQT_GIL_SCOPE;
  init_numpy();
  npy_intp size[2] = {field->getNum(), 3};
  // return a read-only version
  PyObject* obj = PyArray_New(&PyArray_Type, 2, size, NPY_DOUBLE, nullptr,
    (double*)field->getValues(0), 0, NPY_ARRAY_C_CONTIGUOUS | NPY_ARRAY_BEHAVED, nullptr);
  return obj;
}

void InventorBaseDecorator::setValues( SoMFVec4d* field, int start, PyObject* obj )
{
  PYTHONQT_GIL_SCOPE;
  static PyTypeObject* wrapperType = (PyTypeObject*)PythonQt::priv()->getClassInfo("SbVec4d")->pythonQtClassWrapper();
  setVectorValuesHelper<SoMFVec4d, SbVec4d, 4, NPY_DOUBLE, double, float>(field, start, obj, wrapperType);
}

PyObject* InventorBaseDecorator::startEditing( SoMFVec4d* field )
{
  PYTHONQT_GIL_SCOPE;
  init_numpy();
  npy_intp size[2] = {field->getNum(), 4};
  PyObject* obj = PyArray_New(&PyArray_Type, 2, size, NPY_DOUBLE, nullptr,
    (double*)field->startEditing(), 0, NPY_ARRAY_CARRAY, nullptr);
  return obj;
}

PyObject* InventorBaseDecorator::getValues( SoMFVec4d* field )
{
  PYTHONQT_GIL_SCOPE;
  init_numpy();
  npy_intp size[2] = {field->getNum(), 4};
  // return a read-only version
  PyObject* obj = PyArray_New(&PyArray_Type, 2, size, NPY_DOUBLE, nullptr,
    (double*)field->getValues(0), 0, NPY_ARRAY_C_CONTIGUOUS | NPY_ARRAY_BEHAVED, nullptr);
  return obj;
}

//--------------------------------------------------------------------------------------------------
template<class FIELD, class TYPE, int numpyType>
void setValuesHelper( FIELD* field, int start, PyObject* obj )
{
  InventorBaseDecorator::init_numpy();
  PythonQtObjectPtr scopedArray;
  // check if it isn't a numpy array
  if (!PyArray_Check(obj) || PyArray_DESCR((PyArrayObject*) obj)->type_num != numpyType) {
    PyObject* convertedArray = PyArray_FromAny(obj, PyArray_DescrFromType(numpyType), 1, 1, NPY_ARRAY_FORCECAST, nullptr);
    // this takes care of the ref counting...
    scopedArray.setNewRef(convertedArray);
    obj = convertedArray;
  }
  if (obj) {
    PyArrayObject*  contiguousArray = PyArray_GETCONTIGUOUS((PyArrayObject*)obj);
    // we use a PythonQtObjectPtr to handle the ownership of contiguousArray
    scopedArray.setNewRef((PyObject*)contiguousArray);
    if (PyArray_NDIM(contiguousArray) != 1) {
      throw std::invalid_argument("Expecting a numpy array of dimension 1");
    }
    int type = PyArray_DESCR(contiguousArray)->type_num;
    if (type != numpyType) {
      throw std::invalid_argument("Unexpected numpy type");
    }
    int numValues = PyArray_DIMS(contiguousArray)[0];
    field->setValues(start, numValues, (const TYPE*)PyArray_DATA(contiguousArray));
  } else {
    throw std::invalid_argument("Expecting a numpy array or something that is convertible using fromAny()");
  }
}

void InventorBaseDecorator::setValues( SoMFFloat* field, int start, PyObject* obj )
{
  PYTHONQT_GIL_SCOPE;
  setValuesHelper<SoMFFloat, float, NPY_FLOAT>(field, start, obj);
}

PyObject* InventorBaseDecorator::startEditing( SoMFFloat* field )
{
  PYTHONQT_GIL_SCOPE;
  init_numpy();
  npy_intp size[1] = {field->getNum()};
  PyObject* obj = PyArray_New(&PyArray_Type, 1, size, NPY_FLOAT, nullptr,
    (float*)field->startEditing(), 0, NPY_ARRAY_CARRAY, nullptr);
  return obj;
}

PyObject* InventorBaseDecorator::getValues( SoMFFloat* field )
{
  PYTHONQT_GIL_SCOPE;
  init_numpy();
  npy_intp size[1] = {field->getNum()};
  // return a read-only version
  PyObject* obj = PyArray_New(&PyArray_Type, 1, size, NPY_FLOAT, nullptr,
    (float*)field->getValues(0), 0, NPY_ARRAY_C_CONTIGUOUS | NPY_ARRAY_BEHAVED, nullptr);
  return obj;
}

void InventorBaseDecorator::setValues( SoMFDouble* field, int start, PyObject* obj )
{
  PYTHONQT_GIL_SCOPE;
  setValuesHelper<SoMFDouble, double, NPY_DOUBLE>(field, start, obj);
}

PyObject* InventorBaseDecorator::startEditing( SoMFDouble* field )
{
  PYTHONQT_GIL_SCOPE;
  init_numpy();
  npy_intp size[1] = {field->getNum()};
  PyObject* obj = PyArray_New(&PyArray_Type, 1, size, NPY_DOUBLE, nullptr,
    (double*)field->startEditing(), 0, NPY_ARRAY_CARRAY, nullptr);
  return obj;
}

PyObject* InventorBaseDecorator::getValues( SoMFDouble* field )
{
  PYTHONQT_GIL_SCOPE;
  init_numpy();
  npy_intp size[1] = {field->getNum()};
  // return a read-only version
  PyObject* obj = PyArray_New(&PyArray_Type, 1, size, NPY_DOUBLE, nullptr,
    (double*)field->getValues(0), 0, NPY_ARRAY_C_CONTIGUOUS | NPY_ARRAY_BEHAVED, nullptr);
  return obj;
}


void InventorBaseDecorator::setValues( SoMFUInt32* field, int start, PyObject* obj )
{
  PYTHONQT_GIL_SCOPE;
  setValuesHelper<SoMFUInt32, uint32_t, NPY_UINT32>(field, start, obj);
}

PyObject* InventorBaseDecorator::startEditing( SoMFUInt32* field )
{
  PYTHONQT_GIL_SCOPE;
  init_numpy();
  npy_intp size[1] = {field->getNum()};
  PyObject* obj = PyArray_New(&PyArray_Type, 1, size, NPY_UINT32, nullptr,
    (void*)field->startEditing(), 0, NPY_ARRAY_CARRAY, nullptr);
  return obj;
}

PyObject* InventorBaseDecorator::getValues( SoMFUInt32* field )
{
  PYTHONQT_GIL_SCOPE;
  init_numpy();
  npy_intp size[1] = {field->getNum()};
  // return a read-only version
  PyObject* obj = PyArray_New(&PyArray_Type, 1, size, NPY_UINT32, nullptr,
    (void*)field->getValues(0), 0, NPY_ARRAY_C_CONTIGUOUS | NPY_ARRAY_BEHAVED, nullptr);
  return obj;
}

void InventorBaseDecorator::setValues( SoMFInt32* field, int start, PyObject* obj )
{
  PYTHONQT_GIL_SCOPE;
  setValuesHelper<SoMFInt32, int32_t, NPY_INT32>(field, start, obj);
}

PyObject* InventorBaseDecorator::startEditing( SoMFInt32* field )
{
  PYTHONQT_GIL_SCOPE;
  init_numpy();
  npy_intp size[1] = {field->getNum()};
  PyObject* obj = PyArray_New(&PyArray_Type, 1, size, NPY_INT32, nullptr,
    (void*)field->startEditing(), 0, NPY_ARRAY_CARRAY, nullptr);
  return obj;
}

PyObject* InventorBaseDecorator::getValues( SoMFInt32* field )
{
  PYTHONQT_GIL_SCOPE;
  init_numpy();
  npy_intp size[1] = {field->getNum()};
  // return a read-only version
  PyObject* obj = PyArray_New(&PyArray_Type, 1, size, NPY_INT32, nullptr,
    (void*)field->getValues(0), 0, NPY_ARRAY_C_CONTIGUOUS | NPY_ARRAY_BEHAVED, nullptr);
  return obj;
}
