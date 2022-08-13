-- Escribe codigo
require "library"
prepareWindow()

mousePositionX = nil
mousePositionY = nil

-- Define tus variables globales
-- Define tus funciones y llamadas

criaturas = {
    grifo = { texture = "creatures/gryphon.png",maxhp = 50, hp = 50, pos = {x = 30, y = 40}, size = {x = 92, y = 92}},
    mago = { texture = "creatures/mage.png",maxhp = 80, hp = 80, pos = {x = 30, y = 40}, size = {x = 64, y = 64}},
    grunt = { texture = "creatures/grunt.png",maxhp = 10, hp = 10, pos = {x = 30, y = 40}, size = {x = 72, y = 72}},
    peon = { texture = "creatures/peon.png",maxhp = 30, hp = 30, pos = {x = 30, y = 40}, size = {x = 32, y = 32}},
    dragon = { texture = "creatures/dragon.png",maxhp = 200, hp = 200, pos = {x = 30, y = 40}, size = {x = 128, y = 128}},
            }


enemigolist = {}
function enemigolist:new(_name,posx, posy)
     --local enemy = {Name = name,hp = criaturas[name].hp, pos = criaturas[name].pos , textura = criaturas[name].texture, size = criaturas[name].size}
     local enemy = {Name = _name ,maxhp = criaturas[_name].maxhp, hp = criaturas[_name].hp, texture = criaturas[_name].texture, size = criaturas[_name].size, pos = {x = posx, y=posy},ref =nil}
    --local enemy = {}    
    setmetatable(enemy, self)
    self.__index = self
    return enemy
end

function enemigolist:hit()
    self.hp = self.hp - 5
    if self.hp == 0 then
    self.size.x = self.size.x/2
    self.size.y = self.size.y/2
    removeCreature(self.ref)
    self.ref = addCreature(self)
    
    end  
end


enemigolisthuidizo = enemigolist:new("grifo",posx, posy)


function enemigolisthuidizo:hit()
    --self.enemigolist:hit()
    
     self.hp = self.hp - 5
  
    
    
    if (self.hp <= self.maxhp/2) then
        self.pos.x = math.random(1024)
        self.pos.y = math.random(768)
        setPropPosition(self.ref, self.pos.x,self.pos.y)
    end

    if self.hp == 0 then
    self.size.x = self.size.x/2
    self.size.y = self.size.y/2
    removeCreature(self.ref)
    self.ref = addCreature(self)
    end


end

enemigo1 = enemigolist:new("grifo",30,50)
enemigo2 = enemigolisthuidizo:new("peon",300,150)


list = {enemigo1,enemigo2}





    



function addCreature(_enem)
    texture_name = _enem.texture
    return addImage(texture_name, _enem.pos.x, _enem.pos.y, _enem.size.x, _enem.size.y)
end


-- Fin de tus funciones
-- Fin de tus variables globales


enemigo1.ref = addCreature(enemigo1)
enemigo2.ref = addCreature(enemigo2)



-- Termina tu definicion de variables

function onUpdate(seconds)

end

function onClickLeft(down)
    print("Clicked Left")
    if not down then
        -- Escribe tu código para el botón izquierdo
        creatureSizeX, creatureSizeY = getCreatureSize("griphon")
        
      
      
        -- Termina tu código
    end
end

function onClickRight(down)
    print("Clicked Right")
    
    if not down then
        -- Escribe tu código para el botón derecho
        coso =0
        for coso = 1, #list, coso+1 do
        PositionX = list[coso].pos.x 
        PositionY = list[coso].pos.y 
        creatureSizeX = list[coso].size.x
        creatureSizeY = list[coso].size.y
 if(mousePositionX >= PositionX  and  mousePositionX <= (PositionX +creatureSizeX)) then
    if(mousePositionY >= PositionY and  mousePositionY <= (PositionY +creatureSizeY)) then
    list[coso]:hit()
            
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

