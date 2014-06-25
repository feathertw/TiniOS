############################################################
# Note that to protect base register
#	lmw: update register value after load
#	smw: update register value before store
#
############################################################
import sys

def pri(op,rt,rb,n):
	fpOut.write("\t"+op+"\t"+rt+", ["+rb+"+("+str(n*4)+")]\n")
	return n+1

file_in = sys.argv[1]
file_out= sys.argv[2]
fpIn = open(file_in,"r")
fpOut= open(file_out,"w")

line = fpIn.readline()
while line:
	s = line.split()
	if(len(s)>=1 and len(s[0]) >3) : op= s[0][0:3]
	else		 	       : op=""
	if (op == "lmw") or (op == "smw"): 

		cmline="\n"+line[:1]+"!"+line[1:8]+" "+line[9:]
		fpOut.write(cmline)

		if "$sp" in s[1] : rf= 0
		else 		 : rf= int(s[1][2:-1])
		if "$sp" in s[3] : rt= -1
		else 		 : rt= int(s[3][2:-1])
		rb= s[2][1:-2]
		e4= int(s[4])

		if   ( len(s[0])>=7 and s[0][6]=="m") : update=1
		else		 		      : update=0

		if   s[0][4]=="b": base=0
		elif s[0][4]=="a": base=1
		if   s[0][5]=="i": signed= 1
		elif s[0][5]=="d": signed=-1

		width = 0
		width = (rt-rf+1)+str(bin(e4)).count("1")
		width = signed*width

		if   op=="lmw": n = base
		elif op=="smw": n = (base^1)+width*(update^1)
		if   op=="lmw": oop = "lwi"
		elif op=="smw": oop = "swi"

		if (op=="smw" and update) :
			fpOut.write("\t"+"addi"+"\t"+rb+", "+rb+", "+str(width*4)+"\n")

		for i in range(rf,rt+1):
			n = pri(oop,"$r"+str(i),rb,n)
		if e4&8 : n = pri(oop,"$fp",rb,n)
		if e4&4 : n = pri(oop,"$gp",rb,n)
		if e4&2 : n = pri(oop,"$lp",rb,n)
		if e4&1 : n = pri(oop,"$sp",rb,n)

		if (op=="lmw" and update) :
			fpOut.write("\t"+"addi"+"\t"+rb+", "+rb+", "+str(width*4)+"\n")

		fpOut.write("\n")
	else:
		fpOut.write(line)
	line = fpIn.readline()

fpIn.close()
fpOut.close()
