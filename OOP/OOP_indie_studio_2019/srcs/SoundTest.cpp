/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SoundTest
*/

#include "SoundTest.hpp"
#include "MyException.hpp"

SoundTest::SoundTest()
{
}

void SoundTest::SoundPlay(int _sound)
{
	if (_sound == CLICK)
		if (!buffer.loadFromFile("assets/sound/clic.ogg"))
			throw MyException("Sound File not Found");
    if (_sound == FOOTSTEP)
        if (!buffer.loadFromFile("assets/sound/footstep.ogg"))
            throw MyException("Sound File not Found");
    if (_sound == EXPLOSION)
        if (!buffer.loadFromFile("assets/sound/explosion.ogg"))
            throw MyException("Sound File not Found");
    if (_sound == START)
        if (!buffer.loadFromFile("assets/sound/start.ogg"))
            throw MyException("Sound File not Found");
    if (_sound == SPAWN)
        if (!buffer.loadFromFile("assets/sound/spawn.ogg"))
            throw MyException("Sound File not Found");
    if (_sound == BOMB_POSE)
        if (!buffer.loadFromFile("assets/sound/drop_bomb.ogg"))
            throw MyException("Sound File not Found");
    if (_sound == BONUS)
        if (!buffer.loadFromFile("assets/sound/bonus.ogg"))
            throw MyException("Sound File not Found");
    if (_sound == DIE)
        if (!buffer.loadFromFile("assets/sound/die.ogg"))
            throw MyException("Sound File not Found");

    sound.setBuffer(buffer);
    sound.play();
}

void SoundTest::MusicPlay(int _music)
{
    if (_music == MENU)
        if (!music.openFromFile("assets/sound/music_menu.ogg"))
            throw MyException("Sound File not Found");
    if (_music == GAME)
        if (!music.openFromFile("assets/sound/music_game.ogg"))
           throw MyException("Sound File not Found");
    if (_music == SCORE)
        if (!music.openFromFile("assets/sound/music_score_screen.ogg"))
            throw MyException("Sound File not Found");
    music.setVolume(10);
    music.play();
    music.setLoop(true);
}

void SoundTest::MusicStop()
{
    music.stop();
}

SoundTest::~SoundTest()
{
}
