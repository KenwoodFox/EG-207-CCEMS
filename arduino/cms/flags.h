// Flags used throughout the CMS program.

// ACK Flag, raised when command read is complete.
bool ACK = false;

// Command flag, tells us if there was a recent command.
bool COMMAND;

// Loop counter, keeps track of the number of loops run.
byte LC = 0;

// RAM coppies of EEPROM values
int warn;
int error;

// RAM coppies of other values
float temp;
int inst_flow;
int inst_lux;
int inst_uv;

// Testing and misc
int pos = 0;
