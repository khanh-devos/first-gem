require_relative 'lib'


t1 = Process.clock_gettime(Process::CLOCK_MONOTONIC);
200.bigFib

t2 = Process.clock_gettime(Process::CLOCK_MONOTONIC);

p t2 - t1
