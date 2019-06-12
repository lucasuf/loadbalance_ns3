/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c)
 *
 * Author: Juliano J. Bazzo <jjbazzo@gmail.com>
 */

#ifndef LTE450_SPECTRUM_PROPAGATION_LOSS_H
#define LTE450_SPECTRUM_PROPAGATION_LOSS_H


#include <ns3/spectrum-propagation-loss-model.h>


namespace ns3 {

class MobilityModel;


/**
 * \ingroup spectrum
 *
 */
class LTE450SpectrumPropagationLossModel : public SpectrumPropagationLossModel
{

public:
  LTE450SpectrumPropagationLossModel ();
  ~LTE450SpectrumPropagationLossModel ();

  static TypeId GetTypeId ();


  virtual Ptr<SpectrumValue> DoCalcRxPowerSpectralDensity (Ptr<const SpectrumValue> txPsd,
                                                           Ptr<const MobilityModel> a,
                                                           Ptr<const MobilityModel> b) const;


  /**
   * Return the propagation loss L according to the formula
   * in which antenna gains are unitary:
   *
   *      (4 * pi * d * f) ^ 2
   * L = ----------------------
   *               C^2
   *
   * where C = 3e8 m/s is the light speed in the vacuum. The intended
   * use is to calculate Prx = Ptx * G
   *
   * @param f frequency in Hz
   * @param d distance in m
   *
   * @return if Prx < Ptx then return Prx; else return Ptx
   */
  double CalculateLoss (double d) const;

protected:
  double m_propagationSpeed;

};






} // namespace ns3

#endif /* LTE450_SPECTRUM_PROPAGATION_LOSS_H */
