struct stringdin{
	char letra;
	struct stringdin *prox, *ant;
};
typedef struct stringdin StrDin;

void reinicia(StrDin **str)
{
	StrDin *aux;
	while(*str != NULL)
	{
		aux = *str;
		*str = (*str)->prox;
		free(aux);
	}
}

void InicializaTexto(StrDin **str)
{
	*str=NULL;
}
void reiniciaR(StrDin **str, StrDin *s)
{
	if(*str != NULL)
	{
		reiniciaR(&(*str)->prox, s);
		free(*str);
		if(*str == s) //Deixar null o primeiro elemento;
			*str=NULL;
	}
}

void insereChar(StrDin **s, char letra)
{
	StrDin *nova, *aux;
	nova = (StrDin *)malloc(sizeof(StrDin));
	nova->letra=letra;
	nova->ant=NULL;
	nova->prox=NULL;
	if(*s == NULL)
		*s = nova;
	else
	{
		aux = *s;
		while(aux->prox != NULL)
			aux=aux->prox;
		aux->prox=nova;
		nova->ant = aux;
	}
}

int QuantEspacos(StrDin *string)
{
	int cont=0;
	while(string != NULL)
	{
		if(string->letra == 32)
			cont++;
		string=string->prox;
	}
	return cont;
}

void Exibe(StrDin *str, int x, int y, int numCFaltando)
{
	if(str != NULL)
	{
		gotoxy(x,y),printf("%c", str->letra);
		Exibe(str->prox,++x,y, numCFaltando);
	}
	else
	{
		while(numCFaltando>0)
		{
			gotoxy(x++,y),printf(" ");
			numCFaltando--;
		}
	}
}

StrDin *RetornaSubstring(StrDin *str, int andar)
{
	int i;
	for(i=0; i<=andar; i++)
	{
		str=str->prox;
	}
	return str;
}

void copia(StrDin *str1, StrDin **str2)
{
	while(str1 != NULL)
	{
		insereChar(&*str2, str1->letra);
		str1 = str1->prox;
	}
}

void concatena(StrDin *str1, StrDin *str2, StrDin **str3)
{
	copia(str1,&*str3);
	copia(str2,&*str3);
}

int removeChars(StrDin **str, int start, int nro)
{
	StrDin *ant, *aux;
	int CaracteresRemovidos = nro - (start+1);
	if(str != NULL)
	{
		if(start == 0)
		{
			while(*str != NULL && nro > 0)
			{
				aux = *str;
				*str = (*str)->prox;
				free(aux);
				nro--;
			}
		}
		else
		{
			ant = *str;
			while(start != 0)
			{
				ant = ant->prox;
				start--;
			}
			if(ant != NULL)
			{
				while(ant->prox != NULL && nro>0)
				{
					aux = ant->prox;
					ant->prox = aux->prox;
					free(aux);
					nro--;
				}
			}	
		}	
	}
	return CaracteresRemovidos;
}

int BuscaSubstring(StrDin *str, StrDin *subs)
{
	int local = -1, pos=0;
	StrDin *aux, *auxS;
	while(str != NULL && local == -1)
	{
		if(str->letra == subs->letra)
		{
			aux = str;
			auxS = subs;
			while(auxS != NULL && aux != NULL && aux->letra == auxS->letra)
			{
				aux = aux->prox;
				auxS = auxS->prox;	
			}
			if(auxS == NULL)
				local = pos;
		}
		str = str->prox;
		pos++;
	}
		return local;
}


