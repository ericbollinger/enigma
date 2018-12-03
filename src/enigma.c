#include <stdio.h>

#include "rotors.h"

int main() {
    printf("Hello, world!\n");

    int rotors[3] = {1,2,3};
    int positions[3] = {4,5,6};
    int reflector = 1;

    rotor_init(rotors, positions, reflector);
}
