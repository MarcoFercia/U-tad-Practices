#include "Sprite.h"



void Sprite::setCallback(CallbackFunc func)
{

	pCallBack = func;

}


Sprite::Sprite(const ltex_t* tex, int hframes, int vframes):texture(tex),Hframes(hframes),Vframes(vframes)
{
	Pivot = vec2(0.5, 0.5);

}

void* Sprite::getUserData()
{
	return UserData;
}

void Sprite::setUserData(void* data)
{
	UserData = data;
}

const ltex_t* Sprite::getTexture() const
{
	return texture;
}

void Sprite::setTexture(const ltex_t* tex, int hframes, int vframes)
{
	texture = tex;
	Hframes = hframes;
	Vframes = vframes;
}

lblend_t Sprite::getBlend() const
{
	return blend;
}

void Sprite::setBlend(lblend_t mode)
{
	blend = mode;
}
float Sprite::getRed() const
{
	return Red;
}

float Sprite::getGreen() const
{
	return Green;
}

float Sprite::getBlue() const
{
	return Blue;
}

float Sprite::getAlpha() const
{
	return Alpha;
}

void Sprite::setColor(float r, float g, float b, float a)
{
	Red = r;
	Green = g;
	Blue = b;
	Alpha = a;
}

const vec2& Sprite::getPosition() const
{
	return Position;
}

void Sprite::setPosition(const vec2& pos)
{
	Position = pos;

}

float Sprite::getAngle() const
{
	return angle;
}

void Sprite::setAngle(float _angle)
{
	angle = _angle;
}

const vec2& Sprite::getScale() const
{
	return Scale;
}

void Sprite::setScale(const vec2& scale)
{
	Scale = scale;

	int textureX = getTexture()->width;
	int textureY = getTexture()->height;

	float frameX = textureX / getHframes();
	float frameY = textureY / getVframes();

	Size = vec2(frameX * Scale.x, frameY * Scale.y);

}

vec2 Sprite::getSize() const
{
	return Size;
}

const vec2& Sprite::getPivot() const
{
	return Pivot;
}

void Sprite::setPivot(const vec2& pivot)
{
	Pivot = pivot;
}

int Sprite::getHframes() const
{
	return Hframes;
}

int Sprite::getVframes() const
{
	return Vframes;
}

int Sprite::getFps() const
{
	return fps;
}

void Sprite::setFps(int _fps)
{
	fps = _fps;
}

float Sprite::getCurrentFrame() const
{
	return CurrentFrame;
}

void Sprite::setCurrentFrame(int frame)
{
	CurrentFrame = frame;
}


void Sprite::SetFlipX(bool _option)
{
	flipX = _option;
}

void Sprite::update(float deltaTime)
{

	if (!pCallBack)
	{
		return;
	}

	(*pCallBack)(*this, deltaTime);

	timeCounter += deltaTime;

	

	if (timeCounter >= (1.f / getFps()))
	{
		timeCounter = 0;
		float temp = getCurrentFrame();
		
		if ((temp + 1) > getFps())
		{
			setCurrentFrame(1);
		}
		else
		{
			setCurrentFrame(temp + 1);
		}
		
	}



	//setUserData();

}

void Sprite::draw() const
{
	lgfx_setblend(blend);
	
	
	float currentframe = getCurrentFrame();



	int textureX =	getTexture()->width;
	int textureY = getTexture()->height;


	float frameX = textureX / getHframes();
	float frameY = textureY / getVframes();



	float u0 = ((currentframe * frameX) - frameX)/textureX;
	float v0 = ((currentframe * frameY) - frameY)/textureY;


	float u1 = (currentframe * frameX)/textureX;
	float v1 = (currentframe * frameY)/textureY;


	if (flipX)
	{
		float temp = u0;
		u0 = u1;
		u1 = temp;
	}
	



	const ltex_t* texture = getTexture();
	vec2 Position = getPosition();
	vec2 Scale = getScale();
	vec2 Pivot = getPivot();

	lgfx_setcolor(Red, Green, Blue, 1);
	

	ltex_drawrotsized(texture, Position.x, Position.y, getAngle(), Pivot.x, Pivot.y, Scale.x , Scale.y, u0, v0, u1, v1);

	//ltex_drawrotsized(texture, Position.x, Position.y, getAngle(), Pivot.x, Pivot.y, 640 , 92, 0, 0, 1, 1);


	//lgfx_drawrect(Position.x, Position.y, Scale.x, Scale.y);

}
