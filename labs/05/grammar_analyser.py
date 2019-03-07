# Kevin Oswaldo Cabrera Navarro
# A01227157
# LAB 05 - Compilers Lecute
from collections import deque

with open("grammar.txt", "r") as f:
    data = f.readlines()

def getNonTerminals():
    arr = []
    for line in data:
        token = line.split()
        arr.append(token[0])
    return arr    

nonTerminals = getNonTerminals()

def getNonEnding():
    for line in data:
        token = line.split()
        while (True):
            x = token.pop()
            if(x == '-' and not x.isupper()):
                break
            else:
                if(x in nonTerminals):
                    nonTerminals.remove(x)
    nonTerminals.remove(nonTerminals[0])
    return nonTerminals
                
trash = (getNonEnding())
print(trash)

def writeNew(xy):
    fr = open("grammar.txt", "r")
    fw = open("grammar.txt", "w")
    for line in data:
        token = line.split()
        if(len(trash)>0):
            if(trash[xy] not in line):
                fw.write(line)
            else:
                data.remove(line)

for x in range (0, len(trash)):
    writeNew(x)

f.close()
