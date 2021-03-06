// Flags and variables used throughout the CMS program.

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
float inst_temp;
float inst_humidity;
float inst_flow;
float inst_lux;
int inst_uv;

// Testing and misc
byte pos = 0;

// Timeout values, values incremented to count timeout.
byte door_ajar_wait = 80;   // How many cycles to count to before closing the door.
byte door_ajar_timeout = 0; // Counts up to 255 for as long as the door is ajar.

// Deleteme
byte test1;
byte test2;
byte test3;

bool streamerMode;
