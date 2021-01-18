#include <stdio.h>
#include <stdlib.h>
#ifdef WINDOWS
    #include <Windows.h>
#else
    #include <unistd.h> // for usleep

    void Sleep(int milliseconds){ // cross-platform sleep function
        if (milliseconds >= 1000)
            sleep(milliseconds / 1000);
        usleep((milliseconds % 1000) * 1000);
    };
#endif

void ImprimeGato(int** tablero);
int** IngresaGato(int** tablero, int turno);
int ChecaFin(int** tablero);
void titulo();

////////////////////////////////////////////////////////////////////////////////////////////////////////
class Juego {
private:
    int fin = 0, turno = 0, i, j;
    int** tablero = (int**) malloc(3*sizeof(int*));
public:
    Juego() {
        for (i = 0; i < 3; i++)
        {
            tablero[i] = (int*) malloc(3*sizeof(int));
        }
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
            {
                tablero[i][j] = 0;
            }
        }
    };
    void acompletate() {
        do
        {
            fin = ChecaFin(tablero);
            ImprimeGato(tablero);
            if(!fin)
            {
                tablero = IngresaGato(tablero, turno);
                turno = !turno;
            }
        } while (!fin);
    }
    int quienGano() {
        return fin;
    }
};
////////////////////////////////////////////////////////////////////////////////////////////////


int main()
{
    system("cls");
    titulo();
    Juego juego;
    juego.acompletate();
    int ganador = juego.quienGano();
    // anuncia el ganador
    if (ganador != 3) printf("\nHa ganado el tablero %d.", ganador);
    else printf("\nEmpate.");
    return 0;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                            //
//                                               Funciones                                                    //
//                                                                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void titulo() {
    printf(" ____              _____    ____\n");
    printf("/    %c      /%c       |     /    %c\n", 92, 92, 92);
    printf("|   _      /__%c      |     |    |\n", 92);
    printf("|    %c    /    %c     |     |    |\n", 92, 92);
    printf("%c____/   /      %c    |     %c____/\n\n\n", 92, 92, 92);
}

void ImprimeGato(int** tablero)
{
    int i, j;
    for(i = 0; i < 15; i++)
    {
        for(j = 0; j < 3; j++)
        {
            if (tablero[i/5][j] == 1)
            {
                if ((i + 1) % 5 == 1)
                {printf("  ___  ");}
                else if ((i + 1) % 5 == 2)
                {printf(" /   %c ", 92);}
                else if ((i + 1) % 5 == 3)
                {printf(" |   | ");}
                else if ((i + 1) % 5 == 4)
                {printf(" %c___/ ", 92);}
            }
            else if(tablero[i/5][j] == 2)
            {
                if ((i + 1) % 5 == 1)
                {printf("       ");}
                else if ((i + 1) % 5 == 2)
                {printf("  %c /  ", 92);}
                else if ((i + 1) % 5 == 3)
                {printf("   X   ");}
                else if ((i + 1) % 5 == 4)
                {printf("  / %c  ", 92);}
            }
            else
            {
                if ((i + 1) % 5)
                    printf("       ");
            }
            if((i + 1) % 5 == 0 && i != 14)
            {printf("_______");}
            if(i == 14) printf("       ");
            if(j != 2) printf("|");
        }
        printf("\n");
    }
}

int** IngresaGato(int** tablero, int turno)
{
    int valor;
    printf("\n\n");
    printf("Turno del tablero %d.\n", turno + 1);
    printf("tablero %d, ingresa el n%cmero de acuerdo al siguiente ejemplo:\n\n", turno + 1, 163);
    printf("1|2|3\n");
    printf("%c|%c|%c\n", 196, 196, 196);
    printf("4|5|6\n");
    printf("%c|%c|%c\n", 196, 196, 196);
    printf("7|8|9\n\n");
    do
    {
        printf("Ingresa el valor: ");
        do
        {
            scanf("%d", &valor);
            if(valor < 1 || 9 < valor) printf("Valor invalido: El numero debe estar entre 1 y 9.\n");
        } while (valor < 1 || 9 < valor);
        if(tablero[(valor-1)/3][(valor-1)%3]) printf("Valor invalido: Elige un lugar no ocupado.\n");

    } while(tablero[(valor-1)/3][(valor-1)%3]);
    if (turno == 0)
    {tablero[(valor-1)/3][(valor-1)%3] = 1;}
    else {tablero[(valor-1)/3][(valor-1)%3] = 2;}
    return tablero;
}

int ChecaFin(int** tablero)
{
    int fin, k, i, j;
    for(i = 0, fin = 3; i < 3; i++)//Checa si es empate
    {
        for (j = 0; j < 3; j++)
        {
            if (!tablero[i][j]) fin = 0;
        }
    }

    for(i = 0; i < 3; i++)
    {
        if(tablero[i][0]==tablero[i][1]&&tablero[i][1]==tablero[i][2]&&tablero[i][0]==1)//Checa horizontal jugador 1
            fin = 1;
        if(tablero[i][0]==tablero[i][1]&&tablero[i][1]==tablero[i][2]&&tablero[i][0]==2)//Checa horizontal jugador 2
            fin = 2;
        if(tablero[0][i]==tablero[1][i]&&tablero[1][i]==tablero[2][i]&&tablero[0][i]==1)//Checa vertical jugador 1
            fin = 1;
        if(tablero[0][i]==tablero[1][i]&&tablero[1][i]==tablero[2][i]&&tablero[0][i]==2)//Checa vertical jugador 2
            fin = 2;
    }
    if(tablero[0][0]==tablero[1][1]&&tablero[1][1]==tablero[2][2]&&tablero[0][0]==1)//Checa diagonal (\) jugador 1
        fin = 1;
    if(tablero[0][0]==tablero[1][1]&&tablero[1][1]==tablero[2][2]&&tablero[0][0]==2)//Checa diagonal (\) jugador 2
        fin = 2;
    if(tablero[2][0]==tablero[1][1]&&tablero[1][1]==tablero[0][2]&&tablero[2][0]==1)//Checa diagonal (/) jugador 1
        fin = 1;
    if(tablero[2][0]==tablero[1][1]&&tablero[1][1]==tablero[0][2]&&tablero[2][0]==2)//Checa diagonal (/) jugador 2
        fin = 2;
    return fin;
}
