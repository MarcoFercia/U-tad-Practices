#include "Font.h"
#include <cstdio>


Font::Font()
{
}

bool Font::AlphaComponent(int i)
{
	return ((i + 1) % 4) == 0;
}



Font* Font::load(const char* filename, float height)
{

	Font* self = new Font();
	FILE* ttf;

	if (!fopen_s(&ttf, filename, "r"))
	{
		fseek(ttf, 0, SEEK_END);
		long size = ftell(ttf);
		rewind(ttf);

		unsigned char* buff = new unsigned char[size];
		if (fread(buff, 1, size, ttf))
		{
			fclose(ttf);
			stbtt_BakeFontBitmap(buff, 0, height, self->pixels, 512, 512, 0, 256, self->bake);
		}
		delete[] buff;

		int index = sizeof(colorpixel) / sizeof(colorpixel[0]);
		for (int i = 0; i < index; i++)
		{
			if (self->AlphaComponent(i))
			{
				self->colorpixel[i] = self->pixels[(i + 1) / 4];
			}
			else
			{
				self->colorpixel[i] = 255;
			}
		}

		self->texture = ltex_alloc(512, 512, 1);
		ltex_setpixels(self->texture, self->colorpixel);

	}
	self->pixelHeight = height;
	return self;
}



float Font::getHeight() const
{
	return 0.0f;
}

vec2 Font::getTextSize(const char* text) const
{
	vec2 size(0, 0);
	stbtt_aligned_quad q;
	for (const char* charac = text; *charac != '\0'; charac++) {
		stbtt_GetBakedQuad(bake, 512, 512, *charac, &size.x, &size.y, &q, true);
	}

	return size;
}

void Font::draw(const char* text, const vec2& pos) const
{
	vec2 myPos = pos;
	float prevX = myPos.x;
	stbtt_aligned_quad q;
	for (const char* character = text; *character != '\0'; character++) {
		stbtt_GetBakedQuad(bake, 512, 512, *character, &myPos.x, &myPos.y, &q, true);
		ltex_drawrotsized(texture, 	myPos.x, myPos.y, 0.f, 	1.f, 0.f, myPos.x - prevX, pixelHeight,q.s0, q.t0, q.s1, q.t1 );
		prevX = myPos.x;
	}
}
