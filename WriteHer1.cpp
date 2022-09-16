#include<stdio.h>
#include<conio2.h>
#include<stdlib.h>
#include<ctype.h>
#include<windows.h>
#include<string.h>
#include "TadLinha.h"

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
#define VK_Espaco 32
#define VK_Enter 13

void Menu(void)
{
	int i;
	textbackground(LIGHTGRAY);
	textcolor(BLACK);
	gotoxy(0,0), printf("| F2 - ABRIR | F3 - SALVAR | F4 - SAIR | F5 - EXIBIR | F10- NEGRITO |");
	for(i=0; i<51 ; i++)
	{
		gotoxy(i, 0),printf(" ");
	}
	for(i=0; i<119; i++)
	{
		gotoxy(i, 0),printf("%c", 205);
	}
	for(i=0; i<121; i++)
	{
		gotoxy(i, 29),printf("%c", 205);
	}

	textbackground(BLACK);
	textcolor(LIGHTGRAY);
}

void LeCaracter(char c, TpLinha **Linha, TpLinha **Atual, int &startEspaco, int &contColuna, int &contLinha)
{
	char auxC;
	TpLinha *AuxAtual;
	StrDin *Aux;
		
		if((*Atual)->numCaracteres<70 || c != VK_Enter)
		{
			insereChar(&(*Atual)->textoLinha, c);
			(*Atual)->numCaracteres++;
			contColuna++;
			
			if(c == VK_Espaco)
				startEspaco = (*Atual)->numCaracteres;
				
		}
		
		if((*Atual)->numCaracteres == 70 || c == VK_Enter)
		{
			insereLinha(&(*Linha));
			*Atual = (*Atual)->prox;
			contLinha++;
			contColuna=0;
			AuxAtual=(*Atual);
			if(c != VK_Espaco && c != VK_Enter && startEspaco != 0 )
			{
				Aux = RetornaSubstring((*Atual)->ant->textoLinha, startEspaco-1);
				while(Aux != NULL)
				{
					auxC = Aux->letra;
					insereChar(&(*Atual)->textoLinha, auxC);
					(*Atual)->numCaracteres++;
					Aux = Aux->prox;
					contColuna++;
					if((*Atual)->numCaracteres==70 || auxC==VK_Enter)
					{
						insereLinha(&(*Linha));
						*Atual = (*Atual)->prox;
						contLinha++;
					}
				}
				AuxAtual->ant->numCaracteres-=removeChars(&AuxAtual->ant->textoLinha, startEspaco-1, 70);
				startEspaco=0;
			}
		}
}

int main()
{
	char c, auxC;
	int contLinha=0, contColuna=0, i;
	int x=3, y=4;
	TpLinha *Linha, *Atual;
	StrDin *Sentinela, *aux;
	int startEspaco=0;
	Menu();
	InicializaLinha(&Linha);
	insereLinha(&Linha);
	Atual = Linha;
	
	do
    {
    	c = getch();
    	if(c == -32)
		{
      		c = getch();
      		switch(c)
			{
				case VK_Insert:
					//printf("Insert - Ligado: Escreve novos Caracteres | Desligado: Sobreescreve sob o cursor\n");				
					break;
				case VK_Delete:
					//printf("Delete - Apaga Caracter(Sob o Cursor)\n");				
					break;
				case VK_Home:
					//printf("Home - Inicio do Texto\n");				
					break;
				case VK_End:
					//printf("End - Fim do Texto\n");				
					break;
				case VK_PageUp:
					//printf("Page Up - Primeira Pagina\n");				
					break;
				case VK_PageDown:
					//printf("Page Down - Ultima pagina\n");				
					break;
				case VK_Left:
					//printf("Seta <-\n");
					break;
				case VK_Up:
					//printf("Seta /\\\n");
					break;
				case VK_Down:
					//printf("Seta \\/\n");
					break;
				case VK_Right:
					//printf("Seta ->\n");
					break;	

      		}
		}	
      	else
      	{
      		if(c == 0)
      		{
      			c = getch();
	      		switch(c)
	      		{
	      			case VK_F2:
						//printf("F2 - ABRIR\n");
						break;
					case VK_F3:
						//printf("F3 - SALVAR\n");
						break;
					case VK_F4:
						//printf("F4 - SAIR\n");
						break;
					case VK_F5:
						//printf("F5 - EXIBIR\n");
						break;
					case VK_F10:
						//printf("F10 - NEGRITO\n");
						break;
				}
			}
			else
			{	

				if(c>=32)
				{
					LeCaracter(c, &Linha, &Atual, startEspaco, contColuna, contLinha);
					if(Atual->numCaracteres > 1)
					{
						Sentinela= Sentinela->prox;				
					}
					else
					{
						Sentinela = Atual->textoLinha;
					}
				}
				else
				{
					if(c == VK_Backspace)
					{						
						if(Atual->numCaracteres>0)
						{
							aux = Sentinela;
							Sentinela = Sentinela->ant;
							Sentinela->prox=NULL;
							aux->ant=NULL;
							free(aux);
							Atual->numCaracteres--;
							contColuna--;
						}
						else
						{
							Atual=NULL;
						}
					}
				}
				ExibeLinhas(Linha, x, y);
				gotoxy(contColuna+x,contLinha+y);	

			}
		}

    }while(c != VK_F4);
	return 0;
}
