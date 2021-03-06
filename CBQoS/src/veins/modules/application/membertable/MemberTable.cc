/*
 * Copyright (C) 2018 Elisa Rojas(1), Hedayat Hosseini(2);
 *                    (1) GIST, University of Alcala, Spain.
 *                    (2) CEIT, Amirkabir University of Technology (Tehran Polytechnic), Iran.
 *                    OMNeT++ 5.2.1 & INET 3.6.3
 *                    Implementation of parent table for RPL
 *                    Developed in OMNeT++ 5.2.1 & INET 3.6.3
*/
/*
 * Copyright (C) 2020 Elisa Rojas(1), Hedayat Hosseini(2), Mehrnoush Naeini(3);
 *                    (1) GIST, University of Alcala, Spain.
 *                    (2) CEIT, Amirkabir University of Technology (Tehran Polytechnic), Iran.
 *                    (3) @Mehrnoush: Inja benevis
 *                    Implementation of routing table for CBQoS VANET routing protocol
 *                    Developed in OMNeT++ 5 & VEINs4.4
 * Main paper:
 * Lakas, A., Fekair, M.E.A., Korichi, A. and Lagraa, N., 2019.
 * A multiconstrained QoS-compliant routing scheme for highway-based vehicular networks.
 * Wireless Communications and Mobile Computing, 2019.
 */
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

#include "src/veins/modules/application/membertable/MemberTable.h"

//#include <map>
#include <vector>
#include <math.h>


Define_Module(MemberTable);

std::ostream& operator<<(std::ostream& os, const MemberTable::MemberEntry& entry)
{
    os << "{ID=" << entry.id << ", Position=" << entry.position << ", Degree=" << entry.degree << ", creationTime=" << entry.creationTime <<
         ", NMRH=" << entry.nbReceivedHello << ", QoSValue=" << entry.QoSValue  <<
         ", LET=" << entry.L << ", direction=" << entry.direction << ", Delay=" << entry.D << ", Jitter=" << entry.J <<
         ", SpeedD=" << entry.speedDifference << "}";
    return os;
}

MemberTable::MemberTable()
{
    maxMembers = -1; //Unlimited
}

void MemberTable::initialize(int stage)
{
    cSimpleModule::initialize(stage);

    if(stage == 0){
        maxMembers = par("maxMembers");

        WATCH_VECTOR(memberTable);
    }

}

void MemberTable::handleMessage(cMessage *)
{
    throw cRuntimeError("RoutingTable::handleMessage: This module doesn't process messages");
}

int MemberTable::getNumberOfMembers() const
{
    return memberTable.size();
}


/*
 * Add a new Entry to routingTable.
 * -1 if not added. 0 if it is new. 1 if it is updated.
 */

bool MemberTable::updateTable( int id, Coord position, double speed, int degree, simtime_t creationTime, int nbReceivedHello,
        double QoSValue, double direction, double L, double BW, double D, double J, double speedDifference)
{
    Enter_Method("MemberTable::updateTable()");

    for (unsigned int i = 0; i < memberTable.size(); i++){
        if (id == memberTable.at(i).id){
            // Update existing entry
            MemberEntry entry = memberTable.at(i);
            EV << "Updating entry in Routing Table, old entry=> " << entry << endl; //Path ID:"  << entry.pathId << " Scout ID: " << entry.scoutId << " Dest: " << entry.dest << " CH Dest: " << entry.chDest << " CH Next: " << entry.chNext << "\n";
            entry.id = id;
            entry.position = position;
            entry.speed = speed;
            entry.degree = degree;
            entry.creationTime = creationTime;
            entry.nbReceivedHello = nbReceivedHello;
            entry.QoSValue = QoSValue;
            entry.direction = direction;
            entry.L = L;
            entry.BW = BW;
            entry.D = D;
            entry.J = J;
            entry.speedDifference = speedDifference;
            return 1;
        }
    }

    if ((maxMembers != -1) && (getNumberOfMembers() == maxMembers)){ //If there is not a room,
        return -1;
    }
    memberTable.push_back(MemberEntry(id, position, speed, degree, creationTime, nbReceivedHello, QoSValue, direction, L, BW, D, J, speedDifference));
    EV << "A new entry was added to the NeighborsTable: " << MemberEntry(id, position, speed, degree, creationTime, nbReceivedHello, QoSValue, direction, L, BW, D, J, speedDifference) << "\n";
    return 0;
}
/*
const RoutingTable::RouteEntry *RoutingTable::getRouteEntry(int dest) const
{
    if (routingTable.size() == 0)
        return nullptr;

    for (unsigned int i = 0; i < routingTable.size(); i++) {
        if (routingTable.at(i).dest == dest) {
            return &routingTable.at(i);
        }
    }
    return nullptr;
}
*/
void MemberTable::printState() const
{
    EV << endl << "MemberTable" << endl;
    for (unsigned int i = 0; i < memberTable.size(); i++){
        EV << memberTable.at(i) << endl;
    }
}

void MemberTable::clearTable()
{
    memberTable.clear();
}

MemberTable::~MemberTable()
{
    clearTable();
}
