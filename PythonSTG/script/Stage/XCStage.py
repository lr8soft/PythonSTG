from queue import Queue
from enum import Enum
from .Task import Task
import uuid
from script.Stage.Boss import Boss


class StageBackGround(Enum):
    lake = 0
    magic_forest = 1
    river = 2


class StageRank(Enum):
    Easy = 1
    Normal = 2
    Hard = 3
    Lunatic = 4
    Extra = 5


class XCStage:
    def __init__(self, stageName="Stage 0 No name"):
        self.__stageName = stageName
        self.__stageTask = Queue()
        self.__stageBoss = Queue()
        self.__uuid = str(uuid.uuid1())
        self.__background = StageBackGround.lake
        self.__rank = StageRank.Normal
        self.__music = ""

    def addTask(self, task):
        if isinstance(task, Task):
            self.__stageTask.put(task)
        else:
            raise Exception("Insert invalid task.")

    def addBoss(self, boss):
        if isinstance(boss, Boss):
            self.__stageBoss.put(boss)
        else:
            raise Exception("Insert invalid task.")

    def setBackGround(self, background):
        self.__background = background

    def setBackGroundMusic(self, musicPath):
        self.__music = musicPath

    def setStageRank(self, rank = StageRank.Normal):
        self.__rank = rank

    def _cpp_getStageInfo(self):
        return self.__stageName, self.__rank.value, self.__background.value, self.__music

    def _cpp_getTaskSize(self):
        return self.__stageTask.qsize()

    def _cpp_getTaskItem(self):
        return self.__stageTask.get()

    def _cpp_getBossSize(self):
        return self.__stageBoss.qsize()

    def _cpp_getBossItem(self):
        return self.__stageBoss.get()

    def _cpp_getUuid(self):
        return self.__uuid
