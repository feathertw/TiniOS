import sys

file_in = sys.argv[1]
file_out= sys.argv[2]
fpIn = open(file_in,"rb")
fpOut= open(file_out,"w")

p = 0
b = fpIn.read(4)
while b:
	v = (ord(b[0])<<24)
	if len(b)>=2: v = v+(ord(b[1])<<16)
	if len(b)>=3: v = v+(ord(b[2])<<8)
	if len(b)>=4: v = v+(ord(b[3]))
	s = str(bin(v))[2:]
	s = s.zfill(32)
	ss= ""
	for i in range(len(s)):
		if i%4==0 and i!=0 : ss=ss+"_"
		ss=ss+s[i]
	fpOut.write("@"+str(hex(p)[2:])+"\t"+ss+"\n")
	p = p+1
	b = fpIn.read(4)
fpIn.close()
fpOut.close()
