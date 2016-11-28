#define STACK_SIZE 200
#define FORWARD 0
#define REVERSE -1

char serialdata[120];
int program[120];
int program_ptr = 0;
int stack[STACK_SIZE];
int stack_ptr = STACK_SIZE + 1;
int stack_dir = FORWARD;

enum OPS {
  PUSH,
  DROP,
  DUP,
  SWAP,
  REV,
  OUT,
  NEW,
  ADD,
  SUB,
  MUL,
  DIV,
  GOTO
};

void clear_data() {
  memset(serialdata, 0, sizeof(serialdata));
}

int data_exists() {
  if (serialdata[0] != 0) {
    return 0;
  } else {
    return 1;
  }
}

// Move along the stack
// stack_move
void smv(int dir) {
  if (dir == FORWARD) {
    stack_ptr--;
  } else {
    stack_ptr++;
  }
  if (stack_ptr > STACK_SIZE + 1) {
    stack_ptr = stack_ptr - (STACK_SIZE + 2);
    return;
  }
  if (stack_ptr < 0) {
    stack_ptr = stack_ptr + (STACK_SIZE + 2);
    return;
  }
}

// Execute some code
// stack_execute
void sex(int n) {
  switch ((OPS)n) {
    // TODO: Push onto the top of the stack
    // Needs to read an argument...
    case (PUSH): {
        Serial.println(F("Not Yet Implemented."));
        break;
      }
    // Drop the top of the stack
    case (DROP): {
        stack[stack_ptr] = -1;
        smv(REVERSE);
        break;
      }
    // Copy the top of the stack and push onto the stack
    case (DUP): {
        int t = stack[stack_ptr];
        smv(FORWARD);
        stack[stack_ptr] = t;
        break;
      }
    // TODO: Swaps the top two values of the stack
    case (SWAP): {
        Serial.println(F("Not Yet Implemented."));
        break;
      }
    // TODO: Fakes flipping the stack
    case (REV): {
        Serial.println(F("Not Yet Implemented."));
        break;
      }
    // TODO: Prints the stack to stdout
    case (OUT): {
        Serial.println(F("Not Yet Implemented."));
        break;
      }
    // TODO: Pushes a character via Serial input
    case (NEW): {
        Serial.println(F("Not Yet Implemented."));
        break;
      }
    // TODO: drops the first two items from the stack, and pushes their sum to the top of the stack.
    case (ADD): {
        Serial.println(F("Not Yet Implemented."));
        break;
      }
    // TODO: drops the first two items from the stack, and pushes their sum to the top of the stack.
    case (SUB): {
        Serial.println(F("Not Yet Implemented."));
        break;
      }
    // TODO: drops the first two items from the stack, and pushes their product to the top of the stack.
    case (MUL): {
        Serial.println(F("Not Yet Implemented."));
        break;
      }
    // TODO: drops the first two items from the stack, and pushes their quotient to the top of the stack.
    case (DIV): {
        Serial.println(F("Not Yet Implemented."));
        break;
      }
    // TODO: takes a label parameter, and jumps to that label in the execution loop.
    // Needs to read an argument...
    case (GOTO): {
        Serial.println(F("Not Yet Implemented."));
        break;
      }
    default: {
        Serial.print(F("Failed: "));
        Serial.println(n);
      }
  }
}

void setup() {
  for (int i = 0; i < STACK_SIZE; i++) {
    stack[i] = -1;
  }
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect.
  }
}

void loop() {
  Serial.setTimeout(50); // Don't block the loop waiting for input!
  Serial.readBytesUntil(10, serialdata, 80); // 10 == \lf
  if (data_exists() == 0) {
    Serial.println(serialdata);
    for (int i = 0; i < strlen(serialdata); i++) {
      sex(serialdata[i] - '0');
    }
    clear_data();
  } else {

  }
}
