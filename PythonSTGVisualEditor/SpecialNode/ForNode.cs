using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace PythonSTGVisualEditor.SpecialNode
{
    public class ForNode : TreeNode
    {
        private static long forStructTime = 0;

        private const string initScript = "for i in range(0, {0}):\r\n";
        public int repeatTime { get; set; }
        public ForNode(int time) {
            repeatTime = time;
            updateNodeInfo();
            forStructTime++;
        }

        public void updateNodeInfo() {
            Name = "forStruct" + forStructTime;
            Text = string.Format("[循环运行{0}次，自增变量名i]", repeatTime);
        }

        public string getInitScript() {
            return string.Format(initScript, repeatTime);
        }
    }
}
