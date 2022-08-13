#pragma once
//#include "Vector2.h"
#include "Sprite.h"
#include "litegfx.h"
#include <list>
#include <vector>


using namespace std;


struct background
{
	const ltex_t* tex;
	float scrollRatio;
	vec2 scrollSpeed;
	vec2 scroll;
	vec2 scrollOffset;
};


class World
{
public:
	World(
		float _clearRed = 0.15f, float _clearGreen = 0.15f, float _clearBlue = 0.15f,
		const ltex_t* _back0 = nullptr, const ltex_t* _back1 = nullptr,
		const ltex_t* _back2 = nullptr, const ltex_t* _back3 = nullptr);

	~World();

	float getClearRed() const;
	float getClearGreen() const;
	float getClearBlue() const;

	const ltex_t* getBackground(size_t _layer) const;

	float getScrollRatio(size_t _layer) const;
	void setScrollRatio(size_t _layer, float _ratio);

	const vec2& getScrollSpeed(size_t _layer) const;
	void setScrollSpeed(size_t _layer, const vec2& _speed);

	const vec2& getCameraPosition() const;
	void setCameraPosition(const vec2& _pos);

	void addSprite(Sprite& _sprite);
	void removeSprite(Sprite& _sprite);

	void update(float _deltaTime);
	void draw(const vec2& _screenSize);

	void setScreenSize(vec2 _screenSize);


	bool loadMap(const char* _filename, uint16_t _firstColId);
	vec2 getMapSize() const;
	bool moveSprite(Sprite& _sprite, const vec2& _amount);

public:

protected:

	

private:


	float clearRed;
	float clearBlue;
	float clearGreen;

	
	vec2 cameraPosition;


	vec2 mapSize;
	vec2 ScreenSize;

	background backimages[4];

	

	std::list<Sprite*> vSprites;

};