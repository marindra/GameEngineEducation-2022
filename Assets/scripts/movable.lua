function UpdateMoveXForControllable(deltaTime, speed, velocity)
	velX = velocity
	if input:TestInput(0) then
		velX = velX - speed *  deltaTime
	end
	if input:TestInput(1) then
		velX = velX + speed * deltaTime
	end
	return velX
end