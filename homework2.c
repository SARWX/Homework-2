#include <stdio.h>
#include <stdlib.h>

struct Knot
{
    char name[20];
    int* edge;
};

int power(int n, int pow) {   // возводит n в степень pow
    int i, answer = 1;
    for (i = 0; i < pow; i++)
        answer *= n;
    return(answer);
}

int main() {
    int Knots = 0, Edges = 0;
    int connected = 0, unconnected = 0;
    int i, j, k;

    printf("Input the number of your knots: ");
    scanf("%d", &Knots);
                printf("%d", Knots);
    printf("\nInput the number of your edges: ");
    scanf("%d", &Edges);
                printf("%d", Edges);

    int *uncon = calloc(Knots, (sizeof(int) * Edges)); //Массив не связных вершин
    struct Knot *knot;      // Объявили указатель на структуру
    knot = (struct Knot *) calloc(Knots, sizeof(struct Knot *) + (sizeof(int) * Edges)*Knots);        // Задали число массивов
    if(!knot) {
        printf ("Allocation failure.");
        exit (1);
    }

    printf("\nInput names of yours knots via Enter: \n");

    for(i = 0; i < Knots; i++) {
        scanf("%s", knot[i].name);
    }

    printf("\t|");
    for(i = 1; i <= Edges; i++)
        printf("%d|", i);
    printf("\n");

    getchar();
    for(i = 0; i < Knots; i++) {
        printf("%s\t|", knot[i].name);

        knot[i].edge = (int*) calloc(Edges, sizeof(int));
        if(!knot[i].edge) {
            printf ("Allocation failure.");
            exit (1);
        }

        for (j = 0; j < Edges; j++){
            int x = (getchar() - '0');
            knot[i].edge[j] = x;
            getchar();
            connected += x;
        }
        if (connected == 0) {
            uncon[unconnected] = i;  //запоминаем несвязные вершины
            unconnected++;    
        }
        connected = 0;
    }
// Пишем файл
    int trig = 0;

    FILE *file;
    file = fopen("./graph.gv", "w+t");
    //Пишем в файл
    fprintf(file, "graph HomeWork {\n");
    for (j = 0; j < Edges; j++) {
        for (i = 0; i < Knots; i++) {
            if (knot[i].edge[j] == 1) {
                if (trig == 0) {
                    fprintf(file, "\t%s -- ", knot[i].name);
                    trig = (i + 1);     // +1 чтобы trig не равнялся 0
                }
                else {
                    fprintf(file, "%s\n", knot[i].name);
                    trig = 0;
                }
            }      
        }
        if (trig != 0) {
            fprintf(file, "%s\n", knot[(trig-1)].name);
            trig = 0;
        }    
    }
    //Пишем несвязные вершины:
    for (i = 0; i < unconnected; i++) {
        fprintf(file, "\t%s\n", knot[uncon[i]].name);
    }
    fprintf(file, "}");
    //Закрываем файл
    fclose(file);

    // Проверка на связность
    int answer = 0, mask = 0;

    if (unconnected)
        printf("\nYour graph is not connected");
    else {
        for(k = 0; k < Knots; k++) {
            for (i = 0; i < Knots; i++) {
                for (j = 0; j < Edges; j++){
                    if (knot[i].edge[j] == 1)
                        mask += power(2,j); //создаем двоичную маску
                }
                if (((answer & mask) != 0) || (i == 0))
                    answer = answer | mask;
                mask = 0;
            }
        }
        if (answer == (power(2, Edges) - 1))
            printf("\nYour graph is connected");
        else
            printf("\nYour graph is not connected");
    }
    return 0;
}
