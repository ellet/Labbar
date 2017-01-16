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

using System.Collections.Generic;

namespace FlowGraph
{
    public class CPin
    {
        public string myName;
        public bool isInput;
        public string myType;
        public FlowGraph.CommandPath myCommandPath;
    };
    public class CNodeType
    {
        public CNodeType()
        {
            myPins = new List<CPin>();
        }
        public List<CPin> myPins;
        public string myName;
        public string myPath;
    };
    /// <summary>
    /// Encapsulates a flow chart model (nodes and links)
    /// </summary>
    public class FlowGraphModel
    {
        /// <summary>
        /// Creates a new FlowGraphModel for a FlowGraphView
        /// </summary>
        /// <param name="view">Parent control</param>
        public FlowGraphModel(FlowGraphView view)
        {
            myNodesTypes = new List<CNodeType>();
            View = view;

            Nodes = new List<FlowGraphNode>();

            SelectedNodes = new List<FlowGraphNode>();

            Links = new List<FlowGraphLink>();

            ModelX = 0;

            ModelY = 0;

            Zoom = 1.0f;

            CurrentZoom = 1.0f;
        }

        /// <summary>
        /// The FlowGraphView control this model belongs to
        /// </summary>
        public FlowGraphView View { get; private set; }

        /// <summary>
        /// Collection of nodes contained
        /// </summary>
        public List<FlowGraphNode> Nodes { get; private set; }

        public List<CNodeType> myNodesTypes { get; set; }

        public CNodeType GetNodeType(string aName)
        {
            for (var i = 0; i < myNodesTypes.Count; i++)
            {
                if (myNodesTypes[i].myName == aName) return myNodesTypes[i];
            }
            return null;
        }
        /// <summary>
        /// Collection of nodes currently selected
        /// </summary>
        public List<FlowGraphNode> SelectedNodes { get; private set; }

        /// <summary>
        /// Collection of links between the nodes
        /// </summary>
        public List<FlowGraphLink> Links { get; private set; }

        /// <summary>
        /// Orthographic X coordinate of the model
        /// </summary>
        public int ModelX { get; set; }

        /// <summary>
        /// Orthographic Y coordinate of the model
        /// </summary>
        public int ModelY { get; set; }

        /// <summary>
        /// Zoom factor of the model
        /// </summary>
        public float Zoom { get; set; }

        /// <summary>
        /// Current zoom Factor, used for smooth behavior
        /// </summary>
        public float CurrentZoom { get; set; }

        /// <summary>
        /// Returns the index of a node in this model's collection
        /// </summary>
        /// <param name="node"></param>
        /// <returns></returns>
        public int GetNodeIndex(FlowGraphNode node)
        {
            for (var i = 0; i < Nodes.Count; i++)
            {
                if (Nodes[i] == node) return i;
            }

            return -1;
        }

        public FlowGraphNode GetNodeFromUID(long aUID)
        {
            for (var i = 0; i < Nodes.Count; i++)
            {
                if (Nodes[i].myGuid == aUID) return Nodes[i];
            }

            return null;
        }

        /// <summary>
        /// Returns the index of a node in this model's current selection
        /// </summary>
        /// <param name="node"></param>
        /// <returns></returns>
        public int GetSelectionNodeIndex(FlowGraphNode node)
        {
            for (var i = 0; i < SelectedNodes.Count; i++)
            {
                if (SelectedNodes[i] == node) return i;
            }

            return -1;
        }
    }
}
