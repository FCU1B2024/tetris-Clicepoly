#include <stdio.h>



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
    SHAPE_Z  // mirror S
}ShapeId;

typedef struct {
    ShapeId shape;
    Color color;
    int size;
    char rotates[4][4][4];
}Shape;

Shape shape[7] = 
{
    {
        .shape  = SHAPE_I,
        .color  = COLOR_CYAN,
        .size   = 4,
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
    }
};

int main() {
    
    Color cur;
    // how many shapes
    for (int i = 0; i < 7; i++) {

        // rotations
        for (int r = 0; r < 4; r++) {

            // prints the shape
            // what kind
            for (int s = 0; s < shape[i].size; s++) {
                // 2d
                for (int t = 0; t < shape[i].size; t++) {
                    if (shape[i].rotates[r][s][t] == 0) {
                        cur = COLOR_WHITE;

                    }
                    else {
                        cur = shape[i].color;

                    }
                    printf("\033[%dm \033[0m", cur);
                    printf("\033[%dm \033[0m", cur);
                }
                printf("\n");
            }
            
            printf("\n");
        }
        
    }
    return 0;
}