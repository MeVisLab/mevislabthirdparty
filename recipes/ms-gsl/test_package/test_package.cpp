#include <gsl/gsl>

int* use(gsl::not_null<int*> p)
{
  return p;
}

struct Widget
{
    Widget() : owned_ptr(new int(42)) {
    }

    ~Widget() {
      delete owned_ptr;
    }

    void work()
    {
       non_owned_ptr = use(gsl::not_null(owned_ptr)); 
    }

    gsl::owner<int*> owned_ptr = nullptr;
    int* non_owned_ptr = nullptr;
};

int main()
{
    Widget w;
    w.work();
}
