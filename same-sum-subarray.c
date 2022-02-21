#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void Merge(int * arr, int l, int m, int r) 
{ 
	int i, j, k; 
	int n1 = m - l + 1; 
	int n2 = r - m; 

	int L[n1], R[n2]; 

	for (i = 0; i < n1; i++) 
		L[i] = arr[l + i]; 
	for (j = 0; j < n2; j++) 
		R[j] = arr[m + 1+ j]; 

	i = 0;
	j = 0; 
	k = l; 
	while (i < n1 && j < n2) 
	{ 
		if (L[i] <= R[j]) arr[k++] = L[i++]; 
		else arr[k++] = R[j++];  
	} 

	while (i < n1) arr[k++] = L[i++]; 

	while (j < n2) arr[k++] = R[j++]; 
} 

void MergeSort(int * arr, int l, int r) 
{ 
	if (l < r) {
        int m = (r+l)/2; 
		MergeSort(arr, l, m); 
		MergeSort(arr, m+1, r); 
        Merge(arr, l, m, r); 
	} 
} 
//////////////////////////////////////////
int * RANDOMARR(int n){
    int * arr = (int *)malloc(1000*sizeof(int));
    for(int i = 0; i < 1000; i++){
        arr[i] = (n/2) - (rand()%n);
    }
    return arr;
}
///////////BRUTE///////////////////////////
bool SEARCH(int * arr, int x, int count){
    for(int i = 0; i < count;i++){
        if (arr[i] == x) return true;
    }
    return false;
}

bool SAMESUMSUBARRAY(int * arr, int n){
    int * sums = (int*)malloc(n*n*sizeof(int));
    int count=0; 
    int sum = 0;
    for(int i = 0; i < n; i++){
        for(int j = i + 2; j < n-2; j++){
            sum = 0;
            
            for(int k = i; k <= j; k++){
                sum += arr[k];
            }
            if (SEARCH(sums, sum, count)==true) 
               return true;            
            else 
                sums[count++] = sum;
            }
    }
    return false;
}
//////////EFFICIENT///////////////////

bool EFFSAMESUMSUBARRAY(int * arr, int n){
    int prefix_sum[n], subarraysum[n*n];
    prefix_sum[0] = arr[0];
    for(int i = 1; i < n; i++){
        prefix_sum[i] = prefix_sum[i-1] + arr[i];
    }
    int k = 0;
    for(int i = 0; i < n; i++){
        for(int j = i+2; j < n-2;j++){
            subarraysum[k++] = prefix_sum[j] - prefix_sum[i];
        }
    }
    MergeSort(subarraysum, 0, (n*n)-1);
    for(int i = 1; i < n*n; i++){
        if(subarraysum[i] == subarraysum[i-1]) return true;
    }
    return false;
}

////////////////////////////////////////
int main(){
    int n = 1000;
    srand(time(0));
    int * arr = RANDOMARR(1000);
    printf("BRUTE FORCE - %d\n", SAMESUMSUBARRAY(arr, n));
    printf("EFFICIENT  - %d\n", EFFSAMESUMSUBARRAY(arr, n));
    return 0;
}
