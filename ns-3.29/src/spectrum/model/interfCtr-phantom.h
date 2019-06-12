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


#ifndef INTERFCTR_PHANTOM_H
#define INTERFCTR_PHANTOM_H

#include <ns3/object.h>
#include <ns3/packet.h>
#include <ns3/nstime.h>
#include <ns3/spectrum-value.h>
#include <ns3/lte-ue-net-device.h>
#include <ns3/lte-enb-net-device.h>
#include <ns3/interferer-phantom.h>
#include <vector>


using namespace std;

namespace ns3 {


/**
 *
 */
class InterfCtrPhantom : public Object
{
public:

	enum Direction {
			DL, UL, UNKNOWN
	};

	InterfCtrPhantom (Ptr<LteUeNetDevice> ueDev, Ptr<LteEnbNetDevice> eNBDev);
  virtual ~InterfCtrPhantom ();

  /**
   * Register this type.
   * \return The TypeId.
   */
  static TypeId GetTypeId (void);
  

  void addInterferer(Ptr<InterferPhantom> interf, Direction d);

  void updateInterferer(Direction d);


protected:
  void DoDispose ();

  vector< Ptr<InterferPhantom> > getInterfererDL(double orientation, double radius);

private:
  Ptr<LteUeNetDevice> m_ueDev;
  Ptr<LteEnbNetDevice> m_eNBDev;
  vector< Ptr<InterferPhantom> > ulInterf;
  vector< Ptr<InterferPhantom> > dlInterf;

};



} // namespace ns3





#endif /* SPECTRUM_INTERFERENCE_H */
