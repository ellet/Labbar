/*

Copyright (c) 2014, Ivan Mashchenko
Copyright (c) 2011, Thomas ICHE
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the 
following conditions are met:

        * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer 
          in the documentation and/or other materials provided with the distribution.
        * Neither the name of FlowGraph nor the names of its contributors may be used to endorse or promote products derived from this 
          software without specific prior written permission.


THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, 
OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Windows.Forms;
using FlowGraph.Enums;
using FlowGraph.EventArguments;
using FlowGraph.Exceptions;

namespace FlowGraph
{
    public partial class FlowGraphView : UserControl
    {
        /// <summary>
        /// Creates a node given a descriptor and adds it to the model
        /// </summary>
        /// <param name="descriptor">A descriptor to create a new node by</param>
        public FlowGraphNode AddNewNode(FlowGraphNodeDescriptor descriptor)
        {
            if(descriptor == null)
                throw new NullReferenceException();

            var node = new FlowGraphNode(descriptor, Model);

            AddNode(node);

            return node;
        }

        public List<FlowGraphNode> GetAllNodes()
        {
            return Model.Nodes;
        }

        /// <summary>
        /// Adds a node to the model
        /// </summary>
        /// <param name="node">A node to be added</param>

        public void AddNode(FlowGraphNode node)
        {
            var e = new FlowGraphViewNodeEventArgs(node);

            FireNodeAdding(e);

            if (!e.Deny)
            {
                Model.Nodes.Add(node);

                Refresh();

                FireNodeAdded(new FlowGraphViewNodeEventArgs(e.Node));
            }
        }

        /// <summary>
        /// Deletes a node
        /// </summary>
        public bool DeleteNode(FlowGraphNode node)
        {
            var e = new FlowGraphViewNodeEventArgs(node);

            FireNodeRemoving(e);

            if (e.Deny)
                return false;

            if (node.Connectors.Any(connector => !DeleteConnectorLinks(connector)))
                throw new ModelModificationFailedException("Failed delete a connector while deleting a node");

            Model.Nodes.Remove(e.Node);

            FireNodeRemoved(new FlowGraphViewNodeEventArgs(e.Node));

            return true;
        }

        /// <summary>
        /// Deletes the nodes currently selected
        /// </summary>
        public bool DeleteSelectedNodes()
        {
            var success = true;

            foreach (var node in Model.SelectedNodes)
                if (!DeleteNode(node)) success = false;

            Refresh();

            return success;
        }

        /// <summary>
        /// Adds a link between two connectors
        /// </summary>
        /// <param name="leftConnector"></param>
        /// <param name="rightConnector"></param>
        private void AddLink(FlowGraphConnector leftConnector, FlowGraphConnector rightConnector)
        {
            if (leftConnector == null || rightConnector == null)
                throw new NullReferenceException();

            if (leftConnector.Type != ConnectorType.Output || rightConnector.Type != ConnectorType.Input)
                return;

            if (leftConnector.VarType.CompareTo(rightConnector.VarType) != 0)
            {
                return;
            }

            var newLink = new FlowGraphLink(leftConnector, rightConnector);

            leftConnector.AddLink(newLink);
            rightConnector.AddLink(newLink);

            var e = new FlowGraphViewLinkEventArgs(newLink);

            FireLinkAdding(e);

            if (e.Deny) return;

            if (IsLinked(rightConnector))
                DeleteConnectorLinks(rightConnector);

            Model.Links.Add(newLink);

            FireLinkAdded(new FlowGraphViewLinkEventArgs(e.Link));
        }

        /// <summary>
        /// Deletes all links featuring a connector
        /// </summary>
        /// <param name="connector"></param>
        /// <returns>all links deleted succesfully</returns>
        private bool DeleteConnectorLinks(FlowGraphConnector connector)
        {
            var success = true;

            var connectorLinks = Model.Links.Where(link => link.LeftConnector == connector || link.RightConnector == connector).ToList();

            foreach (var link in connectorLinks)
            {
                var e = new FlowGraphViewLinkEventArgs(link);

                FireLinkRemoving(e);

                if (e.Deny)
                {
                    success = false;

                    continue;
                }

                Model.Links.Remove(link);

                FireLinkRemoved(new FlowGraphViewLinkEventArgs(e.Link));

                link.LeftConnector.RemoveLink(link);
                link.RightConnector.RemoveLink(link);
            }

            Refresh();

            return success;
        }

        /// <summary>
        /// Gets a node corresponding an object
        /// </summary>
        /// <param name="obj">An object</param>
        public FlowGraphNode GetCorrespondingNode(object obj)
        {
            var matchingNodes = Model.Nodes.Where(node => node.Object == obj).ToArray();

            if (matchingNodes.Length > 1 || matchingNodes.Length < 0)
                throw new UnexpectedStateExpection();

            return matchingNodes.Length < 1 ? null : matchingNodes[0];
        }

        /// <summary>
        /// Checks if the model has a node corresponding an object
        /// </summary>
        /// <param name="obj">An object</param>
        public bool HasCorrespondingNode(object obj)
        {
            return GetCorrespondingNode(obj) != null;
        }

        [Browsable(false)]
        public List<FlowGraphNode> SelectedNodes {
            get
            {
                return Model.SelectedNodes;
            }
        }

        /// <summary>
        /// A flow chart model (nodes and links container)
        /// </summary>
        [Browsable(false)]
        public FlowGraphModel Model { get; private set; }

        /// <summary>
        /// Chooses if a user can edit the flow chart
        /// </summary>
        public bool IsEditable { get; set; }

        private void FlowGraphView_Load(object sender, EventArgs e)
        {
            InitKeys();
           //Add(0);
          // Add(1);
        }



        void Add(int test)
        {
            FlowGraphNodeDescriptor desc = new FlowGraphNodeDescriptor();
            desc.Title = "Test";


            desc.AddPin(true, "In", "impulse");
            desc.AddPin(true, "Data 2", "int", new CommandPath("GotoCommand.bat", "GoTo"));

            desc.AddPin(false, "Out", "impulse");
            desc.AddPin(false, "Test", "float");
            desc.AddPin(true, "Test2", "string");
            desc.AddPin(true, "Test2", "");
            desc.AddPin(true, "Test2", "");
            desc.AddPin(true, "Test2", "");
            desc.AddPin(true, "Test2", "");
            desc.AddPin(true, "Test2", "");

            desc.X = 100 * test;
            desc.Y = 100;
            FlowGraphNode node = AddNewNode(desc);
        }






    }
}
