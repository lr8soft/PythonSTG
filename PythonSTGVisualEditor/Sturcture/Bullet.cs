using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PythonSTGVisualEditor.Sturcture
{
    public class Bullet : IPythonScript
    {
        public enum BulletColor {
            RED, PURPLE, BLUE, LIGHTBLUE, LIGHTGREEN, YELLOW, ORANGE, WHITE
        };

        private const string bulletInitScript = "{0}={1}()\r\n" +
            "{0}.setInitCoord([{2},{3},0.0])\r\n" +
            "{0}.setRebound({4})\r\n" +
            "{0}.setVelocity({5})\r\n" +
            "{0}.setBulletColor(BulletColor.{6})\r\n" +
            "{0}.setAngle({7})\r\n" +
            "{0}.setAngleAcceleration({8})\r\n" +
            "{0}.setAimToPlayer({9})\r\n";

        public float posX { get; set; }
        public float posY { get; set; }
        public float velocity { get; set; }
        public float Acceleration { get; set; }
        public float angle { get; set; }
        public float angleAcceleration { get; set; }

        public bool aimToPlayer { get; set; }
        public int reBound { get; set; }
        public BulletColor bulletColor { get; set; }

        private string bulletVarName, bulletClassName;

        public Bullet(string varName, string className) {
            bulletVarName = varName;
            bulletClassName = className;
        }

        public string getVarName() {
            return bulletVarName;
        }

        public string getClassName()
        {
            return bulletClassName;
        }

        public string GetInitScript() {
            return string.Format(bulletInitScript, 
                bulletVarName, bulletClassName, posX.ToString(), posY.ToString(),
                reBound.ToString(), velocity.ToString(), bulletColor.ToString(), angle.ToString(), angleAcceleration.ToString(), 
                aimToPlayer ? "True" : "False");
        }
    }
}
