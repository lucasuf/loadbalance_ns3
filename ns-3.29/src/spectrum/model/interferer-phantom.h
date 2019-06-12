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

#ifndef INTERFER_PHANTOM_H
#define INTERFER_PHANTOM_H

#include <ns3/object.h>
#include <ns3/spectrum-value.h>
#include <ns3/position.h>
#include <ns3/antenna-model.h>
#include <ns3/angles.h>

namespace ns3 {

/**
 *
 *
 *
 */

class InterferPhantom: public Object {
public:

	enum Type {
			UE, ENB, UNKNOWN
	};

	InterferPhantom(Ptr<Position> p, Ptr<const SpectrumValue> txPsd, Ptr<AntennaModel> antenna, Type t);
	virtual ~InterferPhantom();



	/**
	 * Register this type.
	 * \return The TypeId.
	 */
	static TypeId GetTypeId(void);

	/**
	 * xxxx.
	 *
	 * @param p the position
	 */
	void setPosition(Ptr<Position> p);

	/**
	 * xxxx.
	 *
	 * @param
	 */
	Ptr<Position> getPosition();

	/**
	 * xxxx.
	 *
	 * @param
	 */
	Ptr<const SpectrumValue> getTxPower();

	/**
	 * xxxx.
	 *
	 * @param
	 */
	Ptr<AntennaModel> getAntenaModel();

	bool isTransmitting();

protected:
	void DoDispose();

private:

	Ptr<Position> m_position;

	Ptr<const SpectrumValue> m_txPower;

	Ptr<AntennaModel> m_antenna;

	Type m_type;

	bool m_transmitting; //!< True if transmittings


};

} // namespace ns3


#endif /* INTERFERER_PHANTOM_H */
