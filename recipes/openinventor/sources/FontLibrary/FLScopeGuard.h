/* *****************************************************************************************
    Copyright 2021 MeVis Medical Solutions AG
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
***************************************************************************************** */

#pragma once

#include <utility>

/**
 * Helper class for performing actions when the current scope is left.
 * Original implementation by Andrei Alexandrescu, C++ and Beyond 2013
 */

#define FL_UTILITIES_CONCATENATE_IMPL(s1,s2) s1##s2
#define FL_UTILITIES_CONCATENATE(s1,s2) FL_UTILITIES_CONCATENATE_IMPL(s1,s2)

// Some compiler does not support __COUNTER__ so there is an alternative
// implementation with __LINE__
#ifdef __COUNTER__
#define FL_UTILITIES_ANONYMOUS_VARIABLE(str)\
  FL_UTILITIES_CONCATENATE(str,__COUNTER__)
#else
#define FL_UTILITIES_ANONYMOUS_VARIABLE(str) \
  FL_UTILITIES_CONCATENATE(str,__LINE__)
#endif

namespace FL
{
  namespace ScopeGuardDetail
  {
    template <class Functor>
    class ScopeGuard
    {
    public:
      explicit ScopeGuard(Functor fn)
        : _f(std::move(fn))
        , _active(true)
      {}

      ScopeGuard(ScopeGuard&& rhs) noexcept
        : _f(std::move(rhs._f))
        , _active(rhs._active)
      {
        rhs._active = false;
      }

      ~ScopeGuard()
      {
        if (_active)
        {
          _f();
        }
      }

      void dismiss()
      {
        _active = false;
      }

    private:
      Functor _f;
      bool _active;

      ScopeGuard() = delete;
      ScopeGuard(const ScopeGuard&) = delete;
      ScopeGuard& operator=(const ScopeGuard&) = delete;
    };

    enum class ScopeGuardOnExit {};
    
    template <class Functor>
    ScopeGuard<Functor> operator+(ScopeGuardOnExit, Functor&& fn)
    {
      return ScopeGuard<Functor>(std::forward<Functor>(fn));
    }
  }
}

/**
 * Use this macro in case of an anonymous scope guard like
 * FL_SCOPE_EXIT { foo.needsToBeDoneOnLeavingTheScope(); };
 * 
 * Note: Don't forget the semicolon after the closing brace!
 */
#define FL_SCOPE_EXIT \
  auto FL_UTILITIES_ANONYMOUS_VARIABLE(SCOPE_EXIT_STATE) \
  = ::FL::ScopeGuardDetail::ScopeGuardOnExit() + [&]()


/**
* Use this macro in case you like an explicit ScopeGuard
* This is handy if there is a case where you want to dismiss the 
* action to be taken on leaving the scope.
* 
* auto localGuard = FL_EXPLICIT_SCOPE_EXIT { foo.needsToBeDoneOnLeavingTheScope(); };
* ...
* if (specialCase)
* {
*   localGuard.dismiss();
* }
* 
* Note: Don't forget the semicolon after the closing brace!
*/

#define FL_EXPLICIT_SCOPE_EXIT \
  ::FL::ScopeGuardDetail::ScopeGuardOnExit() + [&]()
