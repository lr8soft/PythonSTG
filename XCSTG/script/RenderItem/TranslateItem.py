
class TranslateItem:
    def __init__(self, priority = 9):
        self.priority = priority;
    def __eq__(self, other):
        try:
            return self.priority == other.priority;
        except AttributeError:
            return NotImplemented
    def __lt__(self, other):
        try:
            return self.priority < other.priority;
        except AttributeError:
            return NotImplemented
