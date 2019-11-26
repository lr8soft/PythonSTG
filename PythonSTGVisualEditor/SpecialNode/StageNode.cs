using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Microsoft.VisualBasic;
namespace PythonSTGVisualEditor.SpecialNode
{
    public class StageNode : TreeNode
    {
        private string stageVarName, stageDisplayName, stageBackground="river", stageRank= "Lunatic";
        private const string stageInitScript = "{0}= XCStage(\"{1}\")\r\n" +
            "{0}.setBackGround(StageBackGround.{2})\r\n" +
            "{0}.setStageRank(StageRank.{3})\r\n";
        private const string stageAddTaskScript = "{0}.addTask({1})\r\n";
        private const string stageSetMusicScript = "{0}.setBackGroundMusic({1})\r\n";
        public StageNode(string varName, string displayName) : base()
        {
            setNodeInfo(varName, displayName);
        }

        public void setNodeInfo(string varName, string displayName)
        {
            stageVarName = varName;
            stageDisplayName = displayName;

            Name = stageVarName;
            Text = string.Format("[StageName:{0} Rank:{1}]", displayName, stageRank);
        }

        public void setBackground(string info) {
            stageBackground = info;
        }

        public string getInitScript() {
            string value = string.Format(stageInitScript,
                stageVarName, stageDisplayName,  stageBackground, stageRank);
            return value;
        }

        public string getMusicInitScript(string musicPath)
        {
            string value = string.Format(stageSetMusicScript,
                stageVarName, musicPath);
            return value;
        }

        public string getAddTaskScript(string taskVarName)
        {
            string value = string.Format(stageAddTaskScript, stageVarName, taskVarName);
            return value;
        }

        public string getVarName() {
            return stageVarName;
        }

        public string getDisplayName()
        {
            return stageDisplayName;
        }
    }
}
