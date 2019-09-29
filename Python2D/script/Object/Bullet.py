class CircleBullet:
    def __init__(self, position = [0.0,0.0,0.0],velocity = 0.2, angle = 0.0):
        self._pos = position
        self._velocity = velocity
        self._angle = angle
        self._imagePath = "assets/Item/bullet.png"
        self._divideInfo = [8,1,6,1]
        self._scaleSize = [0.08,0.08,0.08]

    def _cpp_getInitCoord(self):
        return tuple(self._pos)

    def _cpp_getGenerateInfo(self):
        return (self._velocity, self._angle)

    def _cpp_getInitRenderInfo(self):
        return (self._imagePath, tuple(self._divideInfo), tuple(self._scaleSize))





