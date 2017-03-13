#include <reg52.h>
#include <string.h>
#include <math.h>
#include <led_number.h>
char pdata RECEIVE_STRING[10] = "";
char RECEIVE_CHAR = 0,OR_NOT_RECEIVE = 0;
void init()
{
	ET1=0;
	TMOD&=0x0f;
	TMOD|=0X20;
	TH1=0xfd;
	TL1=0xfd;
	TR1=1;
	SM0=0;
	SM1=1;
	REN=1;
	EA=1;
	ES=1;
}
void sendConnect()
{
	int i = 0;
	char pdata content[43] = "AT+CIPSTART=\"TCP\",\"192.168.1.101\",8888\r\n\r\n";
	TI=0;
	for(i = 0;i < 43;i ++){
		SBUF=content[i];
		while(!TI);
		TI=0;
	}
	sleep(10);
}
void sendSize()
{
	int i = 0;
	char pdata temp[17] = "AT+CIPSEND=8\r\n\r\n";
	TI=0;
	for(i = 0;i < 17;i ++){
		SBUF=temp[i];
		while(!TI);
		TI=0;
	}
	sleep(10);
}
void sendColseTcp()
{
	int i = 0;
	char pdata temp[15] = "AT+CIPCLOSE\r\n\r\n";
	TI=0;
	for(i = 0;i < 15;i ++){
		SBUF=temp[i];
		while(!TI);
		TI=0;
	}
	sleep(10);
}
void sendGoodsId(char * id)
{
	int i = 0;
	TI=0;
	for(;i < 8;i ++){
		SBUF=id[i];
		while(!TI);
		TI=0;
	}
	sleep(10);
}
int getPace()
{
	int i = 0,pace = 0;
	for(i = 1; i < strlen(RECEIVE_STRING)-1;i ++)
	{
		pace += (((int)RECEIVE_STRING[i] - 48)*pow(10,(strlen(RECEIVE_STRING)-2-i)));
	}
	if(strlen(RECEIVE_STRING) > 4)
		pace++;
	return pace;
}
int sendTcp(char * id)
{
	sendConnect();
	sendSize();
	sendGoodsId(id);
	sendColseTcp();
	OR_NOT_RECEIVE = 1;
	sendConnect();
	sleep(10);
	while(OR_NOT_RECEIVE);
	return getPace();
}
int getGoodsPrace(char * id)
{
	init();
	return sendTcp(id);
}
void set() interrupt 4
{
	RI=0;
	RECEIVE_CHAR = SBUF;
	if(OR_NOT_RECEIVE == 1)
	{
		if(strlen(RECEIVE_STRING) != 0)
			RECEIVE_STRING[strlen(RECEIVE_STRING)] = RECEIVE_CHAR;
		if(RECEIVE_CHAR == 0x23)
			RECEIVE_STRING[strlen(RECEIVE_STRING)] = RECEIVE_CHAR;
		if(RECEIVE_CHAR == 0x40)
		{
			RECEIVE_STRING[strlen(RECEIVE_STRING)] = 0x00;
			OR_NOT_RECEIVE = 0;
		}
	}
}
