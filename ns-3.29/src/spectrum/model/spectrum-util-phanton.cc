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


#include "spectrum-util-phantom.h"

#include <ns3/simulator.h>
#include <ns3/log.h>


namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("SpectrumUtilPhantom");

SpectrumUtilPhantom::SpectrumUtilPhantom ()
{
  NS_LOG_FUNCTION (this);
}

SpectrumUtilPhantom::~SpectrumUtilPhantom ()
{
  NS_LOG_FUNCTION (this);
}

TypeId
SpectrumUtilPhantom::GetTypeId ()
{
  static TypeId tid = TypeId ("ns3::SpectrumUtilPhantom")
    .SetParent<Object> ()
    .SetGroupName ("Spectrum")
    .AddConstructor<SpectrumUtilPhantom> ()
    ;
  return tid;
}

void
SpectrumUtilPhantom::DoDispose ()
{
  NS_LOG_FUNCTION (this);
  Object::DoDispose ();
}

double
getDistance(Position a, Position b)
{
	//TODO: implement euclidean distance
	double d = 0.0;
	return d;
}

} // namespace ns3


