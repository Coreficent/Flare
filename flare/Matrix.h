#pragma once

namespace Flare
{
	class Matrix
	{
	public:
		Matrix();
		~Matrix();

		float a{1.0f};
		float b{0.0f};
		float c{0.0f};
		float d{1.0f};
		float x{0.0f};
		float y{0.0f};

		void translate(float x, float y);

	private:
		const float u{0.0f};
		const float v{0.0f};
		const float w{1.0f};
	};
}
