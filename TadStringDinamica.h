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

int quantEspacos(StrDin *string)
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

void buscaPonto(StrDin *string, StrDin **ponto)
{
	*ponto = NULL;
	while(string != NULL)
	{
		if(string->letra == '.' || string->letra == '?' || string->letra == '!')
			*ponto = string;
		string = string->prox;
	}
}

int ultimaPalavra(StrDin *string, StrDin **inicio, StrDin **fim)
{
	int cont=1;
	(*inicio) =  string;
	(*fim) = string;
	while(string->prox != NULL)
	{
		if(string->letra == 21)
			string = string->prox;
		else
		{
			if(string->letra == 32)
			{	
				cont=0;
				(*inicio)=string;
				if(string->prox !=NULL)
					(*inicio) = (*inicio)->prox;
			}
			(*fim)=string;
			string=string->prox;
			cont++;
		}

	}
	return cont;
}

int ultimoEspaco(StrDin *string)
{
	int cont=0;
	int ultimoEspaco=-1;
	while(string != NULL)
	{
		if(string->letra == 32)
		{	
			ultimoEspaco = cont;
		}
		string=string->prox;
		cont++;
	}
	return ultimoEspaco;
}

void Exibe(StrDin *str, int x, int y, int limiteCaractere, int &color)
{
	int i=0;
	while(str != NULL)
	{
		if(str->letra != 13 && str->letra != 21)
		{
			gotoxy(x,y),printf("%c", str->letra);
			x++;
			i++;
		}
		if(str->letra == 21)
		{
			if(color == 8)
			{
				color= 15;
				textcolor(color);
			}
			else
			{
				color=8;
				textcolor(color);
			}
		}
		str=str->prox;
	}
	while(i<limiteCaractere)
	{
		gotoxy(x,y), printf(" ");
		x++;
		i++;
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


