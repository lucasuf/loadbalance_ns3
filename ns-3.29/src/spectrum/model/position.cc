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

#include "position.h"

#include <ns3/simulator.h>
#include <ns3/log.h>

namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("Position");

Position::Position(double x, double y, double z) {
	m_pos = vector<double> (3);
	m_pos[0] = x;
	m_pos[1] = y;
	m_pos[2] = z;

	NS_LOG_FUNCTION (this);
}

Position::~Position() {
	NS_LOG_FUNCTION (this);
}

TypeId Position::GetTypeId() {
	static TypeId tid = TypeId("ns3::Position") .SetParent<Object> () .SetGroupName("Spectrum");
	return tid;
}

void Position::DoDispose() {
	NS_LOG_FUNCTION (this);
	m_pos = vector<double> (3);
	m_pos[0] = 0.0;
	m_pos[1] = 0.0;
	m_pos[2] = 0.0;
	Object::DoDispose();
}

vector<double> Position::getPosition() {
	return m_pos;
}

void Position::setPosition(double x, double y, double z) {
	m_pos[0] = x;
	m_pos[1] = y;
	m_pos[2] = z;
}

} // namespace ns3


