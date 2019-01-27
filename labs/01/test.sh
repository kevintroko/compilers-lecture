import sys

# commands = ['movq     : Executed 7 times', 'movss    : Executed 3 times','addss    : Executed 2 times']
# functions = ['foo      : Located at 100000ef0 addr', 'main     : Located at 100000ef0 addr' ]
commands = []
functions = []


file = open( sys.argv[1], 'r') 

for line in file: 
    print line

#Start
print ('Hi, this is the output of the analysis of '+sys.argv[0])
print('\tYou have 7 kind of instructions in this object file:')
for command in commands:
    print('\t \t'+command)
print('\tYou have 2 functions:')
for function in functions:
    print('\t \t'+function)
