#include <ruby.h>
#include <sys/statvfs.h>
#include <stdio.h>
#include <math.h>

VALUE check_disk(VALUE self, VALUE path){
    char* dir = StringValuePtr(path);
    struct statvfs buf;
    statvfs(dir, &buf);

    // see at the link: https://man7.org/linux/man-pages/man0/sys_statvfs.h.0p.html
    unsigned long long block_size = buf.f_bsize;
    unsigned long long total_blocks = buf.f_blocks;
    unsigned long long free_blocks = buf.f_bavail;

    // Explanation:
    // - f_bsize === ONE block size = 4096 bytes. (1 bytes = 4bit)
    // - 1GiB = 1024^3 ~ 1000^3 (bytes)
    // f_blocks === all the blocks in the disks.
    // => (f_bsize * f_blocks) / (1024^3) = total size of the disk.

    // f_bavail === the number of free blocks not used (available) in the disk.
    // => (f_bsize * f_bavail) / (1024^3) = total free space of the disk.
    unsigned long long oneGB = pow(1024, 3);
    VALUE hash = rb_hash_new();
    
    // Explanation: pls see the file statvfs.c for details
    rb_hash_aset(hash, 
        ID2SYM(rb_intern("one_block_size_bytes")), 
        ULONG2NUM(block_size)
    );
    
    rb_hash_aset(hash, 
        ID2SYM(rb_intern("disk_total_size_GB")), 
        ULONG2NUM(block_size * total_blocks / oneGB)
    );

    rb_hash_aset(hash, 
        ID2SYM(rb_intern("disk_free_size-GB")), 
        ULONG2NUM(block_size * free_blocks / oneGB)
    );


    return hash;
}


void Init_m_statvfs(VALUE self) {
    // Show all the disks (HDD, SDD, RAM) by Ter: df -k
    // Just take the directory at the right side.
    rb_define_global_function("statvfs", check_disk, 1);
    
}