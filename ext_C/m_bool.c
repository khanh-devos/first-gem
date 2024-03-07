#include <ruby.h>
#include <extconf.h>

#define pi "3.14"

void Init_m_bool() {
  VALUE b = INT2FIX(1000), str;
  rb_global_variable(&b);
  
  
  if(b) {
    VALUE str_arg = rb_funcall(b, rb_intern("to_s"), 0);
    char* string = StringValuePtr(str_arg);
    
    char mallok[100];   //100 == 100 bytes length of mallok (char=1byte)
    sprintf(mallok, "The value of arg is %s", string);

    str = rb_str_new_cstr(mallok);
  }
  else {
    str = rb_str_new_cstr("Arg is false");
  }

  rb_gv_set("$a", str);

}