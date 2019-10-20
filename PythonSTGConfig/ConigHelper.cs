using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace PythonSTGConfig
{

    class ConfigHelper
    {
        private Dictionary<string, string> keyValueSet = null;
        public ConfigHelper()
        {
            keyValueSet = new Dictionary<string, string>();
            FileLoad();
        }
        public string getValue(string key) {
            string value = "";
            if (keyValueSet.ContainsKey(key)) {
                value = keyValueSet[key];
                Console.WriteLine(value);
            }
            return value;
        }
        public void setValue(string key, string value) {
            keyValueSet[key] = value;
        }

        public void FileLoad() {
            try
            {
                StreamReader sr = new StreamReader("pystg.cfg", Encoding.Default);
                string line, info = "";
                while ((line = sr.ReadLine()) != null)
                {
                    info += line;
                }
                sr.Close();

                if (info.Length > 0)
                {
                    bool isFirstTimeRun = false;
                    int strIndex = 0;
                    string head_temp = "", tail_temp = "";
                    for (int head = info.IndexOf('['), tail = info.IndexOf(']'); head != -1 && tail != -1; head = info.IndexOf('[', tail))
                    {
                        if (!isFirstTimeRun)
                        {
                            tail = info.IndexOf(']', head);
                        }

                        string temp_value = info.Substring(head + 1, tail - head - 1);
                        if (strIndex % 2 == 0)
                            head_temp = temp_value;
                        else
                        {
                            tail_temp = temp_value;
                            keyValueSet[head_temp] = tail_temp;
                            Console.WriteLine("key:" + head_temp + " value:" + tail_temp);
                        }
                        isFirstTimeRun = false;
                        strIndex++;
                    }
                }
            }
            catch (Exception expt) {
                FileStream fileStream = new FileStream("pystg.cfg", FileMode.Create);
                fileStream.Flush();
                fileStream.Close();
            }
  
        }

        public void FileSave() {
            FileStream fileStream = new FileStream("pystg.cfg", FileMode.Create);
            StreamWriter streamWriter = new StreamWriter(fileStream,Encoding.Default);
            for (int index = 0; index < keyValueSet.Count; index++) {
                var pair = keyValueSet.ElementAt(index);
                streamWriter.WriteLine('[' + pair.Key + "]=[" + pair.Value + "]");
                streamWriter.Flush();
            }
            streamWriter.Close();
            fileStream.Close();
        }
    }
}
