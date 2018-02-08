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

#include "datalink.h"
#include "string.h"
#include <omnetpp.h>

Define_Module(Datalink);

void Datalink::initialize()
{
    from_al = gate("from_al");
    from_pl = gate("from_pl");
    to_al = gate("to_al");
    to_pl = gate("to_pl");
    // TODO - Generated method body
}

void Datalink::handleMessage(cMessage *msg)
{
    if(msg->getArrivalGate() == from_al){
        A_PDU* a = check_and_cast<A_PDU*>(msg);
        DL_PDU* d = new DL_PDU();
        int id = a->getAid();
        id = (id+1)%2;
        d->setType("DATA");
        d->setDid(id);
        d->encapsulate(a);
        scheduleAt(simTime()+200.0,d);
//        send(d, to_pl);
    } else if(msg->getArrivalGate() == from_pl){
        DL_PDU* d = check_and_cast<DL_PDU*>(msg);
        if(strcmp(d->getType(),"DATA")== 0){
            send(d->decapsulate(), to_al);
            int id = d->getDid();
            id = (id+1)%2;
            DL_PDU* c = new DL_PDU();
            c->setType("ACK");
            c->setDid(id);
            send(c, to_pl);
        }
    } else if(msg->isSelfMessage()){
        DL_PDU* d = check_and_cast<DL_PDU*>(msg);
        send(d, to_pl);
    }
    // TODO - Generated method body
}
