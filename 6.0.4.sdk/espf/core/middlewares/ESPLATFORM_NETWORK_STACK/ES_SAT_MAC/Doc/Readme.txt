To be considered for MAC Gen3.

Latest tests of MAC network, reveal that we are not as efficient as we want detecting network collisions.
Only ~5% of collisions (of 5% collisions) are actually detected (ESPLATFORM_NETWORK_STACK\ES_SAT_MAC\NetworkTests_NewMAC\Test_1_FIX_HI_PRI_10h.xlsx)
Messages randomisation span is not big enough.
Once we make repeat of messages on all protocols above MAC layer, we can optimize network by :
	
	1. Lower priorities count to just HIGH, NORMAL & LOW and make priority and random span from 4TQ to 6TQ
		- Expected throughput will be supposedly as it is now.
	2. Remove collision detection from MAC driver.
		- Increased RS485 compatibility with third party devices
		- Simplify MAC driver logic, thus we may be able to increase communication speed (tests needed)

With these changes, compatibility should be preserved with current network, so we can gradually update devices even on sat.
