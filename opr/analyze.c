#include<stdio.h>
#include<string.h>

FILE *fLIST;
FILE *fIMEM;
FILE *fDMEM;

int GO=1;
void analyze(char *line);
void pprog(FILE *file, int pp, char *p, char *v1, char *v2, char *v3, char *v4, char *c1, char *c2, char *c3);
void pcode(FILE *file, char *v1, char *v2, char *v3, char *v4);
void pascii(FILE *file, char *c1, char *c2, char *c3, char *c4);
void binary(char c, char *value);
int main(int argc, char *argv[])
{
	char line[300];
	char *file_list=argv[1];
	char *file_imem=argv[2];
	char *file_dmem=argv[3];

	fLIST=fopen(file_list,"r");
	fIMEM=fopen(file_imem,"w");
	fDMEM=fopen(file_dmem,"w");
	if( (!fLIST)||(!fIMEM)||(!fDMEM) )
	{
		printf("file cannot do");
		return 1;
	}

	while(fgets(line,300,fLIST)!=NULL && GO)
	{
		if(strlen(line)==1) continue;
		analyze(line);
		//printf("%s",line);
	}
	fclose(fLIST);
	fclose(fIMEM);
	fclose(fDMEM);
	return 0;
}
void analyze(char *line)
{
	char p[100];
	char v1[100];
	char v2[100];
	char v3[100];
	char v4[100];
	char c1[100];
	char c2[100];
	char c3[100];

	int pp;

	sscanf(line," %s %s %s %s %s %s %s %s ",p,v1,v2,v3,v4,c1,c2,c3);

	if(!strcmp("<.comment>:",v1)) GO=0;
	if(p[(strlen(p)-1)]==':' && strcmp("file",v1) )
	{
		//printf("%s",line);
		sscanf(p,"%x",&pp);
		if(0x00000000<=pp&&pp<0x01000000)
		{
			//printf("IM\n");
			pprog(fIMEM,pp,p,v1,v2,v3,v4,c1,c2,c3);
		}
		else if(0x01000000<=pp&&pp<0x02000000)
		{
			//printf("DM\n");
			pprog(fDMEM,pp,p,v1,v2,v3,v4,c1,c2,c3);
		}
	}

}
void pprog(FILE *file, int pp, char *p, char *v1, char *v2, char *v3, char *v4, char *c1, char *c2, char *c3)
{
	pp=pp&0x00FFFFFF;
	fprintf(file,"@%x\t",pp/4);
	if(file==fIMEM) pcode(file,v1,v2,v3,v4);
	if(file==fDMEM) pcode(file,v4,v3,v2,v1);
	if(file==fIMEM) fprintf(file,"\t// %s %s %s",p,c1,c2);
	if(file==fDMEM) fprintf(file,"\t// %s %s %s %s %s ",p,v1,v2,v3,v4);
	if(file==fDMEM) pascii(file,v1,v2,v3,v4);
	fprintf(file,"\n");
}
void pcode(FILE *file, char *v1, char *v2, char *v3, char *v4)
{
	int i;
	char value[32];
	char *v=value;
	binary(v1[0],v); v=v+4;
	binary(v1[1],v); v=v+4;
	binary(v2[0],v); v=v+4;
	binary(v2[1],v); v=v+4;
	binary(v3[0],v); v=v+4;
	binary(v3[1],v); v=v+4;
	binary(v4[0],v); v=v+4;
	binary(v4[1],v); v=v+4;
	for(i=0;i<32;i++)
	{
		fprintf(file,"%c",value[i]);
		if( (file==fIMEM)&&(i==0||i==6||i==11||i==16||i==21||i==26) ) fprintf(file,"_");
		if( (file==fDMEM)&&(i==3||i==7||i==11||i==15||i==19||i==23||i==27) ) fprintf(file,"_");
	}
}
void pascii(FILE *file, char *c1, char *c2, char *c3, char *c4)
{
	int c;
	fprintf(file,"|");
	sscanf(c1,"%x",&c); if(0x20<=c&&c<=0x7E) fprintf(file,"%c",c); else fprintf(file,".");
	sscanf(c2,"%x",&c); if(0x20<=c&&c<=0x7E) fprintf(file,"%c",c); else fprintf(file,".");
	sscanf(c3,"%x",&c); if(0x20<=c&&c<=0x7E) fprintf(file,"%c",c); else fprintf(file,".");
	sscanf(c4,"%x",&c); if(0x20<=c&&c<=0x7E) fprintf(file,"%c",c); else fprintf(file,".");
	fprintf(file,"|");
}
void binary(char c, char *value)
{
	switch(c)
	{
		case '0': value[0]='0'; value[1]='0'; value[2]='0'; value[3]='0'; break;
		case '1': value[0]='0'; value[1]='0'; value[2]='0'; value[3]='1'; break;
		case '2': value[0]='0'; value[1]='0'; value[2]='1'; value[3]='0'; break;
		case '3': value[0]='0'; value[1]='0'; value[2]='1'; value[3]='1'; break;
		case '4': value[0]='0'; value[1]='1'; value[2]='0'; value[3]='0'; break;
		case '5': value[0]='0'; value[1]='1'; value[2]='0'; value[3]='1'; break;
		case '6': value[0]='0'; value[1]='1'; value[2]='1'; value[3]='0'; break;
		case '7': value[0]='0'; value[1]='1'; value[2]='1'; value[3]='1'; break;
		case '8': value[0]='1'; value[1]='0'; value[2]='0'; value[3]='0'; break;
		case '9': value[0]='1'; value[1]='0'; value[2]='0'; value[3]='1'; break;
		case 'a': value[0]='1'; value[1]='0'; value[2]='1'; value[3]='0'; break;
		case 'b': value[0]='1'; value[1]='0'; value[2]='1'; value[3]='1'; break;
		case 'c': value[0]='1'; value[1]='1'; value[2]='0'; value[3]='0'; break;
		case 'd': value[0]='1'; value[1]='1'; value[2]='0'; value[3]='1'; break;
		case 'e': value[0]='1'; value[1]='1'; value[2]='1'; value[3]='0'; break;
		case 'f': value[0]='1'; value[1]='1'; value[2]='1'; value[3]='1'; break;
		default : value[0]='?'; value[1]='?'; value[2]='?'; value[3]='?'; break;
	}
}
