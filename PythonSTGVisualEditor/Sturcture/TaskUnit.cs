using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PythonSTGVisualEditor.Sturcture
{
    public class TaskUnit:ICloneable
    {
        public string unitVarName { get; set; }

        public int waitFrame { get; set; }
        public int repeatTime { get; set; }

        private const string initPythonScript = "{0}=TaskUnit(waitFrame={1}, repeatTime={2})\r\n";
        private const string addBulletScript = "{0}.addBullet({1})";

        public string GetInitScript()
        {
            return string.Format(initPythonScript, unitVarName, waitFrame, repeatTime);
        }

        public string GetAddBulletScript(string bulletVarName) {
            return string.Format(addBulletScript, unitVarName, bulletVarName);
        }

        public object Clone()
        {
            TaskUnit taskUnit = new TaskUnit();
            taskUnit.unitVarName = unitVarName;
            taskUnit.waitFrame = waitFrame;
            taskUnit.repeatTime = repeatTime;

            return taskUnit;
        }
    }
}
