// Macro to remove boilerplate, as all math functions are pretty much identical.
#define math(__name, __op) void __name() { int a = stack[stack_ptr]; stack_next(); int b = stack[stack_ptr]; stack[stack_ptr] = a __op b; stack_previous(); }
#define STACK_SIZE 400

int program_ptr = 0;
int stack[STACK_SIZE]; // All the memory we have!
int stack_ptr = STACK_SIZE + 1;
int stack_dir = 0;

//
void stack_next() {
  if (stack_dir == 0) {
    stack_ptr--;
  } else {
    stack_ptr++;
  }
  return;
}

//
void stack_previous() {
  if (stack_dir == 0) {
    stack_ptr--;
  } else {
    stack_ptr++;
  }
  return;
}

//goto
void _goto(int i) {
  program_ptr = i;
  return;
}

//:label
// Need to build some sort of array/s here

//div
math(div, / )

//mul
math(mul, *)

//sub
math(sub, -)

//add
math(add, +)

//new

//out
void out() {
  if (stack_dir == 0) {
    for (int i = 0; i < STACK_SIZE; i++) {
      if (stack[i] != -1) {
        Serial.print((char)stack[i]);
      }
    }
  } else {
    for (int i = STACK_SIZE; i > 0; i--) {
      if (stack[i] != -1) {
        Serial.print((char)stack[i]);
      }
    }
  }
}

//rev
void rev() {
  stack_dir = 1;
}

//swap
void swap() {
  int a = stack[stack_ptr];
  stack_previous();
  int b = stack[stack_ptr];
}

//dup
void dup() {
  int a = stack[stack_ptr];
  stack_next();
  stack[stack_ptr] = a;
  return;
}

//drop
void drop() {
  stack[stack_ptr] = -1;
  stack_next();
  return;
}

//push
void push(int a) {
  stack_next();
  stack[stack_ptr] = a;
  return;
}

void setup() {
  //Initialise the stack
  for (int i = 0; i < STACK_SIZE; i ++) {
    stack[i] = -1;
  }
  for (int i = 20; i > 0; i--) {
    push(65);
  }
  // Enable serial connections
  Serial.begin(9600);
  Serial.println("Welcome");
}

void loop() {
  out();
  Serial.println("\nLoop fin.");
}
