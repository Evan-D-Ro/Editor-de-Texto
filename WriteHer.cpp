#include<stdio.h>
#include<conio2.h>
#include<stdlib.h>
#include<ctype.h>
#include<windows.h>
#include<string.h>
#include "TadLinha.h"

#define limiteLinhas 21

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

struct TpConfigParagrafo{
	int primeiraLinha;
	int recuoEsquerdo;
	int recuoDireito;
	int limiteCaracteres;	
};

typedef struct TpConfigParagrafo ConfigParagrafo;

//___________________________________________________________________________________________________________________________
//PROTOTIPOS
void posAtual(Cursor posCursor, int quantCharsLinha);

void Menu(void);

void LimpaLinha(Cursor posCursor); //limpa as linhas da tela

void limpar (TpLinha **Linha, Cursor &posCursor); //limpa a estrutura

void organizaEstrutura(TpLinha **Atual, Cursor &posCursor, int limiteCaractere);

void LeCaracter(char c, TpLinha **Atual, Cursor &posCursor, int quantLinhas, TpLinha **Original);

void SalvarArquivo(TpLinha *Linha);

void AbrirArquivo(TpLinha **Linha, TpLinha **Atual, Cursor &posCursor, char nomeArquivo[20], int &quantLinha, int &quantCaracter, int limiteCaractere);

void ExcluiChar(TpLinha **Atual, Cursor &posCursor, int limiteCaractere);

void assistKeys(Cursor &posCursor, char c, int quantCLinha, TpLinha **Atual);

//___________________________________________________________________________________________________________________________
//MODULOS
void posAtual(Cursor posCursor, int quantCharsLinha)
{
	textcolor(WHITE);
	gotoxy(2, 30), printf("COL=  , LIN=   INSERT |||| Quant. Caracteres da Linha=  ");
	gotoxy(2, 30), printf("COL=%d, LIN=%d  INSERT |||| Quant. Caracteres da Linha=%d", posCursor.x+1, posCursor.y+1, quantCharsLinha);
}

void Menu(void)
{
	int i;
	int cor=1;
	textbackground(LIGHTGRAY);
	textcolor(BLACK);
	gotoxy(0,0), printf("| F2 - ABRIR | F3 - SALVAR | F4 - SAIR | F5 - EXIBIR | F6 - CLEAR ALL |F10- NEGRITO |");
	for(i=0; i<35 ; i++)
	{
		gotoxy(i, 0),printf(" ");
	}
	for(i=1; i<81; i++)
	{
		gotoxy(i-1, 0),printf("|", 205);
		if(i%5 == 0)
		{
			if(cor == 1)
			{
				textbackground(DARKGRAY);
				cor=0;
			}
			else
			{
				textbackground(LIGHTGRAY);
				cor=1;
			}
		}
	}
	for(;i<120;i++)
	{
		gotoxy(i,0), printf("-");
	}
	for(i=0; i<121; i++)
	{
		gotoxy(i, 29),printf("%c", 205);
	}
	textbackground(BLACK);
	textcolor(LIGHTGRAY);
}

void LimpaLinha(Cursor posCursor)
{
	int i, j;
	for(j=4; j+posCursor.y<27; j++)
		for(i=0; i<80; i++)
		{
			gotoxy(i, posCursor.y+j), printf(" ");
		}
}

void limpar (TpLinha **Linha, Cursor &posCursor)
{
	TpLinha *auxLDelet;
	StrDin *auxS, *auxDelet;
	while((*Linha) != NULL)
	{
		auxS = (*Linha)->textoLinha;
		while(auxS != NULL)
		{
			auxDelet = auxS;
			auxS = auxS->prox;
			free(auxDelet);
		}
		auxLDelet = (*Linha);
		(*Linha) = (*Linha)->prox;
		free(auxLDelet);
	}
	posCursor.x=0;
	posCursor.y=0;
	LimpaLinha(posCursor);
}

void organizaEstrutura(TpLinha **Atual, Cursor &posCursor, int limiteCaractere)
{
	TpLinha *auxAtual, *auxAtualP;
	StrDin *inicioP, *fimP;
	char c;
	StrDin *ponto;
	int tamPalavra;
	
	int auxPosX;
	auxAtual = *Atual;

	while(auxAtual != NULL)
	{
		while(auxAtual->numCaracteres > limiteCaractere)
		{
			if(auxAtual->prox == NULL) //CRIA UMA LINHA
			{
				if(posCursor.x != auxAtual->numCaracteres)
				{
					LimpaLinha(posCursor);
					auxPosX = posCursor.x;
					posCursor.x = auxAtual->numCaracteres;
					insereLinha(&(auxAtual), &(*Atual), posCursor);
					tamPalavra = ultimaPalavra(auxAtual->ant->textoLinha, &(inicioP), &(fimP));
					inicioP->ant->prox = NULL;
					inicioP->ant=NULL;
					auxAtual->textoLinha = inicioP;
					auxAtual->numCaracteres+=tamPalavra;
					auxAtual->ant->numCaracteres-=tamPalavra;
					posCursor.x=auxPosX;
					posCursor.y--;
				}
				else
				{
					LimpaLinha(posCursor);
					insereLinha(&(auxAtual), &(*Atual), posCursor);
					tamPalavra = ultimaPalavra(auxAtual->ant->textoLinha, &(inicioP), &(fimP));
					inicioP->ant->prox = NULL;
					inicioP->ant=NULL;
					auxAtual->textoLinha = inicioP;
					auxAtual->numCaracteres+=tamPalavra;
					auxAtual->ant->numCaracteres-=tamPalavra;
					posCursor.x=tamPalavra;
					(*Atual) = (*Atual)->prox;
				}
			}
			else
			{
				tamPalavra = ultimaPalavra(auxAtual->textoLinha, &(inicioP), &(fimP));	
				fimP=fimP->prox;
				if(tamPalavra > limiteCaractere - auxAtual->prox->numCaracteres || fimP->letra == '.' || fimP->letra == '!' || fimP->letra == '?')
				{
					if(posCursor.x != auxAtual->numCaracteres)
					{
						LimpaLinha(posCursor);
						auxPosX = posCursor.x;
						posCursor.x = auxAtual->numCaracteres;
						insereLinha(&(auxAtual), &(*Atual), posCursor);
						inicioP->ant->prox = NULL;
						inicioP->ant=NULL;
						auxAtual->textoLinha = inicioP;
						auxAtual->numCaracteres+=tamPalavra;
						auxAtual->ant->numCaracteres-=tamPalavra;
						posCursor.x=auxPosX-auxAtual->ant->numCaracteres;
						(*Atual) = (*Atual)->prox;
					}
					else
					{
						LimpaLinha(posCursor);
						insereLinha(&(auxAtual), &(*Atual), posCursor);
						inicioP->ant->prox = NULL;
						inicioP->ant=NULL;
						auxAtual->textoLinha = inicioP;
						auxAtual->numCaracteres+=tamPalavra;
						auxAtual->ant->numCaracteres-=tamPalavra;
						posCursor.x=tamPalavra;
						(*Atual) = (*Atual)->prox;
					}
				}
				else
				{
					buscaPonto(auxAtual->textoLinha, &ponto);
					if(ponto == NULL)
					{
						fimP->prox = auxAtual->prox->textoLinha;
						auxAtual->prox->textoLinha->ant = fimP;
						inicioP->ant->prox = NULL;
						inicioP->ant = NULL;
						auxAtual->prox->textoLinha = inicioP;
						auxAtual->prox->numCaracteres += tamPalavra;
						auxAtual->numCaracteres-=tamPalavra;
						posCursor.x = tamPalavra;
						posCursor.y++;
						(*Atual) = (*Atual)->prox;
						if(fimP->prox->letra != 32)
						{
							c = ' ';
							insereCaracter(&(*Atual),posCursor, c);
						}
					}
					else
					{
						LimpaLinha(posCursor);
						auxPosX = posCursor.x;
						posCursor.x = auxAtual->numCaracteres;
						tamPalavra = ultimaPalavra(ponto, &inicioP, &fimP);
						insereLinha(&(auxAtual), &(*Atual), posCursor);
						inicioP->ant->prox=NULL;
						inicioP->ant=NULL;
						auxAtual->textoLinha = inicioP;
						auxAtual->numCaracteres+=tamPalavra;
						posCursor.x=tamPalavra;
						(*Atual) = (*Atual)->prox;
					}
				}
			}
		}
		auxAtual = auxAtual->prox;
	}
}

void LeCaracter(char c, TpLinha **Atual, Cursor &posCursor, int quantLinhas, TpLinha **Original, int limiteCaractere)
{
	char auxC;
	TpLinha *auxAtualP, *auxAtual;
	StrDin *inicioPalavra, *fimPalavra;
	int quantChar;
	
	if(c == VK_Enter)
	{
		insereLinha(&(*Atual), &(*Original), posCursor);
		quantLinhas++;
		posCursor.x=0;
	}
	else
	{		
		insereCaracter(&(*Atual),posCursor,c);
		posCursor.x++;
		if(c == 21)
		{
			(*Atual)->numCaracteres--;
			posCursor.x--;
		}
		if((*Atual)->numCaracteres>limiteCaractere)
		{
			organizaEstrutura(&(*Atual),posCursor, limiteCaractere);
		}
	}
}

void SalvarArquivo(TpLinha *Linha, char nomeArquivo[20])
{
	StrDin *auxS;
	FILE *arq = fopen(nomeArquivo, "w");
	while(Linha != NULL)
	{
		auxS = Linha->textoLinha;
		while(auxS != NULL)
		{
			fputc(auxS->letra,arq);
			auxS = auxS->prox;
		}
		Linha = Linha->prox;
		fputc(13,arq);
	}
	fclose(arq);
}
void AbrirArquivo(TpLinha **Linha, TpLinha **Atual, Cursor &posCursor, char nomeArquivo[20], int &quantLinha, int &quantCaracter, int limiteCaractere)
{
	TpLinha *auxL;
	char c;
	FILE *arq = fopen(nomeArquivo, "r");
	if(arq != NULL)
	{
		limpar(&(*Linha), posCursor);
		insereLinha(&(*Linha), &(*Atual), posCursor);
		quantLinha=1;
		quantCaracter=0;
		auxL = (*Linha);
		while(!feof(arq))
		{
			fscanf(arq,"%c",&c);
			LeCaracter(c, &(auxL), posCursor, quantLinha, &(*Linha), limiteCaractere);
		}
		(*Atual) = auxL;
	}
	else
	{
		gotoxy(4,6), printf("Arquivo nao encontrado...");
		getch();
		LimpaLinha(posCursor);
	}
	ExcluiChar(&(*Atual),posCursor, limiteCaractere);
	ExcluiChar(&(*Atual),posCursor, limiteCaractere);
	fclose(arq);
}

void ExcluiChar(TpLinha **Atual, Cursor &posCursor, int limiteCaractere)
{
	char c;
	int i=0;
	int contPalavra=0;
	TpLinha *auxLinha, *AuxLinhaDelet;
	StrDin *charDeletar, *auxChar;
	StrDin *enterDelet;
	StrDin *inicioP, *fimP;
	auxLinha = (*Atual);
	charDeletar = (*Atual)->textoLinha;
	
	if(posCursor.x == 0)
	{
		if((*Atual)->ant != NULL)
		{
			if((*Atual)->numCaracteres > 0)
			{
				contPalavra = inicioFimLinha((*Atual)->textoLinha, &inicioP, &fimP);
				if((*Atual)->ant->numCaracteres > 0)
				{
					auxChar = (*Atual)->ant->textoLinha;
					while(auxChar->prox != NULL)
					{
						auxChar = auxChar->prox;
					}
					while(auxChar->letra == 21)
					{
						auxChar=auxChar->ant;
					}
				}
				else
					auxChar = (*Atual)->ant->textoLinha;
				if((*Atual)->ant->numCaracteres + contPalavra < limiteCaractere && contPalavra>0)
				{
					(*Atual)->ant->numCaracteres +=contPalavra;
					(*Atual)->numCaracteres-=contPalavra;
					if(auxChar != NULL)
					{
						inicioP->ant = auxChar;
						auxChar->prox=inicioP;
						posCursor.x = (*Atual)->ant->numCaracteres-contPalavra;		
					}
					else
					{
						inicioP->ant=NULL;
						(*Atual)->ant->textoLinha = inicioP;
						posCursor.x = (*Atual)->ant->numCaracteres;
					}
					if(fimP->prox != NULL)
					{
						(*Atual)->textoLinha = fimP->prox;
						fimP->prox->ant=NULL;
						fimP->prox=NULL;
					}
					(*Atual) = (*Atual)->ant;
					if((*Atual)->prox->numCaracteres == 0)
					{
						AuxLinhaDelet = (*Atual)->prox;
						if(AuxLinhaDelet->prox == NULL)
						{
							(*Atual)->prox = NULL;
							AuxLinhaDelet->ant=NULL;
							free(AuxLinhaDelet);
						}
						else
						{
							(*Atual)->prox = AuxLinhaDelet->prox;
							AuxLinhaDelet->prox->ant = (*Atual);
							free(AuxLinhaDelet);
						}
					}
				}
				else
				{
					if(auxChar->letra != '.' != auxChar->letra == '?' != auxChar->letra != '!')
					{
						charDeletar = auxChar;
						auxChar = auxChar->ant;
						charDeletar->ant = NULL;
						free(charDeletar);
						(*Atual)->ant->numCaracteres--;						
					}
					inicioP->ant = auxChar;
					
					(*Atual)->textoLinha = inicioP->prox;
					if(inicioP->prox != NULL)
					{
						inicioP->prox->ant=NULL;
					}
					inicioP->prox=NULL;
					auxChar->prox=inicioP;
					(*Atual)->numCaracteres--;
					(*Atual)->ant->numCaracteres++;
					posCursor.x = (*Atual)->ant->numCaracteres-1;
					while((*Atual)->ant->numCaracteres < limiteCaractere && (*Atual)->textoLinha->letra != 32 && (*Atual)->numCaracteres > 0)
					{
						auxChar = auxChar->prox;
						inicioP = (*Atual)->textoLinha;
						inicioP->ant = auxChar;
						(*Atual)->textoLinha = inicioP->prox;
						if(inicioP->prox != NULL)
						{
							inicioP->prox->ant=NULL;
						}
						inicioP->prox=NULL;
						auxChar->prox=inicioP;
						(*Atual)->numCaracteres--;
						(*Atual)->ant->numCaracteres++;
					}
					(*Atual) = (*Atual)->ant;
					if(contPalavra == ((*Atual)->numCaracteres))
					{
						posCursor.x = contPalavra;
					}
				}
			}
			if((*Atual)->numCaracteres == 0)
			{
				if((*Atual)->prox != NULL)
				{
					auxLinha = (*Atual);
					*Atual = (*Atual)->ant;
					auxLinha->prox->ant = auxLinha->ant;
					auxLinha->ant->prox = auxLinha->prox;
					free(auxLinha);
				}
				else
				{
					auxLinha = (*Atual);
					*Atual = (*Atual)->ant;
					auxLinha->ant = NULL;
					(*Atual)->prox= NULL;
					free(auxLinha);
				}
				if(posCursor.x == 0)
					posCursor.x = (*Atual)->numCaracteres;
			}
			posCursor.y--;
			LimpaLinha(posCursor);
		}
	}
	else
	{
		if(posCursor.x == 1)
			{
			if(charDeletar->prox != NULL) //se houver mais de um caracter na primeira linha
			{
				auxChar = charDeletar;
				auxChar = auxChar->prox;
				auxChar->ant=NULL;
				(*Atual)->textoLinha=auxChar;
				free(charDeletar);
			}
			else //se só houver 1 caracter na linha
			{
				free(charDeletar);
				InicializaTexto(&(auxLinha->textoLinha));				
			}
			auxLinha->numCaracteres--;
			posCursor.x--;
		}
		else
		{
			if(posCursor.x > 1)
			{
				while(i < posCursor.x-1)
				{
					charDeletar = charDeletar->prox;
					i++;
				}
				c = charDeletar->letra;
				if(charDeletar->prox == NULL)
				{
					charDeletar->ant->prox=NULL;
					free(charDeletar);
				}
				else
				{
					auxChar = charDeletar->prox;
					auxChar->ant = charDeletar->ant;
					charDeletar->ant->prox = auxChar;
					free(charDeletar);
				}
				if(c != 21)
				{
					auxLinha->numCaracteres--;
					posCursor.x--;
				}
			}
		}	
	}
}

void assistKeys(Cursor &posCursor, char c, int quantCLinha, TpLinha **Atual, int limiteCaracteres)
{	
  	c = getch();
	switch(c)
	{
		case VK_Insert:
			//printf("Insert - Ligado: Escreve novos Caracteres | Desligado: Sobreescreve sob o cursor\n");				
			break;
		case VK_Delete:
			if(posCursor.x < (*Atual)->numCaracteres)
			{
				if(posCursor.x < quantCLinha)
					posCursor.x++;
				else
				{
					if((*Atual)->prox != NULL)
					{
						posCursor.y++;
						*Atual = (*Atual)->prox;
						posCursor.x=0;
					}
				}
				ExcluiChar(&(*Atual),posCursor, limiteCaracteres);	
			}
			break;
		case VK_Home:
			homeButton(posCursor);				
			break;
		case VK_End:
			endButton(posCursor, (*Atual)->numCaracteres);				
			break;
		case VK_PageUp:
			//printf("Page Up - Primeira Pagina\n");				
			break;
		case VK_PageDown:
			//printf("Page Down - Ultima pagina\n");				
			break;
		case VK_Left:
			if(posCursor.x > 0)
				posCursor.x--;
			else
			{
				if(posCursor.y > 0)
				{
					posCursor.y--;
					*Atual = (*Atual)->ant;
					posCursor.x=(*Atual)->numCaracteres;
				}
			}
			break;
		case VK_Up:
			if(posCursor.y > 0)
			{
				posCursor.y--;
				*Atual = (*Atual)->ant;
				if((*Atual)->numCaracteres < posCursor.x)
				{
					posCursor.x=(*Atual)->numCaracteres;
				}				
			}
			break;
		case VK_Down:
			if((*Atual)->prox != NULL)
			{
				posCursor.y++;
				*Atual = (*Atual)->prox;
				if((*Atual)->numCaracteres < posCursor.x)
				{
					posCursor.x=(*Atual)->numCaracteres;
				}
			}
			break;
		case VK_Right:
			if(posCursor.x < quantCLinha)
				posCursor.x++;
			else
			{
				if((*Atual)->prox != NULL)
				{
					posCursor.y++;
					*Atual = (*Atual)->prox;
					posCursor.x=0;
				}
			}
			break;	
	}
}

//___________________________________________________________________________________________________________________________
//APLICAÇÃO

int main()
{
	char c, op;
	int inicioX=1, inicioY=4;
	int quantLinhas=1;
	int quantCaracteres=0;
	int fimX=75;
	int color = 8;
	int maxCaracteres = fimX - inicioX;
	ConfigParagrafo configExibicao;
	configExibicao.recuoDireito=80;
	configExibicao.recuoEsquerdo=1;
	configExibicao.limiteCaracteres = configExibicao.recuoDireito - configExibicao.recuoEsquerdo;
	inicioX= configExibicao.recuoEsquerdo+1;
	
	
	char nomeArquivo[20];
	
	Cursor posCursor, posAux;
	posCursor.x = 0, posCursor.y = 0;
	posAux.x=0, posAux.y=0;
	TpLinha *Linha; //PRINCIPAL
	
	TpLinha *Atual; //ANDA PELA LINHAm	
	StrDin *comecoPalavra;
	InicializaTexto(&comecoPalavra);
	
	Menu();
	
	InicializaLinha(&Linha);
	insereLinha(&Linha, &Atual, posCursor);
	Atual = Linha;
	comecoPalavra = Atual->textoLinha;
	posAtual(posCursor, Atual->numCaracteres);
	gotoxy(posCursor.x+inicioX, posCursor.y+inicioY);
	
	do
    {
    	c = getch();
    	if(c == -32)
		{
			assistKeys(posCursor, c, Atual->numCaracteres, &(Atual), configExibicao.limiteCaracteres);
			ExibeLinhas(Linha, inicioX, inicioY, maxCaracteres, 8);
			posAtual(posCursor, Atual->numCaracteres);
			gotoxy(posCursor.x+inicioX, posCursor.y+inicioY);
		}	
      	else
      	{
      		if(c == 0)
      		{
      			c = getch();
	      		switch(c)
	      		{
	      			case VK_F2:
	      				LimpaLinha(posAux);
	      				gotoxy(4,5), printf("Nome do Arquivo (Sem extensao): "), gets(nomeArquivo);
	      				strcat(nomeArquivo, ".txt");
	      				if(strlen(nomeArquivo) > 1)
	      				{
	      					AbrirArquivo(&Linha, &Atual, posCursor, nomeArquivo,quantLinhas,quantCaracteres, configExibicao.limiteCaracteres);	
						}
						else
						{
							gotoxy(4,6), printf("Nome nao pode ser vazio..."), getch();
						}
						LimpaLinha(posAux);
						ExibeLinhas(Linha, inicioX, inicioY, maxCaracteres, 8);
						posAtual(posCursor, Atual->numCaracteres);
						gotoxy(posCursor.x+inicioX, posCursor.y+inicioY);
						break;
					case VK_F3:
						LimpaLinha(posAux);
	      				gotoxy(4,5), printf("Nome do Arquivo (Sem Extensao): "), gets(nomeArquivo);
	      				if(strlen(nomeArquivo) > 0)
	      				{
	      					strcat(nomeArquivo, ".txt");
							SalvarArquivo(Linha, nomeArquivo);
							gotoxy(4,6), printf("Arquivo salvo!");	
							getch();      					
						}
						else
						{
							gotoxy(4,7), printf("Nome nao pode ser vazio..."), getch();
						}
						LimpaLinha(posAux);
						ExibeLinhas(Linha, inicioX, inicioY, maxCaracteres, 8);
						posAtual(posCursor, Atual->numCaracteres);
						gotoxy(posCursor.x+inicioX, posCursor.y+inicioY);
						break;
					case VK_F4:
						LimpaLinha(posAux);
						if(Linha->numCaracteres == 0 && Linha->prox == NULL)
						{
							
						}
						else
						{
		      				gotoxy(4,5), printf("Deseja salvar seu arquivo atual? (S/N)"), fflush(stdin), op = getch();
							while(op != 'S' && op != 's' && op != 'n' && op != 'N')
							{
								gotoxy(4,5), printf("Deseja salvar seu arquivo atual? (S/N)"), fflush(stdin), op = getch();
							}
							if(op == 'S' || op == 's')
							{
								gotoxy(4,6), printf("Nome do Arquivo (Sem Extensao): "), gets(nomeArquivo);
			      				while(strlen(nomeArquivo) < 0)
			      				{
			      					gotoxy(4,6), printf("Nome do Arquivo (Sem Extensao): "), gets(nomeArquivo);		
								}
			  					strcat(nomeArquivo, ".txt");
								SalvarArquivo(Linha, nomeArquivo);
								gotoxy(4,8), printf("Arquivo salvo!");	
								getch();      				
							}
							else
							{
								limpar(&(Linha),posCursor);
							}
							
						}
						gotoxy(posCursor.x+inicioX, posCursor.y+inicioY);
						break;
					case VK_F5:
    					LimpaLinha(posAux);
    					SalvarArquivo(Linha, "temp.txt");
	      				configExibicao.primeiraLinha=1;
	      				gotoxy(4,6), printf("Recuo Esquerdo: "), scanf("%d", &configExibicao.recuoEsquerdo);
	      				gotoxy(4,7), printf("Recuo Direito: "), scanf("%d", &configExibicao.recuoDireito);
	      				if(configExibicao.recuoEsquerdo < 1 || configExibicao.recuoDireito > 80 || configExibicao.primeiraLinha < 0 || configExibicao.primeiraLinha > 80 || configExibicao.recuoEsquerdo == configExibicao.recuoDireito)
	      				{
	  	      				configExibicao.recuoEsquerdo = 5;
	      					configExibicao.recuoDireito = 75;    					
						}
	      				if(configExibicao.recuoEsquerdo > configExibicao.recuoDireito)
	      				{
	      					configExibicao.recuoEsquerdo = 5;
	      					configExibicao.recuoDireito = 75;
						}
	    				if(configExibicao.recuoEsquerdo + configExibicao.recuoDireito > 80)
	      				{
	      					configExibicao.recuoEsquerdo = 5;
	      					configExibicao.recuoDireito = 75;
						}
						LimpaLinha(posAux);
						configExibicao.limiteCaracteres = configExibicao.recuoDireito - configExibicao.recuoEsquerdo;
						inicioX= configExibicao.recuoEsquerdo+1;
	      				AbrirArquivo(&Linha, &Atual, posCursor, "temp.txt",quantLinhas,quantCaracteres, configExibicao.limiteCaracteres);
	      				remove("temp.txt");
						ExibeLinhas(Linha, inicioX, inicioY, maxCaracteres, 8);
						endButton(posCursor, Atual->numCaracteres);	
						posAtual(posCursor, Atual->numCaracteres);
						gotoxy(posCursor.x+inicioX, posCursor.y+inicioY);
						break;
					case VK_F6:
						limpar(&(Linha),posCursor);
						insereLinha(&Linha, &Atual, posCursor);
						quantLinhas=1;
						Atual = Linha;
						posAtual(posCursor, Atual->numCaracteres);
						gotoxy(posCursor.x+inicioX, posCursor.y+inicioY);
						break;
					case VK_F10:
						c = 21;
						LeCaracter(c, &(Atual), posCursor, quantLinhas, &(Linha), configExibicao.limiteCaracteres);
						ExibeLinhas(Linha, inicioX, inicioY, maxCaracteres, 8);
						posAtual(posCursor, Atual->numCaracteres);
						gotoxy(posCursor.x+inicioX, posCursor.y+inicioY);
						break;
				}
			}
			else
			{	
				if(c>=32 || c== VK_Enter) //Caracter Comum
				{
					LeCaracter(c, &(Atual), posCursor, quantLinhas, &(Linha),configExibicao.limiteCaracteres);
					quantCaracteres++;
				}
				else
				{
					if(c == VK_Backspace)
					{						
						ExcluiChar(&(Atual),posCursor, configExibicao.limiteCaracteres);
					}
				}
				ExibeLinhas(Linha, inicioX, inicioY, maxCaracteres, 8);
				posAtual(posCursor, Atual->numCaracteres);
				gotoxy(posCursor.x+inicioX, posCursor.y+inicioY);
			}
		}

    }while(c != VK_F4);
	return 0;
}
