#include "Var_str.h"
#define NULL ((void *)0)

void initQueue(Queue *q) {
    q->front = q->rear = NULL;
}


void enqueue(Queue *q, Point *node) {
    node->next = NULL;

    if (q->rear == NULL) { 
        q->front = q->rear = node; 
    } else {
        if (node->g + node->h < q->front->g + q->front->h) {
            node->next = q->front;
            q->front = node;
        } else {
            Point *current = q->front;
            while (current->next != NULL && current->next->g + current->next->h < node->g + node->h) {
                current = current->next;
            }
            node->next = current->next;
            current->next = node;
            if (node->next == NULL) {
                q->rear = node;
            }
        }
    }
}


void print_list(int a, int b, int list[a][b]){
    for (int i = 0; i < a; i++){
        for (int j = 0; j < b; j++){
            printf("%d", list[i][j]);
        }
        printf("\n");
    }
}

Point* dequeue(Queue *q) {
    if (q->front == NULL) return NULL;
    Point *temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    return temp;
}

int isQueueEmpty(Queue *q) {
    return q->front == NULL;
}

void freeQueue(Queue *q) {
    Point *current = q->front;
    Point *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    q->front = q->rear = NULL;
}

Point* findNodeInQueue(Queue *queue, int row, int col) {
       Point *current = queue->front;
       while (current != NULL) {
           if (current->row == row && current->col == col) {
               return current;
           }
           current = current->next;
       }
       return NULL;
}

int heuristic(int x1, int y1, int x2, int y2) {
  return (double)sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int isValid(int x, int y, int rows, int cols, int** map) {
    return (x >= 0 && x < cols && y >= 0 && y < rows && map[x][y] == 0);
}

void addNeighbors(Point *node, Queue *queue, Point* end, int** map, int rows, int cols,  int closedList[rows][cols]) {

    static int dx[] = {1, -1, 1, 0, -1, 1, -1, 0}; // звезда
    static int dy[] = {1, 0, -1, 1, -1, 0, 1, -1};

    for (int i = 0; i < 8; i++) { // Теперь проверяем 8 направлений
        int nx = node->row + dx[i];
        int ny = node->col + dy[i];

        if (isValid(nx, ny, rows, cols, map) && 
            ((i % 2 == 1) || (isValid(nx - dx[i], ny, rows, cols, map) && isValid(nx, ny - dy[i], rows, cols, map)))) {
            if (closedList[nx][ny]) continue;

            Point* existingNode = findNodeInQueue(queue, nx, ny); // Функция поиска узла в очереди
            if (existingNode != NULL) {
                if (i > 3) {              
                    if (node->g + 1.4 < existingNode->g) {
                   // Найден более короткий путь
                        existingNode->parent = node;   
                        existingNode->g = node->g + 1.4; 
                    }
                }                        
               // Узел уже в очереди
               if (node->g + 1 < existingNode->g) {
                   // Найден более короткий путь
                   existingNode->parent = node;
                   existingNode->g = node->g + 1;
               }
            }

            else {
                if(i > 3) {               
                    Point *neighbor = (Point*)malloc(sizeof(Point));
            neighbor->row = nx;
            neighbor->col = ny;
            neighbor->parent = node;                           
            neighbor->g = node->g + 1.4;
            neighbor->h = heuristic(neighbor->row, neighbor->col, end->row, end->col);
            enqueue(queue, neighbor);
                }                        
               // Узел не найден в очереди
            Point *neighbor = (Point*)malloc(sizeof(Point));
            neighbor->row = nx;
            neighbor->col = ny;
            neighbor->parent = node;
            neighbor->g = node->g + 1;
            neighbor->h = heuristic(neighbor->row, neighbor->col, end->row, end->col);
            enqueue(queue, neighbor);
            }
        }
    }
}

int checkIntersection(Queue *queue, int rows, int cols, int closedList[rows][cols], Point** meetingNode, char StartOrEnd) {
       Point *current = queue->front;
       while (current != NULL) {
           if (closedList[current->row][current->col]) {
               *meetingNode = current;
               printf("Volna: %c\n", StartOrEnd);
               return 1; // Найдено пересечение
           }
           current = current->next;
       }
       return 0; // Пересечение не найдено
   }


void tracePath(Point *node, int rows, int cols, char Map[rows][cols], char Step) {
    if (node == NULL) return;
    tracePath(node->parent, rows, cols, Map, Step);
    printf("->(%d, %d) ", node->col, node->row);
    if (Map[node->row][node->col] != 'A' && Map[node->row][node->col] != 'B')
        Map[node->row][node->col] = Step;
}


void* my_memset(void* ptr, int value, int num) {
    unsigned char* p = ptr;
    while (num--) {
        *p++ = (unsigned char)value;
    }
    return ptr;
}

