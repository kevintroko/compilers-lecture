import sys
import re

def findCommand(cmd, l):
    if(l!=-1):
        commands[cmd]=commands.get(cmd)+1        

functions = []
position = []
flag = False
index=0
commandList = ['movq','movss','addss','mulss', 'popq', 'retq','pushq','subq','callq','movl']
commands = {commandList[0]:0,commandList[1]:0,commandList[2]:0,commandList[3]:0,commandList[4]:0,commandList[5]:0,commandList[6]:0,commandList[7]:0,commandList[8]:0,commandList[9]:0}

file = open( sys.argv[1], 'r') 

for line in file: 
    if(flag):
        position.append(line[0:8])
        flag=False

    f = re.match('_\w',line)
    if (f!=None and not (re.match('__stub',line)) and not(re.match('__text',line))):
        f = (line)
        functions.append(line)
        flag = True
 
    for cmd in commandList:
        l = line.find(cmd)
        findCommand(cmd,l)

print('Hi, this is the output of the analysis of {:s}'.format(sys.argv[0]))
print('\tYou have {:d} kind of instructions in this object file:'.format(len(commandList)))

for key,val in commands.items():
    print('\t\t{:s} executed:\t{:d} times'.format(key, val))

print('\tYou have {:d} functions:'.format(len(functions)))
for function in functions:
    print('\t\t{:s} located at {:s}'.format(function[:5], position[index]))
    index+=1