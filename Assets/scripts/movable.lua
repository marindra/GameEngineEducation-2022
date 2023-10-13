Update = function(deltaTime, speed, velocityX)
    if TestInput(0) then
        return velocityX - speed*deltaTime
    end
    if TestInput(1) then
        return velocityX + speed*deltaTime
    end
end