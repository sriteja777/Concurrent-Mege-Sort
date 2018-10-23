#include<stdio.h>

void merge (int a[], int st, int en)
{
	int left[100001], right[100001];
	int  i, j, mid=(st +en)/2, k, ll, rl;
	ll=mid-st+1;
	rl=en-mid;
	for (i=st,j=0;i<=mid;i++,j++)
		left[j]=a[i];
	for (i=mid+1,k=0;i<=en;i++,k++)
		right[k]=a[i];
	i=st;
	j=0;
	k=0;

	while(j<ll && k<rl)
	{
		if (left[j]>right[k]) a[i]=right[k++];
		else a[i]=left[j++];
		i++;
	}

	while(k<rl) a[i++]=right[k++];
	while(j<ll) a[i++]=left[j++];
}

void selection_sort(int a[], int l, int r) {
	int n=r-l+1;
	int min;
	int temp;
	for (int i=l;i<=r;i++) {
		min = i;
		for (int j=i+1;j<=r;j++) if (a[j] < a[min]) min = j;
		temp = a[min];
		a[min] = a[i];
		a[i] = temp;
	}

	// for (int i=0;i<n;i++) {
	// 	printf("%d\n",a[i]);
	// }
	// printf("\n");
}

void merge_sort(int a[], int st, int en)
{
	if (en-st+1 <=5) {
		selection_sort(a, st, en);
		return;
	}
	// if (st==en) return;
	int mi=(st+en)/2;
	merge_sort(a, st, mi);
	merge_sort(a, mi+1, en);
	merge(a, st, en);
}

int main () 
{	
	int i, n, a[100002];
	scanf("%d",&n);
	for (i=0;i<n;i++)
		scanf("%d",&a[i]);
	merge_sort(a, 0, n-1);
	for (i=0;i<n;i++)
		printf("%d ",a[i]);
}

