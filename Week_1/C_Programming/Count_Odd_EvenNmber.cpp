#include<stdio.h>

int main(){
	int n;
	int odd=0;
	int even=0;
	scanf("%d", &n);
	for(int i=0; i<n; i++){
		int tmp;
		scanf("%d",&tmp);
		if(tmp%2==0) odd+=1;
		else even+=1;
	}
	printf("%d %d", even, odd);
}
