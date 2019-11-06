from ..TaskEnemy import TaskEnemy, EnemyColor, DropItem


class FairyEnemy(TaskEnemy):
    def __init__(self, durationFrame=0, intervalFrame=0, waitFrame=0):
        super().__init__(durationFrame, intervalFrame, waitFrame)
        super()._setImagePath("assets/Enemy/fairy.png")
        super()._setZoomInfo([0.06, 0.06])
        super()._setDivideInfo(divideType=[12, 4], divideOffset=[0.0, 0.0])
        super()._setSpecialColumn(specialCol1=[1, 5], specialCol2=[6, 12])  # start - end (column)
        super()._setSelectImage(coord=[1, 4])
