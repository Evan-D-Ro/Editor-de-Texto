#include "TadStringDinamica.h"

struct DescritorEditor{
	TpLinha *Linhas
	int quantLinhas;
	int quantCaracteres;
};

struct TpLinha{
	TpLinha *ant, *prox;
	StrDin *textoLinha;
	int numCaracteres;
};

typedef struct TpLinha TpLinha;

void InicializaLinha(TpLinha **linha){
	*linha = NULL;
}

void insereLinha(TpLinha **linha, int contLinha)
{
	TpLinha *nova, *aux;
	nova = (TpLinha *)malloc(sizeof(TpLinha));
	InicializaTexto(&(*nova).textoLinha);
	nova->ant=NULL;
	nova->prox=NULL;
	nova->numCaracteres=0;
	if(*linha == NULL)
		*linha = nova;
	else
	{
		aux = *linha;
		while(contLinha>0)
		{
			aux=aux->prox;
			contLinha--;
		}
		if(aux->prox == NULL)
		{
			aux->prox=nova;
			nova->ant = aux;
		}
		else
		{
			aux->prox->ant=nova;
			nova->prox=aux->prox;
			nova->ant=aux;
			aux->prox=nova;
		}		

	}
}

void ExibeLinhas(TpLinha *Linha, int x, int y)
{
	if(Linha !=NULL)
	{
		Exibe(Linha->textoLinha, x, y, 70-Linha->numCaracteres);
		
		ExibeLinhas(Linha->prox, x,++y);
	}
}

void ExibeTeste(TpLinha *Linha, int x, int y)
{
	while(Linha->prox != NULL)
	{
		Linha = Linha->prox;
	}
	while(Linha->textoLinha->prox != NULL)
	{
		Linha->textoLinha = Linha->textoLinha->prox;
	}
	gotoxy(x,y), printf("%c", Linha->textoLinha->letra);
}





