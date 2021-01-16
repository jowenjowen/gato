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
int main()
{
    system("cls");
    printf(" ____              _____    ____\n");
    printf("/    %c      /%c       |     /    %c\n", 92, 92, 92);
    printf("|   _      /__%c      |     |    |\n", 92);
    printf("|    %c    /    %c     |     |    |\n", 92, 92);
    printf("%c____/   /      %c    |     %c____/\n\n\n", 92, 92, 92);
    int select = 1, fin = 0, turno = 0, valor = 1, i, j, k;
    int*** jugador = (int***) malloc(2*sizeof(int**));
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
    do
    {
        if (select != 0 && select != 1 && select != 2) printf("Valor inv%clido.\n\n", 160);
        printf("Para jugar solo, ingresa 1.\nPara multijugador, ingresa 2.\nPara terminar, ingresa 0.\n\nIngresa el valor: ");
        scanf("%d", &select);
        if (select == 1)
        {
            int esnpc;
            printf("\n\nQui%cn empieza?\nT%c: Ingresa 1.\nLa computadora: Ingresa 2.\nIngresa valor: ", 130, 163);
            do
            {
                scanf("%d", &esnpc);
            } while (esnpc != 1 && esnpc != 2);
            esnpc--;
            printf("\n\n");
            do
            {
                fin = ChecaFin(jugador);
                ImprimeGato(jugador);
                if (!fin && esnpc == turno)
                {
                    jugador = IngresaGato(jugador, turno, 1);
                }
                else if(!fin)
                {
                    printf("\nTurno de la computadora en: "); Sleep(500);
                    printf("3... "); Sleep(500);
                    printf("2... "); Sleep(500);
                    printf("1...\n\n"); Sleep(500);
                    int ver1, ver0, hor1, hor0, diag1_1, diag1_0, diag2_1, diag2_0;
                    int siguiente = 0;
                    for (i = 0; i < 3; i++) //Ganar
                    {
                        for (j = 0, ver1 = 0, ver0 = 0, hor1 = 0, hor0 = 0, diag1_1 = 0, diag1_0 = 0, diag2_1 = 0, diag2_0 = 0; j < 3; j++)
                        {
                            if (jugador[turno][i][j] == 1) {ver1++;}
                            if (jugador[1][i][j] == 0 && jugador[0][i][j] == 0) {ver0 = j + 1;}
                            if (jugador[turno][j][i] == 1) {hor1++;}
                            if (jugador[1][j][i] == 0 && jugador[0][j][i] == 0) {hor0 = j + 1;}
                            if (jugador[turno][j][j] == 1) {diag1_1++;}
                            if (jugador[1][j][j] == 0 && jugador[0][j][j] == 0) {diag1_0 = j + 1;}
                            if (jugador[turno][j][2-j] == 1) {diag2_1++;}
                            if (jugador[1][j][2-j] == 0 && jugador[0][j][2-j] == 0) {diag2_0 = j + 1;}
                        }
                        if (ver1 == 2 && !siguiente && ver0) {jugador[turno][i][ver0-1] = 1; siguiente = 1; printf("horNPC");}
                        if (hor1 == 2 && !siguiente && hor0) {jugador[turno][hor0-1][i] = 1; siguiente = 1; printf("verNPC");}
                        if (diag1_1 == 2 && !siguiente && diag1_0) {jugador[turno][diag1_0-1][diag1_0-1] = 1; siguiente = 1; printf("diag1NPC");}
                        if (diag2_1 == 2 && !siguiente && diag2_0) {jugador[turno][diag2_0-1][1-diag2_0] = 1; siguiente = 1; printf("diag2NPC");}
                    }
                    for (i = 0; i < 3; i++) //Blockear
                    {
                        for (j = 0, ver1 = 0, ver0 = 0, hor1 = 0, hor0 = 0, diag1_1 = 0, diag1_0 = 0, diag2_1 = 0, diag2_0 = 0; j < 3; j++)
                        {
                            if (jugador[!turno][i][j] == 1) {ver1++;}
                            if (jugador[1][i][j] == 0 && jugador[0][i][j] == 0) {ver0 = j+1;}
                            if (jugador[!turno][j][i] == 1) {hor1++;}
                            if (jugador[1][j][i] == 0 && jugador[0][j][i] == 0) {hor0 = j+1;}
                            if (jugador[!turno][j][j] == 1) {diag1_1++;}
                            if (jugador[1][j][j] == 0 && jugador[0][j][j] == 0) {diag1_0 = j+1;}
                            if (jugador[!turno][j][2-j] == 1) {diag2_1++;}
                            if (jugador[1][j][2-j] == 0 && jugador[0][j][2-j] == 0) {diag2_0 = j+1;}
                        }
                        if (ver1 == 2 && !siguiente && ver0) {jugador[turno][i][ver0-1] = 1; siguiente = 1;}
                        if (hor1 == 2 && !siguiente && hor0) {jugador[turno][hor0-1][i] = 1; siguiente = 1;}
                        if (diag1_1 == 2 && !siguiente && diag1_0) {jugador[turno][diag1_0-1][diag1_0-1] = 1; siguiente = 1;}
                        if (diag2_1 == 2 && !siguiente && diag2_0) {jugador[turno][diag2_0-1][3-diag2_0] = 1; siguiente = 1;}
                    }
                    if (esnpc == 1) //Primer turno
                    {
                        for (i = 0, valor = 1; i < 3; i++)
                        {
                            for (j = 0; j < 3; j++)
                            {
                                if (jugador[0][i][j] == 1 || jugador[1][i][j] == 1) {valor = 2;}
                            }
                        }
                        if (valor == 1 && !siguiente) {jugador[turno][0][0] = 1; siguiente = 1;}
                    }
                    if ((jugador[!turno][0][0] == 1 && jugador[!turno][2][2] == 1) || (jugador[!turno][0][2] == 1 && jugador[!turno][2][0] == 1)) //Estrategia para extremos opuestos.
                    {
                        if (!jugador[0][1][0] && !jugador[1][1][0] && !siguiente) {jugador[turno][1][0] = 1; siguiente = 1;}
                        if (!jugador[0][0][1] && !jugador[1][0][1] && !siguiente) {jugador[turno][0][1] = 1; siguiente = 1;}
                        if (!jugador[0][2][1] && !jugador[1][2][1] && !siguiente) {jugador[turno][2][1] = 1; siguiente = 1;}
                        if (!jugador[0][1][2] && !jugador[1][1][2] && !siguiente) {jugador[turno][1][2] = 1; siguiente = 1;}
                    }
                    if (jugador[!turno][0][1] && jugador[!turno][1][0] && !jugador[turno][0][0] && !siguiente) {jugador[turno][0][0] = 1; siguiente = 1;}/////////
                    if (jugador[!turno][0][1] && jugador[!turno][1][2] && !jugador[turno][0][2] && !siguiente) {jugador[turno][0][2] = 1; siguiente = 1;}//Para la estrategia
                    if (jugador[!turno][1][0] && jugador[!turno][2][1] && !jugador[turno][2][0] && !siguiente) {jugador[turno][2][0] = 1; siguiente = 1;}//de Mike
                    if (jugador[!turno][1][2] && jugador[!turno][2][1] && !jugador[turno][2][2] && !siguiente) {jugador[turno][2][2] = 1; siguiente = 1;}/////////
                    if (jugador[0][1][1] == 0 && jugador[1][1][1] == 0 && !siguiente) {jugador[turno][1][1] = 1; siguiente = 1;} //Centro
                    for (i = 0; i < 3; i++) //Simetría
                    {
                        for (j = 0; j < 3; j++)
                        {
                            if ((jugador[0][i][j] == 1 || jugador[1][i][j] == 1) && jugador[0][2-i][2-j] == 0 && jugador[1][2-i][2-j] == 0 && !siguiente) {jugador[turno][2-i][2-j] = 1; siguiente = 1;}
                        }
                    }
                    for (i = 0; i < 2; i++) //Esquinas
                    {
                        for (j = 0; j < 2; j++)
                        {
                            if (jugador[0][2*i][2*j] == 0 && jugador[1][2*i][2*j] == 0 && !siguiente) {jugador[turno][2*i][2*j] = 1; siguiente = 1;}
                        }
                    }
                    while (!siguiente) //Random
                    {
                        i = rand()%3;
                        j = rand()%3;
                        if (jugador[0][i][j] == 0 && jugador[1][i][j] == 0) {jugador[turno][i][j] = 1; siguiente = 1;}
                    }
                }
                turno = !turno;
            } while (!fin);
            if (fin == esnpc + 1)
            {
                printf("\n\nHas ganado!!!");
                Sleep(500);
                printf(".");
                Sleep(500);
                printf(".");
                Sleep(500);
                printf(". ");
                Sleep(500);
                printf("No cre%c que eso fuera posible...", 161);
            }
            else if (fin == 3)
            {
                printf("\n\nEmpate.");
            }
            else
            {
                printf("\n\nPerdiste...");
            }
        }
        if (select == 2)
        {
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
            if (fin != 3) printf("\nHa ganado el jugador %d.", fin);
            else printf("\nEmpate.");
        }
    } while (select != 0 && select != 1 && select != 2);
    return 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                            //
//                                               Funciones                                                    //
//                                                                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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
