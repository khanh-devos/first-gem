#include <ruby.h>
#include <extconf.h>


// Headers ...

// Global variables ...
VALUE rb_cMusic;

VALUE
rb_music_stop(VALUE msc)
{
  return rb_str_new_cstr("stop");
}

VALUE
rb_music_play(VALUE msc, VALUE rpath)
{
  return rpath;
}

void Init_m_music(void)
{
  rb_cMusic = rb_define_class("Music", rb_cObject);
  rb_define_singleton_method(rb_cMusic, "play", rb_music_play, 1);
  rb_define_singleton_method(rb_cMusic, "stop", rb_music_stop, 0);
}