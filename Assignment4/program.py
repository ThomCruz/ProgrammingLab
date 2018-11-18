#program to eliminate left recursion.
#main function
def remove_left_recursion(grammar):
    hash_map = {}
    temp=0 #counts no fo variables
    count = 0 #for new production variable name generation
    for x in grammar.keys():
        hash_map[x] = temp
        temp += 1
    temp_dict = {}
    for x in grammar.keys():
        productions = grammar[x]
        length = len(productions)
        to_be_added = []
        to_be_removed = []
        for i in range(length):
            for j in range(0,26):
                ch = chr(65+j)
                if ch in productions[i]:
                    if hash_map[x] > hash_map[ch]:
                        word = productions[i]
                        to_be_removed.append(productions[i])

                        temp_list = grammar[ch]
                        for k in range(len(temp_list)):
                            to_be_added.append(word.replace(ch,temp_list[k]))

        productions = [l for l in productions if l not in to_be_removed]
        productions += to_be_added
        grammar[x] = productions
        var = []
        const = []
        flag = False
        length = len(productions)
        for i in range(length):
            if productions[i][0] == x:
                flag = True
                var.append(productions[i][1:])
            else:
                const.append(productions[i])

        if flag==True:
            while(chr(count+65) in grammar.keys()):
                count += 1
            ch = chr(65+count)
            new_prod = []
            for l in range(len(const)):
                new_prod.append(const[l]+ch)
            productions = new_prod
            new_prod2 = []
            for l in range(len(var)):
                new_prod2.append(var[l]+ch)
            new_prod2.append("^")
            temp_dict[ch] = new_prod2
            grammar[x] = productions
    for x in temp_dict.keys():
        grammar[x] = temp_dict[x]

    return grammar

# input file processing 
from collections import OrderedDict
fo = open("grammar.txt","r")
lines = fo.readlines()
grammar = OrderedDict()
for x in lines:
    x = x.strip("\t")
    x = x.strip("\n")
    x = x.strip(" ")
    one,two = x.split(" -> ")
    two_list = two.split("|")
    if one in grammar.keys():
        grammar[one] = grammar[one].extend(two_list)
    else:
        grammar[one] = two_list
print(grammar) #output after arranging grammer sequentially.

grammar = remove_left_recursion(grammar)
print(grammar)

#writing to the file 

f = open("output.txt","w")
for i in grammar.keys():
    string = i + " -> "
    temp = grammar[i]
    for j in range(0,len(temp)-1):
        string += temp[j] +" | "
    string += temp[len(temp)-1] +"\n"
    #print(string)
    f.write(string)    
f.close()
