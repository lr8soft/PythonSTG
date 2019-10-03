from queue import Queue
from script.Stage.Task import Task
import uuid
class XCStage:
    def __init__(self, stageName = "Stage 0 No name"):
        self.__stageName = stageName
        self.__stageTask = Queue()
        self.__uuid = str(uuid.uuid1())

    def addTask(self, task):
        if isinstance(task, Task):
            self.__stageTask.put(task)
        else:
            raise Exception("Insert invalid task.")

    def _cpp_getStageName(self):
        return self.__stageName

    def _cpp_getTaskSize(self):
        return self.__stageTask.qsize()

    def _cpp_getTaskItem(self):
        return self.__stageTask.get()

    def _cpp_getUuid(self):
        return self.__uuid

