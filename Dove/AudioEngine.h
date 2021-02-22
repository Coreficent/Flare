#pragma once
#include <sdl/SDL_mixer.h>
#include <string>
#include <map>

namespace Dove {

	using namespace std;

	class SoundEffect
	{
	public:
		friend class AudioEngine;
		void play(int loop = 0);
	private:
		Mix_Chunk* mix_chunk;
	};

	class Music
	{
		
	public:
		friend class AudioEngine;
		 void play(int loop = -1);
		 void stop();
		 void resume();
		 void pause();
	private:
		Mix_Music* mix_music;
	};


	class AudioEngine
	{
	public:
		AudioEngine();
		~AudioEngine();

		void initialize();
		void finalize();

		SoundEffect load_sound_effect(const std::string& file_path);
		Music load_music(const std::string& file_path);
	private:
		map<string, Mix_Chunk*> effect_map;
		map<string, Mix_Music*> music_map;
	};

}
