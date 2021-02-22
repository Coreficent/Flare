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

		const T* begin() const
		{
			return &this->container.front();
		}

		const T* end() const
		{
			return &this->container.front() + this->index;
		}

		T& next()
		{
			if (this->index == this->container.size())
			{
				this->container.emplace_back();
			}
			return this->container[this->index++];
		}

		void push_back(T data)
		{
			if (this->index == this->container.size())
			{
				this->container.push_back(data);
			}else{
				this->container[this->index] = data;
			}
			++this->index;
		}

		const T* data() const noexcept
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


	private:
		std::vector<T> container{};

		unsigned int index{0};
	};
}
