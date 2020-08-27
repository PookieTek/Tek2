/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SoundTest
*/

#ifndef SOUNDTEST_HPP_
#define SOUNDTEST_HPP_

#include <SFML/Audio.hpp>

enum {
    MENU,
    GAME,
    SCORE,
    CLICK,
    FOOTSTEP,
    EXPLOSION,
    BOMB_POSE,
    BONUS,
    DIE,
    SPAWN,
    START,
};

class SoundTest {
    public:
        SoundTest();
        void SoundPlay(int _sound);
        void MusicPlay(int _music);
        void MusicStop();
        ~SoundTest();

    protected:
    private:
        sf::Music       music;
        sf::SoundBuffer buffer;
        sf::Sound       sound;
};


#endif /* !SOUNDTEST_HPP_ */
