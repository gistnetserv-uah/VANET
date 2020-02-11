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

#ifndef CBQOS_VEINS_MODULES_APPLICATION_NEIGHBORTABLE_NEIGHBORTABLE_H_
#define CBQOS_VEINS_MODULES_APPLICATION_NEIGHBORTABLE_NEIGHBORTABLE_H_

#include "veins/base/utils/MiXiMDefs.h"
//begin Mn
#include "veins/modules/mobility/traci/TraCIMobility.h"
#include "veins/modules/mobility/traci/TraCICommandInterface.h"
//end Mn

//begin Mn
using Veins::TraCIMobility;
using Veins::TraCICommandInterface;
using Veins::AnnotationManager;
//end Mn
/**
 * This module handles the mapping between next cluster head and destination cluster head. See the NED definition for details.
 */
class MemberTable : public cSimpleModule
{
  protected:

    int maxMembers; //-1 means the unlimited value

    struct MemberEntry{
        int id;
        Coord position;
        double speed;
        int degree;
        simtime_t creationTime;
        int nbReceivedHello;
        double QoSValue;
        double direction;
        double L;
        double BW;
        double D;
        double J;
        double speedDifference;
        MemberEntry ():
            id(-1),position(Coord()), speed(0), degree(0), creationTime(0), nbReceivedHello(0), QoSValue(0), direction(0), L(0), BW(0), D(0), J(0), speedDifference(0){}

        MemberEntry (int d, Coord pos, double sp, int deg, simtime_t ct, int nbH, double qos, double dir, double l, double bw, double d1, double j, double sd):
               id(d), position(pos), speed(sp), degree(deg), creationTime(ct), nbReceivedHello(nbH), QoSValue(qos), direction(dir), L(l),  BW(bw), D(d1), J(j), speedDifference(sd) {}
    };

   //typedef struct MemberEntry MemberEntryType;
   //typedef std::vector<MemberEntryType> Table;

    typedef std::vector<MemberEntry> Table;
   Table memberTable;


    friend std::ostream& operator<<(std::ostream& os, const MemberEntry& entry);

   // typedef std::vector<RouteEntry> Table;




  protected:

    virtual int numInitStages() const override { return 1; }

    virtual void initialize(int stage) override;

    virtual void handleMessage(cMessage *msg) override;

  public:

    MemberTable();

    ~MemberTable();

  // Table management

protected:

    //virtual const RouteEntry *getRouteEntry(int dest) const;
    //const QoS *getQos(int dest) const;

  public:

    virtual int getNumberOfMembers() const;

    virtual bool updateTable(int id, Coord position, double speed, int degree, simtime_t creationTime, int nbReceivedHello,
            double QoSValue, double direction, double L, double BW, double D, double J, double speedDifference);

    virtual void printState() const;

    virtual void clearTable();

};


#endif // ifndef CBQOS_VEINS_MODULES_APPLICATION_ROUTINGTABLE_ROUTINGTABLE_H_

