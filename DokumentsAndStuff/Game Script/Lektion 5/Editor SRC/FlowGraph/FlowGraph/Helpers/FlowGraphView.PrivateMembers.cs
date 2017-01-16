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
using FlowGraph.Enums;

namespace FlowGraph
{
    partial class FlowGraphView
    {
        private FlowGraphEditMode _editMode;

        // General Behavior
        private int _scrollLastX;
        private int _scrollLastY;

        private readonly Font _debugFont;
        private Point _selectBoxOrigin;
        private Point _selectBoxCurrent;
        private Point _viewSpaceCursorLocation;
        private readonly int _scrollMargins;
        private readonly int _scrollMarginsValue;
        private Point _moveLastPosition;
        private float _linkHardness;

        // Colors
        private Color _nodeTextColor;
        private Color _nodeTextShadowColor;
        private Color _nodeFillColor;
        private Color _nodeFillFailedColor;
        private Color _nodeFillSelectedColor;
        private Color _nodeOutlineColor;
        private Color _nodeOutlineSelectedColor;
        private Color _connectorTextColor;
        private Color _connectorFillColor;
        private Color _connectorOutlineColor;
        private Color _connectorSelectedFillColor;
        private Color _connectorOutlineSelectedColor;
        private Color _selectionFillColor;
        private Color _selectionOutlineColor;
        private Color _linkColor;
        private Color _linkEditableColor;

        // Text Draw tresholds
        // Selection Box
        private Pen _selectionOutline;
        private SolidBrush _selectionFill;

        // Links
        private Pen _link;
        private Pen _linkEditable;
        private Brush _linkArrow;

        // Node HeaderGradient
        private Color _nodeHeaderColor;

        // For Linking
        private FlowGraphConnector _activeLeftConnector;
        private FlowGraphConnector _activeRightConnector;
        private bool _isAltPressed;
        private bool _isCtrlPressed;
        private LinkVisualStyle _linkVisualStyle;
    }
}
