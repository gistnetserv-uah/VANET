//
// Copyright (C) 2006-2011 Christoph Sommer <christoph.sommer@uibk.ac.at>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#ifndef CBQoS_H
#define CBQoS_H

#include "veins/modules/application/ieee80211p/BaseWaveApplLayer.h"
#include "veins/modules/mobility/traci/TraCIMobility.h"
#include "veins/modules/mobility/traci/TraCICommandInterface.h"
//EXTRA BEGIN
#include "src/veins/modules/application/neighbortable/NeighborTable.h"
#include "src/veins/modules/messages/HelloMessage_m.h"
//EXTRA END

using Veins::TraCIMobility;
using Veins::TraCICommandInterface;
using Veins::AnnotationManager;

/**
 * Small IVC Demo using 11p
 */
class CBQoS : public BaseWaveApplLayer {
	public:
		virtual void initialize(int stage) override;
		virtual void receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj, cObject* details) override;
	protected:
		TraCIMobility* mobility;
		TraCICommandInterface* traci;
		TraCICommandInterface::Vehicle* traciVehicle;
		AnnotationManager* annotations;
		simtime_t lastDroveAt;
		bool sentMessage;
		bool isParking;
		bool sendWhileParking;
		static const simsignalwrap_t parkingStateChangedSignal;

		//EXTRA BEGIN
        enum timerTypes{
            SEND_HELLO_TIMER
        };

		//Modules
		NeighborTable* neighborTable;

		//Hello Parameters
        simtime_t helloInterval;
        cMessage* sendHelloTimer;


	public:
        CBQoS();
        ~CBQoS();
        //EXTRA END

	protected:
		virtual void onBeacon(WaveShortMessage* wsm) override;
		virtual void onData(WaveShortMessage* wsm) override;
		void sendMessage(std::string blockedRoadId);
		virtual void handlePositionUpdate(cObject* obj) override;
		virtual void handleParkingUpdate(cObject* obj);
		virtual void sendWSM(WaveShortMessage* wsm) override;

		//EXTRA BEGIN
		virtual void handleSelfMsg(cMessage* msg) override;
		virtual void sendHelloMessage();

		virtual void handleIncomingHello(HelloMessage* helloMessage);

		void finish() override;
		//EXTRA END
};

#endif
