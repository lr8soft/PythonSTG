using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace PythonSTGVisualEditor.SpecialNode
{
    public class TaskNode : TreeNode
    {
        private Task storageTask;
        public TaskNode(Task task) : base(){
            storageTask = task;
            updateNodeInfo();
        }

        public void updateNodeInfo()
        {
            Name = storageTask.taskVarName;
            Text = string.Format("[taskVarName:{0} 持续帧数:{1} 间隔帧数:{2} 等待帧数:{3}]", 
                storageTask.taskVarName, storageTask.taskDuration, storageTask.taskInterval, storageTask.taskWaitFrame);
        }

        public Task GetTask() {
            return storageTask;
        }

        public override string ToString()
        {
            return storageTask.ToString();
        }
    }
}
