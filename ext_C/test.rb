require "etc"
require_relative "lib"



t1 = Process.clock_gettime(Process::CLOCK_MONOTONIC);
p statvfs("/")

t2 = Process.clock_gettime(Process::CLOCK_MONOTONIC);

p t2 - t1
p Etc.uname
