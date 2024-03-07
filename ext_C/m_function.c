#include <ruby.h>
#include <string.h>
#include <ctype.h>

VALUE up_here(VALUE main, VALUE x){
  if (RB_TYPE_P(x, T_STRING)) {
    return rb_funcall(x, rb_intern("*"), 1, INT2FIX(5));
  }
  else if (RB_TYPE_P(x, T_FIXNUM)) {
    return rb_funcall(x, rb_intern("*"), 1, INT2FIX(5));
    // return ULL2NUM(NUM2ULL(x) * 5);
  }
  else {
    return x;
  }
}


VALUE n_func(VALUE self) {
  char* d = StringValuePtr(self); //This is a C string
  int i = 0;
  char n[strlen(d)], y;

  while (y = d[i]) {
    n[i] = toupper(y);
    ++i;
  }

  n[i] = '\0';
  return rb_str_new_cstr(n);
}


void Init_m_func(){
  rb_define_global_function("up", up_here, 1);
  // Now up "1" => "11111", or up 1 => 5

  //Call out class String of ruby
  VALUE rb_string = rb_define_class("String", rb_cObject); 
  
  rb_define_method(rb_string, "cUpcase", n_func, 0);
  // Now we can call "abc".cUpcase => "ABC". 
  // Same built-in method: "abc".upcase()

}