#pragma once

#include <map>
#include <sdl/SDL_mixer.h>
#include <string>

namespace Flare
{
	using namespace std;

	class SoundEffect
	{
	public:
		friend class Audio;
		void play(int loop = 0);
	private:
		Mix_Chunk* mix_chunk;
	};

	class Musice
	{
	public:
		friend class Audio;
		void play(int loop = -1);
		void stop();
		void resume();
		void pause();
	private:
		Mix_Music* mix_music;
	};


	class Audio
	{
	public:
		Audio();
		~Audio();

		void initialize();


		SoundEffect load_sound_effect(const std::string& file_path);
		Musice load_music(const std::string& file_path);
	private:
		map<string, Mix_Chunk*> effect_map;
		map<string, Mix_Music*> music_map;
	};
}
