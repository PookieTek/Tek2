/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Sound
*/

#include "Sound.hpp"
#include <iostream>

Sound::Sound()
{
    sf::SoundBuffer buffer;
    for (int i = 0; i < SoundElem::SoundEffect::COUNT_EFFECT + 1; i++) {
        bufferEffect.push_back(new sf::SoundBuffer);
        soundEffect.push_back(new sf::Sound);
    }
    for (int i = 0; i < SoundElem::SoundMusic::COUNT_MUSIC + 1; i++)
        bufferMusic.push_back(new sf::Music);

    enabledEffect.push_back(bufferEffect[SoundElem::SoundEffect::BONUS]->loadFromFile("assets/sound/bonus.ogg"));
    enabledEffect.push_back(bufferEffect[SoundElem::SoundEffect::CLIC]->loadFromFile("assets/sound/clic.ogg"));
    enabledEffect.push_back(bufferEffect[SoundElem::SoundEffect::DIE]->loadFromFile("assets/sound/die.ogg"));
    enabledEffect.push_back(bufferEffect[SoundElem::SoundEffect::DROP_BOMB]->loadFromFile("assets/sound/drop_bomb.ogg"));
    enabledEffect.push_back(bufferEffect[SoundElem::SoundEffect::EXPLOSION]->loadFromFile("assets/sound/explosion.ogg"));
    enabledEffect.push_back(bufferEffect[SoundElem::SoundEffect::FOOTSTEP]->loadFromFile("assets/sound/footstep.ogg"));
    enabledEffect.push_back(bufferEffect[SoundElem::SoundEffect::PAUSE]->loadFromFile("assets/sound/pause.ogg"));
    enabledEffect.push_back(bufferEffect[SoundElem::SoundEffect::START]->loadFromFile("assets/sound/start.ogg"));
    enabledEffect.push_back(bufferEffect[SoundElem::SoundEffect::VALIDATION_CLIC]->loadFromFile("assets/sound/validation_clic.ogg"));
    enabledMusic.push_back(bufferMusic[SoundElem::SoundMusic::GAME]->openFromFile("assets/sound/music_game.ogg"));
    enabledMusic.push_back(bufferMusic[SoundElem::SoundMusic::MENU]->openFromFile("assets/sound/music_menu.ogg"));
    enabledMusic.push_back(bufferMusic[SoundElem::SoundMusic::SCORE_SCREEN]->openFromFile("assets/sound/music_score_screen.ogg"));
    for (int i = 0; i < soundEffect.size(); i++)
        soundEffect[i]->setBuffer(*bufferEffect[i]);
}

Sound::~Sound()
{
    for (auto p : soundEffect)
        if (p != nullptr)
            delete p;
    for (auto p : bufferEffect)
        if (p != nullptr)
            delete p;
    for (auto p : bufferMusic)
        if (p != nullptr)
            delete p;
    soundEffect.clear();
    bufferEffect.clear();
    bufferMusic.clear();
    enabledMusic.clear();
    enabledEffect.clear();
}

void Sound::PlayEffect(SoundElem::SoundEffect effect) {
    if (effect < soundEffect.size() && enabledEffect[effect]) {
        soundEffect[effect]->play();
        soundEffect[effect]->setVolume(10);
    } else
        std::cout << "didn't found effect : " << effect << std::endl;
}

void Sound::PlayMusic(SoundElem::SoundMusic music) {
    if (music < bufferMusic.size() && enabledMusic[music]) {
        bufferMusic[music]->play();
        bufferMusic[music]->setLoop(true);
        bufferMusic[music]->setVolume(10);
    } else
        std::cout << "didn't found music : " << music << std::endl;
}

void Sound::StopMusic() {
    for (int i = 0; i < bufferMusic.size(); i++)
        bufferMusic[i]->stop();
}