from script.Object.TranslateItem  import TranslateItem
class RenderItem(TranslateItem):
    "The class of the render item. \
    translate is used by the cpp part."
    IsFlexible = False
    ImagePath = "assets/123.png"
    renderPos = [0.0, 0.0, 0.0]
    colorValue = [0.0, 0.0, 0.0, 1.0] #RGBA
    scaleValue = [1.0, 1.0, 1.0, 1.0]
    divideInfo = [3, 3, 0, 0]#column 3, row 3, selected the col 0 row 0 item (right-top is the beginning of the coordinate system)
    def translate(self):
        return "image", self.ImagePath, self.IsFlexible, tuple(self.renderPos), tuple(self.colorValue), \
               tuple(self.scaleValue),  tuple(self.divideInfo)


