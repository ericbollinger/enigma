#define DEBUG 0

typedef struct {
    // Pointers to the three selected rotors, in order
    char *rotors[3];
    // Pointer to the selected reflector
    char *reflector;
    // Integers indicating the current position of each rotor
    int   rotor_positions[3];   
} setup;

typedef enum direction { FORWARD, BACKWARD } direction_e;

void init_enigma(int*, int*, int);
void teardown_enigma();
int char_to_int(char);
char int_to_char(int);
int rotor_encode(int, int, direction_e);
int reflect(int);
void rotate();
char enigmatize(char);
