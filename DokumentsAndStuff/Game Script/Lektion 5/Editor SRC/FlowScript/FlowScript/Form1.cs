using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

using FlowGraph.Enums;
using FlowGraph.EventArguments;
using FlowGraph.Exceptions;
using FlowGraph;


namespace FlowScript
{
    public partial class Form1 : Form
    {
        public string myNodePath;
        public Form1()
        {
           
            InitializeComponent();

            try
            {
                string readText = File.ReadAllText(Application.StartupPath + "\\" + "NodeDir.txt");
                myNodePath = readText;
                myNodeMenu.Items.Clear();
                TextBox textBox = new TextBox();
               // myNodeMenu.Items.Add(textBox);
                LoadScripts();
            }
            catch { }

        }


        private void LoadScripts()
        {
            string theExe = System.Reflection.Assembly.GetEntryAssembly().Location;
            theExe = Path.GetDirectoryName(theExe);
            string[] filePaths = Directory.GetFiles(myNodePath);
            foreach (string fileName in filePaths)
            {
                ProcessFile(fileName);
            }

            AddToContextMenu();
                
        }

        private void AddToContextMenu()
        {
            for (int i = 0; i < myFlowGraph.Model.myNodesTypes.Count(); i++)
            {
                ToolStripMenuItem item = new ToolStripMenuItem();
                item.Tag = myFlowGraph.Model.myNodesTypes[i];
                item.Text = myFlowGraph.Model.myNodesTypes[i].myName;
                item.MouseDown += new MouseEventHandler(nodeMeny_Item_MouseDown);
                myNodeMenu.Items.Add(item);
                
            }
            
        }

        private void ProcessFile(string aFile)
        {
            string[] lines = System.IO.File.ReadAllLines(aFile);

            const string firstLineBox = "--Begin_Box--";
            if (lines[0].CompareTo(firstLineBox) == 0)
            {
                ParseBox(lines, aFile);
            }

        }

        private void ParseBox(string[] someLines, string aPath)
        {
            CNodeType node = new CNodeType();

            node.myPath = aPath;
            const string input = "[InputPin]";
            const string output = "[OutputPin]";
            const string nodeData = "[NodeData]";
            const string end = "End_Box";
            foreach (string line in someLines)
            {
               if (line.Contains(input) == true)
               {
                   CreateInput(line, node);
               }
               else if (line.Contains(output) == true)
               {
                   CreateOutput(line, node);
               }
               else if (line.Contains(end) == true)
               {
                   break;
               }
               else if (line.Contains(nodeData) == true)
               {
                   string nodeName = GetValue("name", line);
                   node.myName = nodeName;
               }
               else if (line.Contains("--") == false)
               { 
                   // Warn!
                   break;
               }
            }
            myFlowGraph.Model.myNodesTypes.Add(node);
        }

        private void CreateInput(string aInput, CNodeType aNode)
        {
            string name = GetValue("name", aInput);
            string varType = GetValue("VarType", aInput);
            FlowGraph.CommandPath commandPath = GetCommandName(aInput);

            CPin pin = new CPin();
            pin.isInput = true;
            pin.myName = name;
            pin.myType = varType;
            pin.myCommandPath = commandPath;
            

            aNode.myPins.Add(pin);
        }

        private void CreateOutput(string aInput, CNodeType aNode)
        {
            string name = GetValue("name", aInput);
            string varType = GetValue("VarType", aInput);
            FlowGraph.CommandPath commandPath = GetCommandName(aInput);

            CPin pin = new CPin();
            pin.isInput = false;
            pin.myName = name;
            pin.myType = varType;
            pin.myCommandPath = commandPath;

            aNode.myPins.Add(pin);
        }

        private FlowGraph.CommandPath GetCommandName(string aInput)
        {
            string commandString = "command";
            string theInput = aInput.ToLower();

            int nameBracketStartInput = theInput.IndexOf(commandString);
            if (nameBracketStartInput == -1)
            {
                return null;
            }
            int nameInput = theInput.IndexOf(commandString) + commandString.Count() + 1;
            int nameInputEnd = theInput.IndexOf("]", nameInput);
            string theCommand = theInput.Substring(nameInput, nameInputEnd - nameInput);

            string nameString = "name:";
            string pathString = "path:";


            int nameIndexStart = theCommand.IndexOf(nameString);
            int nameIndexEnd = theCommand.IndexOf(",");
            string theName = theCommand.Substring(nameIndexStart + nameString.Count(), nameIndexEnd - nameString.Count());

            int pathIndexStart = theCommand.IndexOf(pathString);
            int pathIndexEnd = theCommand.IndexOf(pathString) + pathString.Count();
            string thePath = theCommand.Substring(pathIndexStart + pathString.Count(), theCommand.Count() - pathIndexEnd);

            FlowGraph.CommandPath commandPath = new CommandPath(thePath, theName);
            return commandPath;
        }

        private string GetValue(string aValue, string aInput)
        {
            string theValue = aValue.ToLower();
            string name = theValue;

            string theInput = aInput.ToLower();

            int nameBracketStartInput = theInput.IndexOf(name);
            int nameInput = theInput.IndexOf(name) + name.Count()+1;
            int nameInputEnd = theInput.IndexOf("]", nameInput);
            string theName = theInput.Substring(nameInput, nameInputEnd - nameInput);
            return theName;
        }


        void myFlowGraph_RightClick(object sender, MouseEventArgs e)
        {
            if (e.Button != MouseButtons.Right)
            {
                return;
            }

            myNodeMenu.Show(Cursor.Position);


            return;
        }

        void nodeMeny_Item_MouseDown(object sender, MouseEventArgs e)
        {
            ToolStripMenuItem item = sender as ToolStripMenuItem;
            CNodeType node = item.Tag as CNodeType;

            FlowGraphNodeDescriptor desc = new FlowGraphNodeDescriptor();
            desc.Title = node.myName;
            desc.FilePath = node.myPath;

            for (int i = 0; i < node.myPins.Count(); i++ )
            {
                CPin thePin = node.myPins[i];
                desc.AddPin(thePin.isInput, thePin.myName, thePin.myType, thePin.myCommandPath);
            }

            Point mousePos = myFlowGraph.PointToClient(Cursor.Position);


            int scrollX = myFlowGraph.Model.ModelX;
            int scrollY = myFlowGraph.Model.ModelY;

            int winSizeX = myFlowGraph.Width;
            int winSizeY = myFlowGraph.Height;

            int addPosX = (mousePos.X - (winSizeX / 2)) - scrollX;
            int addPosY = (mousePos.Y - (winSizeY / 2)) - scrollY;

            desc.X = addPosX;
            desc.Y = addPosY;

            myFlowGraph.AddNewNode(desc);

        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog1 = new SaveFileDialog();
            saveFileDialog1.Filter = "Xml file|*.xml";
            saveFileDialog1.Title = "Save";
            saveFileDialog1.ShowDialog();
            if (saveFileDialog1.FileName != "")
            {
                myFlowGraph.SaveGraph(saveFileDialog1.FileName);
            }

               
        }


        private void loadToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                myFlowGraph.LoadGraph(openFileDialog.FileName);
            }
            
        }

        private void mySetNodePath_Click(object sender, EventArgs e)
        {
            var dialog = new System.Windows.Forms.FolderBrowserDialog();
            dialog.SelectedPath = Application.StartupPath; 
            System.Windows.Forms.DialogResult result = dialog.ShowDialog();
            if (result == System.Windows.Forms.DialogResult.OK)
            {
                myNodePath = dialog.SelectedPath;
                myNodeMenu.Items.Clear();
                LoadScripts();

                System.IO.File.WriteAllText(Application.StartupPath + "\\" + "NodeDir.txt", myNodePath);
            }
           
        }

        private void toolStripTextBox1_Click(object sender, EventArgs e)
        {

        }

        private void myAbout_Click(object sender, EventArgs e)
        {

        }


    }
}
