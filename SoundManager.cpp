#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager()
{
}

bool SoundManager::loadSound(const std::string& name, const std::string& filename)
{
	//check if its already loaded under that name
	//This is a better way to check than using a for loop since end will be returned if the item is not present in the map
	if (SoundBuffers.find(name) != SoundBuffers.end())
	{
		return true;
	}
	//check if the file exists, load to buffer if it does
	sf::SoundBuffer currBuffer;
	if (!currBuffer.loadFromFile(filename))
	{
		std::cout << "Failed to load SoundBuffer: " << filename << std::endl;
		return false;
	}
	SoundBuffers[name] = std::move(currBuffer);
	Sounds[name].setBuffer(SoundBuffers[name]);
	return true;
}

void SoundManager::playSound(const std::string& name)
{
	//find and play the sound with the provided name
	auto sfx = Sounds.find(name);
	if (sfx != Sounds.end())
	{
		sfx->second.play();
	}
	else
	{
		std::cout << "Sound not found";
	}
}

void SoundManager::stopSound(const std::string& name)
{
	//find and stop the sound with the provided name
	auto sfx = Sounds.find(name);
	if (sfx != Sounds.end())
	{
		sfx->second.stop();
	}
}

bool SoundManager::playMusic(const std::string& filename, bool loop)
{
	if (!BGM.openFromFile(filename))
	{
		std::cout << "Cannot Open Music File Named: " << filename << std::endl;
		return false;
	}
	BGM.setLoop(loop);
	BGM.play();
	return true;
}

void SoundManager::stopMusic()
{
	BGM.stop();
}
