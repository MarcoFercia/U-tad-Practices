-- Escribe codigo
require "library"
prepareWindow()

mousePositionX = nil
mousePositionY = nil

-- Define tus variables globales
enemies = {}
lifecenemies = {}
index =1
-- Termina tu definicion de variables

function onUpdate(seconds)
end

function onClickLeft(down)
    print("Clicked Left")
    if not down then
        -- Escribe tu código para el botón izquierdo
        creatureSizeX, creatureSizeY = getCreatureSize("griphon")
        
      
        table.insert(enemies,index, (addCreature("griphon", mousePositionX, mousePositionY)))
        table.insert(lifecenemies, index, 25)
        index = index + 1
        -- Termina tu código
    end
end

function onClickRight(down)
    print("Clicked Right")
    creatureSizeX, creatureSizeY = getCreatureSize("griphon")
    if not down then
        -- Escribe tu código para el botón derecho
        coso =0
        for coso = 1, #enemies, coso+1 do
        PositionX, PositionY = getPropPosition(enemies[coso])
      
 if(mousePositionX >= PositionX  and  mousePositionX <= (PositionX +creatureSizeX)) then
    if(mousePositionY >= PositionY and  mousePositionY <= (PositionY +creatureSizeY)) then
    
    lifecenemies[coso] = lifecenemies[coso] - 5
        if(lifecenemies[coso]<=0) then
        removeCreature(enemies[coso])
        end
      end       
   end       
  end    
      
        
        
        
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

