from script.Object.XCItem import XCItem
class Player(XCItem):
    def __init__(self):
        super().__init__()
        self.lastkey = 0
        self.lastaction = -1
        self.lastTime = 0.0
        self.totalTime = 0.0


