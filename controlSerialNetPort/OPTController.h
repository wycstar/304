


/*************************************************
Copyright (C), 2005 OPT MACHINE VISION TECH CO.,LTD. All rights reserved.
Version: 1.0.0          
Date: 2014.10.7         
Description: the set of functions that exported for the controller to control light source, such as turn on/off the light source, 
             adjust the intensity.
History: 
Wang Shengping 2014/10/07 1.0.0 build this moudle 
*************************************************/

#ifndef __OPTCONTROLER_H__
#define __OPTCONTROLER_H__
#define DLL_EXPORT __declspec(dllexport)

typedef	  long                                   OPTController_Handle;

typedef struct OPTController_IntensityItem
{
	int channelIndex;
	int intensity;
}IntensityItem;

typedef struct OPTController_TriggerWidthItem
{
	int channelIndex;
	int triggerWidth;
}TriggerWidthItem;

typedef struct OPTController_HBTriggerWidthItem
{
	int channelIndex;
	int HBTriggerWidth;
}HBTriggerWidthItem;

extern "C"
{
	/*******************************************************************
	Function: OPTController_InitSerialPort
	Description:  initialize an available serial port
	Input(s):  
	    comName  -the name of the serial port. e.g. "COM1"
	Output(s): 
	    controllerHandle -a handle of the controller
	Return:   see the macro definition
	See also: OPTController_ReleaseSerialPort
	*******************************************************************/
	long DLL_EXPORT OPTController_InitSerialPort(char *comName, OPTController_Handle *controllerHandle);
	
	/*******************************************************************
	Function: OPTController_ReleaseSerialPort
	Description: release an existing serial port
	Input(s): 
	    controllerHandle -the handle of the controller
	Return:   see the macro definition       
	See also: OPTController_InitSerialPort                                                        
	****************************************************************/
	long DLL_EXPORT OPTController_ReleaseSerialPort(OPTController_Handle controllerHandle);

	/*******************************************************************
	Function: OPTController_CreateEtheConnectionByIP
	Description: create an Ethernet connection by IP address
	Input(s):  
	    serverIPAddress    -the IP of the server. e.g.: IP address of the device which is employed as server. The server IP address can be 127.0.0.1
	Output(s): 
	    controllerHandle   -the handle of the controller
	Return: see the macro definition       
	See also: OPTController_CancelEtheConnect   
	Others:	connect to a server as a client. We recommend creating an Ethernet connection by SN (compared with by IP) because IP is likely to be changed dynamically in LAN 
	        under the DHCP protocol. We have provided a tool (SearchForControllers.exe) to check SN.
	*******************************************************************/
	long DLL_EXPORT OPTController_CreateEtheConnectionByIP(char *serverIPAddress, OPTController_Handle *controllerHandle);

	/*******************************************************************
	Function: OPTController_CreateEtheConnectionBySN
	Description: create an Ethernet connection by serial number
	Input(s): 
	    serialNumber     -the serial number of the controller 
	Output(s): 
	    controllerHandle -the handle of the controller
	Return: see the macro definition     
	See also: OPTController_DestroyEtheConnect  
	Others:	connect to a server as a client. We recommend creating an Ethernet connection by SN (compared with by IP) because IP is likely to be changed dynamically in LAN 
	under the DHCP protocol. We have provided a tool (SearchForControllers.exe) to check SN.
	*******************************************************************/
	long DLL_EXPORT OPTController_CreateEtheConnectionBySN(char *serialNumber, OPTController_Handle *controllerHandle);

	/*****************************************************************
	Function: OPTController_DestoryEtheConnection
	Description: destroy an existing Ethernet Connection
	Input(s):    
	    controllerHandle  -the handle of the controller
	Return: see the macro definition  
	*****************************************************************/
	long DLL_EXPORT OPTController_DestoryEtheConnection(OPTController_Handle controllerHandle);

	/*******************************************************************
	Function: OPTController_TurnOnChannel
	Description:turn on the specified channel(s)
	Input(s):
	    controllerHandle -the handle of controller
	    channelIndex     -the index(es) of the channel(s) to be opened, range:[0-16] (in decimal form, 0 for all channels)
	Return: see the macro definition      
	See also: OPTController_TurnOffChannel              
	*******************************************************************/
	long DLL_EXPORT OPTController_TurnOnChannel(OPTController_Handle controllerHandle,int channelIndex);

	/*******************************************************************
	Function: OPTController_TurnOnMultiChannel
	Description: Open multiple specified channels simultaneously 
	Input(s):
	    controllerHandle  -the handle of controller
	    channelIndexArray -an array consists of the index(es) of the channel(s) to be opened, range:[0-16] (in decimal form, 0 for all channels)
		length            -the length of the channel index array
	Return: see the macro definition      
	See also: OPTController_TurnOffChannel              
	*******************************************************************/
	long DLL_EXPORT OPTController_TurnOnMultiChannel(OPTController_Handle controllerHandle,int* channelIndexArray, int length);

	/*******************************************************************
	Function: OPTController_TurnOffChannel
	Description: close the specified channel(s)
	Input(s):
	    controllerHandle -the handle of controller
	    channelIndex     -the index(es) of the channel(s) to be opened, range:[0-16] (in decimal form, 0 for all channels);
	Return: see the macro definition                                                                   
	*******************************************************************/
	long DLL_EXPORT OPTController_TurnOffChannel(OPTController_Handle controllerHandle,int channelIndex);

	/*******************************************************************
	Function: OPTController_TurnOffMultiChannel
	Description: close the specified multiple channels
	Input(s):
	    controllerHandle  -the handle of controller;
	    channelIndexArray -an array consists of the index(es) of the Channel(s) to be opened, range:[0-16] (in decimal form, 0 for all channels);
		length            -the length of the channel index array
	Return: see the macro definition                                                                   
	*******************************************************************/
	long DLL_EXPORT OPTController_TurnOffMultiChannel(OPTController_Handle controllerHandle,int* channelIndexArray, int length);

	/*******************************************************************
	Function: SetIntensity
	Description: set intensity for the specified channel
	Input(s):
	    controllerHandle -the handle of controller
	    channelIndex     -the index(es) of the channel(s), range:[0-16] (in decimal form, 0 for all channels)
	    intensity        -the intensity value, range: [0-255] (in decimal form)
	Return:   see the macro definition                                                           
	*******************************************************************/
	long DLL_EXPORT OPTController_SetIntensity (OPTController_Handle controllerHandle,int channelIndex, int intensity);

	/*******************************************************************
	Function: OPTController_SetMultiIntensity
	Description: set intensities for multiple specified channels simultaneously 
	Input(s):
	    controllerHandle -the handle of controller
	    intensityArray   -an array consists of the intensities to be set, range: [0-255] (in decimal form)
		length           -the length of the intensity array
	Return:   see the macro definition                                                           
	*******************************************************************/
	long DLL_EXPORT OPTController_SetMultiIntensity (OPTController_Handle controllerHandle,IntensityItem* intensityArray, int length);

	/*******************************************************************
	Function: ReadIntensity
	Description: read intensity of the specified channel(s)
	Input(s):
	controllerHandle -the handle of controller           
	channelIndex     -the index(es) of the channel(s), range: [1-16] (in decimal form)
	Output(s): 
	    intensity    -the obtained intensity value;
	Return: see the macro definition                                                                         
	****************************************************************/
	long DLL_EXPORT OPTController_ReadIntensity (OPTController_Handle controllerHandle,int channelIndex, int *intensity);

	/*******************************************************************
	Function: SetTriggerWidth
	Description: set trigger pulse width for corresponding channel(s)
	Input(s):
	    controllerHandle  -the handle of controller
	    channelIndex      -the index(es) of the channel(s), range:[0-16] (in decimal form, 0 for all channels)
	    triggerWidth      -the value of the trigger pulse width to be set, range:[1-999]
	Return: see the macro definition                                                                                           
	******************************************************************/
	long DLL_EXPORT OPTController_SetTriggerWidth(OPTController_Handle controllerHandle,int channelIndex, int triggerWidth);

	/*******************************************************************
	Function: SetMultiTriggerWidth
	Description: set trigger pulse width for multiple specified channels simultaneously 
	Input(s):
	    controllerHandle  -the handle of controller
	    triggerWidthArray -an array consists of values of the trigger pulse width to be set, range:[1-999]
		length            -the length of the trigger width array
	Return: see the macro definition                                                                                           
	******************************************************************/
	long DLL_EXPORT OPTController_SetMultiTriggerWidth(OPTController_Handle controllerHandle,TriggerWidthItem* triggerWidthArray, int length);

	/*******************************************************************
	Function: ReadTriggerWidth
	Description: read the trigger pulse width of the specified channel(s)
	Input(s):
	    controllerHandle  -the handle of controller;
	    channelIndex      -the index(es) of the channel(s), range: [0-16] (in decimal form, 0 for all channels)
	Output(s):    
	    triggerWidth      -the obtained trigger pulse width;
	Return: see the macro definition                                                                     
	****************************************************************/
	long DLL_EXPORT OPTController_ReadTriggerWidth(OPTController_Handle controllerHandle,int channelIndex, int* triggerWidth);

	/*******************************************************************
	Function: SetHBTriggerWidth
	Description: set the high brightness trigger pulse width for corresponding channel(s);
	Input(s):
	    controllerHandle  -the handle of controller;
	    channelIndex      -the index(es) of the channel(s), range: [0-16] (in decimal form, 0 for all channels);
	    HBTriggerWidth    -the value of the trigger pulse width to be set, range:[1-500].
	Return: see the macro definition                                                                          
	****************************************************************/
	long DLL_EXPORT OPTController_SetHBTriggerWidth(OPTController_Handle controllerHandle,int channelIndex, int HBTriggerWidth);

	/*******************************************************************
	Function: SetMultiHBTriggerWidth
	Description: set the high brightness trigger pulse width for multiple specified channels simultaneously
	Input(s):
	    controllerHandle    -the handle of controller;
	    HBtriggerWidthArray -an array consists of values of the high brightness trigger pulse width to be set, range:[1-500]
		length              -the length of the high brightness trigger width array
	Return: see the macro definition                                                                          
	****************************************************************/
	long DLL_EXPORT OPTController_SetMultiHBTriggerWidth(OPTController_Handle controllerHandle,HBTriggerWidthItem* HBtriggerWidthArray, int length);

	/*******************************************************************
	Function£ºReadHBTriggerWidth
	Description: read the high brightness trigger pulse width of the specified channelIndex(s)
	Input(s):
	    controllerHandle  -the handle of controller
	    channelIndex      -the index(es) of the Channel(s), range: [0-16] (in decimal form, 0 for all channels)
	Output(s):  	 
	    HBTriggerWidth    -the obtained high brightness trigger pulse width
	HBTriggerWidth: see the macro definition                                                                             
	*****************************************************************/
	long DLL_EXPORT OPTController_ReadHBTriggerWidth(OPTController_Handle controllerHandle,int channelIndex,int* HBTriggerWidth);

	/*******************************************************************
	Function: OPTController_EnableResponse
	Description: to tell whether we need return value
	Input:
		controllerHandle  -the handle of controller
		isResponse        -"true" means "need response" while "false" stands for not
	Return: see the macro definition                                                                   
	*****************************************************************/
	long DLL_EXPORT OPTController_EnableResponse(OPTController_Handle controllerHandle,bool isResponse);

	/*******************************************************************
	Function: OPTController_EnableCheckSum
	Description: to tell whether we need checksum
	Input:
	    controllerHandle  -the handle of controller
	    enable            -"true" means "need checksum" while "false" stands for not
	Return: see the macro definition         
	*****************************************************************/
	long DLL_EXPORT OPTController_EnableCheckSum(OPTController_Handle controllerHandle, bool enable);

	/*******************************************************************
	Function£ºOPTController_EnablePowerOffBackup
	Description: to tell whether we need backup in the case of power off
	Input:
		controllerHandle   -the handle of controller
		isSave:            -"true" means "save" while "false" stands for not
	Return: see the macro definition                                                                   
	*****************************************************************/
	long DLL_EXPORT OPTController_EnablePowerOffBackup(OPTController_Handle controllerHandle,bool isSave);

	/*******************************************************************
	Function£ºOPTController_ReadAltenativeIntensity
	Description: read the alternative intensity
	Input:
		controllerHandle      -the handle of controller
		channelIndex          -the index(es) of the Channel(s), range: [0-16] (in decimal form, 0 for all channels)
	Output:
		alternativeIntensity  -the obtained alternative intensity
	Return: see the macro definition                                                                  
	*****************************************************************/
	long DLL_EXPORT OPTController_ReadAltenativeIntensity(OPTController_Handle controllerHandle, int channelIndex, int *alternativeIntensity);

	/*******************************************************************
	Function: OPTController_ReadSN
	Description: read the SN of the controller
	Input:
		controllerHandle  -the handle of controller
	Output:
		SN 	              -the obtained SN
	Return: see the macro definition                                                                  
	*****************************************************************/
	long DLL_EXPORT OPTController_ReadSN(OPTController_Handle controllerHandle, char *SN);

	/*******************************************************************

	Function: OPTController_ReadIPAddress
	Description: read IP address
	Input:
		OPTController_Handle -the handle of controller
	Output:
		IP                   -the obtained IP address
		subnetMask           -the obtained subnet mask
		defaultGateway       -the obtained default gateway
	Return: see the macro definition.                                                                  
	*****************************************************************/
	long DLL_EXPORT OPTController_ReadIPConfig(OPTController_Handle controllerHandle, char *IP, char *subnetMask, char *defaultGateway);
};

#endif // __OPTCONTROLER_H__





