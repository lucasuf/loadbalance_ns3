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

#ifndef POSITION_H
#define POSITION_H

#include <ns3/object.h>
#include <vector>

using namespace std;

namespace ns3 {

class Position: public Object {
public:
	Position(double x, double y, double z);
	virtual ~Position();

	/**
	 * Register this type.
	 * \return The TypeId.
	 */
	static TypeId GetTypeId(void);

	vector<double> getPosition();

	void setPosition(double x, double y, double z);

protected:
	void DoDispose();

private:
	vector<double> m_pos;

};

} // namespace ns3


#endif /* POSITION_H */
