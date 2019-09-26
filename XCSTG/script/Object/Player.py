from script.Object.XCItem import XCItem
import multiprocessing
class Player(XCItem):
    def __init__(self):
        super().__init__()
        # self.__playerProcessing = multiprocessing.Process(self.playerProcessCallback)
        # self.__playerProcessing.daemon = True
        # self.__playerProcessing.start()
        self.lastkey = 0
        self.lastaction = -1
        self.lastTime = 0.0
        self.totalTime = 0.0

    def keyCheckCallBack(self, key, action):
        pos = super().getPos()
        if 262 == key:
            super().setPos(pos[0]+0.04, pos[1],pos[2])
        elif 263 == key:
            super().setPos(pos[0]-0.04, pos[1],pos[2])
        elif 265 == key:
            super().setPos(pos[0], pos[1]+0.04,pos[2])
        elif 264 == key:
            super().setPos(pos[0], pos[1]-0.04,pos[2])

    def playerProcessCallback(self):
        self.totalTime += 1
        # if  self.totalTime - self.lastTime > 60:
        #     info = super().__divideInfo
        #     if info[2] < 8:
        #         info[2] += 1
        #     else:
        #         info[2] = 0
        #     self.lastTime = self.totalTime

