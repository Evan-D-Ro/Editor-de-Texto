#include<stdio.h>
#include<conio2.h>
#include<ctype.h>
#include<stdlib.h>
#include<String.h>
#include<windows.h>

#define VK_Up 72
#define VK_Left 75
#define VK_Right 77
#define VK_Down 80

#define VK_PageUp 73
#define VK_PageDown 81
#define VK_Delete 83
#define VK_Insert 82
#define VK_Home 71
#define VK_End 79

#define VK_F1 59
#define VK_F2 60
#define VK_F3 61
#define VK_F4 62
#define VK_F5 63
#define VK_F6 64
#define VK_F7 65
#define VK_F8 66
#define VK_F9 67
#define VK_F10 68

#define VK_Backspace 8
#define VK_Esc 27
#define VK_Enter 13


void descobreCodTecla()
{
    unsigned char x = _getch();
    if (0 == x)
    {
        printf("Function key!\n");
        x = _getch();
    }
    printf("key = %02x\n", x);
    
	    if(x == VK_Up)
    {
    	printf("achou UP");
	}
	    if(x == VK_Down)
    {
    	printf("achou Down");
	}
	    if(x == VK_Left)
    {
    	printf("achou Left");
	}
	    if(x == VK_Right)
    {
    	printf("achou Right");
	}
		if(x == VK_PageUp)
    {
    	printf("achou PageUp");
	}
		if(x == VK_PageDown)
    {
    	printf("achou PageDown");
	}
		if(x == VK_Insert)
    {
    	printf("achou Insert");
	}
		if(x == VK_Delete)
    {
    	printf("achou Delete");
	}
		if(x == VK_Home)
    {
    	printf("achou Home");
	}
		if(x == VK_End)
    {
    	printf("achou End");
	}
		if(x == VK_Backspace)
    {
    	printf("achou Backspace");
	}
		if(x == VK_Esc)
    {
    	printf("achou Esc");
	}
		if(x == VK_F1)
    {
    	printf("achou F1");
	}
		if(x == VK_F2)
    {
    	printf("achou F2");
	}
			if(x == VK_F3)
    {
    	printf("achou F3");
	}
			if(x == VK_F4)
    {
    	printf("achou F4");
	}
			if(x == VK_F5)
    {
    	printf("achou F5");
	}
			if(x == VK_F6)
    {
    	printf("achou F6");
	}
			if(x == VK_F7)
    {
    	printf("achou F7");
	}
			if(x == VK_F8)
    {
    	printf("achou F8");
	}
			if(x == VK_F9)
    {
    	printf("achou F9");
	}
			if(x == VK_F10)
    {
    	printf("achou F10");
	}
	
}

int main()
{
	while(1)
	{
	descobreCodTecla();
	}
}
