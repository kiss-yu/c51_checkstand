#include <reg52.h>
#include <intrins.h>
void sleep1(int ms);
void num_1();
void num_2();
void num_3();
void num_4();
void void_num();
void xianshi(int kc);
void led_number(int number);
char code number[]={
0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90
};
char code wei[]={0xf7,0xfb,0xfd,0xfe};

int time=0,k1,k2,k3,k4;
void led_number(int number){
	time=number;
	void_num();
	if(k4>0){
			num_4();
		}
		else if(k3>0){
			num_3();
		}
		else if(k2>0){
			num_2();
		}
		else
			num_1();
}
void sleep(int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
	for(j=0;j<550;j++);
}
void void_num(){
	k4=time/1000;
	k3=time%1000/100;
	k2=time%100/10;
	k1=time%10;
}
void num_1(){
	P2=wei[0];
	xianshi(k1);
}
void num_2(){
	int i=0;
		P2=wei[1];
		xianshi(k2);
		sleep(2);
		P2=wei[0];
		xianshi(k1);
		sleep(2);
}
void num_3(){
		P2=wei[2];
		xianshi(k3);
		sleep(1);
		P2=wei[1];
		xianshi(k2);
		sleep(1);
		P2=wei[0];
		xianshi(k1);
		sleep(2);
}
void num_4(){
		P2=wei[3];
		xianshi(k4);
		sleep(1);
		P2=wei[2];
		xianshi(k3);
		sleep(1);
		P2=wei[1];
		xianshi(k2);
		sleep(1);
		P2=wei[0];
		xianshi(k1);
		sleep(1);
}
void xianshi(int kc){
	P0 = number[kc];
}