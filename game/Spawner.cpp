#include "Spawner.h"

namespace Game
{
	Spawner::Spawner() noexcept
	{
	}

	Spawner::Spawner(shared_ptr<Sprite> spawn_layer) noexcept : spawn_layer{ spawn_layer }
	{

	}
}
