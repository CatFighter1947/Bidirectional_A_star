
void bidirectionalAStar(Point* start, Point* end, int rows, int cols ,int** map, char Map[rows][cols]) {
    Queue forwardQueue, backwardQueue;
    initQueue(&forwardQueue);
    initQueue(&backwardQueue);

    int forwardClosedList[rows][cols];
    my_memset( forwardClosedList, 0, rows*cols*sizeof(int) );
    int backwardClosedList[rows][cols];
    my_memset( backwardClosedList, 0, rows*cols*sizeof(int) );

    Point *startNode = (Point*)malloc(sizeof(Point));
    startNode = start;
    startNode->parent = NULL;
    startNode->g = 0;
    startNode->h = heuristic(start->row, start->col, end->row, end->col);
    enqueue(&forwardQueue, startNode);

    Point *endNode = (Point*)malloc(sizeof(Point));
    endNode = end;
    endNode->parent = NULL;
    endNode->g = 0;
    endNode->h = heuristic(end->row, end->col, start->row, start->col);
    enqueue(&backwardQueue, endNode);

    Point *meetingNodeStart = NULL;
    Point *meetingNodeEnd = NULL;

    while (!isQueueEmpty(&forwardQueue) && !isQueueEmpty(&backwardQueue)) {
        //printf("hello\n");
        Point *forwardNode = dequeue(&forwardQueue);
        forwardClosedList[forwardNode->row][forwardNode->col] = 1;

        Point *backwardNode = dequeue(&backwardQueue);
        backwardClosedList[backwardNode->row][backwardNode->col] = 1;


        addNeighbors(forwardNode, &forwardQueue, end, map, rows, cols, forwardClosedList);
        addNeighbors(backwardNode, &backwardQueue, start, map, rows, cols, backwardClosedList);

        if (checkIntersection(&forwardQueue, rows, cols, backwardClosedList, &meetingNodeStart, 'S') && 
        checkIntersection(&backwardQueue, rows, cols, forwardClosedList, &meetingNodeEnd, 'E')) break;

    }

    printf("MeetingNodeStart: (%d, %d). MeetingNodeEnd: (%d, %d)\n", meetingNodeStart->col, meetingNodeStart->row,
    meetingNodeEnd->col, meetingNodeStart->row);

    if (meetingNodeStart != NULL && meetingNodeEnd != NULL) {
        printf("Put' ot A do tochki vstrechi:  ");
        tracePath(meetingNodeStart, rows, cols, Map, 'O');
        printf("\n");
        printf("Put' ot tochki vstrechi do B:  ");
        tracePath(meetingNodeEnd, rows, cols, Map, 'G');

    } else {
        printf("No path found\n");
    }

    printf("\n");
    forwardClosedList[meetingNodeStart->row][meetingNodeStart->col] = 4;
    forwardClosedList[meetingNodeEnd->row][meetingNodeEnd->col] = 5;
    print_list(rows, cols, forwardClosedList);
    printf("\n");
    backwardClosedList[meetingNodeStart->row][meetingNodeStart->col] = 4;
    backwardClosedList[meetingNodeEnd->row][meetingNodeEnd->col] = 5;
    print_list(rows, cols, backwardClosedList);

    freeQueue(&forwardQueue);
    freeQueue(&backwardQueue);
}
