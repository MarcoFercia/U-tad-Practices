-- Escribe codigo
require "library"
prepareWindow()

creature = drawCreature(layer, "griphon", 256, 256)
mousePositionX = 0
mousePositionY = 0
speedx = 50
speedy = 0



function onUpdate(seconds)
    creaturePositionX, creaturePositionY = getPropPosition(creature)
    -- Empieza tu código para mover a la criatura
    
    creaturePositionX = creaturePositionX + speedx * seconds   
    creaturePositionY = creaturePositionY + speedy * seconds   
    
    -- Termina tu código
    setPropPosition(creature, creaturePositionX, creaturePositionY)
end

function onClickLeft(down)
    if down then
        print("Clicked Left")
        creatureSizeX, creatureSizeY = getCreatureSize("griphon")
        creaturePositionX, creaturePositionY = getPropPosition(creature)
        -- Escribe tu código aqui para botón izquierdo ratón
       temp = 0
       if (not (speedx == 0)) then
           temp = speedx
           speedx = 0 
           speedy = temp      
      
       elseif (not(speedy == 0)) then
           temp = speedy
           speedy = 0 
           speedx = -temp
       end
       
       
        
        -- Termina tu código
    end
end

function onClickRight(down)
    print("Clicked Right")
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

