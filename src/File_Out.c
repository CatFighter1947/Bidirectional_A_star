#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include "Var_str.c"
#include "Alg.c"
#include "Gen_File.c"



int main() {
    srand(time(NULL)); 
    
    int sides = 0;
    int number = 0;
    int height = 0;
    int width = 0;

    printf("Input parameters of map:\n");

    printf("Input width: ");
    scanf("%d", &width);

    printf("Input height: ");
    scanf("%d", &height);

    printf("Input number of obstacles: ");
    scanf("%d", &number);

    printf("Input side of plane: ");
    scanf("%d", &sides);

    printf("Map: \n");
    printf(" \n");

    char Map[height][width];

    CreateMap(number,width,height,Map,sides);

    int **map = Make_matrix(height, width, Map);

    PrintMap(width, height, Map);

    printf("\nInput coordinates of start and end ()\n");

    int xA,yA;
    int xB,yB;


    printf("Coordinates of start(x,y): ");
    scanf("%d %d", &xA, &yA);

    printf("Coordinates of end(x,y): ");
    scanf("%d %d", &xB, &yB);
    printf("\n");


    printf("Map with position of start and end: \n\n");
    Draw_start_end_points(xA,yA,xB,yB,width,height,Map,sides);
    Point start = {xA, yA};
    Point end = {xB, yB};


    PrintMap(width, height, Map);
    
    bidirectionalAStar(&start, &end, height, width, map, Map);

    PrintMap(width, height, Map);

    PrintMapToFile(width, height, Map);

    return 0;
}