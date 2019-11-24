using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PythonSTGVisualEditor
{
    public class Task
    {
        public string taskVarName { get; set; }
        public int taskDuration { get; set; }
        public int taskInterval { get; set; }
        public int taskWaitFrame { get; set; }
        public List<string> targetVarName = new List<string>();

        public override string ToString()
        {
            string info = "varName:{0} duration:{1} interval:{2} waitFrame:{3} ";
            string str = string.Format(info, taskVarName, taskDuration, taskInterval, taskWaitFrame);
            return str;
        }
    }
}
