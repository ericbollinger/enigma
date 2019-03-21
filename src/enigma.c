#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "rotors.h"

int main() {
    int rotors[3] = {1,2,3};
    int positions[3] = {4,4,4};
    int reflector = 2;

    init_enigma(rotors, positions, reflector);

    char input[80];
    char output_buffer[80];
    char c;
    int i, output_idx;
    while (1) {
        printf("Enter a phrase to encode: ");
        fgets(input, 80, stdin);

        i = output_idx = 0;
        while (input[i] != '\n') {
            c = input[i];
            if (isalpha(input[i])) {
                c = enigmatize(toupper(input[i]));
                if (DEBUG) printf("Encrypted: %c\n\n", c);
                if (DEBUG) printf("-----------------------------------\n\n");
                output_buffer[output_idx++] = c;
            }
            i++;
        }
        output_buffer[i] = '\n';

        printf("Encoded string: %s\n\n", output_buffer);
        memset(output_buffer, 0, 80);
    }

    char result = enigmatize('B');
    printf("Final output: %c\n\n", result);

    teardown_enigma();
}
