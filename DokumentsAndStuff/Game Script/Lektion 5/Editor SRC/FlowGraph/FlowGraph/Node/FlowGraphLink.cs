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

using FlowGraph.Enums;
using FlowGraph.Exceptions;

namespace FlowGraph
{
    /// <summary>
    /// Represents a link between two FlowGraphConnectors
    /// </summary>
    public class FlowGraphLink
    {
        /// <summary>
        /// Creates a new link, given input and output connectors
        /// </summary>
        /// <param name="leftConnector">An output connector of a node on the left</param>
        /// <param name="rightConnector">An input connector of a node on the right</param>
        /// 

        public FlowGraphLink(FlowGraphConnector leftConnector, FlowGraphConnector rightConnector)
        {
            if (leftConnector.Type != ConnectorType.Output || rightConnector.Type != ConnectorType.Input)
                throw new InappropriateConnectorTypeException();

            _leftConnector = leftConnector;

            _rightConnector = rightConnector;
        }

        /// <summary>
        /// The first (left) end of the link, that's bound to an output connector of a node
        /// </summary>
        public FlowGraphConnector LeftConnector
        {
            get { return _leftConnector; }
        }

        /// <summary>
        /// The last (right) end of the link, that's bound to an input connector of a node
        /// </summary>
        public FlowGraphConnector RightConnector
        {
            get { return _rightConnector; }
        }

        private readonly FlowGraphConnector _leftConnector;

        private readonly FlowGraphConnector _rightConnector;
    }
}
