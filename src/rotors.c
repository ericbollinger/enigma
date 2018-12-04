#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rotors.h"

#define NUM_ROTORS 3

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

// The letters that trigger a rotation for the next rotor
int notches[5] = {
    17, // Q becomes R
    5,  // E becomes F
    22, // V becomes W
    10, // J becomes K
    0   // Z becomes A
};


void init_enigma(int *rotors, int *positions, int reflector) {
    g_setup = malloc(sizeof(setup));

    for (int i = 0; i < NUM_ROTORS; i++) {
        /*
         * Subtract 1 from the rotor number to uphold the documented numbering
         * scheme for the rotors, i.e. 1-5 instead of 0-4
         */
        g_setup->rotors[i] = available_rotors[rotors[i]-1];
        g_setup->rotor_positions[i] = positions[i];
    }

    g_setup->reflector = available_reflectors[reflector-1];
}

void teardown_enigma() {
    free(g_setup);
}

int char_to_int(char letter) {
    return letter - 'A';
}

char int_to_char(int number) {
    return number + 'A';
}

int rotor_encode(int rotor, int input, direction_e dir) {
    char *letters = g_setup->rotors[rotor];
    //printf("Letters: %s\n", letters);

    int offset = g_setup->rotor_positions[rotor];
    //printf("Offset: %d\n", offset);

    int rotor_input = (input + offset) % 26;
    //printf("Rotor input: %d\n", rotor_input);

    int rotor_output = 0;
    if (dir == FORWARD) {

        char rotor_output_letter = letters[rotor_input];
        rotor_output = char_to_int(rotor_output_letter);

    } else {

        char tmp_c = int_to_char(rotor_input);

        char *char_ptr = malloc(2);
        char_ptr[0] = tmp_c;
        char_ptr[1] = '\0';

        char *pos = strstr(letters, char_ptr);
        rotor_output = pos - letters;
        //printf("String position: %c at %d\n", tmp_c, rotor_output);

        free(char_ptr);

    }

    //printf("Rotor output: %c\n\n", int_to_char(rotor_output));

    rotor_output -= offset;
    rotor_output = (rotor_output < 0) ? rotor_output + 26 : rotor_output;

    return rotor_output;
}

int reflect(int input) {
    char *letters = g_setup->reflector;
    //printf("Reflector letters: %s\n", letters);

    int reflector_output = letters[input];
    //printf("Reflector input: %d\n", input);
    //printf("Reflector output: %c\n\n", reflector_output);

    return char_to_int(reflector_output);
}

void rotate() {
    printf("Rotating first ring...\n");
    int *pos_list = g_setup->rotor_positions;
    pos_list[0] += 1;
    pos_list[0] %= 26;

    if (pos_list[0] != notches[0]) {
        return;
    }

    printf("Rotating second ring...\n");
    pos_list[1] += 1;
    pos_list[1] %= 26;

    if (pos_list[1] != notches[1]) {
        return;
    }

    printf("Rotating third ring...\n");
    pos_list[2] += 1;
    pos_list[2] %= 26;
}

char enigmatize(char input) {
    rotate();

    int cur = char_to_int(input);
    for (int i = 0; i < NUM_ROTORS; i++) {
        cur = rotor_encode(i, cur, FORWARD);
    }

    cur = reflect(cur);

    for (int i = NUM_ROTORS - 1; i >= 0; i--) {
        cur = rotor_encode(i, cur, BACKWARD);
    }
//    printf("--------------------------------------------------\n\n");
    return int_to_char(cur);
}
