#include <ruby.h>
#include <extconf.h>
#include <math.h>

void Init_m_number() {
  int a = pow(2, 30);  //pow is from header "math" in C.
  // float f1 = 10/3.0;
  // double f2 = 10/3.0;
  
  VALUE num = INT2FIX(a);
  // VALUE num2 = rb_float_new(f1);
  
  rb_global_variable(&num);
  rb_gv_set("$a", num);

  // NUM2ULL() convert a C number from a ruby type.
  // So we need an INT2FIX().
  VALUE obj = 11;
  rb_gv_set("$b", INT2FIX(NUM2ULL(obj))); 
  rb_gv_set("$c", INT2FIX(obj));
  unsigned n = 1000000000;
  rb_gv_set("$d", INT2NUM(n));

  
}