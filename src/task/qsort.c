#define swap(T,A,B) (T)=(A); (A)=(B); (B)=(T);
void qsort(int *array, int left, int right);
void qsort(int *array, int left, int right)
{
	if(left>right) return;
	int i;
	int j;
	int pivot;
	int t;

	i=left+1;
	j=right;
	pivot=array[left];

	while(1)
	{
		while(i<=right)
		{
			if(array[i]>pivot) break;
			i=i+1;
		}
		while(j>left)
		{
			if(array[j]<pivot) break;
			j=j-1;
		}
		if(i>j) break;
		swap(t,array[i],array[j]);
	}
	swap(t,array[left],array[j]);
	qsort(array,left,j-1);
	qsort(array,j+1,right);
}
