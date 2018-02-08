//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include <string.h>
#include <omnetpp.h>
#include "node.h"

Define_Module(Node);

void Node::initialize()
{
    gIn = gate("in");
    gOut = gate("out");
    address = par("id");
    if(address == 2){
        cMessage* event = new cMessage();
        scheduleAt(0, event);
    }
    // TODO - Generated method body
}

void Node::handleMessage(cMessage *msg)
{
    if(msg -> isSelfMessage()){
        Pkt* p = new Pkt();
        p->setType("data");
        send (p, gOut);
    } else {
        Pkt* d = check_and_cast<Pkt*>(msg);
        if(strcmp(d->getType(),"data") == 0){
            Pkt* p = new Pkt();
            p->setType("ack");
            send (p, gOut);
        }
    }
    // TODO - Generated method body
}
