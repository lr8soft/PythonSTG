#返回类型 return type
#image (flexible or not flexible render), point sprite
#返回值范例 Return example
#return "image", c_bool(true), (renderX,renderY,renderZ), (ColorR,ColorG,ColorB,ColorA), (ScaleX,ScaleY,ScaleZ), pointer to 16 * c_float32
def RenderImage(dataPointer, Isflexible=False, renderPos=(0.0,0.0,0.0), renderColor=(0.0,0.0,0.0,1.0), scale=(1.0,1.0,1.0)):
    pass