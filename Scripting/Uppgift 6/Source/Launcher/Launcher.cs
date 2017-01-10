using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TBSGame_Launcher
{
    public partial class Launcher : Form
    {
        public Launcher()
        {
            InitializeComponent();
        }

        public const int WM_NCLBUTTONDOWN = 0xA1;
        public const int HTCAPTION = 0x2;
        [DllImport("User32.dll")]
        public static extern bool ReleaseCapture();
        [DllImport("User32.dll")]
        public static extern int SendMessage(IntPtr hWnd, int Msg, int wParam, int lParam);
        
        private void Form1_Load(object sender, EventArgs e)
        {
            exeDirectory = Path.Combine(Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location)/*, "Game"*/);
            exePath = Path.Combine(exeDirectory, "Application (LD, x64).exe");
            resourceDirectory = Path.Combine(exeDirectory/*, "Resources"*/);

            settingsDirectory = Path.Combine(System.Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData), "Sandcastle\\AI-Project\\Config");
            settingsPath = Path.Combine(settingsDirectory, "config.json");
            defaultSettingsPath = Path.Combine(resourceDirectory, "Assets\\Data\\defaultConfig.json");

            if (Directory.Exists(settingsDirectory) == false)
            {
                Directory.CreateDirectory(settingsDirectory);
            }

            DEVMODE vDevMode = new DEVMODE();
            int i = 0;
            List<Resolution> list = new List<Resolution>();
            while (EnumDisplaySettings(null, i, ref vDevMode))
            {
                Resolution resolution = new Resolution
                {
                    Width = vDevMode.dmPelsWidth,
                    Height = vDevMode.dmPelsHeight
                };
                
                float tar = (float)resolution.Width / (float)resolution.Height;
                float sn = 16f / 9f;

                float val = tar - sn;
                if (Math.Abs(val) < 0.1f)
                {
                    if (list.Contains(resolution) == false)
                    {
                        list.Add(resolution);
                    }
                }

                i++;
            }

            if (list.Count == 0)
            {
                list.Add(new Resolution
                {
                    Width = 1280,
                    Height = 720
                });
                list.Add(new Resolution
                {
                    Width = 1920,
                    Height = 1080
                });
            }

            foreach (var res in list.OrderBy(o => o.Width * o.Height))
            {
                comboBox1.Items.Add(res);
            }

            if (!File.Exists(settingsPath))
            {
                File.Copy(defaultSettingsPath, settingsPath);
            }

            JObject obj = JObject.Parse(File.ReadAllText(settingsPath), new JsonLoadSettings
            {
                CommentHandling = CommentHandling.Load,
                LineInfoHandling = LineInfoHandling.Load
            });
            
            checkBox1.Checked = obj["startInFullscreen"].Value<bool>();

            comboBox1.SelectedItem = new Resolution
            {
                Width = obj["resolution"][0].Value<int>(),
                Height = obj["resolution"][1].Value<int>()
            };

            if (comboBox1.SelectedItem == null)
            {
                comboBox1.SelectedIndex = comboBox1.Items.Count - 1;
            }

            button1.FlatStyle = FlatStyle.Flat;
            button1.FlatAppearance.BorderSize = 0;

            button2.FlatStyle = FlatStyle.Flat;
            button2.FlatAppearance.BorderSize = 0;
        }

        public struct Resolution
        {
            public int Width;
            public int Height;

            public override string ToString()
            {
                return string.Format("{0}x{1}", Width, Height);
            }
        }

        [DllImport("user32.dll")]
        public static extern bool EnumDisplaySettings(
              string deviceName, int modeNum, ref DEVMODE devMode);
        const int ENUM_CURRENT_SETTINGS = -1;

        const int ENUM_REGISTRY_SETTINGS = -2;
        private string settingsDirectory;
        private string exeDirectory;
        private string exePath;
        private string resourceDirectory;
        private string defaultSettingsPath;

        [StructLayout(LayoutKind.Sequential)]
        public struct DEVMODE
        {

            private const int CCHDEVICENAME = 0x20;
            private const int CCHFORMNAME = 0x20;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 0x20)]
            public string dmDeviceName;
            public short dmSpecVersion;
            public short dmDriverVersion;
            public short dmSize;
            public short dmDriverExtra;
            public int dmFields;
            public int dmPositionX;
            public int dmPositionY;
            public ScreenOrientation dmDisplayOrientation;
            public int dmDisplayFixedOutput;
            public short dmColor;
            public short dmDuplex;
            public short dmYResolution;
            public short dmTTOption;
            public short dmCollate;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 0x20)]
            public string dmFormName;
            public short dmLogPixels;
            public int dmBitsPerPel;
            public int dmPelsWidth;
            public int dmPelsHeight;
            public int dmDisplayFlags;
            public int dmDisplayFrequency;
            public int dmICMMethod;
            public int dmICMIntent;
            public int dmMediaType;
            public int dmDitherType;
            public int dmReserved1;
            public int dmReserved2;
            public int dmPanningWidth;
            public int dmPanningHeight;

        }

        private void button1_Click(object sender, EventArgs e)
        {
            JObject obj = JObject.Parse(File.ReadAllText(settingsPath), new JsonLoadSettings
            {
                CommentHandling = CommentHandling.Load,
                LineInfoHandling = LineInfoHandling.Load
            });

            obj["resolution"][0] = ((Resolution)comboBox1.SelectedItem).Width;
            obj["resolution"][1] = ((Resolution)comboBox1.SelectedItem).Height;
            obj["startInFullscreen"] = checkBox1.Checked;

            using (StreamWriter stream = new StreamWriter(settingsPath))
            using (JsonWriter writer = new JsonTextWriter(stream))
            {
                var serializer = JsonSerializer.Create();
                serializer.Formatting = Formatting.Indented;
                serializer.Serialize(writer, obj);
            }

            ProcessStartInfo info = new ProcessStartInfo();
            info.FileName = exePath;
            info.WorkingDirectory = resourceDirectory;
            Process.Start(info);

            Close();
        }

        private void pictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                ReleaseCapture();
                SendMessage(Handle, WM_NCLBUTTONDOWN, HTCAPTION, 0);
            }
        }

        public string settingsPath { get; set; }

        private void button2_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
