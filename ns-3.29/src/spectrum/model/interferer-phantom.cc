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

#include "interferer-phantom.h"

#include <ns3/simulator.h>
#include <ns3/log.h>
#include <ns3/position.h>

namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("InterferPhantom");


InterferPhantom::InterferPhantom(Ptr<Position> p, Ptr<const SpectrumValue> txPsd, Ptr<AntennaModel> antenna, Type t)
:m_position(p),
 m_txPower(txPsd),
 m_antenna(antenna),
 m_type(t),
 m_transmitting(false) {
	NS_LOG_FUNCTION (this);
}

InterferPhantom::~InterferPhantom() {
	NS_LOG_FUNCTION (this);
}

TypeId InterferPhantom::GetTypeId() {
	static TypeId tid = TypeId("ns3::InterferPhantom") .SetParent<Object> () .SetGroupName("Spectrum");
	return tid;
}

void InterferPhantom::DoDispose() {
	NS_LOG_FUNCTION (this);
	//m_position = new Ptr<Position>(0.0, 0.0, 0.0); //TODO
	m_txPower = 0;
	m_antenna = 0;
	m_type = UNKNOWN;
	m_transmitting = false;
	Object::DoDispose();
}

void InterferPhantom::setPosition(Ptr<Position> p) {
	m_position = p;
}

Ptr<Position> InterferPhantom::getPosition() {
	return m_position;
}

Ptr<const SpectrumValue> InterferPhantom::getTxPower() {
	return m_txPower;
}

Ptr<AntennaModel> InterferPhantom::getAntenaModel() {
	return m_antenna;
}

bool InterferPhantom::isTransmitting() {
	return m_transmitting;
}

} // namespace ns3


