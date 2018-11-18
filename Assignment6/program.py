#program to count frequency of words from a file, store it in a file and plot distribution of word length.
# function to make a dictionary of word and it's count.
def wordListToFreqDict(wordlist):
    wordfreq = [wordlist.count(p) for p in wordlist]
    return dict(zip(wordlist,wordfreq))

file = open('TheEgg.txt', 'r',encoding="utf8")
book = file.read()
l=[]
dic={}
l=book.lower().replace(';',' ').replace(',',' ').replace('.',' ').replace('”',' ').replace('“',' ').replace('?',' ').split() 
#split('\\,|\\:|\\?|\\"',line)
dic=wordListToFreqDict(l)
#print(dic)
fo = open("inter_out_new3.txt", "w")#intermediate output consisting of word and it's frequencies. 
for k, v in dic.items():
    fo.write(str(k) + ' >>> '+ str(v) + '\n\n')
fo.close()
# finding no of words for each word length
final={}
for k,v in dic.items():
    if len(k) not in final:
        final[len(k)]=v
    else:
        final[len(k)]+=v
        
'''for k,v in final.items():
    print(f'Number of {k} length words : {v}')'''
import matplotlib.pylab as plt
plt.bar(list(final.keys()),final.values())

length=[]
no=[]
percentage=[]
total=[]

for k,v in final.items():
   total.append(final[k]) 

sum=0
for i in total:
    sum+=i
print("\n")
print(f'"Total no.of words :{sum}"')

for i in total:
    percentage.append((i/sum)*100)
#print(f'"Percentage values:{percentage}"')
for k,v in final.items():
    length.append(k)
    no.append(v)
    
plt.title("Word Distribution")
plt.xlabel("Word Length")
plt.ylabel("Number of Words")
plt.bar(length,no)
plt.show()

plt.title("Word Distribution")
plt.xlabel("Word Length")
plt.ylabel("Percentage of Words")
plt.bar(length,percentage)
plt.show()