/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c)
 *
 * Author: Juliano J. Bazzo <jjbazzo@gmail.com>
 */

#include <ns3/mobility-model.h>
#include <ns3/log.h>
#include <ns3/lte450-spectrum-propagation-loss.h>
#include <cmath> // for M_PI


namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("LTE450SpectrumPropagationLossModel");

NS_OBJECT_ENSURE_REGISTERED (LTE450SpectrumPropagationLossModel);


LTE450SpectrumPropagationLossModel::LTE450SpectrumPropagationLossModel ()
{
}

LTE450SpectrumPropagationLossModel::~LTE450SpectrumPropagationLossModel ()
{
}


TypeId
LTE450SpectrumPropagationLossModel::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::LTE450SpectrumPropagationLossModel")
    .SetParent<SpectrumPropagationLossModel> ()
    .AddConstructor<LTE450SpectrumPropagationLossModel> ()
  ;
  return tid;
}


Ptr<SpectrumValue>
LTE450SpectrumPropagationLossModel::DoCalcRxPowerSpectralDensity (Ptr<const SpectrumValue> txPsd,
                                                                 Ptr<const MobilityModel> a,
                                                                 Ptr<const MobilityModel> b) const
{
  Ptr<SpectrumValue> rxPsd = Copy<SpectrumValue> (txPsd);
  Values::iterator vit = rxPsd->ValuesBegin ();
  Bands::const_iterator fit = rxPsd->ConstBandsBegin ();

  NS_ASSERT (a);
  NS_ASSERT (b);

  double d = a->GetDistanceFrom (b);

  double lossSingleRB = CalculateLoss (d);

  while (vit != rxPsd->ValuesEnd ())
    {
      NS_ASSERT (fit != rxPsd->ConstBandsEnd ());
      *vit /= lossSingleRB; // Prx = Ptx / loss
      ++vit;
      ++fit;
    }
  return rxPsd;
}


double
LTE450SpectrumPropagationLossModel::CalculateLoss (double d) const
{
  NS_ASSERT (d >= 10.0);

  /*
  	 * Model from field measurements close to Campinas-SP Brazil.
  	 * L = 117.46 + 24.0*log(d)
  	 */
  	double distInKM = d / 1000.0;

  	//Henb=150m. ITU
  	//double loss = 25.88 + 24.62*log10(distanceInM);

  	//Henb=75m. ITU
  	double loss = 88.6442+39.5814*log10(distInKM);
    NS_LOG_LOGIC ("loss(lte450ITU) = " << loss << " dB");

  	loss = pow(10.0,loss/10.0);

    if (loss < 1)
    {
      loss = 1;
    }

  return loss;
}

}  // namespace ns3
