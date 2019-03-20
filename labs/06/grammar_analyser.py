# Kevin Oswaldo Cabrera Navarro
# A01227157
# LAB 05 - Compilers Lecute

bad_words = ['comment']

with open('tokens.out') as oldfile, open('tokens.txt', 'w') as newfile:
    for line in oldfile:
        if not any(bad_word in line for bad_word in bad_words):
            newfile.write(line)
