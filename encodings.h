/* Elevator direction */
#define UP 1
#define DOWN 2
#define IDLE 3

/* Elevator status */
#define IN_SERVICE 1
#define OUT_OF_SERVICE 2

/* Door status */
#define OPEN 1
#define CLOSED 2

/* IO (ones column indicates floor) */
#define INSIDE_REQ 100
#define ELEVATOR1_REQ 10
#define ELEVATOR2_REQ 20

#define OUTSIDE_REQ 200
#define UP_REQ 10
#define DOWN_REQ 20

/* Standard output positions */
#define ELEVATOR_1_COL 30
#define ELEVATOR_2_COL 60

/* Caller IDs*/
#define DISPATCHER 0
#define IO 1

/* Elevator timing */
#define MS_PER_FLOOR 1000