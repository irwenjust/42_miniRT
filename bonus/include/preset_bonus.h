#ifndef PRESET_BONUS_H
# define PRESET_BONUS_H

#include "miniRT_bonus.h"

/*key preset*/
# define ESC 65307
// # define SPACE 9
//menu key
# define V 118 //view mode
# define C 99 //camera mode
# define B 98 //light bulb mode
# define M 109 //model mode
//common edit key
# define TAB 65289
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define G 103 //reset
# define R 114 //render
//movement key
# define W 119
# define A 97
# define S 115
# define D 100
# define Q 113
# define E 101
//rotate key
# define I 105
# define J 106
# define K 107
# define L 108
# define U 117
# define O 111
//preset key
# define ONE 49
# define TWO 50
# define THREE 51
# define FOUR 52
# define FIVE 53
# define SIX 54
//color efit
# define P 112 //color mode
# define C_INC 93
# define C_DEC 91
//key sets
# define MENU_KEY "vcbm"
# define PRESET_KEY "123456"
# define MOVE_KEY "wasdqe"
# define ROTATE_KEY "ijkluo"

/*preset color*/
# define RED		(t_color){255, 0, 0, 0}
# define YELLOW		(t_color){255, 255, 0, 0}
# define GREEN		(t_color){0, 255, 0, 0}
# define BLUE		(t_color){0, 0, 255, 0}
# define PURPLE		(t_color){210, 70, 255, 0}
# define BLACK		(t_color){0, 0, 0, 0}
# define WHITE		(t_color){255, 255, 255, 0}

/*shape color preset*/
//color preset 1
# define CS1_C1     (t_color){129, 116, 160, 0}
# define CS1_C2     (t_color){168, 136, 181, 0}
# define CS1_C3     (t_color){239, 182, 200, 0}
# define CS1_C4     (t_color){255, 210, 160, 0}
# define CS1_DREAM (t_color[]){CS1_C1, CS1_C2, CS1_C3, CS1_C4}

//color preset 2
# define CS2_C1     (t_color){100, 13, 95, 0}
# define CS2_C2     (t_color){217, 22, 86, 0}
# define CS2_C3     (t_color){235, 91, 0, 0}
# define CS2_C4     (t_color){255, 178, 0, 0}
# define CS2_SUNSET (t_color[]){CS2_C1, CS2_C2, CS2_C3, CS2_C4}

//color preset 3
# define CS3_C1     (t_color){250, 69, 50, 0}
# define CS3_C2     (t_color){250, 129, 47, 0}
# define CS3_C3     (t_color){250, 177, 47, 0}
# define CS3_C4     (t_color){196, 32, 32, 0}
# define CS3_FIRE (t_color[]){CS3_C1, CS3_C2, CS3_C3, CS3_C4}

//color preset 4
# define CS4_C1     (t_color){212, 235, 248, 0}
# define CS4_C2     (t_color){227, 142, 73, 0}
# define CS4_C3     (t_color){31, 80, 154, 0}
# define CS4_C4     (t_color){10, 57, 129, 0}
# define CS4_BLUES (t_color[]){CS4_C1, CS4_C2, CS4_C3, CS4_C4}

//color preset 5
# define CS5_C1     (t_color){37, 48, 14, 0}
# define CS5_C2     (t_color){49, 81, 30, 0}
# define CS5_C3     (t_color){133, 159, 61, 0}
# define CS5_C4     (t_color){238, 255, 146, 0}
# define CS5_FOREST (t_color[]){CS5_C1, CS5_C2, CS5_C3, CS5_C4}

//color preset 6
# define CS6_C1     (t_color){228, 197, 158, 0}
# define CS6_C2     (t_color){175, 130, 96, 0}
# define CS6_C3     (t_color){128, 61, 59, 0}
# define CS6_C4     (t_color){50, 44, 43, 0}
# define CS6_COFFEE (t_color[]){CS6_C1, CS6_C2, CS6_C3, CS6_C4}

/*preset light color*/
# define WARM_W		(t_color){255, 239, 214, 0}
# define COLD_W		(t_color){240, 247, 255, 0}
# define SUNSET		(t_color){250, 160, 90, 0}
# define MOON		(t_color){179, 201, 255, 0}
# define CYERPK		(t_color){230, 130, 255, 0}
# define TOXIC		(t_color){13, 220, 53, 0}

/*camera preset*/
# define C_FRONT (t_vector){0, 0, 1}
# define C_BACK (t_vector){0, 0, -1}
# define C_TOP (t_vector){0, -1, 0}
# define C_BOTTOM (t_vector){0, 1, 0}
# define C_LEFT (t_vector){1, 0, 0}
# define C_RIGHT (t_vector){-1, 0, 0}

#endif