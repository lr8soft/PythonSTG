using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
namespace PythonSTGVisualEditor.Sturcture
{
    [XmlRoot("Stage")]
    public class Stage
    {
        [XmlElement("stageVarName")]
        public string stageVarName { get; set; }
        [XmlElement("stageDisplayName")]
        public string stageDisplayName { get; set; }
        [XmlElement("stageBackground")]
        public string stageBackground { get; set; }
        [XmlElement("stageRank")]
        public string stageRank { get; set; }

        public Stage() {
            this.stageBackground = "river";
            this.stageRank = "Lunatic";
        }
    }
}
