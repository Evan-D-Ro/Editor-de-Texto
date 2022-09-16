#include "TadStringDinamica.h"

struct TpLinha{
	TpLinha *ant, *prox;
	StrDin *textoLinha;
	int numCaracteres;
};

typedef struct TpLinha TpLinha;

void InicializaLinha(TpLinha **linha){
	*linha = NULL;
}

void insereLinha(TpLinha **linha)
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
		while(aux->prox != NULL)
			aux=aux->prox;
		nova->ant = aux;
		aux->prox=nova;
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



