require 'mkmf'
$LDFLAGS << " -lX11"  

create_header

create_makefile('lib')