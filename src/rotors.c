#include <stdio.h>
#include <stdlib.h>

#include "rotors.h"

static setup *g_setup;

// The five available rotors. Can be arranged in any order.
char *available_rotors[5] = {
    "EKMFLGDQVZNTOWYHXUSPAIBRCJ",
    "AJDKSIRUXBLHWTMCQGZNPYFVOE",
    "BDFHJLCPRTXVZNYEIWGAKMUSQO",
    "ESOVPZJAYQUIRHXLNFTGKDCMWB",
    "VZBRGITYUPSDNHLXAWMJQOFECK"
};

// The three available reflector rotors
char *available_reflectors[3] = {
    "EJMZALYXVBWFCRQUONTSPIKHGD",
    "YRUHQSLDPXNGOKMIEBFZCWVJAT",
    "FVPJIAOYEDRZXWGCTKUQSBNMHL"
};

// The letters that trigger a rotation for each rotor
char *notches[5] = {
    "Q",
    "E",
    "V",
    "J",
    "Z"
};

void
rotor_init(int *rotors, int *positions, int reflector) {
    g_setup = malloc(sizeof(setup));

    for (int i = 0; i < 3; i++) {
        // Subtract 1 from the rotor number to uphold the documented numbering
        // scheme for the rotors, i.e. 1-5 instead of 0-4
        g_setup->rotors[i] = available_rotors[rotors[i-1]];
        g_setup->rotor_positions[i] = positions[i];
    }

    g_setup->reflector = available_reflectors[reflector];

    printf("Wheel 1: %s\n", g_setup->rotors[0]);
}

int
char_to_int(char letter) {
    return letter - 'a';
}

char
int_to_char(int number) {
    return number + 'a';
}

int
rotor_encode(int rotor, int input) {
    char *letters = g_setup->rotors[rotor];
    int offset = g_setup->rotor_positions[rotor];

    int rotor_input = input + offset % 26;
    char rotor_output = letters[rotor_input];
    return char_to_int(rotor_output);
}

char
enigmatize(char c) {
    return 'a';
}
