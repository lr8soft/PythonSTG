from ..Helper.ImageHelper import ImageHelper
import uuid


class Player(ImageHelper):
    def __init__(self, frameName="Hakurei Reimu"):
        super().__init__()
        super()._setImagePath("assets/Item/player.png")
        super()._setZoomInfo([0.06, 0.08])
        super()._setDivideInfo(divideType=[8, 3], divideOffset=[0.0, 0.0])
        super()._setSpecialRow(specialRow1=3, specialRow2=1, specialRow3=2)

        self._uuid = str(uuid.uuid1())
        self._playerFrameName = frameName

        self._moveSpeed = 1.45
        self._basePower = 1.0

    def setPlayerImage(self, imagePath, imageColsAndRows=[8, 3], scaleSize=[0.06, 0.08], standByRow=1, turnLeftRow=2, turnRightRow=3):
        super()._setImagePath(imagePath)
        super()._setDivideInfo(divideType=imageColsAndRows, divideOffset=[0.0, 0.0])
        super()._setZoomInfo(scaleSize)
        super()._setSpecialRow(specialRow1=standByRow, specialRow2=turnLeftRow, specialRow3=turnRightRow)

    def setPlayerData(self, moveSpeed=1.45, imageSwapInterval=0.08, basePower=1.0):
        self._moveSpeed = moveSpeed
        self._imageSwapInterval = imageSwapInterval
        self._basePower = basePower

    def _cpp_getPlayerData(self):
        return (self._playerFrameName, self._moveSpeed, self._basePower)

    def _cpp_getUUID(self):
        return self._uuid
