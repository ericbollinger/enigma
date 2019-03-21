#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rotors.h"

#define NUM_ROTORS 3
#define MIDDLE_ROTOR_INDEX 1

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
    16, // Q is about to become R
    4,  // E is about to become F
    21, // V is about to become W
    9,  // J is about to become K
    25  // Z is about to become A
};

/* Build global setup struct with selected rotors and starting positions */
void init_enigma(int *rotors, int *positions, int reflector) {
    g_setup = malloc(sizeof(setup));

    for (int i = 0; i < NUM_ROTORS; i++) {
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

/* Pass an integer-ized digit through a rotor in some direction */
int rotor_encode(int rotor, int input, direction_e dir) {
    char *letters = g_setup->rotors[rotor];
    if (DEBUG) printf("Letters: %s\n", letters);

    int offset = g_setup->rotor_positions[rotor];
    if (DEBUG) printf("Offset: %d\n", offset);

    int rotor_input = (input + offset) % 26;
    if (DEBUG) printf("Rotor input: %d\n", rotor_input);

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
        if (DEBUG) printf("String position: %c at %d\n", tmp_c, rotor_output);

        free(char_ptr);
    }

    if (DEBUG) printf("Rotor output: %c\n\n", int_to_char(rotor_output));

    rotor_output -= offset;
    rotor_output = (rotor_output < 0) ? rotor_output + 26 : rotor_output;

    return rotor_output;
}

/* Pass an integer-ized digit through the selected reflector */
int reflect(int input) {
    char *letters = g_setup->reflector;
    int reflector_output = letters[input];

    if (DEBUG) printf("Reflector input: %d\n", input);
    if (DEBUG) printf("Reflector output: %c\n\n", reflector_output);

    return char_to_int(reflector_output);
}

/* Determine if each rotor needs to rotate */
void rotate() {
    if (DEBUG) printf("Rotating first ring...\n");

    /* If rotating_mark[i] becomes 1 for any reason, rotor i will rotate */
    int rotating_mark[NUM_ROTORS];
    int *pos_list = g_setup->rotor_positions;

    // Always rotate first rotor
    rotating_mark[0] = 1;

    /* If middle rotor is on its notch, it will rotate */
    rotating_mark[MIDDLE_ROTOR_INDEX] = (pos_list[1] == notches[1]) ? 1 : 0;

    for (int i = 0; i < NUM_ROTORS; i++) {
        /* If a rotor is on its notch... */
        if (pos_list[i] == notches[i]) {
            /* And it is not the last rotor... */
            if (i + 1 < NUM_ROTORS) {
                /* Mark the next rotor for rotation! */
                rotating_mark[i + 1] = 1;
            }
        }

        /* Rotate each marked rotor */
        if (rotating_mark[i] == 1) {
            if (DEBUG) printf("Rotating Ring #%d...\n", i+1);
            pos_list[i] += 1;
            pos_list[i] %= 26;
        }
    }
}

/* Run a full cycle of the machine, and encode a single letter */
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

    return int_to_char(cur);
}
