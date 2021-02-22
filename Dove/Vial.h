#pragma once
#include <vector>


namespace Dove
{
	template <typename T>

	

	class Vial
	{
	public:
		Vial()
		{
		}

		~Vial()
		{
		}





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

		class IType
		{
		};

	private:
		std::vector<T> container{};

		unsigned int index{0};
	};
}
