using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
namespace PythonSTGVisualEditor.Sturcture
{
    [XmlRoot("TaskUnit")]
    public class TaskUnit : ICloneable, IPythonScript
    {
        [XmlElement("unitVarName")]
        public string unitVarName { get; set; }
        [XmlElement("waitFrame")]
        public int waitFrame { get; set; }
        [XmlElement("repeatTime")]
        public int repeatTime { get; set; }

        private const string initPythonScript = "{0}=TaskUnit(waitFrame={1}, repeatTime={2})\r\n";
        private const string addBulletScript = "{0}.addBullet({1})\r\n";

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
