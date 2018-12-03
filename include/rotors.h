typedef struct {
    // Pointers to the three selected rotors, in order
    char *rotors[3];
    // Pointer to the selected reflector
    char *reflector;
    // Integers indicating the current position of each rotor
    int   rotor_positions[3];   
} setup;

void rotor_init(int*, int*, int);
int char_to_int(char);
char int_to_char(int);
int rotor_encode(int, int);
char enigmatize(char);
