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

using System.Drawing;
using System.Windows.Forms;
using FlowGraph.Enums;

namespace FlowGraph
{
    partial class FlowGraphView
    {
        public FlowGraphView()
        {
            InitializeComponent();

            #region State

            Model = new FlowGraphModel(this);

            _editMode = FlowGraphEditMode.Idle;

            _viewSpaceCursorLocation = new Point();

            _isAltPressed = false;

            _isCtrlPressed = false;

            _selectBoxOrigin = new Point();

            _selectBoxCurrent = new Point();

            _scrollLastX = 0;

            _scrollLastY = 0;


            _activeLeftConnector = null;

            _activeRightConnector = null;

            #endregion

            #region Colors

            NodeTextColor = Color.FromArgb(255, 255, 255, 255);

            NodeTextShadowColor = Color.FromArgb(128, 0, 0, 0);

            NodeFillColor = Color.FromArgb(255, 128, 128, 128);

            NodeFillSelectedColor = Color.FromArgb(255, 160, 128, 100);

            NodeFillFailedColor = Color.FromArgb(255, 180, 70, 70);

            NodeOutlineColor = Color.FromArgb(255, 180, 180, 180);

            NodeOutlineSelectedColor = Color.FromArgb(255, 192, 160, 128);

            ConnectorTextColor = Color.FromArgb(255, 64, 64, 64);

            ConnectorFillColor = Color.FromArgb(40, 40, 40); // Color.FromArgb(255, 0, 0, 0);

            ConnectorFillSelectedColor = Color.FromArgb(255, 32, 32, 32);

            ConnectorOutlineColor = Color.FromArgb(60, 60, 60); // Color.FromArgb(255, 32, 32, 32);

            ConnectorOutlineSelectedColor = Color.FromArgb(255, 64, 64, 64);

            SelectionFillColor = Color.FromArgb(64, 128, 90, 30);

            SelectionOutlineColor = Color.FromArgb(192, 255, 180, 60);

            NodeHeaderColor = Color.FromArgb(128, 0, 0, 0);

            LinkColor = Color.FromArgb(120, 120, 120); // Color.FromArgb(255, 32, 200, 0); // Color.FromArgb(255, 180, 180, 180);
            
            LinkEditableColor = Color.FromArgb(255, 64, 255, 0);

            #endregion

            #region Fonts

            _debugFont = new Font("Tahoma", 8.0f);

            NodeTitleFont = new Font("Tahoma", 8.0f);

            NodeConnectorFont = new Font("Tahoma", 7.0f);

            NodeScaledTitleFont = new Font(NodeTitleFont.Name, NodeTitleFont.Size);

            NodeScaledConnectorFont = new Font(NodeConnectorFont.Name, NodeConnectorFont.Size);

            #endregion

            #region Other

            IsEditable = true;

            _scrollMargins = 32;

            _scrollMarginsValue = 10;

            NodeTitleZoomThreshold = 0.5f;

            NodeLabelsZoomTreshold = 0.8f;

            NodeHeaderSize = 24;

            LinkHardness = 2.0f;

            LinkVisualStyle = LinkVisualStyle.Curve;

            ConnectorHitZoneBleed = 2;

            ShowDebugData = false;

            Dock = DockStyle.Fill;

            DoubleBuffered = true;
            
            ShowGrid = true;

            GridPadding = 256;

            GridAlpha = 32;

            DrawShadow = true;

            SmoothBehavior = false;

            #endregion
        }
    }
}
