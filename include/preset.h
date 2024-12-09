#ifndef PRESET_H
# define PRESET_H

#include "miniRT.h"

//preset color
# define RED		(t_color){255, 0, 0, 0}
# define YELLOW		(t_color){255, 255, 0, 0}
# define GREEN		(t_color){0, 255, 0, 0}
# define BLUE		(t_color){0, 0, 255, 0}

# define PURPLE		(t_color){210, 70, 255, 0}
# define BLACK		(t_color){0, 0, 0, 0}
# define WHITE		(t_color){255, 255, 255, 0}

/*shape color preset*/
//preset 1
# define CS1_C1     (t_color){129, 116, 160, 0}
# define CS1_C2     (t_color){168, 136, 181, 0}
# define CS1_C3     (t_color){239, 182, 200, 0}
# define CS1_C4     (t_color){255, 210, 160, 0}
# define CS1_DREAM (t_color[]){CS1_C1, CS1_C2, CS1_C3, CS1_C4}

//preset 2
# define CS2_C1     (t_color){100, 13, 95, 0}
# define CS2_C2     (t_color){217, 22, 86, 0}
# define CS2_C3     (t_color){235, 91, 0, 0}
# define CS2_C4     (t_color){255, 178, 0, 0}
# define CS2_SUNSET (t_color[]){CS2_C1, CS2_C2, CS2_C3, CS2_C4}

//preset 3
# define CS3_C1     (t_color){250, 69, 50, 0}
# define CS3_C2     (t_color){250, 129, 47, 0}
# define CS3_C3     (t_color){250, 177, 47, 0}
# define CS3_C4     (t_color){196, 32, 32, 0}
# define CS3_FIRE (t_color[]){CS3_C1, CS3_C2, CS3_C3, CS3_C4}

//preset 4
# define CS4_C1     (t_color){212, 235, 248, 0}
# define CS4_C2     (t_color){227, 142, 73, 0}
# define CS4_C3     (t_color){31, 80, 154, 0}
# define CS4_C4     (t_color){10, 57, 129, 0}
# define CS4_BLUES (t_color[]){CS4_C1, CS4_C2, CS4_C3, CS4_C4}

//preset 5
# define CS5_C1     (t_color){37, 48, 14, 0}
# define CS5_C2     (t_color){49, 81, 30, 0}
# define CS5_C3     (t_color){133, 159, 61, 0}
# define CS5_C4     (t_color){238, 255, 146, 0}
# define CS5_FOREST (t_color[]){CS5_C1, CS5_C2, CS5_C3, CS5_C4}

//preset 6
# define CS6_C1     (t_color){228, 197, 158, 0}
# define CS6_C2     (t_color){175, 130, 96, 0}
# define CS6_C3     (t_color){128, 61, 59, 0}
# define CS6_C4     (t_color){50, 44, 43, 0}
# define CS6_COFFEE (t_color[]){CS6_C1, CS6_C2, CS6_C3, CS6_C4}

// # define CS_SPRING (t_color[]){S_PINK, S_BLUE, S_ORANGE, S_YELLOW, S_GREEN}

// # define CS_TEST (t_color[]){GREEN, BLUE, PURPLE}
// # define CS_SPRING_SIZE (sizeof(CS_SPRING) / sizeof(CS_SPRING[0]))
// # define CS_TEST_SIZE (sizeof(CS_TEST) / sizeof(CS_TEST[0]))
// # define CS_SIZE (int[]){CS_SPRING_SIZE, CS_TEST_SIZE}

//preset light color
# define WARM_W		(t_color){255, 239, 214, 0}
# define COLD_W		(t_color){240, 247, 255, 0}
# define SUNSET		(t_color){250, 160, 90, 0}
# define MOON		(t_color){179, 201, 255, 0}
# define CYERPK		(t_color){230, 130, 255, 0}
# define TOXIC		(t_color){13, 220, 53, 0}



#define CP_1 "C 0,0,0 0,0,1 90"  // 正视图
#define CP_2 "C 0,0,30 0,0,-1 90"  // 后视图
#define CP_3 "C 0,15,15 0,-1,0 90"  // 上视图
#define CP_4 "C 0,-15,15 0,1,0 90"  // 下视图
#define CP_5 "C -15,0,15 1,0,0 90"  // 左视图
#define CP_6 "C 15,0,15 -1,0,0 90"  // 右视图

#endif