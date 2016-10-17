import StaX

c = StaX.Controller()
program = """
push:H
push:i
push:!
push:_n
rev
:loop
out
goto:loop
"""
StaX.parse(c, program)
