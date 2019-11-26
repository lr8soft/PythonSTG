using PythonSTGVisualEditor.Sturcture;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace PythonSTGVisualEditor.SpecialNode
{
    public class TaskUnitNode : TreeNode
    {
        public TaskUnit storageUnit { get; set; }
        public TaskUnitNode(TaskUnit unit) : base() {
            storageUnit = unit;
            updateNodeInfo();
        }

        public void updateNodeInfo() {
            Name = storageUnit.unitVarName;
            Text = string.Format("[变量名称:{0} 等待帧数:{1} 循环次数:{2}]",
                storageUnit.unitVarName, storageUnit.waitFrame, storageUnit.repeatTime);
        }
    }
}
