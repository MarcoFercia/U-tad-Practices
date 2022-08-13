#pragma once

#include "stb_truetype.h"

#include"Vector2.h"
#include <litegfx.h>


class Font
{
public:


	static Font* load(const  char* filename, float height);
	float getHeight() const;
	vec2 getTextSize(const char* text) const;
	void draw(const char* text, const vec2& pos) const;

	ltex_t* texture=nullptr;
	stbtt_bakedchar bake[256]{};


	//vec2 TextSize;
	//float Height;

private:

	unsigned char pixels[512 * 512]{};
	unsigned char colorpixel[512 * 512*4]{};
	int pixelHeight=32;
	bool AlphaComponent(int i);

	Font();
	~Font();
};
	

	