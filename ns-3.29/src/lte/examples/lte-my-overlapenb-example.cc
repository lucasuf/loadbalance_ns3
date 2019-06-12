/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) jjbazzo
 *
 * Author: Juliano J. Bazzo <jbazzo@gmail.com>
 */

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/lte-module.h"
#include "ns3/config-store.h"
#include "ns3/radio-bearer-stats-calculator.h"
#include "ns3/log.h"
#include "ns3/config-store-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-helper.h"
#include "ns3/applications-module.h"
#include "ns3/constant-velocity-mobility-model.h"
#include "ns3/ptr.h"
#include "ns3/multi-model-spectrum-channel.h"
#include "ns3/spectrum-helper.h"
#include "ns3/nstime.h"
#include "ns3/antenna-model.h"
#include "ns3/ipv4-interface-container.h"
#include "ns3/udp-socket-factory.h"
#include "ns3/tcp-socket-factory.h"
#include "ns3/on-off-helper.h"
//#include "ns3/random-variable-stream-helper.h"
#include "ns3/random-variable-stream.h"

#include <vector>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <string>

using namespace ns3;
using namespace std;
NS_LOG_COMPONENT_DEFINE("lte-my-overlapenb-example");


vector<Vector> getCellsPosition(int nCells) {
	vector<Vector> cellPosit(nCells);
	assert(nCells > 0);

	for (int i = 0; i < nCells; i++) {
		cellPosit[i] = Vector(0.0, 0.0, 0.0);
	}

	return cellPosit;
}



/**
 * This simulation script creates two eNodeBs at the same place.
 */
int main(int argc, char *argv[]) {

	//IMPORTANT: These are the default parameters if no overwritten by the command line.
	//Otherwise, you have to check the command line parameters like:
	//--ns3::ConfigStore::Filename=input-lte450.txt
	//--ns3::ConfigStore::Mode=Load --ns3::ConfigStore::FileFormat=RawText
	//--numUes=5 --useFixedDist=1 --distFixedUEs=17678

	//System
	double antBeamwidth = 90.0; //degree (ignored for single cell)
	//double antBeamwidth = 120.0; //degree
	double antMaxGain = 14.0; //dBi
	double ueRXAntennaGain = 3.0; //dBi
	int ueAllowedAreaCoef = 4; //It means that the UE can move in a square area
	//of 4 times radius x 4 times radius

	//string ueMobilityModel = "ns3::RandomDirection2dMobilityModel";
	string ueMobilityModel = "ns3::ConstantPositionMobilityModel";
	//string ueSpeed = "0.83"; //3 km/h
	string ueSpeed = "0.0"; //for static user
	double logEpoch = 0.25; //s
	double simDuration = 12.0;
	Time simTime = Seconds(simDuration); //check
	int srsPeriodicity = 40; //Allowed values: 2 5 10 20 40=default 80 160 320
	int transmissionMode = 2; //2=mimo, 0=siso


	vector<int> dlEarfcn{3100, 3100}; //for more than 2, update this
	vector<int> ulEarfcn{21100, 21100};

	///////////////////////////////////////////////////////////////////
	//This variables can be changed by input parameters. TAKE CARE!!
	///////////////////////////////////////////////////////////////////
	//System
	double cellRadius = 10000.0;
	int nCells = 2;
	int nSectors = 1; //if 1, the antenna wilsimSeedl be omnidirectional.
	double ueDistrRadius = 1 * cellRadius; //the area that the UEs will be dropped.
	uint32_t numUesBE = 1; //total number of UEs with BE (UDP)
	uint32_t numUesVoIP = 1; // total number of VoIP UEs

	//Used for UDP traffic generator.
	double interPacketInterval = 30; //ms
	double maxPacketSize = 1480; //bytes
	int simSeed = 1;
	///////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////


	//ATTENTION: These variables can be changed.
	CommandLine cmd;
	cmd.AddValue("numUesBE", "number of BE ues", numUesBE);
	cmd.AddValue("numUesVoIP", "number of VoIP ues", numUesVoIP);
	cmd.AddValue("nCells", "number of cells", nCells);
	cmd.AddValue("nSectors", "number of sectors", nSectors);
	cmd.AddValue("interPacketInterval", "pkg interv in ms", interPacketInterval);
	cmd.AddValue("maxPacketSize", "pkg size in bytes", maxPacketSize);
	cmd.AddValue("cellRadius", "the cell radius", cellRadius);
	cmd.AddValue("ueDistrRadius", "the user distribution radius", ueDistrRadius);
	cmd.AddValue("simSeed", "simulation seed", simSeed);

	cmd.Parse(argc, argv);
	std::cout << "after parse" << std::endl;

	RngSeedManager::SetSeed(simSeed);

	int numUes = numUesBE + numUesVoIP; //total number of UEs
	int nENBs = nCells * nSectors;

	vector<double> sectorsOrientVec(nSectors);
	double orientDivision = 360.0 / nSectors;
	for (int n = 0; n < nSectors; n++) {
		sectorsOrientVec[n] = orientDivision * n;
	}

	ConfigStore inputConfig;
	inputConfig.ConfigureDefaults();

	// parse again so you can override default values from the command line
	cmd.Parse(argc, argv);

	Rectangle recArea(-ueAllowedAreaCoef * cellRadius, ueAllowedAreaCoef * cellRadius, -ueAllowedAreaCoef * cellRadius, ueAllowedAreaCoef * cellRadius);

	double ueTput = maxPacketSize * 8.0 * 1000 / interPacketInterval;
	std::cout << "UE tput [kbps]:" << ueTput << std::endl;

	//MaxPacketSize = round(ueTput * interPacketInterval / (8.0 * 1000.0));

	Config::SetDefault("ns3::LteEnbRrc::SrsPeriodicity", UintegerValue(srsPeriodicity));
	Config::SetDefault("ns3::LteEnbRrc::DefaultTransmissionMode", UintegerValue(transmissionMode)); // 2=MIMO Spatial Multiplexity (2 layers)
	Config::SetDefault("ns3::IsotropicAntennaModel::Gain", DoubleValue(ueRXAntennaGain));

	UintegerValue runValue;
	GlobalValue::GetValueByName("RngRun", runValue);

	std::ostringstream tag;
	tag << "_radius" << std::setw(3) << std::setfill('0') << std::fixed << std::setprecision(0) << cellRadius << "_numUes" << std::setw(3) << std::setfill('0')
			<< numUes << "_rngRun" << std::setw(3) << std::setfill('0') << runValue.Get();

	Ptr<LteHelper> lteHelper = CreateObject<LteHelper> ();
	Ptr<PointToPointEpcHelper> epcHelper = CreateObject<PointToPointEpcHelper> ();
	lteHelper->SetEpcHelper(epcHelper);
	//lteHelper->SetSchedulerType("ns3::RrFfMacScheduler");
	//lteHelper->SetHandoverAlgorithmType ("ns3::NoOpHandoverAlgorithm"); // disable automatic handover

	//Enable the fast fading. This file is generated from a .m script.
	//TODO: The fading file below is just an example.
	lteHelper->SetAttribute("FadingModel", StringValue("ns3::TraceFadingLossModel"));
	std::ifstream ifTraceFile;
	ifTraceFile.open("../../src/lte/model/fading-traces/fading_trace_EPA_3kmph.fad", std::ifstream::in);
	lteHelper->SetFadingModelAttribute("TraceFilename", StringValue("src/lte/model/fading-traces/fading_trace_EPA_3kmph.fad"));


	//Set eNB position
	Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
	vector<Vector> cellsPosit = getCellsPosition(nCells);
	cout << nENBs << " eNodeBs with positions..." << endl;
	int k = 0;
	for (int i = 0; i < nCells; i++) {
		for (int j = 0; j < nSectors; j++) {
			//Create the UEs for each ue container.
			//ueNodeContVec[i*nSectors+j].Create(numUes);
			if (nSectors > 1) {
				lteHelper->SetEnbAntennaModelType("ns3::CosineAntennaModel");
			}
			positionAlloc->Add(cellsPosit[i]);
			cout << "eNodeB(" << k << "):" << cellsPosit[i].x << ", " << cellsPosit[i].y << ", " << cellsPosit[i].z << endl;
			k++;
		}
	}

	// Create the node containers. A node container is a set of nodes.
	// Each eNB Node has a container of UEs.
	NodeContainer enbNodesCont;
	enbNodesCont.Create(nENBs);
	//Create the mobility model for the eNB. It wouldn't make sense to have
	//a mobile eNB but the simulator gives this opportunity.
	MobilityHelper enbMobility;
	//The eNodeBs are static of course.
	enbMobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	//enbMobility.SetMobilityModel("ns3::RandomDirection2dMobilityModel");
	enbMobility.SetPositionAllocator(positionAlloc);
	enbMobility.Install(enbNodesCont);

	//Create the UEs for each ue container.
	NodeContainer ueNodeCont;
	ueNodeCont.Create(numUes);
	//Create the mobility model for the UEs.
	//The bounds means that the UE won't cross this border.
	//This value must be calibrated with the hexagonal grid size.
	//The maximum is 4*radius so far.
	//The speed is in m/s and must be aligned with the fading parameters.
	MobilityHelper mobHelper;
	mobHelper.SetPositionAllocator("ns3::UniformDiscPositionAllocator", "X", DoubleValue(0.0), "Y", DoubleValue(0.0), "rho", DoubleValue(ueDistrRadius));
	//if you want to drop the user in a fixed location, use the code below.
	//	mobHelper.SetPositionAllocator("ns3::UniformDiscPositionAllocator", "X",
	//			DoubleValue(8000.0), "Y", DoubleValue(9000.0), "rho",
	//			DoubleValue(500));

	//TODO: The mobility model for the use can be changed.
	// Other options are ns3::RandomDirection2dMobilityModel"

	if (ueMobilityModel.compare("ns3::RandomDirection2dMobilityModel") == 0) {
		assert(ueSpeed.compare("0.0") != 0 && "This model must be used with speed greater than 0");
		mobHelper.SetMobilityModel(ueMobilityModel, "Bounds", RectangleValue(recArea), "Speed",
				StringValue("ns3::ConstantRandomVariable[Constant=" + ueSpeed + "]"));
	} else if (ueMobilityModel.compare("ns3::ConstantPositionMobilityModel") == 0) {
		assert(ueSpeed.compare("0.0") == 0 && "This model must be with static UE");
		mobHelper.SetMobilityModel(ueMobilityModel);
	} else {
		assert(false && "Invalid mobility model");
	}

	mobHelper.Install(ueNodeCont);
	cout << ueNodeCont.GetN() << " UEs with positions..." << endl;

	for (unsigned int w = 0; w < ueNodeCont.GetN(); w++) {
		Ptr<MobilityModel> m = ueNodeCont.Get(w)->GetObject<MobilityModel> ();
		Vector v = m->GetPosition();
		cout << "UE(" << w << "):" << v.x << ", " << v.y << ", " << v.z << endl;
	}

	Ptr<Node> pgw = epcHelper->GetPgwNode();

	// Create a single RemoteHost
	NodeContainer remoteHostContainer;
	remoteHostContainer.Create(1);
	Ptr<Node> remoteHost = remoteHostContainer.Get(0);
	InternetStackHelper internet;
	internet.Install(remoteHostContainer);

	// Create the Internet
	PointToPointHelper p2ph;
	p2ph.SetDeviceAttribute("DataRate", DataRateValue(DataRate("100Gb/s")));
	p2ph.SetDeviceAttribute("Mtu", UintegerValue(1500));
	p2ph.SetChannelAttribute("Delay", TimeValue(Seconds(0.010)));
	NetDeviceContainer internetDevices = p2ph.Install(pgw, remoteHost);
	Ipv4AddressHelper ipv4h;
	ipv4h.SetBase("1.0.0.0", "255.0.0.0");
	Ipv4InterfaceContainer internetIpIfaces = ipv4h.Assign(internetDevices);
	Ipv4Address remoteHostAddr = internetIpIfaces.GetAddress(1);

	// Routing of the Internet Host (towards the LTE network)
	Ipv4StaticRoutingHelper ipv4RoutingHelper;
	Ptr<Ipv4StaticRouting> remoteHostStaticRouting = ipv4RoutingHelper.GetStaticRouting(remoteHost->GetObject<Ipv4> ());
	// interface 0 is localhost, 1 is the p2p device
	remoteHostStaticRouting->AddNetworkRouteTo(Ipv4Address("7.0.0.0"), Ipv4Mask("255.0.0.0"), 1);


	// Install LTE Devices in eNB and UEs
	NetDeviceContainer enbNetDevCont = lteHelper->InstallEnbDevice(enbNodesCont);
	NetDeviceContainer ueNetDevCont = lteHelper->InstallUeDevice(ueNodeCont);


	//Set add the antennas
	cout << "Set the antenna for each eNodeB." << endl;

	for (int i = 0; i < nCells; i++) {
		for (int j = 0; j < nSectors; j++) {
			int idx = i * nSectors + j;
			Ptr<LteEnbNetDevice> dev = enbNetDevCont.Get(idx)->GetObject<LteEnbNetDevice> ();
			dev->SetDlEarfcn (dlEarfcn[idx]);
			dev->SetUlEarfcn (ulEarfcn[idx]);

			Ptr<LteEnbPhy> enbPhy = dev->GetPhy();
			if (nSectors > 1) { // If a single sector, the antenna would be omnidirectional.
				cout << "Orientation: " << sectorsOrientVec[j] << endl;
				enbPhy->GetDownlinkSpectrumPhy()->GetRxAntenna()->SetAttribute("Orientation", DoubleValue(sectorsOrientVec[j]));
				enbPhy->GetDownlinkSpectrumPhy()->GetRxAntenna()->SetAttribute("Beamwidth", DoubleValue(antBeamwidth));
				enbPhy->GetDownlinkSpectrumPhy()->GetRxAntenna()->SetAttribute("MaxGain", DoubleValue(antMaxGain));
			}
		}
	}

	// Install the IP stack on the UEs
	internet.Install(ueNodeCont);
	Ipv4InterfaceContainer ueIpIfaces;
	ueIpIfaces = epcHelper->AssignUeIpv4Address(NetDeviceContainer(ueNetDevCont));

	//Important change that is not in the base code.
	//The UE is attached with the best eNodeB in terms of RX power.
	lteHelper->AttachRXPowerEnb(ueNetDevCont, enbNetDevCont);

	for (int i = 0; i < (int) ueNodeCont.GetN(); i++) {
		Ptr<Node> ueNode = ueNodeCont.Get(i);

		// Set the default gateway
		Ptr<Ipv4StaticRouting> ueStaticRouting = ipv4RoutingHelper.GetStaticRouting(ueNode->GetObject<Ipv4> ());
		ueStaticRouting->SetDefaultRoute(epcHelper->GetUeDefaultGatewayAddress(), 1);
	}

	// randomize a bit start times to avoid simulation artifacts
	// (e.g., buffer overflows due to packet transmissions happening
	// exactly at the same time)
	Ptr<UniformRandomVariable> startTimeSeconds = CreateObject<UniformRandomVariable> ();
	startTimeSeconds->SetAttribute("Min", DoubleValue(0.05));
	startTimeSeconds->SetAttribute("Max", DoubleValue(0.06));

	////////////////////////INSTALL UEs////////////////////

	// Install and start applications on UEs and remote host
	uint16_t dlPort = 10000;
	uint16_t ulPort = 20000;
	bool disableDl = false;
	bool disableUl = false;
	uint16_t numBearersPerUe = 2;

	// Create the bearers.
	// It is going to be associated for each UE afterward.
	enum EpsBearer::Qci qngbr = EpsBearer::NGBR_VIDEO_TCP_DEFAULT; //QCI=9
	EpsBearer bearerngbr(qngbr);
	enum EpsBearer::Qci gbr = EpsBearer::GBR_CONV_VOICE; //QCI=1
	EpsBearer bearergbr(gbr);


	for (uint32_t u = 0; u < (uint32_t) numUes; ++u) {
		Ptr<Node> ue = ueNodeCont.Get(u);
		// Set the default gateway for the UE
		Ptr<Ipv4StaticRouting> ueStaticRouting = ipv4RoutingHelper.GetStaticRouting(ue->GetObject<Ipv4> ());
		ueStaticRouting->SetDefaultRoute(epcHelper->GetUeDefaultGatewayAddress(), 1);

		for (uint32_t b = 0; b < numBearersPerUe; ++b) {
			ApplicationContainer clientApps;
			ApplicationContainer serverApps;
			Ptr<EpcTft> tft = Create<EpcTft> ();

			if (!disableDl) {
				++dlPort;

				if (u < numUesBE) {
					NS_LOG_LOGIC ("installing UDP DL app for UE " << u);
					UdpClientHelper dlClientHelper(ueIpIfaces.GetAddress(u), dlPort);
					clientApps.Add(dlClientHelper.Install(remoteHost));
					lteHelper->ActivateDedicatedEpsBearer(ueNetDevCont.Get(u), bearerngbr, tft);
				} else { // for non BE (VoIP for instance)  - Parameters neeed to be adjusted
					OnOffHelper dlClientHelper("ns3::UdpSocketFactory", Address(InetSocketAddress(ueIpIfaces.GetAddress(u), dlPort)));
					dlClientHelper.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=1.0]"));
					dlClientHelper.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=1.0]"));
					dlClientHelper.SetAttribute("PacketSize", UintegerValue(100));
					//		//onOffAP.SetAttribute("DataRate", DoubleValue (3.0e6));
					dlClientHelper.SetAttribute("DataRate", StringValue("8kbps"));
					clientApps.Add(dlClientHelper.Install(remoteHost));
					lteHelper->ActivateDedicatedEpsBearer(ueNetDevCont.Get(u), bearergbr, tft);
				}

				PacketSinkHelper dlPacketSinkHelper("ns3::UdpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), dlPort));
				serverApps.Add(dlPacketSinkHelper.Install(ue));

				EpcTft::PacketFilter dlpf;
				dlpf.localPortStart = dlPort;
				dlpf.localPortEnd = dlPort;
				tft->Add(dlpf);
			}

			if (!disableUl) {
				++ulPort;

				if (u < numUesBE) {
					NS_LOG_LOGIC ("installing UDP UL app for UE " << u);
					UdpClientHelper ulClientHelper(remoteHostAddr, ulPort);
					clientApps.Add(ulClientHelper.Install(ue));
					lteHelper->ActivateDedicatedEpsBearer(ueNetDevCont.Get(u), bearerngbr, tft);
				} else { // for non BE (VoIP for instance) - Parameters neeed to be adjusted
					OnOffHelper ulClientHelper("ns3::UdpSocketFactory", Address(InetSocketAddress(remoteHostAddr, ulPort)));
					ulClientHelper.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=1.0]"));
					ulClientHelper.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=1.0]"));
					ulClientHelper.SetAttribute("PacketSize", UintegerValue(100));
					//		//onOffAP.SetAttribute("DataRate", DoubleValue (3.0e6));
					ulClientHelper.SetAttribute("DataRate", StringValue("9kbps"));
					clientApps.Add(ulClientHelper.Install(ue));
					lteHelper->ActivateDedicatedEpsBearer(ueNetDevCont.Get(u), bearergbr, tft);
				}

				PacketSinkHelper ulPacketSinkHelper("ns3::UdpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), ulPort));
				serverApps.Add(ulPacketSinkHelper.Install(remoteHost));

				EpcTft::PacketFilter ulpf;
				ulpf.remotePortStart = ulPort;
				ulpf.remotePortEnd = ulPort;
				tft->Add(ulpf);
			}

			//EpsBearer bearer(EpsBearer::NGBR_VIDEO_TCP_DEFAULT);
			//lteHelper->ActivateDedicatedEpsBearer(ueNetDevCont.Get(u), bearer, tft);

			Time startTime = Seconds(startTimeSeconds->GetValue());
			serverApps.Start(startTime);
			clientApps.Start(startTime);
			clientApps.Stop(simTime);

		}
	}

	//Simulator::Schedule (Seconds(simDuration), &MyStats::PrintStatsMMS, vecMmsUtil);
	Simulator::Stop(simTime);

	// Insert RLC Performance Calculator
	std::string dlOutFname = "DlRlcStats";
	dlOutFname.append(tag.str());
	std::string ulOutFname = "UlRlcStats";
	ulOutFname.append(tag.str());

	//lteHelper->EnablePhyTraces ();
	lteHelper->EnableMacTraces();
	lteHelper->EnableRlcTraces();
	lteHelper->EnablePdcpTraces();
	//lteHelper->GetPdcpStats()->SetEpoch(TimeValue (Seconds (1.0)));
	lteHelper->GetPdcpStats()->SetEpoch(Seconds(logEpoch));

	//p2ph.EnablePcap ("my-pcap-file.pcap", internetDevices, true);

	cout << "Running the simulation..." << endl;
	Simulator::Run();
	Simulator::Destroy();
	return 0;
}

