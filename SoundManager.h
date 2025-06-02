#pragma once
#include <SFML/Audio.hpp>
#include <map>
class SoundManager
{
private:
	std::map<std::string, sf::SoundBuffer> SoundBuffers;
	std::map<std::string, sf::Sound> Sounds;
	sf::Music BGM;
public:
	SoundManager();
	//Sound Management
	//return as bool for easy debugging
	bool loadSound(const std::string& name, const std::string& filename);
	void playSound(const std::string& name);
	void stopSound(const std::string& name);
	//BGM Management
	bool playMusic(const std::string& filename, bool loop = true);
	void stopMusic();

};

