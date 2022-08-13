-- Escribe codigo
require "library"
require "prepare"

-- Define tus variables globales
vector2 = { x= 0,y=0}
-- Termina tu definicion de variables

function pintarPunto(punto)
    -- Rellenar c�digo para pintar un punto en la pantalla
drawPoint(punto.x,punto.y)
    -- Fin de c�digo
end

function onUpdate(seconds)
end

function onDraw()
    -- Empieza tu c�digo, que debe emplear la funcion pintarPunto
    vector2.x = 500
    vector2.y = 350
    pintarPunto(vector2)
    -- Termina tu c�digo
end

function onClickLeft(down)
    print("Clicked Left")
    if down then
    end
end

function onClickRight(down)
    print("Clicked Right")
    if down then
    end
end


function onMouseMove(posX, posY)
    --print("Mouse Moved to " .. posX .. ","..posY)
end

function onKeyPress(key, down)
    print("Key pressed: "..key)
end



callbackConfiguration(onClickLeft, onClickRight, onMouseMove, onKeyPress, onDraw, window_layer)
mainLoop()

