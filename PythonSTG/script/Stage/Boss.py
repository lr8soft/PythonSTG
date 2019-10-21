from .Task import Task, TaskUnit, Queue


class SpellCard:
    def __init__(self):
        self.spellCardName = "No Name"
        self.spellCardTime = 30.0
        self.spellCardHealthPoint = 50.0
        self.isSpellCard = False
        self.spellCardTask = Queue()

    def setSpellCardName(self,name):
        self.spellCardName = name

    def setIsSpellCard(self,isSpellCard = True):
        self.isSpellCard = isSpellCard

    def setSpellCardTime(self, time = 30.0):
        self.spellCardTime = time

    def setSpellCardHealthPoint(self, hp = 50.0):
        self.spellCardHealthPoint = hp

    def addTask(self, task):
        if isinstance(task, Task):
            self.spellCardTask.put(task)
        else:
            raise Exception("Insert invalid task.")

    def _cpp_getSpellCardInfo(self):
        return self.spellCardName,  self.isSpellCard, self.spellCardTime, self.spellCardHealthPoint

    def _cpp_getTaskSize(self):
        return self.spellCardTask.qsize()

    def _cpp_getTaskItem(self):
        return self.spellCardTask.get()


class Boss:
    def __init__(self):
        self.spellCardGroup = Queue()
        self.bossName = "TestBoss"
        self.bossImage = "assets/Boss/TestBoss.png"
        self.imageDivideInfo = [4, 3]
        self.bossStandBy = 3
        self.bossWalk = 2
        self.bossAttack = 1

    def AddSpellCard(self, spellcard):
        if isinstance(spellcard, SpellCard):
            self.spellCardTask.put(spellcard)
        else:
            raise Exception("Insert invalid spellcard.")

    def _cpp_getBossInfo(self):
        return self.bossName, self.bossImage, self.imageDivideInfo, self.bossStandBy, self.bossWalk, self.bossAttack

    def _cpp_getSpellCardSize(self):
        return self.spellCardGroup.qsize()

    def _cpp_getSpellCardItem(self):
        return self.spellCardGroup.get()
