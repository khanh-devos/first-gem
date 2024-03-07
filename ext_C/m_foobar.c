#include <ruby.h>
#include <extconf.h>


VALUE rb_hello(VALUE class) {
  VALUE str = rb_str_new_cstr("hello!");
  rb_funcall(rb_mKernel, rb_intern("puts"), 1, str);
  return Qnil;
}

void Init_m_foobar()
{
    VALUE klass = rb_define_class("Greeting", rb_cObject);
    rb_define_singleton_method(klass, "hello", rb_hello, 0);

}