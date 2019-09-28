from script.Object.XCItem import XCItem
class Player(XCItem):
    def __init__(self, frameName = "Satsuki Rin"):
        super().__init__()
        self._divideInfo = [8, 3]
        self._isFlexible = True
        self._playerFrameName = frameName
        self._playerStandByRow = 3
        self._playerTurnLeftRow = 1
        self._playerTurnRightRow = 2

        self._moveSpeed = 1.45
        self._imageSwapInterval = 0.08
        self._basePower = 1.0

        self._scaleSize = [0.06,0.08, 1.0] #3:4 img


    def setPlayerImage(self, imagePath, imageColsAndRows = [8, 3], scaleSize = [0.06,0.08, 1.0], standByRow = 1, turnLeftRow = 2, turnRightRow = 3):
        super().setImage(imagePath,imageColsAndRows,scaleSize,True)
        self._playerStandByRow = standByRow
        self._playerTurnLeftRow = turnLeftRow
        self._playerTurnRightRow = turnRightRow

    def setPlayerData(self, moveSpeed = 1.45, imageSwapInterval=0.08, basePower = 1.0):
        self._moveSpeed = moveSpeed
        self._imageSwapInterval = imageSwapInterval
        self._basePower = basePower

    #for cpp recall
    def _cpp_getInitRenderInfo(self):
        return (self._imagePath, tuple(self._divideInfo),tuple(self._scaleSize),
                (self._playerStandByRow, self._playerTurnLeftRow, self._playerTurnRightRow))

    def _cpp_getPlayerData(self):
        return (self._playerFrameName, self._moveSpeed, self._imageSwapInterval, self._basePower)





