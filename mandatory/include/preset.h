/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preset.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:32:34 by yzhan             #+#    #+#             */
/*   Updated: 2025/02/14 17:32:36 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRESET_H
# define PRESET_H

# include "miniRT.h"

/*key preset*/
# define ESC 65307
// # define SPACE 9
//menu key
# define V 118
# define C 99
# define B 98
# define M 109
//common edit key
# define TAB 65289
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define G 103
# define R 114
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
# define P 112
# define C_INC 93
# define C_DEC 91
//key sets
# define MENU_KEY "vcbm"
# define PRESET_KEY "123456"
# define MOVE_KEY "wasdqe"
# define ROTATE_KEY "ijkluo"

/*preset color*/
# define BLACK	0x000000FF
# define WHITE	0xFFFFFFFF
# define BACKGROUND BLACK

/*shape color preset*/
//CS1_DREAM
# define CS1_C1 0x8174A0FF
# define CS1_C2 0xA888B5FF
# define CS1_C3 0xEFB6C8FF
# define CS1_C4 0xFFD2A0FF

//CS2_SUNSET
# define CS2_C1 0x640D5FFF
# define CS2_C2 0xD91656FF
# define CS2_C3 0xEB5B00FF
# define CS2_C4 0xFFB200FF

//CS3_FIRE
# define CS3_C1 0xFA4532FF
# define CS3_C2 0xFA812FFF
# define CS3_C3 0xFAB12FFF
# define CS3_C4 0xC42020FF

//CS4_BLUES
# define CS4_C1 0xD4EBF8FF
# define CS4_C2 0xE38E49FF
# define CS4_C3 0x1F509AFF
# define CS4_C4 0x0A3981FF

//CS5_FOREST
# define CS5_C1 0x25300EFF
# define CS5_C2 0x31511EFF
# define CS5_C3 0x859F3DFF
# define CS5_C4 0xEEFF92FF

//CS6_COFFEE 
# define CS6_C1 0xE4C59EFF
# define CS6_C2 0xAF8260FF
# define CS6_C3 0x803D3BFF
# define CS6_C4 0x322C2BFF

/*preset light color*/
# define WARM_W 0xFFEFD6FF
# define COLD_W 0xF0F7FFFF
# define SUNSET 0xFAA05AFF
# define MOON   0xB3C9FFFF
# define CYERPK 0xE682FFFF
# define TOXIC  0x0DDC35FF

#endif
