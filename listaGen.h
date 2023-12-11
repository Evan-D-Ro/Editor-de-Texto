struct TpListaGen{
	char Letra;
	TpListaGen *prox, *proxNivel;
	char fimP;
};

typedef struct TpListaGen ListaGen;

void InicializaListaGen(ListaGen **lista){
	*lista = NULL;
}

bool Atomo(ListaGen *Lista)
{
	if(ListaGen->proxNivel == NULL)
	{
		return true;
	}
	else
		return false;
}

void insereNaLista(ListaGen **lista, char palavra[20])
{
	int nivel=0;
	ListaGen *Atual, *ant, *nova, *antLinha;
	Atual = ant = *lista;
	
	nova = (ListaGen *)malloc(sizeof(ListaGen));
	nova->Letra = palavra[nivel];
	nova->prox=NULL
	nova->proxNivel=NULL;
	nova->fimP= 'F';
	
	if(lista == NULL)
	{
		*lista = nova;
		Atual = *lista;
		ant = Atual;
		nivel++;
		while(nivel < strlen(palavra))
		{
			nova = (ListaGen *)malloc(sizeof(ListaGen));
			nova->Letra = palavra[nivel];
			nova->prox=NULL
			nova->proxNivel=NULL;
			if(nivel+1 == strlen(palavra))
				nova->fimP= 'T';
			else
				nova->fimP= 'F';
			Atual->proxNivel =  nova;
			ant=Atual;
			Atual=Atual->prox;
		}
	}
	else
	{
		while(Atual->prox != NULL && Atual->Letra <= palavra[nivel] && nivel+1 != strlen(palavra))
		{
			if(Atual->Letra == palavra[nivel])
			{
				nivel++;
				antLinha= Atual;
				Atual = Atual->proxNivel;
				ant = Atual;
			}
			else
			{
				ant = Atual;
				Atual = Atual->prox;
			}
		}
		if(nivel+1 == strlen(palavra)
		{
			if(Atual->Letra == palavra[nivel])
			{
				Atual->fimP = 'T';
			}
			else
			{
				nova = (ListaGen *)malloc(sizeof(ListaGen));
				nova->Letra = palavra[nivel];
				nova->fimP= 'T';
				nova->proxNivel=NULL;
				if(palavra[nivel] < Atual->Letra)
				{
					nova->prox= Atual;
					Atual = nova;
				}
				else
				{
					while(Atual-prox != NULL && palavra[nivel] > Atual->Letra)
					{
						ant=Atual;
						Atual = Atual->prox;
					}
					if(Atual->prox == NULL)
					{
						Atual->prox=nova;
					}
					else
					{
						nova->prox = Atual->prox;
						Atual->prox=nova;
					}
				}
			}
		}
		else
		{
			if(Atual->proxNivel == NULL && nivel+1 < strlen(palavra))
			{
				while(nivel+1 < strlen(palavra))
				{
					nova = (ListaGen *)malloc(sizeof(ListaGen));
					nova->Letra = palavra[nivel];
					nova->proxNivel=NULL;
					nova->prox=NULL;
					
					if(nivel+1 == strlen(palavra))
					{
						nova->fimP= 'T';
					}
					else
					{
						nova->fimP= 'F';
					}
					Atual->proxNivel = nova;
					ant = Atual;
					Atual = Atual->prox;
					nivel++;
				}
			}
			else
			{
				if(Atual->Letra < palavra[nivel])
				{
					nova = (ListaGen *)malloc(sizeof(ListaGen));
					nova->Letra = palavra[nivel];
					nova->proxNivel=NULL;
					if(nivel+1 == strlen(palavra))
					{
						nova->fimP= 'T';
					}
					else
					{
						nova->fimP= 'F';
					}		
					if(Atual->prox !=NULL)
					{
						nova->prox=Atual->prox;
						Atual->prox=nova;
					}
					else
					{
						Atual->prox=nova;
					}
					Atual = Atual->prox;
					ant = Atual;
					nivel++;
					while(nivel+1 < strlen)
					{
						nova = (ListaGen *)malloc(sizeof(ListaGen));
						nova->Letra = palavra[nivel];
						nova->proxNivel=NULL;
						nova->prox=NULL;
						
						if(nivel+1 == strlen(palavra))
						{
							nova->fimP= 'T';
						}
						else
						{
							nova->fimP= 'F';
						}
						Atual->proxNivel = nova;
						ant = Atual;
						Atual = Atual->prox;
						nivel++;
					}
				}
				else
				{
					if(Atual->Letra > palavra[nivel])
					{
						nova = (ListaGen *)malloc(sizeof(ListaGen));
						nova->Letra = palavra[nivel];
						nova->proxNivel=NULL;
						if(nivel+1 == strlen(palavra))
						{
							nova->fimP= 'T';
						}
						else
						{
							nova->fimP= 'F';
						}
						if(ant != Atual)
						{
							ant->prox = nova;
							nova->prox = Atual;
							ant = nova;
							Atual = nova;
						}
						else
						{
							nova->prox = Atual;
							antLinha->proxNivel = nova;
							Atual = nova;
							ant = nova;
						}
						nivel++;
						while(nivel+1 < strlen)
						{
							nova = (ListaGen *)malloc(sizeof(ListaGen));
							nova->Letra = palavra[nivel];
							nova->proxNivel=NULL;
							nova->prox=NULL;
							
							if(nivel+1 == strlen(palavra))
							{
								nova->fimP= 'T';
							}
							else
							{
								nova->fimP= 'F';
							}
							Atual->proxNivel = nova;
							ant = Atual;
							Atual = Atual->prox;
							nivel++;
						}
					}
				}
			}
		}
	}
}
