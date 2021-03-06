#pragma once
#include <vector>

namespace Flare
{
	template <typename T>
	class Vial
	{
	public:
		T& operator[](unsigned int i)
		{
			return this->container[i];
		}

		T& next()
		{
			if (this->index == this->container.size())
			{
				this->container.emplace_back();
			}
			return this->container[this->index++];
		}

		const T* data() const
		{
			return this->container.data();
		}

		unsigned int size() const
		{
			return this->index;
		}

		void clear()
		{
			this->container.clear();
			this->index = 0;
		}

		void refill()
		{
			this->index = 0;
		}

		bool empty()
		{
			return this->index == 0;
		}

		T& at(int index)
		{
			return this->container.at(index);
		}

		int get_index() {
			return this->index;
		}

	private:
		std::vector<T> container{};

		unsigned int index{ 0 };
	};
}
