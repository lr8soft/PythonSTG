using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PythonSTGVisualEditor
{
    public class FormatHelper
    {
        public static string getFormatScript(string info, int tabCount) {
            string targetScript = "";
            for (int head = 0, index = info.IndexOf("\r\n"); index != -1 && head != -1; index = info.IndexOf("\r\n", head))
            {
                targetScript += "       ";
                for (int i=0; i < tabCount; i++) {
                    targetScript += "   ";
                }
                targetScript += info.Substring(head, index - head) + "\r\n";
                head = index + 2;

            }
            return targetScript;
        }
    }
}
