int  mgetn();
int  mgets(int*);

void mputn(int);
void mputs(char*);
void mputc(char);
void mputo(char*, int);

int div_u10(int n);
int mul_u10(int n);
int mod_u10(int n);

void *imemcpy(void *dest, void *src, uint n);

void _read(RegSet *rs, Pipe_Ringbuffer *pipe);
void _write(RegSet *rs, Pipe_Ringbuffer *pipe);

