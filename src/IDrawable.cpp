#include "IDrawable.h"

void Graphics::Draw()
{
	Iterator begin = elements.begin();
	Iterator end = elements.end();
	while (begin != end)
	{
		(**begin).Draw();
		++begin;
	}
}
