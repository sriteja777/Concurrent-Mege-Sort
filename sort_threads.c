#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
typedef struct args
{
	int *a;
	int l;
	int r;
} args;

void merge (int a[], int st, int en)
{
	int left[100001], right[100001];
	int i, j, mid=(st +en)/2, k, ll, rl;
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

// void merge_sort(int a[], int st, int en)
void* merge_sort(void *arg)
{	int st = ((args*)arg)->l, en = ((args*)arg)->r;
	if (en-st+1 <=5) {
		selection_sort(((args*)arg)->a, st, en);
		return 0;
	}
	// if (st==en) return 0;
	args str, str_1;
	pthread_t tid_l, tid_r;
	str.a = ((args*)arg)->a;
	str_1.a = ((args*)arg)->a;
	int mi=(st+en)/2;
	str.l = st;
	str.r = mi;
	str_1.l = mi+1;
	str_1.r = en; 
	int stat = pthread_create(&tid_l,NULL, merge_sort, (void*)&str);
	if (stat) {
		printf("Thread creation failed\n");
	}
	// merge_sort(&str);
	stat = pthread_create(&tid_r,NULL, merge_sort, (void*)&str_1);
	if (stat) printf("Thread creation failed.\n");
	pthread_join(tid_l, NULL);
	pthread_join(tid_r, NULL);
	// merge_sort(&str);
	merge(str.a, st, en);
}

int main () 
{	
	args *arg;
	arg = (args*)malloc(sizeof(args));
	// int i, n, a[100002];
	int n;
	scanf("%d",&n);
	arg->r = n-1;
	arg->l = 0;
	arg->a = (int*)malloc(sizeof(int)*n);
	for (int i=0;i<n;i++)
		scanf("%d",&arg->a[i]);

	merge_sort((void*)arg);
	for (int i=0;i<n;i++)
		printf("%d ",arg->a[i]);
	printf("\n");
}

