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

using System.ComponentModel;
using System.Drawing;

namespace FlowGraph
{
    partial class FlowGraphView
    {
        [Browsable(false)]
        public SolidBrush NodeText { get; private set; }

        [Browsable(false)]
        public SolidBrush NodeTextShadow { get; private set; }

        [Browsable(false)]
        public SolidBrush NodeHeaderFill { get; private set; }

        [Browsable(false)]
        public Pen NodeOutline { get; private set; }

        [Browsable(false)]
        public Pen NodeOutlineSelected { get; private set; }

        [Browsable(false)]
        public SolidBrush NodeFill { get; private set; }

        [Browsable(false)]
        public SolidBrush NodeFillFailed { get; private set; }


        [Browsable(false)]
        public SolidBrush NodeFillSelected { get; private set; }

        [Browsable(false)]
        public SolidBrush ConnectorText { get; private set; }

        [Browsable(false)]
        public Pen ConnectorOutline { get; private set; }

        [Browsable(false)]
        public SolidBrush ConnectorFill { get; private set; }

        [Browsable(false)]
        public Pen ConnectorOutlineSelected { get; private set; }

        [Browsable(false)]
        public SolidBrush ConnectorFillSelected { get; private set; }

        [Category("FlowGraph Panel Fonts")]
        public Font NodeTitleFont { get; set; }

        [Category("FlowGraph Panel Fonts")]
        public Font NodeConnectorFont { get; set; }

        [Browsable(false)]
        public Font NodeScaledTitleFont { get; set; }

        [Browsable(false)]
        public Font NodeScaledConnectorFont { get; set; }
    }
}
