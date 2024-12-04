#ifndef PRESET_H
# define PRESET_H

#include "miniRT.h"

//preset color
# define RED		(t_color){255, 0, 0, 0}
# define YELLOW		(t_color){255, 255, 0, 0}
# define GREEN		(t_color){0, 255, 0, 0}
# define BLUE		(t_color){0, 0, 255, 0}
# define PINK		(t_color){255, 100, 180, 0}
# define PURPLE		(t_color){210, 70, 255, 0}
# define BLACK		(t_color){0, 0, 0, 0}
# define WHITE		(t_color){255, 255, 255, 0}

//preset light color
# define WARM_W		(t_color){255, 239, 214, 0}
# define COLD_W		(t_color){240, 247, 255, 0}
# define SUNSET		(t_color){250, 160, 90, 0}
# define MOON		(t_color){179, 201, 255, 0}
# define CYERPK		(t_color){230, 130, 255, 0}
# define TOXIC		(t_color){13, 220, 53, 0}

// # define CP_1 "C 0,0,5 0,0,-1 90"
// # define CP_2 "C 0,0,-5 0,0,1 90"
// # define CP_3 "C 0,5,0 0,-1,0 90"
// # define CP_4 "C 0,-5,0 0,1,0 90"
// # define CP_5 "C -5,0,0 1,0,0 90"
// # define CP_6 "C 5,0,0 -1,0,0 90"

#define CP_1 "C -2.5,-2.5,-1 0,0,1 90"  // 正视图
#define CP_2 "C -2.5,-2.5,36 0,0,-1 90"  // 后视图
#define CP_3 "C 0,50,0 0,-1,0 90"  // 上视图
#define CP_4 "C 0,-50,0 0,1,0 90"  // 下视图
#define CP_5 "C -50,0,0 1,0,0 90"  // 左视图
#define CP_6 "C 50,0,0 -1,0,0 90"  // 右视图

#endif