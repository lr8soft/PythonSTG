

class ImageHelper:
    def __init__(self):
        self.imagePath = "assets/Item/particle.png"#default image

        self.imageSwapSpeed = 0.1
        self.imageZoomInfo = [0.05, 0.05]#zoom image as [x, y]
        self.imageDivideInfo = [1, 1] #divide as 1 colunm 1 row
        self.imageDivideOffset = [0.0, 0.0] #start divide from [x, y]

        self.imageSelectSubImage = [1, 1]#current selected

        self.imageSpecialColumn1 = [1, 1]#read image from x column to y column
        self.imageSpecialColumn2 = [1, 1]
        self.imageSpecialColumn3 = [1, 1]

        self.imageSpecialRow1 = 1 #indicate the special row 1
        self.imageSpecialRow2 = 1
        self.imageSpecialRow3 = 1

    def _setImagePath(self, path):
        self.imagePath = path

    def _setImageSwapSpeed(self, speed):
        self.imageSwapSpeed = speed

    def _setZoomInfo(self, zoom = [0.05, 0.05]):
        self.imageZoomInfo = zoom

    def _setSelectImage(self, coord = [1, 1]):
        self.imageSelectSubImage = coord

    def _setDivideInfo(self, divideType = [1, 1], divideOffset = [0.0, 0.0]):
        self.imageDivideInfo = divideType
        self.imageDivideOffset = divideOffset

    def _setSpecialColumn(self, specialCol1=[1, 1], specialCol2=[1, 1], specialCol3=[1, 1]):
        self.imageSpecialColumn1 = specialCol1
        self.imageSpecialColumn2 = specialCol2
        self.imageSpecialColumn3 = specialCol3

    def _setSpecialRow(self, specialRow1 = 1,specialRow2 = 1,specialRow3 = 1):
        self.imageSpecialRow1 = specialRow1
        self.imageSpecialRow2 = specialRow2
        self.imageSpecialRow3 = specialRow3

    def _getSelectImage(self):
        return self.imageSelectSubImage

    def _cpp_getImageInfo(self):
        return self.imagePath, self.imageSwapSpeed, tuple(self.imageSelectSubImage), \
               tuple(self.imageZoomInfo), tuple(self.imageDivideInfo), tuple(self.imageDivideOffset), \
               tuple(self.imageSpecialColumn1),  tuple(self.imageSpecialColumn2),  tuple(self.imageSpecialColumn3), \
               (self.imageSpecialRow1, self.imageSpecialRow2, self.imageSpecialRow3)