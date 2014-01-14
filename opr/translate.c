#include<stdio.h>
#include<string.h>

FILE *fSRC;
FILE *fDST;

void analyze(char *line);
void analyze_lmw_smw(char *line);
void pcode(char *op,char *rt,char *rs,char *s,int *b, int *n);
int main(int argc, char *argv[])
{
	char line[300];
	char *file_src=argv[1];
	char *file_dst=argv[2];

	fSRC=fopen(file_src,"r");
	fDST=fopen(file_dst,"w");
	if( (!fSRC)||(!fDST) )
	{
		printf("file cannot do");
		return 1;
	}
	while(fgets(line,300,fSRC)!=NULL)
	{
		if(strlen(line)==1) 
		{
			fprintf(fDST,"%s",line);
			continue;
		}
		analyze(line);
	}
	fclose(fSRC);
	fclose(fDST);
	return 0;
}
void analyze(char *line)
{
	char op[100];
	sscanf(line,"%s",op);
	if( (op[0]=='s'&&op[1]=='m'&&op[2]=='w')||(op[0]=='l'&&op[1]=='m'&&op[2]=='w') )
	{
		analyze_lmw_smw(line);
	}
	else
	{
		fprintf(fDST,"%s",line);
	}
}
void analyze_lmw_smw(char *line)
{
	char op[100];
	char rb[100];
	char ra[100];
	char re[100];
	char enable4[100];

	int irb;
	int ire;
	int ienable4;

	char opcode[100];
	char reg[100];
	int n;
	char s;
	int ss;
	int b;

	int i;
	sscanf(line,"%s %s %s %s %s",op,rb,ra,re,enable4);
	//printf("%s",line);
	fprintf(fDST,"\n");
	fprintf(fDST,"\t! %s %s %s %s %s\n",op,rb,ra,re,enable4);
	n=0;
	if(op[4]=='a') b=4;
	if(op[4]=='b') b=0;
	if(op[5]=='i') s='+';
	if(op[5]=='d') s='-';
	if(s=='+') ss=1;
	if(s=='-') ss=-1;
	
	for(i=0;i<strlen(ra);i++) if(ra[i]=='['||ra[i]==']') ra[i]=' ';
	sscanf(ra,"%s",ra);
	sscanf(enable4,"%d",&ienable4);

	if(op[0]=='s'&&op[1]=='m'&&op[2]=='w') strcpy(opcode,"swi");
	if(op[0]=='l'&&op[1]=='m'&&op[2]=='w') strcpy(opcode,"lwi");
	if(op[5]=='d')
	{
		if(ienable4&0x1) pcode(opcode,"$sp",ra,&s,&b,&n);
		if(ienable4&0x2) pcode(opcode,"$lp",ra,&s,&b,&n);
		if(ienable4&0x4) pcode(opcode,"$gp",ra,&s,&b,&n);
		if(ienable4&0x8) pcode(opcode,"$fp",ra,&s,&b,&n);
		if(strcmp(rb,"$sp,"))
		{
			for(i=0;i<strlen(rb);i++) if(rb[i]=='$'||rb[i]=='r'||rb[i]==',') rb[i]=' ';
			for(i=0;i<strlen(re);i++) if(re[i]=='$'||re[i]=='r'||re[i]==',') re[i]=' ';
			sscanf(rb,"%d",&irb);
			sscanf(re,"%d",&ire);
			for(i=ire;i>=irb;i--)
			{
				sprintf(reg,"$r%d",i);
				pcode(opcode,reg,ra,&s,&b,&n);
			}
		}
	}
	if(op[5]=='i')
	{
		if(strcmp(rb,"$sp,"))
		{
			for(i=0;i<strlen(rb);i++) if(rb[i]=='$'||rb[i]=='r'||rb[i]==',') rb[i]=' ';
			for(i=0;i<strlen(re);i++) if(re[i]=='$'||re[i]=='r'||re[i]==',') re[i]=' ';
			sscanf(rb,"%d",&irb);
			sscanf(re,"%d",&ire);
			for(i=irb;i<=ire;i++)
			{
				sprintf(reg,"$r%d",i);
				pcode(opcode,reg,ra,&s,&b,&n);
			}
		}
		if(ienable4&0x8) pcode(opcode,"$fp",ra,&s,&b,&n);
		if(ienable4&0x4) pcode(opcode,"$gp",ra,&s,&b,&n);
		if(ienable4&0x2) pcode(opcode,"$lp",ra,&s,&b,&n);
		if(ienable4&0x1) pcode(opcode,"$sp",ra,&s,&b,&n);
	}

	if(op[6]=='m') fprintf(fDST,"\taddi\t%s, %s, %d\n",ra,ra,ss*(4*n) );
	fprintf(fDST,"\n");
}
void pcode(char *op,char *rt,char *rs,char *s,int *b, int *n)
{
	fprintf(fDST,"\t%s\t%s, [%s%c(%d)]\n",op,rt,rs,*s,(*b)+4*(*n) );
	*n=*n+1;
}
