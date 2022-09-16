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
#define VK_Espaco 20
#define VK_Esc 27

struct TpCharacter{
	TpCharacter *prox, *ant;
	char caractere;
};

struct TpLinha{
	TpCharacter **Linha;
	TpLinha *prox, *ant;
};

int main()
{
    char op;
    do
    {
    	op = getch();
    	if(op == -32)
		{
      		op = getch();
      		switch(op)
			{
				case VK_Insert:
					printf("Insert - Ligado: Escreve novos Caracteres | Desligado: Sobreescreve sob o cursor\n");				
					break;
				case VK_Delete:
					printf("Delete - Apaga Caracter(Sob o Cursor)\n");				
					break;
				case VK_Home:
					printf("Home - Inicio do Texto\n");				
					break;
				case VK_End:
					printf("End - Fim do Texto\n");				
					break;
				case VK_PageUp:
					printf("Page Up - Primeira Pagina\n");				
					break;
				case VK_PageDown:
					printf("Page Down - Ultima pagina\n");				
					break;
				case VK_Left:
					printf("Seta <-\n");
					break;
				case VK_Up:
					printf("Seta /\\\n");
					break;
				case VK_Down:
					printf("Seta \\/\n");
					break;
				case VK_Right:
					printf("Seta ->\n");
					break;	

      		}
		}	
      	else
      	{
      		if(op == 0)
      		{
      			op = getch();
	      		switch(op)
	      		{
	      			case VK_F2:
						printf("F2 - ABRIR\n");
						break;
					case VK_F3:
						printf("F3 - SALVAR\n");
						break;
					case VK_F4:
						printf("F4 - SAIR\n");
						break;
					case VK_F5:
						printf("F5 - EXIBIR\n");
						break;
					case VK_F10:
						printf("F10 - NEGRITO\n");
						break;
				}
			}
			else
			{	
				switch(op)
				{
					case VK_Backspace:
						printf("Backspace - Apaga Caractere\n");
						break;
					default:
						printf("%c\n", op);
						break;
				}
			}
		}

    }while(op != VK_F4);
}
