#include "Audio.h"
#include <sdl/SDL_mixer.h>

namespace Flare
{
	void SoundEffect::play(int loop)
	{
		if (Mix_PlayChannel(-1, this->mix_chunk, loop) == -1)
		{
			if (Mix_PlayChannel(rand()%8, this->mix_chunk, loop) == -1)
			{
				printf("no channel left");
			}
		}
	}

	void Musice::play(int loop)
	{
		Mix_PlayMusic(this->mix_music, loop);
	}

	void Musice::stop()
	{
		Mix_HaltMusic();
	}

	void Musice::resume()
	{
		Mix_ResumeMusic();
	}

	void Musice::pause()
	{
		Mix_PauseMusic();
	}

	Audio::Audio()
	{
	}


	Audio::~Audio()
	{
		//used sdl quit else where
		Mix_CloseAudio();
		Mix_Quit();
	}

	void Audio::initialize()
	{
		if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == -1)
		{
			// TODO 
			printf("mixer initilization failed");
		}
		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT, 2, 1024))
		{
			//TODO
			printf("audio failed to open");
		}
	}


	SoundEffect Audio::load_sound_effect(const std::string& file_path)
	{
		auto it = this->effect_map.find(file_path);

		SoundEffect effect;

		if (it == this->effect_map.end())
		{
			Mix_Chunk* chunk = Mix_LoadWAV(file_path.c_str());
			if (chunk == nullptr)
			{
				printf("load sound filed");
			}
			effect.mix_chunk = chunk;
			this->effect_map[file_path] = chunk;
		}
		else
		{
			effect.mix_chunk = it->second;
		}
		return effect;
	}

	Musice Audio::load_music(const std::string& file_path)
	{
		auto it = this->music_map.find(file_path);

		Musice effect;

		if (it == this->music_map.end())
		{
			Mix_Music* music = Mix_LoadMUS(file_path.c_str());
			if (music == nullptr)
			{
				printf("load sound filed");
			}
			effect.mix_music = music;
			this->music_map[file_path] = music;
		}
		else
		{
			effect.mix_music = it->second;
		}
		return effect;
	}
}
