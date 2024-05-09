#include <stdio.h>
#include <stdbool.h>
#define CANVAS_WIDTH 10
#define CANVAS_HEIGHT 20


typedef enum { // colors of tetris pieces
    COLOR_RED = 41,
    COLOR_GREEN,
    COLOR_YELLOW,
    COLOR_BLUE,
    COLOR_PURPLE,
    COLOR_CYAN,
    COLOR_WHITE,
    COLOR_BLACK = 0,
}Color;

typedef enum { // shape names of tetris pieces
    SHAPE_EMPTY = -1,
    SHAPE_I,
    SHAPE_J, // mirror L
    SHAPE_L,
    SHAPE_O,
    SHAPE_S,
    SHAPE_T,
    SHAPE_Z, // mirror S
    SHAPE_X,  // cursed
    HUGE_L
}ShapeId;

typedef struct {
    Color color;
    ShapeId shape;
    bool current;
}Block;

typedef struct {
    ShapeId shape;
    Color color;
    int size;
    char rotates[6][6][6];
}Shape;

Shape shape[9] = // 0~7 normal
{
    {
        .shape = SHAPE_I,
        .color = COLOR_CYAN,
        .size = 4,
        .rotates = {
            {
                {0,0,0,0},
                {1,1,1,1},
                {0,0,0,0},
                {0,0,0,0}
            },
            {
                {0,0,1,0},
                {0,0,1,0},
                {0,0,1,0},
                {0,0,1,0}
            },
            {
                {0,0,0,0},
                {0,0,0,0},
                {1,1,1,1},
                {0,0,0,0}
            },
            {
                {0,1,0,0},
                {0,1,0,0},
                {0,1,0,0},
                {0,1,0,0}
            }
        }
    },
    {
        .shape = SHAPE_J,
        .color = COLOR_YELLOW,
        .size = 3,
        .rotates = {
            {
                {0,0,1},
                {0,0,1},
                {0,1,1}
            },
            {
                {0,0,0},
                {1,0,0},
                {1,1,1}
            },
            {
                {1,1,0},
                {1,0,0},
                {1,0,0}
            },
            {
                {1,1,1},
                {0,0,1},
                {0,0,0}
            }


        }
    },
    {
        .shape = SHAPE_L,
        .color = COLOR_BLUE,
        .size = 3,
        .rotates = {
            {
                {1,0,0},
                {1,0,0},
                {1,1,0}
            },
            {
                {1,1,1},
                {1,0,0},
                {0,0,0}
            },
            {
                {0,1,1},
                {0,0,1},
                {0,0,1}
            },
            {
                {0,0,0},
                {0,0,1},
                {1,1,1}
            }


        }
    },
    {
        .shape = SHAPE_O,
        .color = COLOR_WHITE,
        .size = 2,
        .rotates = {
            {
                {1,1},
                {1,1}
            },
            {
                {1,1},
                {1,1}
            },
            {
                {1,1},
                {1,1}
            },
            {
                {1,1},
                {1,1}
            }
        }
    },
    {
        .shape = SHAPE_T,
        .color = COLOR_PURPLE,
        .size = 3,
        .rotates = {
            {
                {1,1,1},
                {0,1,0},
                {0,0,0}
            },
            {
                {0,0,1},
                {0,1,1},
                {0,0,1}
            },
            {
                {0,0,0},
                {0,1,0},
                {1,1,1}
            },
            {
                {1,0,0},
                {1,1,0},
                {1,0,0}
            }


        }
    },
    {
        .shape = SHAPE_S,
        .color = COLOR_RED,
        .size = 3,
        .rotates = {
            {
                {0,1,1},
                {1,1,0},
                {0,0,0}
            },
            {
                {0,1,0},
                {0,1,1},
                {0,0,1}
            },
            {
                {0,0,0},
                {0,1,1},
                {1,1,0}
            },
            {
                {1,0,0},
                {1,1,0},
                {0,1,0}
            }


        }
    }, {
        .shape = SHAPE_Z,
        .color = COLOR_GREEN,
        .size = 3,
        .rotates = {

            {
                {0,0,0},
                {1,1,0},
                {0,1,1}
            },
            {
                {0,0,1},
                {0,1,1},
                {0,1,0}

            },

            {
                {1,1,0},
                {0,1,1},
                {0,0,0}

            },

            {
                {0,1,0},
                {1,1,0},
                {1,0,0}
            },


        }
    },  {



        // cursed pieces section

            .shape = SHAPE_X,
            .color = COLOR_YELLOW,
            .size = 3,
            .rotates = {
                {
                    {1,0,1},
                    {0,1,0},
                    {1,0,1}
                },
                {
                    {1,0,1},
                    {0,1,0},
                    {1,0,1}
                },
                {
                    {1,0,1},
                    {0,1,0},
                    {1,0,1}
                },
                {
                    {1,0,1},
                    {0,1,0},
                    {1,0,1}
                }


            }
        }, {
            .shape = HUGE_L,
            .color = COLOR_YELLOW,
            .size = 6,
            .rotates = {
                {
                    {1,1,0,0,0,0},
                    {1,1,0,0,0,0},
                    {1,1,0,0,0,0},
                    {1,1,0,0,0,0},
                    {1,1,1,1,0,0},
                    {1,1,1,1,0,0}
                },
                {
                    {0,0,0,0,0,0},
                    {0,0,0,0,0,0},
                    {0,0,0,0,1,1},
                    {0,0,0,0,1,1},
                    {1,1,1,1,1,1},
                    {1,1,1,1,1,1}
                },
                {
                    {0,0,1,1,1,1},
                    {0,0,1,1,1,1},
                    {0,0,0,0,1,1},
                    {0,0,0,0,1,1},
                    {0,0,0,0,1,1},
                    {0,0,0,0,1,1}
                },
                {
                    {1,1,1,1,1,1},
                    {1,1,1,1,1,1},
                    {1,1,0,0,0,0},
                    {1,1,0,0,0,0},
                    {0,0,0,0,0,0},
                    {0,0,0,0,0,0}
                }


            }
        }

};

void setBlock(Block* block, Color color, ShapeId shape, bool current) {
    block->color = color;
    block->shape = shape;
    block->current = current;
}
void resetBlock(Block* block) {
    block->color = COLOR_BLACK;
    block->shape = SHAPE_EMPTY;
    block->current = false;
}

typedef struct {
    int x;
    int y;
    int score;
    int rotate;
    int fallTime;
    ShapeId queue[4];
}State;



int main() {

    //Color cur;
    // how many shapes
    Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH];
    State state = {
        .x = CANVAS_HEIGHT / 2,
        .y = 0,
        .score = 0,
        .rotate = 0,
        .fallTime = 0
    };






    for (int i = 0; i < CANVAS_HEIGHT; i++) {
        for (int j = 0; j < CANVAS_WIDTH; j++) {
            resetBlock(&canvas[i][j]);
        }
    }

    Shape tmp = shape[1];

    for (int i = 0; i < tmp.size; i++) {
        for (int j = 0; j < tmp.size; j++) {
            if (tmp.rotates[1][i][j] == 1) {

                setBlock(&canvas[i + state.y][j + state.x], tmp.color, tmp.shape, 1);

            }
        }
    }

    printf("\033[0:0H\n");
    for (int i = 0; i < CANVAS_HEIGHT; i++) {
        printf("|");
        for (int j = 0; j < CANVAS_WIDTH; j++) {
            printf("\033[%dm\u3000", canvas[i][j].color);
        }
        printf("\033[%0m");
        printf("|\n");
    }








    return 0;
}