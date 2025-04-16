#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Verghe.h"
#define TEST puts("pippo")


/*TEST;
system("pause");*/

/*lettura del file txt e creazione della lista */
Codice* leggi()
{

	FILE* fp;
	Codice* lista;
	lista = NULL;



	fp = fopen("Verghe.txt", "r");

	while (feof(fp) == 0)
	{
		Codice* n_cod;
		Verga* n_ver ;

		n_cod = (Codice*)malloc(sizeof(Codice));
		n_ver = (Verga*)malloc(sizeof(Verga));


		n_cod->prev = NULL;
		n_cod->next = NULL;
		n_cod->indice = 0;

		fscanf(fp, "%d", &n_ver->lato1);
		fscanf(fp, "%d", &n_ver->lato2);
		fscanf(fp, "%d", &n_ver->sp);
		fscanf(fp, "%d", &n_ver->lunghezza);
		fscanf(fp, "%d", &n_ver->qt);
		fscanf(fp, "%s", n_cod->code);

		ins_elem(&lista, n_cod, n_ver);

    }


		fclose(fp);
		return lista;
}

/* funzione di inserimento in lista*/
void ins_elem(Codice** lista, Codice* cod, Verga* ver)
{
	Codice* temp;
char i ;
	temp = *lista;

	while (temp != NULL )
	{
		if (strcmp(temp->code , cod->code)== 0)
		{
		    for (i = temp->indice ; i < temp->indice + ver->qt ; i++)
            {
                temp->lista[i].lato1 = ver->lato1;
                temp->lista[i].lato2 = ver->lato2;
                temp->lista[i].lunghezza = ver->lunghezza;
                temp->lista[i].qt = 1;
                temp->lista[i].sp = ver->sp;

            }
            temp->indice += ver->qt;

			break;
/*migliorabile togliere il break*/
		}
		temp = temp->next;
	}
		if (temp == NULL)
		{
		    cod->lista = (Verga*)malloc(sizeof(Verga)*MAX);/*alloco memoria all array della struttura*/


			for (i = 0 ; i < ver->qt ; i++) /*lo imposto fino al quantitatico della nuova struttura*/
            {
                cod->lista[i].lato1 = ver->lato1;
                cod->lista[i].lato2 = ver->lato2;
                cod->lista[i].lunghezza = ver->lunghezza;
                cod->lista[i].qt = 1;
                cod->lista[i].sp = ver->sp;
              
            }
            cod->indice += ver->qt;


			cod->next = *lista;
			*lista = cod;

		}

}


/*stampa della lista */
void stampa(Codice* lista)
{
	Codice* temp;

	char i ;

	temp = lista;

	while (temp != NULL)
	{
		printf("codice: %s \n", temp->code);
		printf("Indice: %d \n", temp->indice);

		for ( i = 0 ; i < temp->indice ; i++)
		{
			printf("tubolare %d x %d L%d\n qt %d\n", temp->lista[i].lato1, temp->lista[i].lato2, temp->lista[i].lunghezza , temp->lista[i].qt);

		}

		temp = temp->next;
	}
}

int *gen_masc(int l_arr)
{

    int *array;
    char i;


    array = ( int*)malloc(sizeof(int)*l_arr);

       for(i = 0; i < l_arr ; i++)
       {
           array[i]= ( rand()%2);
       }

return array;
}


void calc_tub(Codice *lista)
{
    Codice *temp;
    
    FILE* fs;

    int controllo;
    int *ord_tagl;
    int i ;
    int resto;

    fs = fopen("Output_verghe.txt", "w+");
    temp = lista;

    while ( temp != NULL)
    {
        controllo = 1;
        
        while ( controllo == 1)
        {
            ord_tagl = tagli(temp->lista,1000,temp->indice); /* estrazione ordine di taglio*/


            puts("\nTagli verga 6000");
            fprintf(fs,"\nTagli verga 6000\n");
            
            
            resto = 6000;

        for(i=0 ; i < temp->indice ; i++)
            {
                  
                if(ord_tagl[i] == 1)
                {
                    resto = resto - temp->lista[i].lunghezza;
                    
                    printf("%dx%d sp%d L = %d \n", temp->lista[i].lato1, temp->lista[i].lato2, temp->lista[i].sp,temp->lista[i].lunghezza);
                    fprintf(fs, "%dx%d sp%d L = %d \n", temp->lista[i].lato1, temp->lista[i].lato2, temp->lista[i].sp, temp->lista[i].lunghezza);
                    temp->lista[i].qt = 0;
                }
            }
        printf(" Resto = %d\n", resto);
        fprintf(fs,"Resto = %d\n", resto);

            controllo = contr_arr(temp->lista, temp->indice);
           
        }

        
        temp = temp->next;
    }
    
    fclose(fs);

}

int *tagli (Verga *ver, int ricor , int l_arr)
{
    char i;

    int *v_1;
    int *v_2;

    int l_1;
    int l_2;
    
    
    l_1 = 0;

    do
    {
        l_2 = 0;

        v_2 = gen_masc(l_arr);

        for ( i = 0 ; i < l_arr ; i++)
        {
            if(v_2[i] == 1 && ver[i].qt > 0)
            {
                l_2 = l_2 + ver[i].lunghezza;
            }
            if (v_2[i] == 1 && ver[i].qt == 0) /*lo azzero se le quantità sono a zero */
            {
                v_2[i] = 0;
            }


        }
        
    } while (l_2 > 6000 );

    
    if (ricor <= 0)
    {
 
        return v_2 ;
    }
      /*  printf("--L%d\n", l_2);*/
        ricor--;

    v_1 = tagli(ver,ricor,l_arr);


    for(i= 0 ; i < l_arr ; i++)
    {
        if(v_1[i]==1)
        {
            l_1 = l_1 + ver[i].lunghezza;
        }

    }

    if( l_1 > l_2)
    {
        free(v_2);
        return v_1;
    }
    else
        {
        free(v_1);
        return v_2;
        }

}


int contr_arr(Verga *ver , int indice)
{
    char i ;

    for(i = 0 ; i < indice ; i++)
    {
        if(ver[i].qt == 1)
        {

            return 1;
            
        }
    }

    return 0;
}

int main()
{
	Codice *lista;
    srand(time(NULL));

	lista = leggi();

    /*stampa(lista);*/

    calc_tub(lista);


	return 0;
}
