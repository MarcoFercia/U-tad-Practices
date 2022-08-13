#pragma once
#include <litegfx.h>
#include "Vector2.h"



class Sprite
{
public:

	// Tipo de la función callback
	typedef void (*CallbackFunc)(Sprite&, float);


	// Indicamos el número de frames en horizontal y vertical
	// que tendrá la imagen del sprite
	Sprite(const ltex_t* tex, int hframes = 1, int vframes = 1);


	// Establecemos puntero a la función callback
	void setCallback(CallbackFunc func);

	

	// Puntero genérico a datos (normalmente introducimos aquí los datos
	// del sprite que se van a utilizar en la función callback)
	void* getUserData();
	void setUserData(void* data);


	const ltex_t* getTexture() const;
	void setTexture(const ltex_t* tex, int hframes = 1, int vframes = 1);


	lblend_t getBlend() const;
	void setBlend(lblend_t mode);


	float getRed() const;
	float getGreen() const;
	float getBlue() const;
	float getAlpha() const;
	void setColor(float r, float g, float b, float a);


	const vec2& getPosition() const;
	void setPosition(const vec2& pos);


	float getAngle() const;
	void setAngle(float _angle);


	const vec2& getScale() const;
	void setScale(const vec2& scale);


	// Tamaño de un frame multiplicado por la escala
	vec2 getSize() const;


	// Este valor se pasa a ltex_drawrotsized en el pintado
	// para indicar el pivote de rotación
	const vec2& getPivot() const;
	void setPivot(const vec2& pivot);


	int getHframes() const;
	int getVframes() const;


	// Veces por segundo que se cambia el frame de animación
	int getFps() const;
	void setFps(int _fps);


	// Frame actual de animación
	float getCurrentFrame() const;
	void setCurrentFrame(int frame);


	void update(float deltaTime);
	void draw() const;


	void SetFlipX(bool _option);


public:

	CallbackFunc pCallBack;


	
	float timeCounter;


	


private:
	void* UserData = nullptr;
	const ltex_t* texture;
	lblend_t blend;
	float Red = 0;
	float Green = 0;
	float Blue = 0;
	float Alpha = 0;
	vec2 Scale = vec2(0.f, 0.f);
	float angle = 0;
	vec2 Position = 0;
	int fps = 0;
	int Hframes = 1;
	int Vframes = 1;
	vec2 Pivot = vec2(0.f, 0.f);
	vec2 Size = vec2(0.f, 0.f);
	float CurrentFrame = 1;
	bool flipX = false;












};