MAC
==================================================================================================
MAC layer is implemented as per-project driver and does not have specific common implementation here.
Common headers are in ESPLATFORM_NETWORK_STACK_v1\ES_SAT_MAC\


Modules API (inter-sat communication)
==================================================================================================
In order to use API :
x. clone ESPLATFORM_NETWORK_STACK_v1 as a sub-repo with dir name ESPLATFORM_NETWORK_STACK somewhere in your module repo.
x. copy private\ESSA_StackConfig.h to your project and customize it.
x. Include ESSA_Stack.c/h to your project.
x. Also include what modules are needed in your project from "include" and "source" dirs
x. If your project is provider of the service, use private/ESSA_LED.c as example how to connect to the API (struct names must be prepended with ESSA_)
x. Provide ESSATMAC_GetModuleAddr function declared in ES_SAT_MAC.h
x. Provide ESSATMAC_EnqMessage  function declared in ES_SAT_MAC.h - connect to your ES MAC Driver implementation.
x. Make sure your MAC driver call ESSA_Stack_DataDispatch on message reception, to dispatch message through the stack.

Service Protocol over MAC layer (inter-sat communication)
==================================================================================================
1. Description/Function
	Service Protocol is designed to support the very basic back-bone of satellite modules operation, configuration and provisioning.
	For all modules that want to support direct communication with Ground Station this protocol is mandatory (for now).
	Common GUI application will be developed over this protocol to expose some of the functions below to the end user.
	Implemented functionality :
	- Reliable Discovery Protocol with ability to filter devices with specific parameters (operation mode, type, "master" devices in configuration of two or more)
	- Remote restart of modules in different modes.
	- Remote set module MAC address by module serial number.
	- Set module initial configuration after JTAG programming (Module : Type, HWConfig, HWRevision, Serial Number)
	- Prepare and Enter Ship mode.
	- Collect GS command statuses for all modules. This one will be moved to GS protocols later on.
	- To be considered adding : common frequent broadcast for power supply with battery status, common frequent broadcast for current ConOps.
	- Configurable to work with stack defined channel names (ESSASNI_SYS_PRI etc)
	- Each operation may be started simultaneously (except set MAC address) on several MAC channels.
	- No operation will start internally on several channels.
	- Optional functionalities as well as used channels can be disabled to conserve RAM/ROM/CPU.
	
2. Dependencies
	This protocol is designed to be on top of MAC layer, but it uses our stack.
	MAC Driver send notification also must work inside driver at 100%.
	It should be called on success or failure of each request to send message (provided that callback is set).
	Task function should be called at least within 100-200 ms time period
	Be careful not to issue too many discovery requests one after another, since it may flood network.
	If all devices should be enumerated, use intervals of at least 30 sec between requests.
	
3. Integration
	Add files to your project :
	ESPLATFORM_NETWORK_STACK\ES_SAT_API\include\ESSA_ServiceProtocol_Types.h (as link)
	ESPLATFORM_NETWORK_STACK\ES_SAT_API\Source\ESSA_ServiceProtocol_Impl.h (as link)
	ESPLATFORM_NETWORK_STACK\ES_SAT_API\Source\ESSA_ServiceProtocol_Impl.c (as link)
	ESPLATFORM_NETWORK_STACK\ES_SAT_API\Source\ESSA_ServiceProtocol_Impl_CCP.h (as link)
	ESPLATFORM_NETWORK_STACK\ES_SAT_API\Source\ESSA_ServiceProtocol_Impl_CCP.c (as link)
	ESPLATFORM_NETWORK_STACK\ES_SAT_API\private\ESSA_ServiceProtocol_Handler.h (Copy to your project)
	ESPLATFORM_NETWORK_STACK\ES_SAT_API\private\ESSA_ServiceProtocol_Handler.c (Copy to your project and customize needed callbacks)

	Additions to ESSA_StackConfig.h local project file (usual module configuration):
	// General Enable/Disable of internal MAC network channels
	#define ESSA_SYS_PRI_ENABLED
	//#define ESSA_SYS_SEC_ENABLED
	//#define ESSA_PAY_PRI_ENABLED
	//#define ESSA_PAY_SEC_ENABLED

	#define ESSASP_TickGet16					TickGet16	/* return 16 bit tick timer from system restart */
	#define ESSASP_ASSERT						ASSERT  	/* or ((void)0) if not used */

	//#define ESSASP_SUPPORT_DISCOVERY_CLIENT
	//#define ESSASP_SUPPORT_SET_REMOTE_DEVICE_MAC_ADDR
	//#define ESSASP_SUPPORT_GS_CMD_CLIENT
	#define ESSASP_SUPPORT_GS_CMD_SERVER

	Add ESSASP_ServiceProtocolHook to FS_PROTOCOL_HANDLERS_LIST
	
	Operation :
	Call ESSA_SP_Init,  ESSA_SP_Task & ESSA_SP_Exit from your local ESSA_ServiceProtocol_Handler.h as appropriate.
	ESSA_SP_Init should be called before ESSA_Stack_Init()
	Call ESSASP_SendAnnounce after device restart for each available interface.
	These will be moved to be automatic in stack, once we convert it to real stack.
	You need to include only ESSA_ServiceProtocol_Impl.h where you will use protocol functionality.

