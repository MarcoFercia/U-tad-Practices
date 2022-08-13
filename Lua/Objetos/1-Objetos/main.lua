-- Escribe tu código

vector = {}


function vector.new(x,y)
    local vec = {x = x, y = y}
    setmetatable(vec, vector)
    return vec
end

function vector.__add(vec,other_vec)
     return vector.new(vec.x+other_vec.x, vec.y+other_vec.y)
end

function vector.__sub(vec,other_vec)
     return vector.new(vec.x-other_vec.x, vec.y-other_vec.y)
end

function vector.dot(vec,other_vec)
    return vec.x * other_vec.x + vec.y * other_vec.y
end

function vector.lenght(vec)
      return math.sqrt(vec.x^2 + vec.y^2)
end


function vector.normalize(vec)
      m = vector.lenght(vec)
      if (m ~=0) then
        return vector.new(vec.x/m, vec.y/m)
      end
      return vec
end


function vector.scale(vec)
    return vector.new(vec.x* value, vec.y * value)
end

function vector.print(vec)
    print("x -->", vec.x, "y -->", vec.y)
end


enemypos = vector.new(70,30)
allypos = vector.new (20,50)
normallypos = vector.normalize(allypos)
leghtallypos = vector.lenght(allypos)
addpos = enemypos + allypos
sbubpos = allypos - enemypos
dotporductallyenemy = vector.dot(allypos,enemypos)
vector.print(addpos)


-- Termina tu código
io.read()
