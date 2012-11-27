-- Testea que #attrClip defina correctamente el área de clipping y esta sea respetada cuando se usa #drawRect
canvas:attrClip(100,100,200,200)
canvas:attrColor("red")
canvas:drawRect("fill",0,0,500,500)
canvas:flush()