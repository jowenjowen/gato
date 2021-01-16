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

void ImprimeGato(int*** jugador);
int*** IngresaGato(int*** jugador, int turno, int solitario);
int ChecaFin(int*** jugador);
class Juego {
private:
    int fin = 0, turno = 0, i, j;
    int*** jugador = (int***) malloc(2*sizeof(int**));
public:
    Juego() {
        for (i = 0; i < 2; i++)
        {
            jugador[i] = (int**) malloc(3*sizeof(int*));
            for (j = 0; j < 3; j++)
            {
                jugador[i][j] = (int*) malloc(3*sizeof(int));
            }
        }
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
            {
                jugador[0][i][j] = 0;
                jugador[1][i][j] = 0;
            }
        }
    };
    void acompletate() {
        do
        {
            fin = ChecaFin(jugador);
            ImprimeGato(jugador);
            if(!fin)
            {
                jugador = IngresaGato(jugador, turno, 0);
                turno = !turno;
            }
        } while (!fin);
    }
    int quienGano() {
        return fin;
    }
};

void titulo();

int main()
{
    system("cls");
    titulo();
    Juego juego;
    juego.acompletate();
    int ganador = juego.quienGano();
    // anuncia el ganador
    if (ganador != 3) printf("\nHa ganado el jugador %d.", ganador);
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

void ImprimeGato(int*** jugador)
{
    int i, j;
    for(i = 0; i < 15; i++)
    {
        for(j = 0; j < 3; j++)
        {
            if (jugador[1][i/5][j] == 1)
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
            else if(jugador[0][i/5][j] == 1)
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

int*** IngresaGato(int*** jugador, int turno, int solitario)
{
    int valor;
    printf("\n\n");
    if (!solitario)
    {
        printf("Turno del jugador %d.\n", turno + 1);
        printf("Jugador %d, ingresa el n%cmero de acuerdo al siguiente ejemplo:\n\n", turno + 1, 163);
    }
    else
    {
        printf("Tu turno.\nIngresa el n%cmero de acuerdo al siguiente ejemplo:\n\n", 163);
    }
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
        if(jugador[0][(valor-1)/3][(valor-1)%3] || jugador[1][(valor-1)/3][(valor-1)%3]) printf("Valor invalido: Elige un lugar no ocupado.\n");

    } while(jugador[0][(valor-1)/3][(valor-1)%3] || jugador[1][(valor-1)/3][(valor-1)%3]);
    jugador[turno][(valor-1)/3][(valor-1)%3] = 1;
    return jugador;
}

int ChecaFin(int*** jugador)
{
    int fin, k, i, j;
    for(i = 0, fin = 3; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (jugador[0][i][j] == 0 && jugador[1][i][j] == 0) fin = 0;
        }
    }
    for(k = 0; k < 2; k++)
    {
        for(i = 0; i < 3; i++)
        {
            if(jugador[k][i][0]==jugador[k][i][1]&&jugador[k][i][1]==jugador[k][i][2]&&jugador[k][i][0]==1)
                fin = k + 1;
            if(jugador[k][0][i]==jugador[k][1][i]&&jugador[k][1][i]==jugador[k][2][i]&&jugador[k][0][i]==1)
                fin = k + 1;
        }
        if(jugador[k][0][0]==jugador[k][1][1]&&jugador[k][1][1]==jugador[k][2][2]&&jugador[k][0][0]==1)
            fin = k + 1;
        if(jugador[k][2][0]==jugador[k][1][1]&&jugador[k][1][1]==jugador[k][0][2]&&jugador[k][2][0]==1)
            fin = k + 1;
    }
    return fin;
}
