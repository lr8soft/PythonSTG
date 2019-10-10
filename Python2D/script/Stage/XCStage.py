from queue import Queue
from enum import Enum
from script.Stage.Task import Task
import uuid


class StageBackGround(Enum):
    lake = 0
    magic_forest = 1


class XCStage:
    def __init__(self, stageName="Stage 0 No name"):
        self.__stageName = stageName
        self.__stageTask = Queue()
        self.__uuid = str(uuid.uuid1())
        self.__background = StageBackGround.lake;

    def addTask(self, task):
        if isinstance(task, Task):
            self.__stageTask.put(task)
        else:
            raise Exception("Insert invalid task.")

    def setBackGround(self, background):
        self.__background = background

    def _cpp_getStageName(self):
        return self.__stageName

    def _cpp_getBackground(self):
        return self.__background.value

    def _cpp_getTaskSize(self):
        return self.__stageTask.qsize()

    def _cpp_getTaskItem(self):
        return self.__stageTask.get()

    def _cpp_getUuid(self):
        return self.__uuid
