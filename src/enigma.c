#include <stdio.h>

#include "rotors.h"

int main() {
    printf("Hello, world!\n");

    int rotors[3] = {1,2,3};
    int positions[3] = {0,0,0};
    int reflector = 1;

    init_enigma(rotors, positions, reflector);

    char result = enigmatize('F');
    printf("Final output: %c\n\n", result);

    teardown_enigma();
}
