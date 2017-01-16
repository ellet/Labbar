/*

Copyright (c) 2014, Ivan Mashchenko
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
using System.Drawing;
using System.Collections.Generic;

namespace FlowGraph
{
    public class NodePin
    {
        public NodePin()
        {
            myName = "Unnamed";
            myIsInput = true;
            myCommandPath = null;
        }

        public string myName;
        public bool myIsInput;
        public string myType;
        public CommandPath myCommandPath;
    }
    public class FlowGraphNodeDescriptor
    {
        public List<NodePin> myPins;
        public FlowGraphNodeDescriptor()
        {
            myPins = new List<NodePin>();
            Width = 100;
            Height = 25;
        }

        public void AddPin(bool isInput, string aName, string aType, CommandPath aCommandPath = null)
        {
            NodePin nodePin = new NodePin();
            nodePin.myIsInput = isInput;
            nodePin.myName = aName;
            nodePin.myType = aType;
            nodePin.myCommandPath = aCommandPath;
            myPins.Add(nodePin);
            Height += 25;
        }

        public void AddPin(NodePin aPin)
        {
            myPins.Add(aPin);
            Height += 25;
        }
       
        public int X { get; set; }

        public int Y { get; set; }

        public int Width { get; set; }

        public int Height { get; set; }

        public string Title { get; set; }

        public string Comment { get; set; }

        public int InputsQty { get; set; }

        public int OutputsQty { get; set; }

        public string FilePath { get; set; }

        public string[] InputLabels { get; set; }

        public string[] OutputLabels { get; set; }

        public object Object { get; set; }

        public void SetControlCoordinates(int x, int y, FlowGraphView control)
        {
            var point = control.ControlToModel(new Point(x, y));

            X = point.X;

            Y = point.Y;
        }

        public Tuple<int, int> GetControlCoordinates(FlowGraphView control)
        {
            var point = control.ModelToControl(new Point(X, Y));

            return new Tuple<int, int>(point.X, point.Y);
        }
    }
}
