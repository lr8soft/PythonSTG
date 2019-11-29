using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Microsoft.VisualBasic;
using PythonSTGVisualEditor.Sturcture;

namespace PythonSTGVisualEditor.SpecialNode
{
    public class StageNode : TreeNode
    {
        public Stage storageStage { get; set; }
        private const string stageInitScript = "{0}= XCStage(\"{1}\")\r\n" +
            "{0}.setBackGround(StageBackGround.{2})\r\n" +
            "{0}.setStageRank(StageRank.{3})\r\n";
        private const string stageAddTaskScript = "{0}.addTask({1})\r\n";
        private const string stageSetMusicScript = "{0}.setBackGroundMusic({1})\r\n";

        private const string stageFuncDefine = "def setup{0}():\r\n";
        private const string stageFuncEndDefine = "return {0}\r\n";

        public StageNode(string varName, string displayName) : base()
        {
            storageStage = new Stage();
            setNodeInfo(varName, displayName);
            
            storageStage.stageVarName = varName;
            storageStage.stageDisplayName = displayName;
        }

        public void setNodeInfo(string varName, string displayName)
        {
            storageStage.stageVarName = varName;
            storageStage.stageDisplayName = displayName;

            Name = storageStage.stageVarName;
            Text = string.Format("[StageName:{0} Rank:{1}]", displayName, storageStage.stageRank);
        }

        public void setBackground(string info) {
            storageStage.stageBackground = info;
        }


        public string getFuncInitScript() {
            return string.Format(stageFuncDefine, storageStage.stageVarName);
        }

        public string getFuncEndInitScript() {
            return string.Format(stageFuncEndDefine, storageStage.stageVarName);
        }

        public string getInitScript() {
            string value = string.Format(stageInitScript,
                storageStage.stageVarName, storageStage.stageDisplayName, storageStage.stageBackground, storageStage.stageRank);
            return value;
        }

        public string getMusicInitScript(string musicPath)
        {
            string value = string.Format(stageSetMusicScript,
                storageStage.stageVarName, musicPath);
            return value;
        }

        public string getAddTaskScript(string taskVarName)
        {
            string value = string.Format(stageAddTaskScript, storageStage.stageVarName, taskVarName);
            return value;
        }

        public string getVarName() {
            return storageStage.stageVarName;
        }

        public string getDisplayName()
        {
            return storageStage.stageDisplayName;
        }

        public string getSetupFuncName() {
            return string.Format("setup{0}", storageStage.stageVarName);
        }
    }
}
