//----------------------------------------------------------------------------------
// **InsertLicense** code
//----------------------------------------------------------------------------------
#ifndef SO_REF_H
#define SO_REF_H

//! SoRef proves an intrusive smart pointer for any SoBase derived class and
//! uses the ref()/unref() methods of SoBase to manage the ref counting.
template <class T>
class SoRef
{
public:
  SoRef():_object(0) {}

  SoRef(const SoRef<T> &p):_object(0) {
    setObject(p._object);
  }

  SoRef(T* o) {
    _object = o;
    if (o) {
      o->ref();
    }
  }

  ~SoRef() { if (_object) _object->unref(); }

  SoRef<T> &operator=(const SoRef<T> &p) {
    setObject(p._object);
    return *this;
  }

  template<class T2>
  SoRef<T> &operator=(const SoRef<T2> &p) {
    setObject(p._object);
    return *this;
  }

  SoRef<T> &operator=(T* o) {
    setObject(o);
    return *this;
  }

  bool operator==( const SoRef<T> &p ) const {
    return _object == p._object;
  }

  bool operator!= ( const SoRef<T>& p ) const {
    return !( *this == p );
  }

  bool operator==( T* p ) const {
    return _object == p;
  }

  bool operator!= ( T* p ) const {
    return _object != p;
  }

  T* operator->() const { return _object; }

  T& operator*() const { return *( _object ); }

  //! Get access to the underlying pointer automatically.
  //! This was deprecated at VSG, but we consider it more useful than dangerous.
  operator T*() const { return _object; }

  //! Get access to the underlying pointer (VSG compatibility).
  T* ptr() const { return _object; }

  //! Get access to the underlying pointer.
  T* get() const { return _object; }

  //! Get access to the underlying pointer without deleting the object.
  //! This is useful in some places where the user knows that he
  //! will pass the object to a place which will take over ref counting.
  T* releaseNoDelete() {
    T* p = _object;
    if (_object) {
      _object->unrefNoDelete();
      _object = NULL;
    }
    return p;
  }

protected:
  void setObject(T* o) {
    if (o != _object) {
      T* oldObject = _object;
      _object = o;
      if (_object) _object->ref();
      if (oldObject) oldObject->unref();
    }
  }

private:
  T* _object;
};

#endif

