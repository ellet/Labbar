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
using System.Drawing;
using System.Windows.Forms;
using FlowGraph.Enums;



namespace FlowGraph
{
  
    partial class FlowGraphView
    {
        CInputManager myInputManager;
        public void InitKeys()
        {
            myInputManager = new CInputManager();
            myInputManager.InitKeys();
            CInputManager.OnKeyPressed += MessageHooks_OnHookCallBack;
        }

        void MessageHooks_OnHookCallBack(int keyPressed)
        {
            Keys key = (Keys)keyPressed;

            if (key == Keys.Alt) _isAltPressed = true;

            if (key == Keys.Control) _isCtrlPressed = true;

            if (key == Keys.Delete && IsEditable) DeleteSelectedNodes();

            // do something with the keypress
        }

        private void FlowGraphView_MouseWheel(object sender, MouseEventArgs e)
        {
            if (e.Delta != 0)
            {
                var newViewZoom = Model.Zoom + (e.Delta * 0.001f);

                if (newViewZoom > 0.1f && newViewZoom < 2.0f)
                    Model.Zoom = newViewZoom;
            }

            if (_editMode == FlowGraphEditMode.SelectingBox)
                _selectBoxCurrent = ControlToModel(new Point(e.X, e.Y));

            UpdateFontSize();

            Refresh();
        }

        private void FlowGraphView_MouseDown(object sender, MouseEventArgs e)
        {
            this.Focus();
            switch (_editMode)
            {
                case FlowGraphEditMode.Idle:
                    switch (e.Button)
                    {
                        case MouseButtons.Middle:

                            _editMode = FlowGraphEditMode.Scrolling;

                            _scrollLastX = e.Location.X;

                            _scrollLastY = e.Location.Y;

                            break;

                        case MouseButtons.Left:
                            if (!IsEditable) break;

                            if (HitAll(e.Location) == HitType.Connector)
                            {
                                if (!_isAltPressed)
                                {
                                    _editMode = FlowGraphEditMode.Linking;

                                    _activeLeftConnector = GetHitConnector(e.Location);

                                    _activeRightConnector = null;
                                }
                                else
                                {
                                    var connector = GetHitConnector(e.Location);

                                    DeleteConnectorLinks(connector);
                                }
                            }
                            else if (Model.SelectedNodes.Count > 0 && HitSelected(e.Location) == HitType.Node)
                            {
                                _editMode = FlowGraphEditMode.MovingSelection;

                                _moveLastPosition = ControlToModel(e.Location);
                            }
                            else
                            {
                                _editMode = FlowGraphEditMode.Selecting;

                                _selectBoxCurrent = ControlToModel(new Point(e.X, e.Y));

                                _selectBoxOrigin = ControlToModel(new Point(e.X, e.Y));

                                UpdateHighlights();

                                CreateSelection();

                                if (Model.SelectedNodes.Count > 0)
                                {
                                    _editMode = FlowGraphEditMode.MovingSelection;

                                    _moveLastPosition = ControlToModel(e.Location);

                                    if (Model.SelectedNodes.Count == 1)
                                    {
                                        PropertiesOnNodeSelected(Model.SelectedNodes[0]);
                                    }
                                }
                                else
                                {
                                    PropertiesOnNodeSelected(null);
                                }

                            }
                            break;
                    }
                    break;
            }
            Refresh();
        }

        // TODO: Deal with FlowGraphView_MouseWheel
        
        /*
        /// <summary>
        /// Behavior when Mouse Wheel is turned
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void FlowGraphView_MouseWheel(object sender, MouseEventArgs e)
        {
            if (e.Delta != 0)
            {
                var newViewZoom = Model.Zoom + (e.Delta * 0.001f);

                if (newViewZoom > 0.1f && newViewZoom < 2.0f)
                    Model.Zoom = newViewZoom;
            }

            if (_editMode == FlowGraphEditMode.SelectingBox)
                _selectBoxCurrent = ControlToModel(new Point(e.X, e.Y));

            UpdateFontSize();

            Refresh();
        }
        */

        /// <summary>
        /// Behavior when Mouse Click is released
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void FlowGraphView_MouseUp(object sender, MouseEventArgs e)
        {
            switch (_editMode)
            {
                case FlowGraphEditMode.Scrolling:
                    if (e.Button == MouseButtons.Middle)
                        _editMode = FlowGraphEditMode.Idle;

                    break;

                case FlowGraphEditMode.Selecting:

                case FlowGraphEditMode.SelectingBox:
                    if (!IsEditable) break;

                    if (e.Button == MouseButtons.Left)
                    {
                        CreateSelection();

                        _editMode = FlowGraphEditMode.Idle;
                    }

                    break;

                case FlowGraphEditMode.MovingSelection:
                    if (!IsEditable) break;

                    if (e.Button == MouseButtons.Left)
                        _editMode = FlowGraphEditMode.Idle;

                    break;

                case FlowGraphEditMode.Linking:
                    if (!IsEditable) break;

                    _activeRightConnector = GetHitConnector(e.Location);

                    AddLink();

                    _editMode = FlowGraphEditMode.Idle;

                    break;
            }
        }

        /// <summary>
        /// Behavior when mouse is moved
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void FlowGraphView_MouseMove(object sender, MouseEventArgs e)
        {
            _viewSpaceCursorLocation = ControlToModel(new Point(e.X, e.Y));

            switch (_editMode)
            {
                case FlowGraphEditMode.Scrolling:
                    Model.ModelX += (int)((e.Location.X - _scrollLastX) / Model.Zoom);

                    Model.ModelY += (int)((e.Location.Y - _scrollLastY) / Model.Zoom);

                    _scrollLastX = e.Location.X;

                    _scrollLastY = e.Location.Y;

                    Refresh();

                    break;

                case FlowGraphEditMode.Selecting:
                    if (!IsEditable) break;

                    _editMode = FlowGraphEditMode.SelectingBox;

                    _selectBoxCurrent = ControlToModel(new Point(e.X, e.Y));

                    UpdateHighlights();

                    Refresh();

                    break;

                case FlowGraphEditMode.SelectingBox:
                    if (!IsEditable) break;

                    if (IsInScrollArea(e.Location))
                        UpdateScroll(e.Location);

                    _selectBoxCurrent = ControlToModel(new Point(e.X, e.Y));

                    UpdateHighlights();

                    Refresh();

                    break;

                case FlowGraphEditMode.MovingSelection:
                    if (!IsEditable) break;

                    if (IsInScrollArea(e.Location))
                        UpdateScroll(e.Location);

                    var currentCursorLoc = ControlToModel(e.Location);

                    var deltaX = _moveLastPosition.X - currentCursorLoc.X;

                    var deltaY = _moveLastPosition.Y - currentCursorLoc.Y;

                    MoveSelection(new Point(deltaX, deltaY));

                    Refresh();

                    _moveLastPosition = currentCursorLoc;

                    break;

                case FlowGraphEditMode.Linking:
                    if (!IsEditable) break;

                    if (IsInScrollArea(e.Location))

                        UpdateScroll(e.Location);
                    Refresh();

                    break;

                default:
                    Refresh();

                    break;
            }
        }

        /// <summary>
        /// Behavior when panel is resized
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void FlowGraphView_Resize(object sender, EventArgs e)
        {
            Refresh();
        }

        /// <summary>
        /// Behavior when keyboard key is pushed
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void FlowGraphView_KeyDown(object sender, KeyEventArgs e)
        {
           /* if (e.Alt) _isAltPressed = true;

            if (e.Control) _isCtrlPressed = true;

            if (e.KeyCode == Keys.Delete && IsEditable) DeleteSelectedNodes();*/
        }

        /// <summary>
        /// Behavior when keyboard key is released
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void FlowGraphView_KeyUp(object sender, KeyEventArgs e)
        {
            if (!e.Alt) _isAltPressed = false;

            if (!e.Control) _isCtrlPressed = false;
        }
    }
}
