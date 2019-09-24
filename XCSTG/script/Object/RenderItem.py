from script.Object.TranslateItem  import TranslateItem
import ctypes
class RenderItem(TranslateItem):
    "The class of the render item. \
    translate is used by the cpp part."
    IsFlexible = True
    ImagePath = "assets/123.png"
    renderPos = [0.5, -0.3, 1.0]
    colorValue = [0.0, 0.1, 0.2, 1.0] #RGBA
    scaleValue = [1.2, 1.3, 1.4]
    divideInfo = [3, 3, 1, 2]#column 3, row 3, selected the col 0 row 0 item (right-top is the beginning of the coordinate system)
    def translate(self):
        rpos = tuple(self.renderPos)
        cval = tuple(self.colorValue)
        sval = tuple(self.scaleValue)
        dinfo = tuple(self.divideInfo)
        return ( "image", self.ImagePath, self.IsFlexible, rpos, cval, sval,  dinfo)


