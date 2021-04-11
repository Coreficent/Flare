#include "Program.h"
#include "debug.h"
#include "Audio.h"

namespace Flare
{
	void Program::run(Flare::Renderer& renderer, Audio& audio)
	{
		if (Key::is_down(SDLK_w))
		{
			renderer.camera.setPosition(renderer.camera.getPosition() + glm::vec2(0.0, -5.0));
		}
		if (Key::is_down(SDLK_s))
		{
			renderer.camera.setPosition(renderer.camera.getPosition() + glm::vec2(0.0, 5.0));
		}
		if (Key::is_down(SDLK_a))
		{
			renderer.camera.setPosition(renderer.camera.getPosition() + glm::vec2(-5.0, 0.0));
		}
		if (Key::is_down(SDLK_d))
		{
			renderer.camera.setPosition(renderer.camera.getPosition() + glm::vec2(5.0, 0.0));
		}
		if (Key::is_down(SDLK_q))
		{
			renderer.camera.setScale(renderer.camera.getScale() + 0.1f);
		}
		if (Key::is_down(SDLK_e))
		{
			renderer.camera.setScale(renderer.camera.getScale() - 0.1f);
		}
		if (Key::is_down(SDL_BUTTON_LEFT))
		{
			glm::vec2 mouse_position = Key::mouse_position;
			mouse_position = renderer.camera.global_to_local(mouse_position);
			dout << mouse_position.x << " :: " << mouse_position.y << endl;
		}
		if (Key::is_down(SDL_BUTTON_LEFT))
		{
			SoundEffect sound2 = audio.load_sound_effect("sound/bounce.wav");
			sound2.play();
		}
	}
}
