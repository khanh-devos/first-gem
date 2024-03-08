#include <sys/statvfs.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <X11/Xlib.h>

#include <stdio.h>
#include <math.h>

void for_statvfs(){
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


    
}

void for_sysinfo(){
    struct sysinfo buf2;
    char status = sysinfo(&buf2);
    if (status == -1) return 0;

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
}

void for_utsname() {
    struct utsname buf3;
    char status3 = uname(&buf3);
    if (status3 == -1) return 0;

    printf("sys name : %s \n", buf3.sysname);
    printf("node name : %s \n", buf3.nodename);
    printf("release : %s \n", buf3.release);
    printf("version : %s \n", buf3.version);
    printf("machine : %s \n", buf3.machine);
}

int main() {
    printf("=============statvfs==========================\n");
    for_statvfs();
  
    //==========================
    // SYSINFO only
    printf("=============sysinfo==========================\n");
    //==========================
    for_sysinfo();
    


    //=======================utsname=====================
    printf("=============utsname==========================\n");
    for_utsname();
    



    //==============================================
    //======use X11 ===================================
    // HOW RUN? Ter: gcc -l X11 starvfs.c && ./a.out
    //==============================================

    Display *d;
    Window w;
    XEvent e;
    int s;

    if (!(d = XOpenDisplay(NULL))) {
        fprintf(stderr, "Couldn't open display, but Arch is the best!\n");
        exit(1);
    }

    s = DefaultScreen(d);
    w = XCreateSimpleWindow(d, RootWindow(d,s), 0, 0, 410, 200, 0, 
                            0, WhitePixel(d,s));
    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapWindow(d,w);

    while (1) {
        XNextEvent(d, &e);
        if (e.type == Expose) {
            XDrawString(d, w, DefaultGC(d, s), 5, 15, "Arch is the best!", 17);
        }
    }

    XCloseDisplay(d);

    //HOW RUN? Ter: gcc -l X11 starvfs.c
    //HOW RUN? Ter: gcc -lX11 starvfs.c


    return 0;
}