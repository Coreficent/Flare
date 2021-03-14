#include "flare/Flare_core.h"
#include "gsl/gsl"
#include <iostream>
#include "flare/ResourceManager.h"

int main(int argc, char** argv)
{
	using namespace Flare::Core;

	std::cout << "Hello World from Benchmark!\n";

	Flare_core core{ 500,1000 };



	static auto cake_texture = Flare::ResourceManager::getTexture("texture/cake.png");

	Flare::Display::Sprite cake1{};
	cake1.set_texture_id(cake_texture.id);
	cake1.set_width(200.0f);
	cake1.set_height(200.0f);
	cake1.set_y(200.0f);

	core.get_stage().add_child(cake1);

	Flare::Display::Sprite cake2{};
	cake2.set_texture_id(cake_texture.id);
	cake2.set_width(150.0f);
	cake2.set_height(150.0f);
	cake1.set_y(400.0f);

	core.get_stage().add_child(cake2);



	static auto texture_arrow = Flare::ResourceManager::getTexture("texture/arrow.png");

	Flare::Display::Sprite arrow{};
	arrow.set_texture_id(texture_arrow.id);
	arrow.set_width(200.0f);
	arrow.set_height(200.0f);
	arrow.set_x(200.0f);
	arrow.set_y(200.0f);

	core.get_stage().add_child(arrow);



	core.run();

	return 0;
}
