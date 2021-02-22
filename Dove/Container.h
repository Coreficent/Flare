#pragma once
#include "Display.h"
#include <memory>

namespace Dove
{
	class Container : public Display
	{
	public:
		Container();
		~Container();
		
		void add_child(std::shared_ptr<Display> child);
		void remove_child(std::shared_ptr<Display> child);
		void render() const override;

	private:
		std::vector<std::shared_ptr<Display>> children;
	};

}
