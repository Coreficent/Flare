#include "Program.h"
#include "debug.h"
#include "Audio.h"

namespace Flare
{
	void Program::run(Key& key, Flare::Render::Renderer& renderer, Audio& audio)
	{
		if (key.input_manager.keyPressed(SDLK_w))
		{
			renderer.camera.setPosition(renderer.camera.getPosition() + glm::vec2(0.0, -5.0));
		}
		if (key.input_manager.keyPressed(SDLK_s))
		{
			renderer.camera.setPosition(renderer.camera.getPosition() + glm::vec2(0.0, 5.0));
		}

		if (key.input_manager.keyPressed(SDLK_a))
		{
			renderer.camera.setPosition(renderer.camera.getPosition() + glm::vec2(-5.0, 0.0));
		}
		if (key.input_manager.keyPressed(SDLK_d))
		{
			renderer.camera.setPosition(renderer.camera.getPosition() + glm::vec2(5.0, 0.0));
		}

		if (key.input_manager.keyPressed(SDLK_q))
		{
			renderer.camera.setScale(renderer.camera.getScale() + 0.1f);
		}
		if (key.input_manager.keyPressed(SDLK_e))
		{
			renderer.camera.setScale(renderer.camera.getScale() - 0.1f);
		}
		if (key.input_manager.keyPressed(SDL_BUTTON_LEFT))
		{
			glm::vec2 mouse_position = key.input_manager.get_mouse_position();
			mouse_position = renderer.camera.global_to_local(mouse_position);
			dout << mouse_position.x << " :: " << mouse_position.y << endl;
		}
		if (key.input_manager.keyPressed(SDL_BUTTON_LEFT))
		{
			SoundEffect sound2 = audio.load_sound_effect("sound/cg1.wav");
			sound2.play();
		}
	}
}
