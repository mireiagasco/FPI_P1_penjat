#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEM 40
#define MAX_INTENTS 10
#define MIN 1
#define TRUE 1
#define FALSE 0

int main()
{
    FILE *fit;
    char nom[MAX_ELEM], paraula[MAX_ELEM], resposta[MAX_ELEM], lletra,s_n, llet_util[MAX_ELEM];
    int cont, recompte, num_aleat, intents, i, j, num_lletres, no_valid, repetida, repetir, num_paraules, encerts, errors;

    /*inici*/

    fit=fopen("paraules.txt", "r");

    /*comprovem que s'ha pogut obrir el fitxer*/
    if (fit==NULL)
    {
        printf("Hi ha algun error amb el fitxer");
    }
    else    /*si s'ha obert correctament seguim amb el programa*/
    {
        /*comptem el nombre de paraules que hi ha al fitxer*/
        fscanf(fit, "%s",paraula);
        num_paraules=0;
        while (!feof(fit)) /*mentre no s'acabi el fitxer*/
        {
            num_paraules++;
            fscanf(fit, "%s", paraula);
        }
        if(num_paraules>10 || num_paraules<1)     /*si el fitxer està buit o conté mes de 10 paraules*/
        {
            if (num_paraules>10)
            {
                printf("Hi ha massa paraules al fitxer (el maxim es 10)");
            }
            if (num_paraules<1)
            {
                printf("El fitxer no conte paraules");
            }
        }
        else
        {
            /*demanem el nom, això no es repetirà*/
            printf("Benvingut/da al joc del penjat! Com et dius?\n");
            gets(nom);
            system("cls");

            /*mostrem les normes del joc*/
            printf("Normes del joc:\n");
            printf("-Tens 10 intents.\n");
            printf("-Introdueix nomes una lletra cada vegada, encara que ja sapigues la paraula.\n");
            printf("-Si encertes la lletra, no se't descomptara cap intent.\n");
            printf("-Si falles la lletra, perdras un intent.\n");
            printf("-Guanyes quan encertes la paraula abans que s'acabin els intents.\n");
            printf("Bona sort!\n");
            system("pause");
            system("cls");

            /*inicialitzem variables*/
            encerts=0;
            errors=0;

            do  /*inici del joc, part que es repeteix*/
            {
                /*obtenim un numero aleatori*/
                srand(time(NULL));
                num_aleat=rand()%(num_paraules+1);

                /*obtenim la paraula corresponent*/
                cont=0;
                fclose(fit);
                fit=fopen("paraules.txt", "r");
                while(cont<num_aleat)
                {
                    fscanf(fit, "%s", paraula);
                    cont++;
                }

                /* generem la paraula resposta*/
                i=0;
                num_lletres=0;
                while(paraula[i]!='\0')
                {
                    resposta[i]='_';    /*igualem el nombre de lletres de la resposta a les de la paraula*/
                    num_lletres++;      /*comptem quantes lletres te*/
                    i++;
                }
                if(paraula[i]=='\0') /*afegim el centinella al final de la paraula resposta*/
                {
                    resposta[i]='\0';
                }

                /*comença el joc*/

                /*inicialitzem variables*/
                j=0;
                llet_util[j]='\0';  /*posem a zero la taula amb les lletres utilitzades*/
                intents=MAX_INTENTS;
                recompte=1;
                printf("%s (%d lletres)\n", resposta, num_lletres);

                /*mentre no final i no encertat*/
                while (intents>0 && recompte!=0)
                {
                    repetida=TRUE;  /*inicialitzem a true per fer que entri al bucle*/
                    no_valid=FALSE;
                    printf("Et queden %d intents. %s, quina lletra apostes?",intents, nom);

                    /*comprovem que la lletra sigui valida i no estigui repetida*/
                    while(no_valid || repetida)
                    {
                        scanf(" %c",&lletra);
                        no_valid=(lletra<'a' || lletra>'z');

                        if(no_valid)    /*si no es valida avisem a l'usuari*/
                        {
                            printf("Valor no valid, escriu una lletra (en minuscules):");
                        }

                        repetida=FALSE; /*la posem a fals*/

                        i=0;
                        while(llet_util[i]!='\0')   /*comprovem si esta repetida*/
                        {
                            if (llet_util[i]==lletra)
                            {
                                repetida=TRUE;
                            }
                            i++;
                        }

                        if(repetida)    /*si esta repetida, avisem a l'usuari*/
                        {
                            printf("Ja has utilitzat aquesta lletra, indica'n una altra:");
                        }
                    }

                    if (j!=0)   /*només posem coma a partir de la segona lletra*/
                    {
                        llet_util[j]=',';
                        j++;
                    }
                    llet_util[j]=lletra;    /*posem la nova lletra a lletres utilitzades*/
                    llet_util[j+1]='\0';
                    j++;

                    cont=0;
                    i=0;
                    while(paraula[i]!='\0') /*mentre no s'acabi la paraula*/
                    {
                        if(paraula[i]==lletra) /*si la lletra coincideix la col·loquem a la resposta*/
                        {
                            resposta[i]=lletra;
                            cont++;     /*aquest contador ens diu si la lletra esta a la paraula o no*/
                        }
                        i++;
                    }

                    if (cont!=0) /*si la lletra esta a la paraula*/
                    {
                        printf("%s      Lletres utilitzades: %s\nMolt be!",resposta,llet_util);
                    }
                    else        /*si la lletra no esta a la paraula*/
                    {
                        intents--;
                        printf("%s      Lletres utilitzades: %s\nOh, la lletra %c no esta a la paraula.", resposta,llet_util,lletra);
                    }
                    i=0;
                    recompte=0;
                    while (resposta[i]!='\0')   /*comprovem si s'ha encertat la paraula*/
                    {
                        if (resposta[i]=='_')
                        {
                            recompte++;     /*si el recompte de '_' és diferent de 0, vol dir que encara no ha trobat la paraula*/
                        }
                        i++;
                    }
                }
                if(recompte==0)     /*si ha encertat la paraula*/
                {
                    printf("\nEnhorabona %s! La paraula es %s\n",nom, paraula);
                    encerts++;
                }
                else                /*si ha fallat*/
                {
                    printf("\nLlastima %s! La paraula era %s\n", nom, paraula);
                    errors++;
                }
                system("pause");

                system("cls");

                /*preguntem si es vol jugar de nou*/
                printf("%s, vols jugar de nou? (escriu 's' per a si i 'n' per a no)\n", nom);
                scanf(" %c", &s_n);
                while ((s_n!='s')&&(s_n!='n')&&(s_n!='S')&&(s_n!='N'))  /*en cas que l'usuari no hagi escrit ni s ni n*/
                {
                    printf("Escriu s per a si i n per a no \n");
                    scanf(" %c", &s_n);
                }
                repetir=((s_n=='s')||(s_n=='S'));

            }while(repetir);

            /*si no vol jugar mes, informem de les partides guanyades i perdudes*/
            printf("Partides guanyades: %d\nPartides perdudes: %d\n", encerts, errors);
            printf("Fins aviat!\n");
            system("pause");
        }
    }
    fclose(fit);
    return 0;
}
