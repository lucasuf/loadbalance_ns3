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


#ifndef SPECTRUM_UTIL_PHANTON_H
#define SPECTRUM_UTIL_PHANTON_H

#include <ns3/object.h>
#include "ns3/position.h
#include <vector>

namespace ns3 {

class SpectrumUtilPhantom : public Object
{
	public:
	  SpectrumUtilPhantom ();
	  virtual ~SpectrumUtilPhantom ();


	  /**
	   * Register this type.
	   * \return The TypeId.
	   */
	  static TypeId GetTypeId (void);

	  static double getDistance(Position a, Position b);

	protected:
	  void DoDispose ();

	private:
};


} // namespace ns3





#endif /* SPECTRUM_UTIL_PHANTON_H */
