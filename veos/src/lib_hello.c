#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
uint64_t hello() {
    printf("Hello, VE.\n");
    return 0;
}
uint64_t static_hello(uint64_t x, uint64_t y) {
    printf("Hello, I am a static function call.\n");
    printf("x = %d y = %d.\n", x, y);
}
uint64_t dynamic_hello(char *c, char *ret) {
    printf("Hello, I am a dynamic function call.\n");
    printf("args = %s.\n", c);
    char *src = "return value";
    memcpy(ret, src, 13);
}
