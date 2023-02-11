#include <stdio.h>

/*
* 判断机器字节序
* 现代PC大多采用小端字节序，因此小端字节序又被称为主机字节序
**/


void byte_order() {
    union
    {
        short value;
        char union_bytes[sizeof(short)];
    } test;
    test.value = 0x0102;
    if ((test.union_bytes[0] == 1) && (test.union_bytes[1] == 2)) {
        printf("big endian\n");
    } else if ((test.union_bytes[0] == 2) && (test.union_bytes[1] == 1)) {
        printf("little endian\n");
    } else {
        printf("unknow...\n");
    }
}


int main() {
    byte_order();
    return 0;
}