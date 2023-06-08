#include "main.h"
/**
  *get_endianness - this checks if a machine is little or big endian
  * Return: 0 for big, 1 for little
  */

int main() {
    int endianness = get_endianness();
    if (endianness == 1) {
        printf("Little endian\n");
    } else {
        printf("Big endian\n");
    }

    return 0;
}
