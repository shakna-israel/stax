# StaX

This is the reference implementation for StaX, a programming language resembling a [Turing Tarpit](https://en.wikipedia.org/wiki/Turing_tarpit).

The aim is for a bytecode interpreter of StaX to be used as the target language for several toy languages I'm developing.

This reference implementation is far too slow for that, but serves to demonstrate the inner workings of StaX.

---

# Usage

Currently, StaX can only be used as a library, running it simply produces a Hello, World.

```
import StaX

c = StaX.Controller()
program = """
push:H
push:e
push:l
push:l
push:o
push:,
push:_s
push:W
push:o
push:r
push:l
push:d
push:!
rev
out
"""
StaX.parse(c, program)
```

# Language

StaX is a stack-based language.

The user has access to 10 LIFO (Last-In-First-Out) stacks, and can cycle between them using the ```inc``` and ```dec``` commands.

```push``` can be used to push an item onto the stack.

It takes a single character, that can be a number, or normal character, which will get cast to an integer.

If the user supplies more than a single character, StaX will crash, with an error message.

To call push, write ```push``` followed by a colon, ```:```, followed by the character to push to the stack.

```drop``` can be used to remove an item from the top of the stack.

```dup``` can be used to copy the top item of the stack, and push the copy.

e.g. If the stack is [0, 1, 2] and we called ```dup```, the stack would become [0, 0, 1, 2]

```swap``` changes the positions of the top two items on the stack.

e.g. If the stack is [0, 1, 2] amd we ca;;ed ```swap```, the stack would become [1, 0, 2]

```rev``` reverses the entire stack.

```out``` casts each integer on the stack to a character, and then writes it to stdout.

```new``` reads a single keystroke from stdin, and treats it as if we tried to ```push``` the character.

```add``` drops the first two items from the stack, and pushes their sum to the top of the stack.

```sub``` drops the first two items from the stack, and pushes their difference to the top of the stack.

```mul``` drops the first two items from the stack, and pushes their product to the top of the stack.

```div``` drops the first two items from the stack, and pushes their quotient to the top of the stack.

```goto``` takes a label parameter, and jumps to that label in the execution loop.

A label is any sequence of characters beginning with a colon, ```:```, for example: ```:main```.

The goto to use to jump to the label, ```:main```, would be ```goto:main```.

**Note:** StaX needs a conditional construct. At this point in time, it doesn't exist, as the least surprising behaviours seem difficult to reason about.

# License

Unless otherwise mentioned within a file, all contents are licensed according to the contents of [LICENSE.md](LICENSE.md)
