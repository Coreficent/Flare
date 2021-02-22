#include "AudioManager.h"
#include <sdl/SDL.h>
#include <iostream>

namespace Flare
{
	using namespace std;

	AudioManager::AudioManager()
	{
	}


	AudioManager::~AudioManager()
	{
	}

	void AudioManager::load(const std::string& file_path)
	{
		SDL_AudioSpec audio_spec{};
		Uint8* wav_start{nullptr};
		Uint32 wave_length{};

		if (!SDL_LoadWAV(file_path.c_str(), &audio_spec, &wav_start, &wave_length))
		{
			//TODO
			cerr << "cannot load wave" << file_path << endl;
		}

		AudioStruct audio = {};
		audio.position = wav_start;
		audio.length = wave_length;

		audio_spec.callback = this->audio_callback;
		audio_spec.userdata = &audio;


		auto device_id = SDL_OpenAudioDevice(nullptr, 0, &audio_spec, nullptr, SDL_AUDIO_ALLOW_ANY_CHANGE);
		if (!device_id)
		{
			//TODO
			cerr << "cannot open audio device" << SDL_GetError << endl;
		}

		SDL_PauseAudioDevice(device_id, 0);

		while (audio.length > 0)
		{
			SDL_Delay(10000);
		}

		SDL_CloseAudioDevice(device_id);

		SDL_FreeWAV(wav_start);
	}

	void AudioManager::audio_callback(void* user_data, Uint8* stream, int stream_length)
	{
		auto audio = static_cast<AudioStruct*>(user_data);

		if (!audio->length)
		{
			return;
		}
		auto length = static_cast<Uint32>(stream_length);
		length = length > audio->length ? audio->length : length;
		SDL_memcpy(stream, audio->position, length);
		audio->position += length;
		audio->length -= length;
	}
}
