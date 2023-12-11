#include "TadStringDinamica.h"

struct TpCursor{
	int x;
	int y;
};
typedef struct TpCursor Cursor;

struct TpLinha{
	struct TpLinha *ant, *prox;
	StrDin *textoLinha;
	int numCaracteres;
};
typedef struct TpLinha TpLinha;

void InicializaLinha(TpLinha **linha){
	*linha = NULL;
}

bool insereCaracter(TpLinha **Linha, Cursor &posCursor, char letra)
{
	bool organizou = false;
	StrDin *novoChar;
	StrDin *auxTexto, *auxChar;
	TpLinha *auxLinha;
	int i;

	auxLinha = *Linha;	
	novoChar = (StrDin *)malloc(sizeof(StrDin));
	novoChar->letra=letra;
	novoChar->ant=NULL;
	novoChar->prox=NULL;

	if(posCursor.x == 0) //se pos cursor for 0 insere como primeiro caracter da linha
	{
		if((*Linha)->textoLinha == NULL)
		{
			auxLinha->textoLinha = novoChar;
		}
		else
		{
			auxChar = auxLinha->textoLinha;
			if(letra == 21)
			{
				novoChar->prox = auxChar;
				auxChar->ant = novoChar;
				auxLinha->textoLinha = novoChar;
			}
			else
			{
				if(auxChar->letra == 21)
				{
					while(auxChar->prox != NULL && auxChar->letra == 21)
					{
						auxChar = auxChar->prox;
					}
					if(auxChar->prox != NULL)
					{
						auxChar->prox->ant = novoChar;
						novoChar->prox = auxChar->prox;
						novoChar->ant = auxChar;
						auxChar->prox = novoChar;							
					}
					else
					{
						auxChar->prox = novoChar;
						novoChar->ant=auxChar;	
					}
				}
				else
				{
					if(auxChar->prox != NULL)
					{					
						novoChar->prox = auxChar;
						auxChar->ant = novoChar;
						auxLinha->textoLinha = novoChar;	
					}
					else
					{
						auxChar->prox = novoChar;
						novoChar->ant=auxChar;	
					}
				}
			}
		}
	}
	else
	{
		auxTexto = auxLinha->textoLinha;
		if(posCursor.x == auxLinha->numCaracteres)
		{
			while(auxTexto->prox != NULL)
			{
				auxTexto=auxTexto->prox;
			}
			auxTexto->prox = novoChar;
			novoChar->ant = auxTexto;
		}
		else
		{
			i=0;
			while(i < posCursor.x)
			{
				if(auxTexto->letra == 21)
				{
					auxTexto=auxTexto->prox;
				}
				i++;
				auxTexto=auxTexto->prox;
			}
			novoChar->ant = auxTexto->ant;
			novoChar->prox = auxTexto;
			auxTexto->ant->prox = novoChar;
			auxTexto->ant = novoChar;
		}
	}
	auxLinha->numCaracteres++;
	return false;
}

void homeButton(Cursor &posCursor)
{
	posCursor.x = 0;
}

void endButton(Cursor &posCursor, int numCaracteresLinha)
{
	posCursor.x = numCaracteresLinha;
}

void retornaCharLinha(StrDin *texto, StrDin **charAt, int x)
{
	int i=0;
	while(i < x)
	{
		texto = texto->prox;
		i++;
	}
	*charAt = texto;
}

int contaCharsPalavra(StrDin *palavra)
{
	int cont=0;
	
	while(palavra != NULL)
	{
		cont++;
		palavra=palavra->prox;
	}
	return cont;
}

int inicioFimLinha(StrDin *palavra, StrDin **inicio, StrDin **fim) //parei aqui
{
	int cont=1;
	*inicio = palavra;
	while(palavra->prox !=NULL)
	{
		if(palavra->letra == 21)
			palavra=palavra->prox;
		else
		{
			cont++;
			palavra=palavra->prox;
		}
	}
	if(palavra->prox == NULL)
		*fim = palavra;
	return cont;
}

void insereLinha(TpLinha **linha, TpLinha **Original, Cursor &posCursor)
{
	TpLinha *nova, *aux;
	StrDin *auxString;
	
	int quantChar;
	
	nova = (TpLinha *)malloc(sizeof(TpLinha));
	InicializaTexto(&(*nova).textoLinha);
	nova->ant=NULL;
	nova->prox=NULL;
	nova->numCaracteres=0;
	
	if(*linha == NULL)
		*linha = nova;
	else
	{	
		if(posCursor.x == (*linha)->numCaracteres) // SE TA NO FINAL
		{
			if((*linha)->prox == NULL)
			{
				nova->ant = (*linha);
				(*linha)->prox = nova;	
			}
			else
			{
				nova->prox=(*linha)->prox;
				nova->ant= (*linha);
				(*linha)->prox->ant = nova;
				(*linha)->prox = nova;			
			}	
			posCursor.y++;
			*linha = (*linha)->prox;	
		}
		else
		{
			if(posCursor.x == 0) //SE TA NO COMEÇO
			{
				if((*linha)->ant == NULL)
				{
					nova->prox=(*linha);
					(*linha)->ant = nova;
					*Original = (*Original)->ant;
				}
				else
				{
					nova->prox=(*linha);
					nova->ant= (*linha)->ant;
					(*linha)->ant->prox = nova;
					(*linha)->ant = nova;							
				}
				posCursor.y++;
			}
			else
			{
				if(posCursor.x > 0 && posCursor.x < (*linha)->numCaracteres)
				{
					retornaCharLinha((*linha)->textoLinha, &(auxString), posCursor.x);
					quantChar = contaCharsPalavra(auxString);
					
					auxString->ant->prox = NULL;
					auxString->ant = NULL;
					nova->textoLinha = auxString;
					nova->numCaracteres += quantChar;
					(*linha)->numCaracteres-=quantChar;
					
					if((*linha)->prox == NULL)
					{	
						nova->ant = (*linha);
						(*linha)->prox = nova;	
					}
					else
					{
						nova->prox=(*linha)->prox;
						nova->ant = (*linha);
						(*linha)->prox->ant = nova;
						(*linha)->prox = nova;
					}
					posCursor.y++;		
					*linha = (*linha)->prox;				
				}
			}
		}
	}
}

void ExibeLinhas(TpLinha *Linha, int x, int y, int limiteCaractere, int color)
{
	textcolor(color);
	if(Linha !=NULL)
	{
		Exibe(Linha->textoLinha, x, y, limiteCaractere, color);
		
		ExibeLinhas(Linha->prox, x,++y, limiteCaractere, color);
	}
}


