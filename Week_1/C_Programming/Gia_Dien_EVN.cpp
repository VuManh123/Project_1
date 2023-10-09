#include<stdio.h>

int main(){
	float giaDienCu = 0;
	float giaDienMoi = 0;
	int soDien;
	scanf("%d", &soDien); 
	if(0<=soDien && soDien<=50){
		giaDienCu = soDien*1728;
		giaDienMoi = soDien*1728;
	}
	else if(50<soDien && soDien<=100){
		giaDienCu = 50*1728 + (soDien-50)*1786;
		giaDienMoi = soDien*1728;
	}
	else if(100<soDien && soDien<=200){
		giaDienCu = 50*1728 + 50*1786 + (soDien-100)*2074;
		giaDienMoi = 100*1728 + (soDien-100)*2074;
	}
	else if(200<soDien && soDien<=300){
		giaDienCu = 50*1728 + 50*1786 + 100*2074 + (soDien-200)*2612;
		giaDienMoi = 100*1728 + 100*2074 +(soDien-200)*2612;
	}
	else if(300<soDien && soDien<=400){
		giaDienCu = 50*1728 + 50*1786 + 100*2074 + 100*2612 + (soDien-300)*2919;
		giaDienMoi = 100*1728 + 100*2074 +(soDien-200)*2612;
	}
	else if(400<soDien && soDien<=700){
		giaDienCu = 50*1728 + 50*1786 + 100*2074 + 100*2612 + 100*2919 + (soDien-400)*3015;
		giaDienMoi = 100*1728 + 100*2074 + 200*2612 + (soDien-400)*3111;
	}
	else{
		giaDienCu = 50*1728 + 50*1786 + 100*2074 + 100*2612 + 100*2919 + (soDien-400)*3015;
		giaDienMoi = 100*1728 + 100*2074 + 200*2612 + 300*3111 + (soDien-700)*3457;
	}
	float chenhLech = (giaDienMoi - giaDienCu)*1.1;
	printf("%.2f", chenhLech);
}
