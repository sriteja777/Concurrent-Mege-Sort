#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/ipc.h>

key_t key = IPC_PRIVATE;

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
	pid_t pid, pid_l, pid_r, pid_c;
	// if(st==en) return;
	int mi=(st+en)/2;
	int stat, stat_c;
	pid = fork();
	if (pid==-1) {
		printf("Fork failed\n");
		exit(1);
	}

	else if (pid==0) {
		pid_c = fork();
		if (pid_c==-1) {
			printf("Fork failed\n");
			exit(1);
		}
		else if (pid_c==0) {
			merge_sort(a, st, mi);
			exit(0);
		}
		else {
			merge_sort(a, mi+1, en);
			waitpid(pid_c, &stat, WUNTRACED);
			exit(0);
		}
	}
	else {
		
		waitpid(pid, &stat, WUNTRACED);
		merge(a, st, en);
	}
	
		
}


int main() {
	int shmid, *sh_arr, n;
	scanf("%d",&n);
	shmid = shmget(key, sizeof(int)*n, IPC_CREAT| 0666);
	if(shmid == -1) {
		perror("Shmget failed");
		exit(1);
	}
	sh_arr = shmat(shmid, 0, 0);
	if(sh_arr == (void *)-1) {
		perror("Shmat failed");
		exit(1);
	}
	for (int i=0;i<n;i++) 
		scanf("%d",&sh_arr[i]);
	merge_sort(sh_arr, 0, n-1);

	for(int i = 0; i < n; i++) 
		printf("%d ", sh_arr[i]);
	printf("\n");


}