/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Config
*/

#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include <include/irrlicht.h>

#define BLOCK_SIZE          128 // Square px
#define EXPLODE_TIME        3000 // Ms
#define RESOLUTION_X        1920 // Px
#define RESOLUTION_Y        1080 // Px
#define INIT_SPEED          1
#define INIT_BOMBS          3
#define INIT_LIFE           2
#define INIT_RADIUS         4
#define GAME_TIME           180000 // Ms
#define CINETIC_TRANSMISSION 80 // % (will go XX% of player speed)
#define RESPAWN_TIMER       2000 // ms
#define FIRE_TIME           1000 // ms
#define CHANCE_BONUS        80 // %
#define PLAYER_SPEED        15 // px

//KEY BINDING

#define UP_PLAYER_1         irr::KEY_KEY_Z
#define RIGHT_PLAYER_1      irr::KEY_KEY_D
#define DOWN_PLAYER_1       irr::KEY_KEY_S
#define LEFT_PLAYER_1       irr::KEY_KEY_Q
#define THROW_BOMB_1        irr::KEY_KEY_A

#define UP_PLAYER_2         irr::KEY_UP
#define RIGHT_PLAYER_2      irr::KEY_RIGHT
#define DOWN_PLAYER_2       irr::KEY_DOWN
#define LEFT_PLAYER_2       irr::KEY_LEFT
#define THROW_BOMB_2        irr::KEY_RETURN

#endif /* !CONFIG_HPP_ */
