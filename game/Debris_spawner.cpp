#include "Debris.h"
#include "Debris_spawner.h"

namespace Game
{
	Debris_spawner::Debris_spawner() noexcept
	{

	}

	Debris_spawner::Debris_spawner(shared_ptr<Sprite> spawn_target) noexcept : Spawner{ spawn_target }
	{

	}

	void Debris_spawner::enter_frame() noexcept
	{
		shared_ptr<Debris> debris{ make_shared<Debris>("texture/Debris.png") };
		debris->width = 100;
		debris->height = 100;
		debris->x = spawn_target->global_x();
		debris->y = spawn_target->global_y();
		this->add_child(debris);
	}
}
