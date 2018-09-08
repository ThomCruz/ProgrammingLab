import re
key_list=['auto','break','case','char','const','continue','default','do','double','else','enum','extern','float','for','goto','if','int','long','register','return','short','signed','sizeof','static','struct','switch','typedef','union','unsigned','void','volatile','while']
key_Dict={}
pflag=1
sflag=1
def main():
    f=open('input.c','r')
    contents=f.readlines()
    print(contents)
    new_line=''
    it=iter(contents)
    for line in it:
        if not (line.startswith('//')):
            if line.startswith('/*'):
                new_line= next(it)
                while(new_line.find('*/')<0):
                    new_line=next(it)
                new_line=next(it)
                line=new_line
            elif line.startswith('printf("'):
                if ((line.find(');')+3)==len(line)):
                    new_line=next(it)
                    line=new_line
                elif(line.find(');')>0 and line.find(');')+1)<len(line):
                    line=line[line.find(');')+2:len(line)]
                elif(line.find('"',line.find('"')+1)<0):                    
                    new_line=next(it)
                    while(pflag):
                        if(new_line.find('"')<0):
                            new_line=next(it)
                        else:
                            if(new_line.find(');')<0):
                                new_line=next(it)
                            else:
                                if (line.find(');')+3)==len(line):
                                    new_line=next(it)
                                    line=new_line
                                    pflag=0
                                else:
                                    line=line[line.find(');')+2:len(line)]
                                    pflag=0

            elif line.startswith('scanf("'):
                if ((line.find(');')+3)==len(line)):
                    new_line=next(it)
                    line=new_line
                elif(line.find(');')>0 and line.find(');')+1)<len(line):
                    line=line[line.find(');')+2:len(line)]
                elif(line.find('"',line.find('"')+1)<0):                    
                    new_line=next(it)
                    while(sflag):
                        if(new_line.find('"')<0):
                            new_line=next(it)
                        else:
                            if(new_line.find(');')<0):
                                new_line=next(it)
                            else:
                                if (line.find(');')+3)==len(line):
                                    new_line=next(it)
                                    line=new_line
                                    sflag=0
                                else:
                                    line=line[line.find(');')+2:len(line)]
                                    sflag=0
                    
            keyword(line)    
def keyword(line):
    word_list=re.split('\\;|\\(|\\ ',line)
    print(word_list)
    for k_word in word_list:
        if k_word in key_list:
            if k_word in key_Dict:
                key_Dict[k_word]+=1
            else:
                key_Dict[k_word]=1

    f_write=open('output.txt','w+')
    for k, v in key_Dict.items():
        f_write.write(str(k) + ' > '+ str(v) + '\n')
    f_write.close()

main()
