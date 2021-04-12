#include "Spawner.h"

namespace Game
{
	Spawner::Spawner() noexcept
	{
	}

	Spawner::Spawner(shared_ptr<Sprite> spawn_target) noexcept : spawn_target{ spawn_target }
	{

	}
}
