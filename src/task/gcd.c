int gcd(int m, int n)
{
	while(1)
	{
		if(m>n) m=m-n;
		else	n=n-m;
		if(m==0) return n;
		if(n==0) return m;
	}
}
