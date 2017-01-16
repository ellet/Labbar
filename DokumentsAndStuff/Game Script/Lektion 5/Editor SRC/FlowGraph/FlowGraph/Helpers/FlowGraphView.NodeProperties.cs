using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace FlowGraph
{
    public partial class FlowGraphView
    {
        private int myNextPosition;
        public void PropertiesOnNodeSelected(FlowGraphNode aNode)
        {
            myPropertiesNodeData.Controls.Clear();
            if (aNode == null)
            {
                return;
            }

            myNextPosition = 1;
            for (int i = 0; i < aNode.InputConnectors.Count; i++)
            {
                FillProperties(aNode.InputConnectors[i]);
            }
        }

        private void OnTextChanged(object sender, EventArgs e)
        {
            TextBox textbox = sender as TextBox;
            FlowGraphConnector connection = textbox.Tag as FlowGraphConnector;
            connection.myData = textbox.Text;
        }

        private bool CanChangeDataOnType(string aType)
        {
            if (aType.CompareTo("impulse") == 0)
            {
                return false;
            }
            else if (aType.CompareTo("pointer") == 0)
            {
                return false;
            }
            else if (aType.CompareTo("") == 0)
            {
                return false;
            }

            return true;
        }

        private void FillProperties(FlowGraphConnector aConnection)
        {
            string type = aConnection.VarType;


            int posX = myNextPosition * 25;

            Label label = new Label();
            label.Text = aConnection.Label;
            label.ForeColor = Color.White;
            label.Location = new Point(0, posX);
            //label.Width = label.Text.Count() * 9;
            label.Width = TextRenderer.MeasureText(label.Text, label.Font).Width;
            myPropertiesNodeData.Controls.Add(label);

            if (CanChangeDataOnType(type) == false)
            {
                myNextPosition += 1;
                return;
            }

            TextBox textBox = new TextBox();
            textBox.Width = 100;
            textBox.Location = new Point(label.Location.X + label.Width, posX);
            textBox.TextChanged += new System.EventHandler(this.OnTextChanged);
            textBox.Tag = aConnection;
            if (aConnection.HasLink())
            {
                textBox.BackColor = Color.IndianRed;
                textBox.Enabled = false;
            }
            else 
            if (aConnection.myData != null)
            {
                textBox.Text = aConnection.myData;
            }

            myPropertiesNodeData.Controls.Add(textBox);

            Label labelType = new Label();
            labelType.Text = "[" + type + "]";
            labelType.ForeColor = Color.White;
            labelType.Location = new Point(textBox.Location.X + textBox.Width, posX);
          //  labelType.Width = label.Text.Count() * 7;
            labelType.Width = TextRenderer.MeasureText(labelType.Text, labelType.Font).Width;
            myPropertiesNodeData.Controls.Add(labelType);


            if (aConnection.myCommandPath != null && aConnection.myCommandPath.myPath != string.Empty)
            {
                Button commandButton = new Button();
                commandButton.Location = new Point(labelType.Location.X + labelType.Width, posX);
                commandButton.Name = aConnection.myCommandPath.myName;
                commandButton.AutoSize = true;
                commandButton.TabIndex = 0;
                commandButton.Text = aConnection.myCommandPath.myName;
                commandButton.Tag = aConnection;
                commandButton.UseVisualStyleBackColor = true;

                commandButton.Click += new System.EventHandler(this.CommandButtonClick);
           
                myPropertiesNodeData.Controls.Add(commandButton);
            }

            myNextPosition += 1;
        }

        private void CommandButtonClick(object sender, EventArgs e)
        {
            Button senderButton = sender as Button;
            if (senderButton == null)
            {
                return;
            }

            FlowGraphConnector connector = senderButton.Tag as FlowGraphConnector;

            FlowGraphNodeDescriptor descriptor = connector.Node.GetDescriptor();
            StartFile(connector.myCommandPath.myPath, connector.myData, descriptor.FilePath);
        }

        private void StartFile(string aFile, string someData, string aPath)
        {
            string dirPath = System.IO.Path.GetDirectoryName(aPath);
            string fullPath = dirPath + "\\" + aFile;
            try 
            {
                System.Diagnostics.Process.Start(fullPath, someData);
            }
            catch 
            {
                MessageBox.Show(aFile + " could not start. Full path: " + fullPath, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
           


        }
    }
}
