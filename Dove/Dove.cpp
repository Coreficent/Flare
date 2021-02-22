#include <iostream>
#include <string>
#include <array>
#include "Dove.h"
#include "ResourceManager.h"
#include "Display.h"
#include "mathematics.h"
#include "debug.h"

namespace Dove
{
	using namespace std;

	Dove* Dove::core{nullptr};

	Dove::Dove(int windowWdith, int windowHeight)
		:  camera{windowWdith, windowHeight},  quad_batch_{}, input_manager{}, frame_manager{}, text_batch{}, currentState{GameState::running}, currentTicks{0}, windowWidth{windowWdith}, windowHeight{windowHeight}
	{
		dout << "<Debug Mode>" << endl;

		

		///////////////////

		/////
		//this->window.borderless = true;
		//this->window.full_screen = true;
		this->window.initialize("Dove", this->windowWidth, this->windowHeight);
		this->render.initialize();
		this->audio.initialize();
		this->sprite_font.initialize("font/disney.ttf", 64);

		this->quad_batch_.initialize();
		this->initializeShader();

		this->text_batch.initialize();


		//
		//this->camera.initialize();
		//
		// initialize audio
		

		core = this;
	}

	Dove::~Dove()
	{
		
	}

	void Dove::run()
	{
		
		Musice music = this->audio.load_music("music/x.ogg");
		music.play(-1);

		// running the game logic
		this->gameLoop();
	}



	void Dove::initializeShader()
	{
		this->colorProgram.compileShader("shader/colorShade.sv", "shader/colorShade.sf");
		this->colorProgram.addAttribute("vertexPosition");
		this->colorProgram.addAttribute("vertexColor");
		this->colorProgram.addAttribute("vertexUV");
		this->colorProgram.linkShader();
	}

	// main loop
	void Dove::gameLoop()
	{
		while (this->currentState != GameState::ended)
		{
			this->frame_manager.calculate_fps();
			//this->timeTracker += 0.1f;
			this->processInput();
			this->camera.update();

			this->renderLoop();
		}
	}

	// process input
	void Dove::processInput()
	{
		SDL_Event event{};

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				this->currentState = GameState::ended;
				break;
			case SDL_MOUSEMOTION:
				this->input_manager.setMousePosition(event.motion.x, event.motion.y);
				break;
			case SDL_KEYDOWN:
				this->input_manager.pressKey(event.key.keysym.sym);
				break;
			case SDL_KEYUP:
				this->input_manager.releaseKey(event.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				this->input_manager.pressKey(event.button.button);
				//TODO use member var
				SoundEffect sound = this->audio.load_sound_effect("sound/shotgun.wav");
				sound.play();

				break;
			case SDL_MOUSEBUTTONUP:
				this->input_manager.releaseKey(event.button.button);
				SoundEffect sound2 = this->audio.load_sound_effect("sound/cg1.wav");
				sound2.play();
				break;
			}
		}


		if (this->input_manager.keyPressed(SDLK_w))
		{
			this->camera.setPosition(this->camera.getPosition() + glm::vec2(0.0, -5.0));
		}
		if (this->input_manager.keyPressed(SDLK_s))
		{
			this->camera.setPosition(this->camera.getPosition() + glm::vec2(0.0, 5.0));
		}

		if (this->input_manager.keyPressed(SDLK_a))
		{
			this->camera.setPosition(this->camera.getPosition() + glm::vec2(-5.0, 0.0));
		}
		if (this->input_manager.keyPressed(SDLK_d))
		{
			this->camera.setPosition(this->camera.getPosition() + glm::vec2(5.0, 0.0));
		}

		if (this->input_manager.keyPressed(SDLK_q))
		{
			this->camera.setScale(this->camera.getScale() + 0.1f);
		}
		if (this->input_manager.keyPressed(SDLK_e))
		{
			this->camera.setScale(this->camera.getScale() - 0.1f);
		}
		if (this->input_manager.keyPressed(SDL_BUTTON_LEFT))
		{
			glm::vec2 mouse_position = this->input_manager.get_mouse_position();
			mouse_position = this->camera.global_to_local(mouse_position);
			cout << mouse_position.x << " :: " << mouse_position.y << endl;
		}
	}

	// render
	void Dove::renderLoop()
	{
		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		this->colorProgram.use();
		glActiveTexture(GL_TEXTURE0);

		auto textureLocation = this->colorProgram.getUniform("cakeSampler");
		glUniform1i(textureLocation, 0);

		// update timeTracker
		//auto location = this->colorProgram.getUniform("timeTracker");
		//glUniform1f(location, this->timeTracker);

		// camera location
		auto locationCamera = this->colorProgram.getUniform("cameraPosition");
		auto cameraMatrix = this->camera.getCameraMatrix();

		glUniformMatrix4fv(locationCamera, 1, GL_FALSE, &(cameraMatrix[0][0]));

		this->quad_batch_.begin();
		glm::vec4 position{0.0f,0.0f,50.0f,50.0f};
		glm::vec4 uv{0.0f,0.0f,1.0f,1.0f};
		static auto texture = ResourceManager::getTexture("texture/cake.png");
		Color color;
		color.r = 255;
		color.g = 255;
		color.b = 255;
		color.a = 255;
		Display display_object{};
		display_object.set_texture_id(texture.id);
		display_object.set_width(100.0f);
		display_object.set_height(100.0f);
		display_object.scale(2.0f);
		display_object.rotate(to_radian(0.0f));
		for (auto i{0}; i < 1500; ++i)
		{
			display_object.set_x(100.0f * i);
			display_object.render();
		}
		///////// stage renderer
		this->stage.render();

		//////////


		this->sprite_font.draw(this->quad_batch_, "a b c d e f g \nh i j k l n m \no p q r s t \nu v w x y z", glm::vec2(1.0f), glm::vec2(1.0f), 0.0f, Color{125,0,125,125});

		// ouput sprite sheet
		Glyph& glyph = this->quad_batch_.next_glyph();

		glyph.top_left.color = color;
		glyph.top_left.setPosition(0.0f, 0.0f);
		glyph.top_left.setUV(0.0f, 0.0f);

		glyph.top_right.color = color;
		glyph.top_right.setPosition(500.0f, 0.0f);
		glyph.top_right.setUV(1.0f, 0.0f);

		glyph.down_left.color = color;
		glyph.down_left.setPosition(0.0f, 500.0f);
		glyph.down_left.setUV(0.0f, 1.0f);

		glyph.down_right.color = color;
		glyph.down_right.setPosition(500.0f, 500.0f);
		glyph.down_right.setUV(1.0f, 1.0f);

		glyph.texture = this->sprite_font._texID;

		////////// out put sprite sheet
		this->quad_batch_.end();
		this->quad_batch_.render();

		//this->draw_text();

		glBindTexture(GL_TEXTURE_2D, 0);
		this->colorProgram.unuse();

		this->window.swap_window();
	}
}
