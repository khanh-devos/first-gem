#include <sys/statvfs.h>
#include <sys/sysinfo.h>
#include <stdio.h>
#include <math.h>

int main() {

    struct statvfs buf;
    statvfs("/", &buf);

    // see at the link: https://man7.org/linux/man-pages/man0/sys_statvfs.h.0p.html
    unsigned long long block_size = buf.f_bsize;
    unsigned long long total_blocks = buf.f_blocks;
    unsigned long long free_blocks = buf.f_bavail;

    printf("%d - %d - %d \n", block_size, total_blocks, free_blocks);


    // HOW TO RUN THIS CODE
    // Ter: gcc statvfs.c && ./a.out
    // "gcc" is a compiler for some common languages: C, C++, Go, Ada
    // Explanation:
    // - f_bsize === ONE block size = 4096 bytes. (1 bytes = 4bit)
    // - 1GiB = 1024^3 ~ 1000^3 (bytes)
    // f_blocks === all the blocks in the disks.
    // => (f_bsize * f_blocks) / (1024^3) = total size of the disk.

    // f_bavail === the number of free blocks not used (available) in the disk.
    // => (f_bsize * f_bavail) / (1024^3) = total free space of the disk.
    unsigned long long oneGB = pow(1024, 3);

    printf("%dGB - %dGB \n", 
        (block_size * total_blocks) / oneGB,
        (block_size * free_blocks) / oneGB
    );


    struct sysinfo buf2;
    sysinfo(&buf2);
  
    //==========================
    // SYSINFO only
    //==========================

    // check ram of system
    unsigned long long oneG = pow(1024, 3);
    //   printf("total Ram %d GiB \n", (unsigned long long)buf.totalram / oneG);  
    //   printf("free Ram %d GiB \n", (unsigned long long)buf.freeram / oneG);  
    //   printf("shared Ram %d B \n", (unsigned long long)buf.sharedram);  
    //   printf("buffer Ram %d B \n", (unsigned long long)buf.bufferram);  
    //   printf("total swap %d B \n", (unsigned long long)buf.totalswap);  

    // Others
    long double load = 1.0 / (1 << SI_LOAD_SHIFT);
    printf("avg_Loads_1min %Lf \n", (long double)buf2.loads[0] * load);  
    printf("avg_Loads_5min %Lf \n", (long double)buf2.loads[1] * load);
    printf("avg_Loads_15min %Lf \n", (long double)buf2.loads[2] * load);
    printf("load itself %Lf \n", load);    
    // printf: %d int, %f float, %lf double, %Lf long double || %c char, %s string

    // Ter: gcc sysinfo.c && ./a.out
    // MOTE EXACTLY, Ter: ./a.out && cat /proc/loadavg

    return 0;
}