
scorepowerup = 30
timepowerup= 5
speedpowerup = 2
--colorPowerup 
rcolor = 255
gcolor = 255
bcolor = 255
scoretobroncemedall = 20
scorecoin = 5



function setColor(_lives)
	if _lives == 1.5 then
		return 255, 0, 0
	elseif _lives == 1 then
		return 255, 165, 0
	elseif _lives == 0.5 then
		return 0, 255, 0
	elseif _lives == 0 then
		return 0, 0, 255
	end
	return 255, 255, 255
end