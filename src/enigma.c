#include <ctype.h>
#include <stdio.h>

#include "rotors.h"

int main() {
    int rotors[3] = {1,2,3};
    int positions[3] = {16,0,0};
    int reflector = 2;

    init_enigma(rotors, positions, reflector);

    char input[80];
    char c;
    int i;
    while (1) {
        printf("Enter a phrase to encode: ");
        fgets(input, 80, stdin);

        i = 0;
        while (input[i] != '\n') {
            if (isalpha(input[i])) {
                c = enigmatize(toupper(input[i]));
                printf("Encrypted: %c\n\n", c);
                printf("-----------------------------------\n\n");
            }
            i++;
        }
    }

    char result = enigmatize('B');
    printf("Final output: %c\n\n", result);

    teardown_enigma();
}
