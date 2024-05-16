#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>

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
typedef struct {
    int x;
    int y;
    int score;
    int rotate;
    int fallTime;
    ShapeId queue[4];
}State;
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

void printCanvas(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], State* state)
{
    printf("\033[0;0H\n");
    for (int i = 0; i < CANVAS_HEIGHT; i++) {
        printf("|");
        for (int j = 0; j < CANVAS_WIDTH; j++) {
            printf("\033[%dm\u3000", canvas[i][j].color);
        }
        printf("\033[0m|\n");
    }

    //輸出Next:
    printf("\033[%d;%dHNext:", 3, CANVAS_WIDTH * 2 + 5);
    //輸出有甚麼方塊
    for (int i = 1; i <= 3; i++)
    {
        Shape shapeData = shape[state->queue[i]];
        for (int j = 0; j < 4; j++) {
            printf("\033[%d;%dH", i * 4 + j, CANVAS_WIDTH * 2 + 15);
            for (int k = 0; k < 4; k++) {
                if (j < shapeData.size && k < shapeData.size && shapeData.rotates[0][j][k]) {
                    printf("\x1b[%dm  ", shapeData.color);
                }
                else {
                    printf("\x1b[0m  ");
                }
            }
        }
    }
    return;
}

bool move(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], int originalX, int originalY, int originalRotate, int newX, int newY, int newRotate, ShapeId shapeId) {
    Shape shapeData = shape[shapeId];
    int size = shapeData.size;

    //判斷方塊有沒有不符合條件
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (shapeData.rotates[newRotate][i][j]) {
                //判斷有沒有出去邊界
                if (newX + j < 0 || newX + j >= CANVAS_WIDTH || newY + i < 0 || newY + i >= CANVAS_HEIGHT) {
                    return false;
                }
                //判斷有沒有碰到別的方塊
                if (!canvas[newY + i][newX + j].current && canvas[newY + i][newX + j].shape != SHAPE_EMPTY) {
                    return false;
                }
            }
        }
    }

    // 移除方塊舊的位置
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (shapeData.rotates[originalRotate][i][j]) {
                resetBlock(&canvas[originalY + i][originalX + j]);
            }
        }
    }

    // 移動方塊至新的位置
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (shapeData.rotates[newRotate][i][j]) {
                setBlock(&canvas[newY + i][newX + j], shapeData.color, shapeId, true);
            }
        }
    }

    return true;

}

int clearLine(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH])
{
    for (int i = 0; i < CANVAS_HEIGHT; i++)
    {
        for (int j = 0; j < CANVAS_WIDTH; j++)
        {
            if (canvas[i][j].current)
            {
                canvas[i][j].current = false;
            }
        }
    }

    int linesCleared = 0;
    /*....日後會再更新*/
    return linesCleared;
}

void logic(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], State* state)
{
    if (move(canvas, state->x, state->y, state->rotate, state->x, state->y + 1, state->rotate, state->queue[0]))
    {
        state->y++;
    }
    else
    {
        state->score += clearLine(canvas);

        state->x = CANVAS_WIDTH / 2;
        state->y = 0;
        state->rotate = 0;
        state->queue[0] = state->queue[1];
        state->queue[1] = state->queue[2];
        state->queue[2] = state->queue[3];
        state->queue[3] = rand() % 7;

    }
    return;
}






int main()
{
    srand(time(NULL));
    State state = {
        .x = CANVAS_WIDTH / 2,
        .y = 0,
        .score = 0,
        .rotate = 0,
        .fallTime = 0 };

    for (int i = 0; i < 4; i++)
    {
        state.queue[i] = rand() % 7;
    }

    Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH];
    for (int i = 0; i < CANVAS_HEIGHT; i++)
    {
        for (int j = 0; j < CANVAS_WIDTH; j++)
        {
            resetBlock(&canvas[i][j]);
        }
    }

    Shape shapeData = shape[state.queue[0]];

    for (int i = 0; i < shapeData.size; i++)
    {
        for (int j = 0; j < shapeData.size; j++)
        {
            if (shapeData.rotates[0][i][j])
            {
                setBlock(&canvas[state.y + i][state.x + j], shapeData.color, state.queue[0], true);
            }
        }
    }


    while (1) {
        printCanvas(canvas, &state);
        logic(canvas, &state);
        Sleep(100);
    }
    // printf("\e[?25l"); // hide cursor

    return 0;
}