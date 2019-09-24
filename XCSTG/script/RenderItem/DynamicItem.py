from abc import abstractmethod
class DynamicItem():
    @abstractmethod
    def init(self):
        pass

    @abstractmethod
    def render(self):
        pass