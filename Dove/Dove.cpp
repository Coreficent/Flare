#include <iostream>
#include <string>
#include <array>
#include "Dove.h"
#include "ResourceManager.h"
#include "display_object.h"

namespace Dove
{
	using namespace std;


	Dove::Dove(int windowWdith, int windowHeight) : sprite_font{nullptr}, window{}, camera{windowWdith, windowHeight}, camera_interface{windowWdith, windowHeight}, quad_batch_{}, input_manager{}, frame_manager{}, text_batch{}, audio_engine{}, currentState{GameState::running}, currentTicks{0}, windowWidth{windowWdith}, windowHeight{windowHeight}
	{
	}

	Dove::~Dove()
	{
	}

	void Dove::run()
	{
		this->initialize();

		Music music = this->audio_engine.load_music("music/x.ogg");
		music.play(-1);

		// running the game logic
		this->gameLoop();
	}

	void Dove::initialize()
	{
		// sdl initialization
		SDL_Init(SDL_INIT_EVERYTHING);

		// have two alternating buffers to render to smooth the rendering
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		this->window.createWindow("Dove", this->windowWidth, this->windowHeight, 0);

		this->quad_batch_.initialize();
		this->initializeShader();

		this->text_batch.initialize();

		this->sprite_font = new SpriteFont{"font/disney.ttf",64};
		//
		//this->camera.initialize();
		//
		// initialize audio
		this->audio_engine.initialize();
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
			this->camera_interface.update();
			this->render();
		}
		SDL_Quit();
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
				SoundEffect sound = this->audio_engine.load_sound_effect("sound/shotgun.wav");
				sound.play();

				break;
			case SDL_MOUSEBUTTONUP:
				this->input_manager.releaseKey(event.button.button);
				SoundEffect sound2 = this->audio_engine.load_sound_effect("sound/cg1.wav");
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
	void Dove::render()
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
		for (auto i{0}; i < 1000; ++i)
		{
			this->quad_batch_.draw(position + glm::vec4{50.0f * i,0.0f,0.0f,0.0f}, uv, texture.id, 0.0f, color);
		}
		
		this->quad_batch_.draw(glm::vec4{ 0.0f,0.0f,512.0f,1024.0f }, uv, this->sprite_font->_texID, 0.0f, color);
		// TODO display object test
		
		Display_object display_object{ texture.id };
		display_object.set_x(-50.0f);
		display_object.set_width(50.0f);
		display_object.set_height(50.0f);

		this->quad_batch_.glyphs.emplace_back();

		

		display_object.render(this->quad_batch_.glyphs.back());
		
		// TODO display object test //
		this->quad_batch_.end();
		this->quad_batch_.render();

		this->draw_text();

		glBindTexture(GL_TEXTURE_2D, 0);
		this->colorProgram.unuse();

		this->window.swapBuffer();
	}

	void Dove::draw_text()
	{
		auto locationCamera = this->colorProgram.getUniform("cameraPosition");
		auto cameraMatrix = this->camera_interface.getCameraMatrix();

		glUniformMatrix4fv(locationCamera, 1, GL_FALSE, &(cameraMatrix[0][0]));

		static int rand_test = 0;

		static int count = 0;

		if (count % 1000 == 0)
		{
			rand_test = rand() % 9;
		}

		count++;

		char buffer[256];
		this->text_batch.begin();
		//TODO make it dynamic to prevent overflow
		sprintf_s(buffer, "a b c d e f g \nh i j k l n m \no p q r s t \nu v w x y z");
		this->sprite_font->draw(this->text_batch, buffer, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f), 0.0f, Color{125,0,125,125}, Justification::LEFT);
		

		this->text_batch.end();
		this->text_batch.render();
	}
}
