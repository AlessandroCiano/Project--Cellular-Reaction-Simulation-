//Alessandro Costanzo Ciano 887896
#include<stdlib.h>
#include<stdio.h>
#include <string.h>
#include <stdbool.h>

#define N 6
#define K 5

struct reazioni{
    char r; //identificatore alfabetico
    int rea[2]; //reagenti
    int inib; //inibitori
    int prod[2]; //prodotti
    int n; //avvenimenti totali
    int a; //avvenimento locale [vedi "main" //reazioni]
};

//alloca memoria a un puntatore e salva le sostanze dichiarate, convertendole in interi
//salva anche la lunghezza dell'array di tipo puntatore allocato
void riempis(int **vec, int **lvec){ //passi (riga di comando)
    char str1[200];
    char newStr[N][5];
    int ctr=0;

    fgets(str1, sizeof str1, stdin);
    for(int i=0, j=0; i<=(strlen(str1)); i++)
    {
        //se trova "spazio" o NULL, assegna NULL all'ultimo elemento di newStr[ctr]
        if(str1[i]==' '||str1[i]=='\0')
        {
            newStr[ctr][j]='\0';
            ctr++;  //passa alla parola successiva
            j=0;    //imposta il primo posto della stringa successiva
        }else{
            newStr[ctr][j]=str1[i];
            j++;
        }
    }
    if(ctr>N){ //non ha senso che vengano date più di N sostanze
        exit(EXIT_FAILURE);
    }
    //alloca spazio e vi salva i valori, convertendo in interi
    *vec=(int*)malloc(ctr*sizeof(int));
    for(int i=0; i<ctr; i++){
        *(i+*vec)=atoi(newStr[i]);
    }
    *lvec=(int*)malloc(sizeof(int));
    **lvec=ctr;
    return;
}

//salva i dati della reazione numero "nreac" dichiarati con un puntatore struct reazioni
void riempir(struct reazioni **struc, int nreac){
    char str1[30];
    char newStr[K][5];
    int ctr=0;

    fgets(str1, sizeof str1, stdin);
    for(int i=0, j=0; i<=(strlen(str1)); i++)
    {
        if(str1[i]==' '||str1[i]=='\0')
        {
            newStr[ctr][j]='\0';
            ctr++;
            j=0;
        }else{
            newStr[ctr][j]=str1[i];
            j++;
        }
    }
    if(ctr>6){ //non ha senso che nelle reazioni vi siano più di 5 sostanze (+ 1 lettera identificativa)
        exit(EXIT_FAILURE);
    }
    //imposta a 0 gli avvenimenti
    (nreac+(*struc))->n=0;
    //salva i valori
    (nreac+(*struc))->r=newStr[0][0];
    (nreac+(*struc))->rea[0]=atoi(newStr[1]);
    (nreac+(*struc))->rea[1]=atoi(newStr[2]);
    (nreac+(*struc))->inib=atoi(newStr[3]);
    (nreac+(*struc))->prod[0]=atoi(newStr[4]);
    (nreac+(*struc))->prod[1]=atoi(newStr[5]);
    return;
}

//valuta se una reazione avviene o meno
bool avreazione(int **sos, int nsos, struct reazioni reazione){
    //presenza inibitori?
    for(int i=0; i<nsos; i++){
        if(*(i+*sos)==reazione.inib){
            return false;
        }
    }
    //presenza entrambi reagenti?
    int r1=0, r2=0;
    for(int i=0; i<nsos; i++){
        if(*(i+*sos)==reazione.rea[0]){
            r1++;
        }
        if(*(i+*sos)==reazione.rea[1]){
            r2++;
        }
    }
    if(r1==1 && r2==1){
        return true;
    }else{
        return false;
    }
}

//ordina vettore con bubblesort (utile per la funzione Xdoppioni)
void bubblesort(int **v, int lv){
    int var, nscambi;
    do {
        nscambi=0;
        for(int i=0; i<lv-1; ++i){
            if(*(i+*v)>*(i+1+*v)){
                var=*(i+*v);
                *(i+*v)=*(i+1+*v);
                *(i+1+*v)=var;
                ++nscambi;
            }
        }
    } while(nscambi!=0);
}

//elimia doppioni di un vettore ordinadolo
//restituisce la nuova lunghezza
int Xdoppioni(int **v, int lv){
    int var;
    bubblesort(v, lv);
    for(int i=0; i<lv-1; i++){
        if(*(i+*v)==*(i+1+*v)){//confronta ogni elemento con il successivo
            //scambio il secondo doppione con l'ultimo elemento
            var=*(lv-1+*v);
            *(lv-1+*v)=*(i+1+*v);
            *(i+1+*v)=var;
            //riduco di 1 la lunghezza e il vettore relativo
            lv--;
            *v=realloc(*v, lv*sizeof(int));
            bubblesort(v, lv);
            lv=Xdoppioni(v, lv); //il valore corretto calcolato dalla ricorsione più interna viene memorizzato
        }
    }
    return lv;
}


int main(int argc, char* argv[]){ //passi max simulazione (riga di comando)
    int passimax=0;
    int *sostanze;
    int *nsostanze;
    struct reazioni *reazione;
    int nreaz=0; //numero totale reazioni avvenute (in un passo)

    passimax=atoi(argv[1]);

    riempis(&sostanze, &nsostanze);

    //reazioni
    reazione=(struct reazioni*)malloc(K*sizeof(struct reazioni));
    for(int j=0; j<K; j++){
        riempir(&reazione, j);
    }

    //riordine e stampa sostanze iniziali
            bubblesort(&sostanze, *nsostanze);
            printf("Sostanze passo 0 = {");
            for(int i=0; i<*nsostanze-1; i++){
                printf("%d, ", *(i+sostanze));
            }
            printf("%d}\n", *(*nsostanze-1+sostanze));
    //"p", "j" e "i" si riferiscono rispettivamente a passo, reazione e sostanze
    for(int p=0, j=0, i=0; p<passimax; p++){
        nreaz=0;
        //valutazione avvenimento locale reazioni
        for(j=0; j<K; j++){
            if(avreazione(&sostanze, *nsostanze, *(j+reazione))==true){
                ((j+reazione)->n)++; //incremento avvenimenti totali di una reazione
                ((j+reazione)->a)=1; //avvenimento locale = positivo
                nreaz++; //incremento numero di reazioni contemporanee locali
            }else{
                ((j+reazione)->a)=0; //avvenimento locale = negativo
            }
        }
        //calcolo nuove sostanze e stampa di queste
        if(nreaz==0){
            printf("Al passo %d non avvengono reazioni (fine simulazione)\n", p+1);
            break;
        }else{
            //riempio sostanze (dagli estremi verso l'interno), eliminando lo spazio per i doppioni
            free(sostanze);
            sostanze=NULL;
            sostanze=(int*)malloc(2*nreaz*sizeof(int));
            j=0;
            i=0;
            while(i<nreaz){
                if((j+reazione)->a==1){
                    *(i+sostanze)=(j+reazione)->prod[0];
                    *((2*nreaz-1-i)+sostanze)=(j+reazione)->prod[1];
                    i++;
                }
                j++;
            }
            *nsostanze=Xdoppioni(&sostanze, 2*nreaz); //elimina doppioni e riordina
            //stampa sostanze attuali
            printf("Sostanze passo %d = {", p+1);
            for(i=0; i<*nsostanze-1; i++){
                printf("%d, ", *(i+sostanze));
            }
            printf("%d}\n", *(*nsostanze-1+sostanze));
        }
    }
    //stampa di quante volte avviene ogni reazione
    for(int j=0; j<K; j++){
        printf("Avvenimenti reazione [%c] = %d\n", (j+reazione)->r, (j+reazione)->n);
    }

    free(sostanze);
    free(nsostanze);
    free(reazione);

    exit(EXIT_SUCCESS);
}
