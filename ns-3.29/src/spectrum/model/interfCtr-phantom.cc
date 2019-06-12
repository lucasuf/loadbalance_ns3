/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2019
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Juliano J. Bazzo <j.bazzo@gmail.com>
 */


#include "interfCtr-phantom.h"

#include <ns3/simulator.h>
#include <ns3/log.h>
#include <ns3/lte-ue-net-device.h>
#include <ns3/lte-enb-net-device.h>


using namespace std;

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("InterfCtrPhantom");

InterfCtrPhantom::InterfCtrPhantom (Ptr<LteUeNetDevice> ueDev, Ptr<LteEnbNetDevice> eNBDev)
:m_ueDev(ueDev),
 m_eNBDev(eNBDev)
{
  NS_LOG_FUNCTION (this);
}

InterfCtrPhantom::~InterfCtrPhantom ()
{
  NS_LOG_FUNCTION (this);
}

TypeId
InterfCtrPhantom::GetTypeId ()
{
  static TypeId tid = TypeId ("ns3::InterfCtrPhantom")
    .SetParent<Object> ()
    .SetGroupName ("Spectrum")
    ;
  return tid;
}

void InterfCtrPhantom::DoDispose() {
	NS_LOG_FUNCTION (this);
	Object::DoDispose();
}


void InterfCtrPhantom::addInterferer(Ptr<InterferPhantom> interf, Direction d) {
	switch(d) {
	case UL:
		ulInterf.push_back(interf);
	break;
	case DL:
		dlInterf.push_back(interf);
		break;
	case UNKNOWN:
		//TODO: error
		break;
	}
}

void InterfCtrPhantom::updateInterferer(Direction d) {
	switch(d) {
		case UL:
			for(vector< Ptr<InterferPhantom> >::iterator it = ulInterf.begin(); it != ulInterf.end(); ++it) {
				//m_eNBDev.

				//it->doSomething();
			 }

		break;
		case DL:

			break;
		case UNKNOWN:
			//TODO: error
			break;
		}
}


vector< Ptr<InterferPhantom> > InterfCtrPhantom::getInterfererDL(double orientation, double radius) {

	/*
	if(orientation==0.0) {
		//m_eNBDev->GetPhy()->GetDlSpectrumPhy()->GetMobility()->GetA
		double x = radius + (radius / 2.0);
		double y = radius * (sqrt(3.0) / 2.0);
		Ptr<Position> p = new Ptr<Position>(x, y, 0.0);
		Ptr<InterferPhantom> m = new Ptr<InterferPhantom>(p, )
	} else if(orientation==120.0) {

	} else { //240

	}
	vector<Vector> cellPosit(nCells);
	assert(nCells <= 19 && nCells > 0);
	double x = 0.0;
	double y = 0.0;
	double z = 0.0;
	for (int i = 0; i < nCells; i++) {
		switch (i) {
		case 0:
			x = 0.0;
			y = 0.0;
			break;
		case 1:
			x = 0.0;
			y = radius * sqrt(3.0);
			break;

		case 2:
			x = -(radius + (radius / 2.0));
			y = radius * (sqrt(3.0) / 2.0);
			break;

		case 3:
			x = -(radius + (radius / 2.0));
			y = -(radius * (sqrt(3.0) / 2.0));
			break;

		case 4:
			x = 0;
			y = -(radius * sqrt(3.0));
			break;

		case 5:
			x = radius + (radius / 2.0);
			y = -(radius * (sqrt(3.0) / 2.0));
			break;

		case 6:
			x = radius + (radius / 2.0);
			y = radius * (sqrt(3.0) / 2.0);
			break;

		case 7:
			x = 0.0;
			y = 2.0 * (radius * sqrt(3.0));
			break;

		case 8:
			x = -(radius + (radius / 2.0));
			y = 3.0 * (radius * (sqrt(3.0) / 2.0));
			break;

		case 9:
			x = -(3.0 * radius);
			y = radius * sqrt(3.0);
			break;

		case 10:
			x = -(3.0 * radius);
			y = 0.0;
			break;

		case 11:
			x = -(3.0 * radius);
			y = -(radius * sqrt(3.0));
			break;

		case 12:
			x = -(radius + (radius / 2.0));
			y = -(3.0 * (radius * (sqrt(3.0) / 2.0)));
			break;

		case 13:
			x = 0.0;
			y = -(2.0 * (radius * sqrt(3.0)));
			break;

		case 14:
			x = radius + (radius / 2.0);
			y = -(3.0 * (radius * (sqrt(3.0) / 2.0)));
			break;

		case 15:
			x = 3.0 * radius;
			y = -(radius * sqrt(3.0));
			break;
		case 16:
			x = 3.0 * radius;
			y = 0.0;
			break;
		case 17:
			x = 3.0 * radius;
			y = radius * sqrt(3.0);
			break;

		case 18:
			x = radius + (radius / 2.0);
			y = 3.0 * (radius * (sqrt(3.0) / 2.0));
			break;
		}
		cellPosit[i] = Vector(x, y, z);
	}

	return cellPosit;
	*/
	vector< Ptr<InterferPhantom> > r;
	return r;
}




} // namespace ns3


