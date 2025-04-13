// Структура для хранения точки
typedef struct Point {
    int row;
    int col;
    double g; // Стоимость пути от начальной точки
    double h; // Эвристическая оценка стоимости пути от текущей точки до конечной
    struct Point *parent;
    struct Point *next; // Указатель на родительский узел

} Point;


typedef struct Queue{ //Структура очереди
    Point *front;
    Point *rear;
} Queue;

void initQueue(Queue *q);

void enqueue(Queue *q, Point *node);

void print_list(int a, int b, int list[a][b]);

Point* dequeue(Queue *q);

int isQueueEmpty(Queue *q);

void freeQueue(Queue *q);

Point* findNodeInQueue(Queue *queue, int row, int col);

int heuristic(int x1, int y1, int x2, int y2);

int isValid(int x, int y, int rows, int cols, int** map);

void addNeighbors(Point *node, Queue *queue, Point* end, int** map, int rows, int cols,  int closedList[rows][cols]);

int checkIntersection(Queue *queue, int rows, int cols, int closedList[rows][cols], Point** meetingNode, char StartOrEnd);

void tracePath(Point *node, int rows, int cols, char Map[rows][cols], char Step);

void* my_memset(void* ptr, int value, int num); 
