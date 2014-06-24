int  mgetn();
int  mgets(int*);

void mputn(int);
void mputs(char*);
void mputc(char);
void mputo(char*, int);
void mputu(uint *u);

int div_u10(int n);
int mul_u10(int n);
int mod_u10(int n);

uint setbuff(uint *buff, char *s);
int istrcmp(const int *a, const int *b);
void *imemcpy(void *dest, void *src, uint n);

void _read(RegSet *rs, Pipe_Ringbuffer *pipe);
void _write(RegSet *rs, Pipe_Ringbuffer *pipe);

uint mkfifo(char *pathname);
uint open(char *pathname);
