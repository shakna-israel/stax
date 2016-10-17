import sys
import getch

class Controller(object):
    def __init__(self):
        self.stacks = [Stack() for i in range(0, 10)]
        self.stack_pointer = 0

    def inc(self):
        self.stack_pointer += 1
        if self.stack_pointer == 10:
            self.stack_pointer = 0

    def dec(self):
        self.stack_pointer -= 1
        if self.stack_pointer == -1:
            self.stack_pointer = 9

    def push(self, obj):
        self.stacks[self.stack_pointer].push(obj)

    def drop(self):
        self.stacks[self.stack_pointer].drop()

    def dup(self):
        self.stacks[self.stack_pointer].dup()

    def swap(self):
        self.stacks[self.stack_pointer].swap()

    def rev(self):
        self.stacks[self.stack_pointer].rev()

    def out(self):
        self.stacks[self.stack_pointer].out()

    def new(self):
        self.stacks[self.stack_pointer].new()

    def add(self):
        self.stacks[self.stack_pointer].add()

    def sub(self):
        self.stacks[self.stack_pointer].sub()

    def mul(self):
        self.stacks[self.stack_pointer].mul()

    def div(self):
        self.stacks[self.stack_pointer].div()

class Stack(object):
    def __init__(self):
        self.contents = []

    def push(self, obj):
        self.contents.insert(0, obj)

    def drop(self):
        self.contents.pop(0)

    def dup(self):
        self.contents.insert(0, self.contents[0])

    def swap(self):
        newList = []
        newList.insert(0, self.contents[1])
        newList.insert(1, self.contents[0])
        self.contents = newList + self.contents[2:]

    def rev(self):
        self.contents.reverse()

    def out(self):
        for each in self.contents:
            sys.stdout.write(chr(each))

    def new(self):
        self.push(ord(getch.getch()))

    def add(self):
        a = self.drop()
        b = self.drop()
        self.push(a + b)

    def sub(self):
        a = self.drop()
        b = self.drop()
        self.push(a - b)

    def mul(self):
        a = self.drop()
        b = self.drop()
        self.push(a * b)

    def div(self):
        a = self.drop()
        b = self.drop()
        try:
            result = a / b
        except ZeroDivisionError:
            result = 0
        self.push(result)

def parse(controllerObj, stringer):
    stringer = "{0} ".format(stringer)
    stringer = stringer.replace("\n", " ")
    commands = stringer.split(" ")
    labels = {}
    # find all goto labels before we parse!
    # Makes it easier to jump to the label
    for iter, op in enumerate(commands):
        if op:
            if op[0] == ":":
                labels[op[1:]] = iter
    # We don't use a proper for loop here,
    # so we can use gotos!
    iter = 0
    while iter + 1 < len(commands):
        # Let's do a goto first:
        # syntax: goto:name
        if commands[iter][:4] == "goto":
            iter = labels[commands[iter][5:]]
        # Let's push data to the stack!
        # If data isn't an int, we try to convert it,
        # if we can't, syntax error!
        # syntax: push:data
        elif commands[iter][:4] == "push":
            if commands[iter][5:] == "_s":
                controllerObj.push(ord(" "))
            elif commands[iter][5:] == "_n":
                controllerObj.push(ord("\n"))
            elif commands[iter][5:] == "_t":
                controllerObj.push(ord("\t"))
            else:
                try:
                    controllerObj.push(int(commands[iter][5:]))
                except ValueError:
                    controllerObj.push(ord(commands[iter][5:]))
                except TypeError:
                    sys.sterr.write("Error: Cannot push!\n\n{0}\n\nPerhaps at symbol {1}.".format(commands[iter], iter + 1))
                    exit(1)
        # Let's select the next stack!
        # syntax: inc
        elif commands[iter] == "inc":
            controllerObj.inc()
        # Let's select the previous stack!
        # syntax: dec
        elif commands[iter] == "dec":
            controllerObj.dec()
        # Let's drop the first item from the stack
        # syntax: drop
        elif commands[iter] == "drop":
            controllerObj.drop()
        # Let's copy the top of the stack, and push it
        # syntax: dup
        elif commands[iter] == "dup":
            controllerObj.dup()
        # Let's swap the position of the top two items
        # syntax: swap
        elif commands[iter] == "swap":
            controllerObj.swap()
        # Let's reverse the entire stack
        # syntax: rev
        elif commands[iter] == "rev":
            controllerObj.rev()
        # Let's copy the entire stack to stdout, converting ints to chars
        # syntax: out
        elif commands[iter] == "out":
            controllerObj.out()
        # Let's take a single char from stdin, and cast to an int
        # syntax: new
        elif commands[iter] == "new":
            controllerObj.new()
        # Let's replace the top two items with their sum
        # syntax: add
        elif commands[iter] == "add":
            controllerObj.add()
        # Let's replace the top two items with their difference
        # syntax: sub
        elif commands[iter] == "sub":
            controllerObj.sub()
        # Let's replace the top two items with their product
        # syntax: mul
        elif commands[iter] == "mul":
            controllerObj.mul()
        # Let's replace the top two items with their quotient
        # Dividing by zero results with a 0
        # syntax: div
        elif commands[iter] == "div":
            controllerObj.div()
        iter += 1

if __name__ == "__main__":
    c = Controller()
    program = """push:H
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
out"""
    parse(c, program)
