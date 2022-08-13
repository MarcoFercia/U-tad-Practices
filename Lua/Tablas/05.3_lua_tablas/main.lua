-- Escribe codigo
require "library"
prepareWindow()

mousePositionX = nil
mousePositionY = nil

-- Define tus variables globales

creatures = {}
creatures.grifo = { image = "creatures/gryphon.png"}
creatures.mago = { image = "creatures/mage.png"}
creatures.grunt = { image = "creatures/grunt.png"}
creatures.peon = { image = "creatures/peon.png"}
creatures.dragon = { image = "creatures/dragon.png"}




vector2pos = {x =30, y = 40}
vector2size = {x =84, y = 83}



-- Fin de tus variables globales

-- Define tus funciones y llamadas
function addCreature(nombre,pos,size)
    addImage(nombre,pos.x,pos.y,size.x,size.y) 
    --drawCreature(layer, nombre, pos.x, pos.y)
end

-- Fin de tus funciones




creature  = addCreature(creatures.grifo.image, vector2pos,vector2size)



function onUpdate(seconds)
end

function onClickLeft(down)
    print("Clicked Left")
    if not down then
        -- Escribe tu código para el botón izquierdo
        --vector2pos.x =mousePositionX
       -- vector2pos.y = mousePositionY
        --addCreature(creatures.dragon,vector2pos,vector2size)
        -- Termina tu código
    end
end

function onClickRight(down)
    print("Clicked Right")
    if not down then
        -- Escribe tu código para el botón derecho
        -- Termina tu código
    end
end

function onMouseMove(posX, posY)
    mousePositionX = posX
    mousePositionY = posY
    --print("Mouse Moved to " .. posX .. ","..posY)
end

function onKeyPress(key, down)
    print("Key pressed: "..key)
end



callbackConfiguration(onClickLeft, onClickRight, onMouseMove, onKeyPress)
mainLoop()

