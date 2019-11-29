using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
namespace PythonSTGVisualEditor.SpecialNode
{
    public class TaskNode : TreeNode
    {
        public Task storageTask { get; set;}
        public TaskNode(Task task) : base(){
            storageTask = task;
            updateNodeInfo();
        }

        public void updateNodeInfo()
        {
            Name = storageTask.taskVarName;
            if (storageTask.targetVarName.Count == 0)
            {
                Text = string.Format("[变量名称:{0} 持续帧数:{1} 间隔帧数:{2} 等待帧数:{3}]",
                storageTask.taskVarName, storageTask.taskDuration, storageTask.taskInterval, storageTask.taskWaitFrame);
            }
            else {
                Text = string.Format("[变量名称:{0} 持续帧数:{1} 间隔帧数:{2} 等待帧数:{3}",
           storageTask.taskVarName, storageTask.taskDuration, storageTask.taskInterval, storageTask.taskWaitFrame);
                Text += " 等待变量:";

                for(int i=0; i< storageTask.targetVarName.Count;i++) {
                    Text += storageTask.targetVarName[i];
                    if (i!= storageTask.targetVarName.Count-1) {
                        Text += ',';
                    }
                }
                Text +=']';
            }
        }

        public override string ToString()
        {
            return storageTask.ToString();
        }
    }
}
