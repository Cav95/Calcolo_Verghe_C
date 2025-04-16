#define LEN 16
#define MAX 50


typedef struct Verghe
{
	int lato1;
	int lato2;
	int sp;

	int lunghezza;
	int qt;

}Verga;
typedef struct Codici
{
	char code[LEN];

	int indice;
	struct Verghe *lista;

	struct Codici* prev;
	struct Codici* next;
}Codice;


/*lettura del file txt e creazione della lista */
Codice* leggi();

/* funzione di inserimento in lista*/
void ins_elem(Codice** lista, Codice* cod, Verga* ver);

/*stampa della lista */
void stampa(Codice* lista);

/*genera maschera di bit*/
char *gen_masc(int l_arr);

/*calcolo e stampa del tubolare*/
void calc_tub(Codice *lista);

/*genera tagli esportando la maschera di bit corretta*/
char *tagli (Verga *ver, int ricor , int l_arr);

/*controllo array*/
int contr_arr(Verga *ver , int indice);
