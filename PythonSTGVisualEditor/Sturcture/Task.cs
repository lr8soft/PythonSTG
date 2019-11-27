using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PythonSTGVisualEditor
{
    public class Task : ICloneable, IPythonScript
    {
        public string taskVarName { get; set; }
        public int taskDuration { get; set; }
        public int taskInterval { get; set; }
        public int taskWaitFrame { get; set; }
        public List<string> targetVarName = new List<string>();

        private const string initPythonScript = "{0}=Task(duration={1}, intervalFrame={2}, waitFrame={3})\r\n";
        private const string initDependScript = "{0}.addTargetUuid({1}.getUuid())\r\n";
        private const string addUnitScript = "{0}.addUnit({1})\r\n";

        public override string ToString()
        {
            string info = "varName:{0} duration:{1} interval:{2} waitFrame:{3} ";
            string str = string.Format(info, taskVarName, taskDuration, taskInterval, taskWaitFrame);
            return str;
        }

        public object Clone()
        {
            Task task = new Task();
            task.taskVarName = taskVarName;
            task.taskDuration = taskDuration;
            task.taskInterval = taskInterval;
            task.taskWaitFrame = taskWaitFrame;
            task.targetVarName.AddRange(targetVarName);
            return task;
        }

        public string GetInitScript() {
            string value = string.Format(initPythonScript, taskVarName, taskDuration, taskInterval, taskWaitFrame);
            if (targetVarName.Count > 0) {
                foreach (string varName in targetVarName) {
                    value += string.Format(initDependScript, taskVarName, varName);
                }
            }
            return value;
        }

        public string GetAddUnitScript(string unitVarName) {
            return string.Format(addUnitScript, taskVarName, unitVarName);
        }
    }
}
