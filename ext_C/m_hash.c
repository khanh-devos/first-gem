#include <ruby.h>
#include <time.h>

VALUE time_func(VALUE obj){
  // create a hash with a key "obj" and value is current_time.
  VALUE hash = rb_hash_new();
  struct timespec tv;
  gettimeofday(&tv, NULL);
    
  rb_hash_aset(hash, obj, rb_time_new(tv.tv_sec, tv.tv_nsec));

  return hash;
}

void Init_m_hash() {
  VALUE hash = rb_hash_new();
  // {"data"=>10}
  rb_hash_aset(hash, rb_str_new_cstr("data"), INT2FIX(10));
  // {:data=>11}
  char* s = "data";
  rb_hash_aset(hash, ID2SYM(rb_intern(s)), INT2FIX(11));

  rb_global_variable(&hash);
  rb_gv_set("$h", hash);

  // hack the kernel:
  VALUE _kernel = rb_define_module("Kernel");
  rb_define_method(_kernel, "time", time_func, 0);
}