from .Task import Task, TaskUnit, Queue
import uuid

class SpellCard:
    def __init__(self):
        self.spellCardName = "No Name"
        self.spellCardTime = 30.0
        self.spellCardHealthPoint = 50.0
        self.isSpellCard = False
        self.spellCardTask = Queue()
        self.bossMoveTo = [0.0, 0.6]

    def setSpellCardName(self,name):
        self.spellCardName = name

    def setIsSpellCard(self,isSpellCard = True):
        self.isSpellCard = isSpellCard

    def setSpellCardTime(self, time = 30.0):
        self.spellCardTime = time

    def setSpellCardHealthPoint(self, hp = 50.0):
        self.spellCardHealthPoint = hp

    def setBossMovePosition(self, pos = [0.0, 0.8]):
        self.bossMoveTo = pos;

    def addTask(self, task):
        if isinstance(task, Task):
            self.spellCardTask.put(task)
        else:
            raise Exception("Insert invalid task.")

    def _cpp_getSpellCardInfo(self):
        return self.spellCardName,  self.isSpellCard, self.spellCardTime, self.spellCardHealthPoint

    def _cpp_getBossMovePosition(self):
        return tuple(self.bossMoveTo)

    def _cpp_getTaskSize(self):
        return self.spellCardTask.qsize()

    def _cpp_getTaskItem(self):
        return self.spellCardTask.get()


class Boss:
    def __init__(self):
        self.spellCardGroup = Queue()
        self.bossName = "TestBoss "
        self.targetUuid = Queue()
        self.uuid = str(uuid.uuid1())
        self.waitFrame = 0


        self.bossImage = "assets/Boss/TestBoss.png"
        self.bossImageDivide = [4, 3]
        self.bossImageScale = [0.12, 0.16]
        self.bossStandBy = 3
        self.bossWalk = 2
        self.bossAttack = 1

    def AddSpellCard(self, spellcard):
        if isinstance(spellcard, SpellCard):
            self.spellCardGroup.put(spellcard)
        else:
            raise Exception("Insert invalid spellcard.")

    def AddTargetUuid(self, uuid):
        self.targetUuid.put(uuid)

    def SetBossWaitFrame(self, waitFrame):
        self.waitFrame = waitFrame

    def _cpp_getBossInfo(self):
        return self.bossName, self.uuid, self.waitFrame

    def _cpp_getImageInfo(self):
        return self.bossImage, tuple(self.bossImageDivide), tuple(self.bossImageScale), self.bossStandBy, self.bossWalk, self.bossAttack

    def _cpp_getSpellCardSize(self):
        return self.spellCardGroup.qsize()

    def _cpp_getSpellCardSingle(self):
        return self.spellCardGroup.get()

    def _cpp_getTargetUuidSize(self):
        return self.targetUuid.qsize()

    def _cpp_getTargetUuidSingle(self):
        return self.targetUuid.get()
