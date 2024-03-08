#include <ruby.h>
#include <sys/utsname.h>
#include <math.h>

struct utsname buf3;
char *sysname="", *nodename="", *release="", *version="", *machine=""; 

void iniStat() {
  char status = uname(&buf3);  
  if (status == 0) {
    sysname = buf3.sysname;
    nodename = buf3.nodename;
    release = buf3.release;
    version = buf3.version;
    machine = buf3.machine; 
  };  
}


VALUE check_utsname(VALUE self) {
  return rb_ary_new_from_args(5, 
    rb_str_new_cstr(sysname),
    rb_str_new_cstr(nodename),
    rb_str_new_cstr(release),
    rb_str_new_cstr(version), 
    rb_str_new_cstr(machine)
  );
}

void Init_m_utsname() {
  iniStat();
  rb_define_global_function("utsname", check_utsname, 0);
}