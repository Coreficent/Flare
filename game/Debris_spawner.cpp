#include "Debris.h"
#include "Debris_spawner.h"

namespace Game
{
	Debris_spawner::Debris_spawner() noexcept
	{

	}

	Debris_spawner::Debris_spawner(shared_ptr<Sprite> spawn_layer) noexcept : Spawner{ spawn_layer }
	{

	}

	void Debris_spawner::enter_frame() noexcept
	{
		shared_ptr<Debris> debris{ make_shared<Debris>("texture/Debris.png") };
		debris->width = 100;
		debris->height = 100;
		debris->x = spawn_layer->global_x();
		debris->y = spawn_layer->global_y();
		this->add_child(debris);
	}
}
