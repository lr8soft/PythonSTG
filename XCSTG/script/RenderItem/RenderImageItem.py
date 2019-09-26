from script.RenderItem.TranslateItem  import TranslateItem
class RenderImageItem(TranslateItem):
    "The class of the render item. \
    translate is used by the cpp part."
    def __init__(self):
        self.IsFlexible = False
        self.ImagePath = "assets/123.png"
        self.renderPos = [0.0, 0.0, 0.0]
        self.colorValue = [0.0, 0.0, 0.0, 1.0] #RGBA
        self.scaleValue = [1.0, 1.0, 1.0]
        self.divideInfo = [0, 0, 0, 0]#column 3, row 3, selected the col 0 row 0 item (right-top is the beginning of the coordinate system)

    def translate(self):
        rType = "image"
        rpos = tuple(self.renderPos)
        cval = tuple(self.colorValue)
        sval = tuple(self.scaleValue)
        dinfo = tuple(self.divideInfo)
        return ( rType, self.ImagePath, self.IsFlexible, rpos, cval, sval,  dinfo)

