#include <pacman_include.hpp>
#include "lua.h"
#include <stdio.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"


lua_State* L;

int num_coins = 0;
const int platas_para_oro = 5;
const int bronces_para_plata = 100;

const float max_vida = 1.5f;
float vida = max_vida;


int scorepowerup = 5;
float timepowerup = 5;
float speedpowerup = 2;
struct colorpowerUp
{
    int r = 0;
    int g = 0;
    int b = 0;

};

colorpowerUp colorpacmanpowerup;
//colorpowerUp colorpacmanlife;

int scoretobroncemedall = 20;
int scorecoin = 5;


unsigned char* luaSetColor(float& _lives)
{
    unsigned char cColor[] = { 0, 0, 0 };
    lua_getglobal(L, "setColor");
    if (lua_isfunction(L, -1))
    {
        lua_pushnumber(L, vida);
        lua_pcall(L, 1, 3, 0);
        if (!lua_isnil(L, -1))
        {
            for (int i = 2; i >= 0; --i)
            {
                cColor[i] = (char)lua_tonumber(L, -1);
                lua_pop(L, 1);
            }
        }
    }
    return cColor;
}



bool pacmanEatenCallback(int& score, bool& muerto)
{ // Pacman ha sido comido por un fantasma
    vida -= 0.5f;
    muerto = vida < 0.0f;

    return true;
}

bool coinEatenCallback(int& score)
{ // Pacman se ha comido una moneda
    ++num_coins;
    score = num_coins * scorecoin;

    return true;
}

bool frameCallback(float time)
{ // Se llama periodicamente cada frame
    return false;
}

bool ghostEatenCallback(int& score)
{ // Pacman se ha comido un fantasma
    return false;
}

bool powerUpEatenCallback(int& score)
{ // Pacman se ha comido un powerUp
    setPacmanSpeedMultiplier(speedpowerup);
    setPowerUpTime(timepowerup);
    unsigned char* cPowerUpColor = luaSetColor(vida);

    colorpacmanpowerup.r = cPowerUpColor[0];
    colorpacmanpowerup.g = cPowerUpColor[1];
    colorpacmanpowerup.b = cPowerUpColor[2];

    setPacmanColor(colorpacmanpowerup.r, colorpacmanpowerup.g, colorpacmanpowerup.b);


    score += scorepowerup;

    return true;
}

bool powerUpGone()
{ // El powerUp se ha acabado
    setPacmanColor(255, 0, 0);
    setPacmanSpeedMultiplier(1.0f);
    return true;
}

bool pacmanRestarted(int& score)
{
    score = 0;
    num_coins = 0;
    vida = max_vida;

    return true;
}

bool computeMedals(int& oro, int& plata, int& bronce, int score)
{

    bronce = score / scoretobroncemedall;


    plata = score / bronces_para_plata;
    //bronce = score % bronces_para_plata;

    oro = plata / platas_para_oro;
    plata = plata % platas_para_oro;

    return true;
}

bool getLives(float& vidas)
{
    vidas = vida;
    return true;
}

bool setImmuneCallback()
{
    return true;
}

bool removeImmuneCallback()
{
    return true;
}

bool InitGame()
{

    L = luaL_newstate(); /* crea el entorno de lua */
    luaL_openlibs(L); /* abre las librerias */
    int error = luaL_loadfile(L, "test.lua"); /* carga el codigo en la pila */
    error |= lua_pcall(L, 0, 0, 0); // ejecuta el codigo
    if (error)
    {
        fprintf(stderr, "%s", lua_tostring(L, -1)); // el mensaje de error esta en la cima de la pila
        lua_pop(L, 1); // quitar el mensaje de error de la pila
    }

    

 
    lua_getglobal(L, "scorepowerup");
    scorepowerup = (int)lua_tointeger(L, -1);

    lua_getglobal(L, "timepowerup");
    timepowerup = (float)lua_tonumber(L, -1);

    lua_getglobal(L, "speedpowerup");
     speedpowerup = (float)lua_tonumber(L, -1);

    lua_getglobal(L, "rcolor");
    colorpacmanpowerup.r  = (int)lua_tointeger(L, -1);

    lua_getglobal(L, "gcolor");
    colorpacmanpowerup.g = (int)lua_tointeger(L, -1);

    lua_getglobal(L, "bcolor");
    colorpacmanpowerup.b = (int)lua_tointeger(L, -1);

    lua_getglobal(L, "scoretobroncemedall");
     scoretobroncemedall = (int)lua_tointeger(L, -1);

    lua_getglobal(L, "scorecoin");
    scorepowerup = (int)lua_tointeger(L, -1);






    return true;
}

bool EndGame()
{
    lua_close(L); /* cierra el entorno */
    return true;
}