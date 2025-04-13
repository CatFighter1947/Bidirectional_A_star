int min( int a, int b ){
    if (a < b){ return a; } else { return b; }
}


int max( int a, int b ){
    if (a > b){ return a; } else { return b; }
}

void PrintMapToFile(int cols,int rows,char Map[rows][cols]){
    FILE *f;
    f=fopen("map.txt", "w");
    if (f == NULL) {
        return;
    }
    fputs("  \n", f);
    for (int i = 0; i<rows; i++){
        for (int j = 0; j<cols; j++) {
            if (j == cols - 1) {
                fprintf(f,"%c\n", Map[i][j]);
            } else {
                fprintf(f,"%c", Map[i][j]);
            }
        }
    }
    fclose(f);
}

void PrintMap(int cols, int rows, char Map[rows][cols]) {           // Вывод карты
    printf("\n");
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            printf("%c ", Map[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}



void CheckHorizontal(int x1, int y1, int x2, int y2, int width, int height, char Map[height][width],int sides, int* flag){
    for(int i = min(y1-sides,y2-sides); i < max(y1+sides,y2+sides)+1;i++){
        for(int j=x1-sides; j<x1+sides+1; j++){
            if (Map[i][j] == '*'){
                *flag += 1;
            }
        }
    }
}

void CheckVertical(int x1, int y1, int x2, int y2, int width, int height, char Map[height][width],int sides, int* flag){
    for(int i = y1-sides; i<y1+sides+1;i++){
            for(int j = min(x1-sides, x2-sides); j < max(x1+sides,x2+sides)+1; j++){
                if (Map[i][j] == '*'){
                    *flag += 1;
                }
            }
        }
}

void CheckDiagonal_1(int x1, int y1, int x2, int y2, int width, int height, char Map[height][width],int sides, int* flag){
    for (int i = 0; i <= abs(x2-x1)+1+2*sides; i++) {
            int x = x1 + i - sides;
            int y = y1 + i - sides;
            if ((x > 0) && (x < (width-2)) && (y > 0) && (y < (height-2))) {
                for(int j=x; j<x+3*sides+2;j++){
                    if (Map[y][j] == '*'){
                        *flag += 1; 
                }
            }
        }
    }
}

void CheckDiagonal_2(int x1, int y1, int x2, int y2, int width, int height, char Map[height][width],int sides, int* flag){
    for (int i = 0; i <= abs(x2-x1)+1 + 2*sides; i++) {
            int x = x1 + i - sides;
            int y = y1 - i + sides;
            if ((x >= 0) && (x < (width-2)) && (y >= 0) && (y < (height-2))) {
                for(int j=x; j<x+6*sides+2;j++){
                    if (Map[y][j] == '*'){
                        *flag += 1;
                }
            }
        }
    }
}


int Check(int x1, int y1, int x2, int y2,int width, int height, char Map[height][width],int sides,int direction){
    int flag=0;
    switch (direction) {
    
        case 1:
            CheckHorizontal(x1, y1, x2, y2, width, height, Map, sides, &flag);
            break;
        case 2:
            CheckVertical(x1, y1, x2, y2, width, height, Map, sides, &flag);
            break;
        case 3:
            CheckDiagonal_1(x1, y1, x2, y2, width, height, Map, sides, &flag);
            break;
        case 4:
            CheckDiagonal_2(x1, y1, x2, y2, width, height, Map, sides, &flag);
            break;
    }

    if (flag==0){
        return 1;
    }
    else{
        return 0;
    }
}



void Borders(int cols, int rows, char Map[rows][cols]){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
                Map[i][j] = '*';
            } else {
                Map[i][j] = ' ';
            }
        }
    }
}

void CreateMap(int number,int cols, int rows,char Map[rows][cols],int sides) {
    
    Borders(cols, rows, Map);

    for(int l=0; l<number; l++){
        int direction=1+rand()%4;
        int x1=(sides+1)+rand()%(cols-sides-1);
        int y1=(sides+1)+rand()%(rows-sides-1);
        int xN=(2*sides+1)+rand()%(cols/2);
        int yN=(2*sides+1)+rand()%(rows/2);

        if(Map[y1][x1]!='*'){
            if (direction==1){
                int y2=2+rand()%(rows-sides-1);
                int x2=x1;
                if ((Check(x1,y1,x2,y2,cols,rows,Map,sides,direction)==1)&&(abs(y2-y1)<rows-4-sides)&&(abs(y2-y1)>3)){
                    for(int j = min(y1,y2); j < max(y1,y2)-1; j++ ){
                        Map[j][x1] = '*';
                    }
                }
                else{
                    l--;
                }
            }
            if (direction==2){
                int x2=2+rand()%(cols-sides-1);
                int y2=y1;
                if ((Check(x1,y1,x2,y2,cols,rows,Map,sides,direction)==1)&&(abs(x2-x1)<cols-4-sides)&&(abs(x2-x1)>3)){
                    for(int i = min(x1,x2); i < max(x1,x2)-1; i++ ){
                        Map[y1][i] = '*';
                    }
                }
                else{
                    l--;
                }
            }
            if (direction==3){
                int x2N=(xN+1)+rand()%(cols-2*sides-1);
                int y2N=yN+abs(x2N-xN);
                if ((Check(xN,yN,x2N,y2N,cols,rows,Map,sides,direction)==1) && (y2N>2*sides+1)&&(y2N<(rows-2*sides-1)) && ((x2N-xN)>4)){
                    for (int i = 0; i <= abs(x2N-xN)+1; i++) {
                        int x = xN + i;
                        int y = yN + i;
                        Map[y][x] = '*';
                    }
                }
                else{
                    l--;
                }
            }
            if (direction==4){
                int x2N=(xN+1)+rand()%(cols-2*sides-1);
                int y2N=yN-abs(x2N-xN);
                if ((Check(xN,yN,x2N,y2N,cols,rows,Map,sides,direction)==1) && (y2N>2*sides+1)&&(y2N<(rows-2*sides-1)) && ((x2N-xN)>4)){
                    for (int i = 0; i <= abs(x2N-xN)+1; i++) {
                        int x = xN + i;
                        int y = yN - i;
                        Map[y][x] = '*';
                    }
                }
                else{
                    l--;
                }
            }
        }
        else{
            l--;
        }
    }
    PrintMapToFile(cols,rows,Map);
}



void DrawPoint(int x, int y, int cols, int rows, char symbol, char Map[rows][cols], int sides) {
    for(int i = x; i > x - sides; i--){ 
        for(int j = y; j > y - sides; j--){ 
            Map[i][j] = symbol; 
        } 
    } 
}

void Draw_start_end_points(int xA,int yA,int xB,int yB,int cols, int rows,char Map[rows][cols],int sides){ 
    DrawPoint(xA, yA, cols, rows, 'A', Map, sides);
    DrawPoint(xB, yB, cols, rows, 'B', Map, sides);
    
}

int** Make_matrix(int rows, int cols, char Map[rows][cols]){
    int **map = (int **)malloc(rows * sizeof(int *));

    for (int i = 0; i < rows; i++) {
        map[i] = (int *)malloc(cols * sizeof(int));
            for (int j = 0; j < cols; j++) {
                if (Map[i][j] == '*')
                    map[i][j] = 1;
                else
                    map[i][j] = 0;
                }
    }
    return map;
}