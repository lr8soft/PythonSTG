from script.Object.TranslateItem  import TranslateItem
class RenderColorItem(TranslateItem):
    "The class of the render item. \
    translate is used by the cpp part."
    renderPos = [0.0, 0.0, 0.0]
    colorValue = [0.0, 0.0, 0.0, 1.0] #RGBA
    renderSize = [1.0, 1.0, 1.0]
    def translate(self):
        rType = "colorblock"
        rpos = tuple(self.renderPos)
        cval = tuple(self.colorValue)
        rsval = tuple(self.renderSize)
        return ( rType, "None", False, rpos, cval, rsval,  (0, 0, 0, 0))
