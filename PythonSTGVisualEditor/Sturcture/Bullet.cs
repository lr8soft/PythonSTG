using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
namespace PythonSTGVisualEditor.Sturcture
{
    [XmlRoot("Bullet")]
    public class Bullet : IPythonScript, ICloneable
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
        [XmlElement("posX")]
        public string posX { get; set; }
        [XmlElement("posY")]
        public string posY { get; set; }
        [XmlElement("velocity")]
        public string velocity { get; set; }
        [XmlElement("Acceleration")]
        public string Acceleration { get; set; }
        [XmlElement("angle")]
        public string angle { get; set; }
        [XmlElement("angleAcceleration")]
        public string angleAcceleration { get; set; }

        [XmlElement("aimToPlayer")]
        public bool aimToPlayer { get; set; }
        [XmlElement("reBound")]
        public string reBound { get; set; }
        [XmlElement("bulletColor")]
        public BulletColor bulletColor { get; set; }

        [XmlElement("bulletVarName")]
        public string bulletVarName { get; set; }
        [XmlElement("bulletClassName")]
        public string bulletClassName { get; set; }


        public string GetInitScript() {
            return string.Format(bulletInitScript, 
                bulletVarName, bulletClassName, posX.ToString(), posY.ToString(),
                reBound.ToString(), velocity.ToString(), bulletColor.ToString(), angle.ToString(), angleAcceleration.ToString(), 
                aimToPlayer ? "True" : "False");
        }

        public object Clone()
        {
            Bullet bullet = new Bullet();

            bullet.bulletVarName = bulletVarName;
            bullet.bulletClassName = bulletClassName;

            bullet.posX = posX;
            bullet.posY = posY;
            bullet.velocity = velocity;
            bullet.Acceleration = Acceleration;
            bullet.aimToPlayer = aimToPlayer;
            bullet.angle = angle;
            bullet.angleAcceleration = angleAcceleration;
            bullet.reBound = reBound;
            bullet.bulletColor = bulletColor;
            return bullet;
        }
    }
}
