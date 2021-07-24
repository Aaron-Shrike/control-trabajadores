#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

#define MAX 20
#define LIM 50


// operacions basicas de datos simples
int leeEntero(char msje[], int min, int max,char msje1[])
{
	int num,flag;

   	do
	{
   		printf("%s", msje);
      	scanf("%d", &num);
      	if(num<=min && num>=max)
		{
      		printf("%s", msje1);
      	}
   	}while(!(num>=min && num<=max));

  	return num;
}

float leeReal(char msje[], float min, float max)
{ 
	float num;
	
  	do
	{
     	printf("%s", msje);
     	scanf("%f", &num);
  	}while(!(num>=min && num<=max));
  	
  	return num;
}

//Adicionales
char leeSexo(char msje[])
{
	char rpta;

   	cout << " F : Femenino" <<endl;
   	cout << " M : Masculinoino" <<endl;
   	do
	{
   		printf("%s", msje);
      	fflush(stdin);
      	scanf("%c",&rpta);
      	rpta= toupper(rpta);
   	}while(!(rpta=='F' || rpta== 'M'));
   	
   	return rpta;
}

char leeCaracter(char msje1[],char msje2[],char A,char B,char msje[])
{
	char rpta;

   	cout << msje1 <<endl;
   	cout << msje2 <<endl;
   	do
	{
   		printf("%s", msje);
      	fflush(stdin);
      	scanf("%c",&rpta);
      	rpta= toupper(rpta);
   	}while(!(rpta==A || rpta== B));

   return rpta;
}

