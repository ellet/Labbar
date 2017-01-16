using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml;
using System.IO;

namespace FlowGraph
{
    public partial class FlowGraphView
    {
        public void SaveGraph(string aToPath)
        {
            var settings = new XmlWriterSettings();
            settings.OmitXmlDeclaration = true;
            settings.Indent = true;
            settings.NewLineOnAttributes = true;

            XmlWriter writer = XmlWriter.Create(aToPath, settings);
            writer.WriteStartDocument();
            writer.WriteStartElement("NodeTree");

            List<FlowGraphNode> nodes = GetAllNodes();
            foreach (FlowGraphNode node in nodes)
            {
                SaveNode(node, writer);
            }

            writer.WriteEndElement();
            writer.WriteEndDocument();
            writer.Close();
        }

        private void SaveNode(FlowGraphNode aNode, XmlWriter aWriter)
        {
            FlowGraphNodeDescriptor descriptor = aNode.GetDescriptor();

            aWriter.WriteStartElement("Node");

            aWriter.WriteElementString("Name", descriptor.Title);

            aWriter.WriteElementString("UID", aNode.myGuid.ToString());

            aWriter.WriteElementString("PosX", aNode.X.ToString());
            aWriter.WriteElementString("PosY", aNode.Y.ToString());

            string filePath = Path.GetFileName(descriptor.FilePath);
            aWriter.WriteElementString("FilePath", filePath);

            aWriter.WriteStartElement("Connections");
            SaveConnections(aNode, aWriter);
            aWriter.WriteEndElement();

            aWriter.WriteEndElement();

        }

        private void SaveConnections(FlowGraphNode aNode, XmlWriter aWriter)
        {
            for (int i = 0; i < aNode.InputConnectors.Count; i++)
            {
                FlowGraphConnector connector = aNode.InputConnectors[i];
                AddConnector(aNode, aWriter, connector);
            }
            for (int i = 0; i < aNode.OutputConnectors.Count; i++)
            {
                FlowGraphConnector connector = aNode.OutputConnectors[i];
                AddConnector(aNode, aWriter, connector);
            }

        }

        private void AddConnector(FlowGraphNode aNode, XmlWriter aWriter, FlowGraphConnector connector)
        {
            aWriter.WriteStartElement("Connection");

            aWriter.WriteElementString("Index", connector.Index.ToString());
            aWriter.WriteElementString("VarType", connector.VarType);
            aWriter.WriteElementString("Type", connector.Type.ToString());
            aWriter.WriteElementString("Name", connector.Label);
            if (connector.myLinks != null && connector.myLinks.Count > 0)
            {
                foreach (FlowGraphLink link in connector.myLinks)
                {
                    FlowGraphConnector leftConnector = link.LeftConnector;
                    FlowGraphConnector rightConnector = link.RightConnector;
                    aWriter.WriteStartElement("PinConnection");
                    if (leftConnector != null && leftConnector.Node != null && leftConnector.Node != aNode)
                    {
                        aWriter.WriteElementString("ConnectedTo", leftConnector.Node.myGuid.ToString());
                        aWriter.WriteElementString("PinIndex", leftConnector.Index.ToString());
                    }
                    if (rightConnector != null && rightConnector.Node != null && rightConnector.Node != aNode)
                    {
                        aWriter.WriteElementString("ConnectedTo", rightConnector.Node.myGuid.ToString());
                        aWriter.WriteElementString("PinIndex", rightConnector.Index.ToString());
                    }
                    aWriter.WriteEndElement();
                }

            }
            else
            {
                if (connector.myData != null)
                {
                    aWriter.WriteElementString("PinData", connector.myData.ToString());
                }
            }
            aWriter.WriteEndElement();
        }


        // LOADING
        /////////////////////////////////////////////////////////////////
        public void LoadGraph(string aToPath)
        {
            Model.Nodes.Clear();
            Model.Links.Clear();


            XmlDocument xdXml = new XmlDocument();
            xdXml.Load(aToPath);

            //Make a nodelist
            XmlNodeList xnNodes = xdXml.SelectNodes("/NodeTree/Node");

            //Walk through the list
            foreach (XmlNode node in xnNodes)
            {
                LoadNode(node);
            }

            // Resolve connections
            foreach (XmlNode node in xnNodes)
            {
                LoadNodeConnections(node);
            }

            //Clean up
            xdXml = null;
            xnNodes = null;
        }

        private void LoadNodeConnections(XmlNode aNode)
        {
            XmlNodeList childNodes = aNode.ChildNodes;
            long uid = 0;
            foreach (XmlNode child in childNodes)
            {
                switch (child.Name)
                {
                    case "UID":
                        uid = long.Parse(child.InnerText);
                        break;
                    case "Connections":
                        LoadNodeConnection(child, uid);
                        break;
                }
            }
        }

        private void LoadNodeConnection(XmlNode aNode, long aUID)
        {
            XmlNodeList childNodes = aNode.ChildNodes;
            
            foreach (XmlNode child in childNodes)
            {
                switch (child.Name)
                {

                    case "Connection":
                        LoadNodePinConnections(child, aUID);
                        break;
                }
            }
        }

        private void LoadNodePinConnections(XmlNode aNode, long aUID)
        {
            XmlNodeList childNodes = aNode.ChildNodes;
            int pinIndex = -1;
            string pinData = null;
            foreach (XmlNode child in childNodes)
            {
                switch (child.Name)
                {
                    case "Index":
                        pinIndex = int.Parse(child.InnerText);
                        break;
                    case "PinConnection":
                        LoadNodePinConnection(child, aUID, pinIndex);
                        break;
                    case "PinData":
                        FlowGraphNode theNode = Model.GetNodeFromUID(aUID);
                        if (theNode == null)
                        {
                            return;
                        }
                        FlowGraphConnector firstConnector = GetConnectorWithIndex(theNode, pinIndex);
                        firstConnector.myData = child.InnerText;
 
                        break;
                }
            }

        }

        private void LoadNodePinConnection(XmlNode aNode, long aUID, int aPinIndex)
        {
            XmlNodeList childNodes = aNode.ChildNodes;
            long connectedToUID = -1;
            int pinIndex = -1;
           
            foreach (XmlNode child in childNodes)
            {
                switch (child.Name)
                {
                    case "ConnectedTo":
                        connectedToUID = long.Parse(child.InnerText);
                        break;
                    case "PinIndex":
                        pinIndex = int.Parse(child.InnerText);
                        break;
                }
            }

             //aWriter.WriteElementString("PinData", connector.myData.ToString());

            if (connectedToUID != -1 && pinIndex != -1)
            {
                ConnectNodes(aUID, connectedToUID, aPinIndex, pinIndex );
            }
        }

        private void ConnectNodes(long aNodeUid, long aSecondNodeUID, int aFirstPinIndex, int aSecondPinIndex)
        {
            FlowGraphNode firstNode = Model.GetNodeFromUID(aNodeUid);
            FlowGraphNode secondNode = Model.GetNodeFromUID(aSecondNodeUID);
            if (firstNode == null || secondNode == null)
            {
                return;
            }
            FlowGraphConnector firstConnector = GetConnectorWithIndex(firstNode, aFirstPinIndex);
            FlowGraphConnector secondConnector = GetConnectorWithIndex(secondNode, aSecondPinIndex); // secondNode.InputConnectors[aSecondPinIndex];

            if (firstConnector == null || secondConnector == null)
            {
                return;
            }
            AddLink(firstConnector, secondConnector);
            
        }

        FlowGraphConnector GetConnectorWithIndex(FlowGraphNode aNode ,int aIndex)
        {
            foreach (FlowGraphConnector flowConnector in aNode.InputConnectors)
            {
                if (flowConnector.Index == aIndex)
                {
                    return flowConnector;  
                }
            }
            foreach (FlowGraphConnector flowConnector in aNode.OutputConnectors)
            {
                if (flowConnector.Index == aIndex)
                {
                    return flowConnector;
                }
            }
            return null;
        }


        private void LoadNode(XmlNode aNode)
        {
            XmlNodeList childNodes = aNode.ChildNodes;
            FlowGraphNodeDescriptor desc = new FlowGraphNodeDescriptor();
            string uid = "";
            int posX = 0;
            int posY = 0;

            foreach (XmlNode child in childNodes)
            {
                switch (child.Name)
                {
                    case "Name": desc.Title = child.InnerText; break;
                    case "FilePath": desc.FilePath = child.InnerText; break;
                    case "Connections": LoadConnections(desc, child); break;
                    case "UID": uid = child.InnerText; break;
                    case "PosX": posX = int.Parse(child.InnerText); break;
                    case "PosY": posY = int.Parse(child.InnerText); break;
                }
            }

            CNodeType nodeType = Model.GetNodeType(desc.Title);
            if (nodeType == null)
            {
                MessageBox.Show("Lua node is missing for the box: " + desc.Title + ". Deleted?", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            childNodes = null;
            desc.X = posX;
            desc.Y = posY;
            FlowGraphNode node = AddNewNode(desc);
            node.myGuid = long.Parse(uid);

            desc.FilePath = nodeType.myPath;


            if (node.Connectors.Count() != nodeType.myPins.Count())
            {
                MessageBox.Show("Node warning:  " + desc.Title + ". Pin count is not matching! Please update the node!" , "Warning", MessageBoxButtons.OK, MessageBoxIcon.Error);
                node.myisFailed = true;
                return;
            }
            else 
            {
                for (int i = 0; i < node.Connectors.Count(); i++)
                {
                    FlowGraphConnector connector = node.Connectors[i];
                    connector.myCommandPath = nodeType.myPins[i].myCommandPath;
                }
            }

  
            node.X = posX;
            node.Y = posY;

        }

        private void LoadConnections(FlowGraphNodeDescriptor aDesc, XmlNode aNode)
        {
            XmlNodeList childNodes = aNode.ChildNodes;
            foreach (XmlNode child in childNodes)
            {
                switch (child.Name)
                {
                    case "Connection":
                        NodePin nodePin = new NodePin();
                        LoadConnection(nodePin, child);
                        aDesc.AddPin(nodePin);
                        break;
                }
            }
        }

        private void LoadConnection(NodePin aPin, XmlNode aNode)
        {
            XmlNodeList childNodes = aNode.ChildNodes;
            foreach (XmlNode child in childNodes)
            {
                switch (child.Name)
                {
                    case "Index": break;
                    case "VarType": aPin.myType = child.InnerText; break;
                    case "Type": aPin.myIsInput = (child.InnerText == "Input") ? true : false; break;
                    case "Name": aPin.myName = child.InnerText; break;
                }
            }
        }

        private void ReadElement(XmlTextReader aReader)
        {
            string theName = aReader.Name;
        }
    }
}
