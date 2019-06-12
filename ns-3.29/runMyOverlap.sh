#######################################################
#
#  Copyright (c)
#
# Author: Juliano J. Bazzo <jjbazzo@gmail.com>
#######################################################


date
rm teste.txt

#export NS_LOG="*=level_all|prefix_func|prefix_time" 
#export NS_LOG="*=prefix_func|prefix_time" 

#export 'NS_LOG=MmsServer=level_all|prefix_func|prefix_time:MmsClient=level_all|prefix_func|prefix_time:MmsAdaptServer=level_all|prefix_func|prefix_time:MmsAdaptClient=level_all|prefix_func|prefix_time:CotpServer=level_all|prefix_func|prefix_time:CotpClient=level_all|prefix_func|prefix_time' 

#The total number of UEs
#NBUE_BE=(2 10 30 50)
#NBUE_MM=(2 5 7 10)
NBUE_BE=(2)
NBUE_MM=(2)

#Cell radius in m
CELLRADIUS=2000

#Number of nCells
NCELLS=2

#The number of sectors
NSECTORS=1

#UE drop radius in m
UEDISTRADIUS=2000

#package interval in ms
PKGINT=30

#package interval in ms
PKGSIZE=1480

MYPATH=output/sim
MYBIN=lte-my-overlapenb-example
CONFIGFILE=input-my-overlap.txt

	for nuebe in "${NBUE_BE[@]}"
	do
		for nuemm in "${NBUE_MM[@]}"
		do
			time ./waf --run src/lte/examples/$MYBIN --command-template="%s --ns3::ConfigStore::Filename=$CONFIGFILE --ns3::ConfigStore::Mode=Load --ns3::ConfigStore::FileFormat=RawText --numUesBE=${nuebe} --numUesVoIP=${nuemm} --nCells=$NCELLS --cellRadius=$CELLRADIUS --nSectors=$NSECTORS --ueDistrRadius=$UEDISTRADIUS --interPacketInterval=$PKGINT --maxPacketSize=$PKGSIZE"
			mv DlMacStats.txt $MYPATH/DlMac_${nue}_${distue}.csv
			mv DlPdcpStats.txt $MYPATH/DlPdcp_${nue}_${distue}.csv
			mv DlRlcStats.txt $MYPATH/DlRlc_${nue}_${distue}.csv
			mv UlMacStats.txt $MYPATH/UlMac_${nue}_${distue}.csv
			mv UlPdcpStats.txt $MYPATH/UlPdcp_${nue}_${distue}.csv
			mv UlRlcStats.txt $MYPATH/UlRlc_${nue}_${distue}.csv
		done
	done
date



