#Python equivalent of the input_read.cpp
#(Actually this code is more robust, BUT ANYWAY)

class DM_Input:
    def __init__(self,path):
        infile = open(path,'r')
        self.keyval = {}
        for line in infile:
            line = line.strip(' \t\n')
            if len(line) == 0:
                continue
            line = line.split('#')[0].strip(' \t\n')
            if len(line) == 0:
                continue
            key,val = line.split('=')
            key,val = key.strip(' '),val.strip(' ')
            self.keyval[key] = val
        infile.close()
        
    def get(self,conv,name):
        return conv(self.keyval[name])