from script.RenderItem.TranslateItem  import TranslateItem
class RenderColorItem(TranslateItem):
    "The class of the render item. \
    translate is used by the cpp part."
    def __init__(self):
        super().__init__()
        self.renderPos = [0.0, 0.0, 0.0]
        self.colorValue = [0.0, 0.0, 0.0, 1.0] #RGBA
        self.renderSize = [1.0, 1.0, 1.0]
        self.isFlexible = False
    def translate(self):
        rType = "colorblock"
        rpos = tuple(self.renderPos)
        cval = tuple(self.colorValue)
        rsval = tuple(self.renderSize)
        return ( rType, "None", self.isFlexible, rpos, cval, rsval,  (0, 0, 0, 0))
