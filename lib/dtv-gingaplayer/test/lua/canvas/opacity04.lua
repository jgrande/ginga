-- Testea que #attrOpacity no tenga ningún efecto sobre el canvas principal.
local opacity = 100
canvas:attrColor("red")
canvas:drawRect("fill",0,0,720,576)
canvas:attrOpacity(opacity)
canvas:flush()