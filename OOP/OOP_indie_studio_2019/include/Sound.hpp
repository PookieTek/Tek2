/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Sound
*/

#ifndef SOUND_HPP_
#define SOUND_HPP_
#include <SFML/Audio.hpp>

namespace SoundElem {

    enum SoundEffect {
        BONUS,
        CLIC,
        DIE,
        DROP_BOMB,
        EXPLOSION,
        FOOTSTEP,
        PAUSE,
        START,
        VALIDATION_CLIC,
        COUNT_EFFECT,       // Use to get number of effect
    };

    enum SoundMusic {
        GAME,
        MENU,
        SCORE_SCREEN,
        COUNT_MUSIC,    // use to get number of music
    };
};

class Sound {
    public:
        Sound();
        ~Sound();

        void PlayEffect(SoundElem::SoundEffect);
        void PlayMusic(SoundElem::SoundMusic);
        void StopMusic();

    protected:
    private:
        std::vector<sf::SoundBuffer *>  bufferEffect;
        std::vector<sf::Sound *>        soundEffect;
        std::vector<sf::Music *>        bufferMusic;
        std::vector<bool>               enabledEffect;
        std::vector<bool>               enabledMusic;
};

#endif /* !SOUND_HPP_ */
