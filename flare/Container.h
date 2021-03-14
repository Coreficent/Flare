#pragma once

#include "Quad.h"
#include "Sprite.h"

#include <memory>
#include <vector>

namespace Flare::Display
{
	using namespace std;
	using namespace Flare::Display;

	class Container
	{

	public:
		Container() noexcept;
		Container(const Container& value) = default;
		Container(Container&& value) = default;
		Container& operator=(const Container& value) = default;
		Container& operator=(Container&& value) = default;
		virtual ~Container();

		void add_child(shared_ptr<Sprite> child);
		void reomve_last_child() noexcept;
		virtual void enter_frame() noexcept;

		vector<Quad> get_quads();

	private:
		vector<shared_ptr<Sprite>> children{};

	};

}
