import sys

file_defop = sys.argv[1]
file_list  = sys.argv[2]

defop=[]
fpIn = open(file_defop,"r")
line = fpIn.readline()
while line :
	if (not "TY" in line) and ("define" in line):
		s = line.split()
		if s[1]=="JJ":      s="J"
		elif s[1]=="SWIBI": s="SWI.BI"
		elif s[1]=="LWIBI": s="LWI.BI"
		else:	       	    s=s[1]
		defop.append(s)
	line = fpIn.readline()
if "JR" in defop: defop.append("RET")
fpIn.close()

r=0
fpIn = open(file_list,"r")
line = fpIn.readline()
sys.stdout.write("\033[93m")
while line :
	if ".data" in line: break
	s = line.split()
	if (len(s)>=6) and ( ":" in s[0]):
		op=s[5].upper()
		if not op in defop: 
			print "THERE ARE NO OPCODE "+op
			r=1
	line = fpIn.readline()
sys.stdout.write("\033[0m")
fpIn.close()
exit(r)
