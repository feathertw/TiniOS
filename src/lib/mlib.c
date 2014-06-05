void *imemcpy(void *dest, void *src, unsigned int n)
{
	unsigned int *d = dest;
	const unsigned int *s = src;
	unsigned int i;
	for(i=0;i<n;i++)
	{
		d[i]=s[i];
	}
}
