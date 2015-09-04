// -*- C++ -*-
/*!
 * @file rtcdControlComp.cpp
 * @brief Standalone component
 * @date $Date$
 *
 * $Id$
 */

#include <rtm/Manager.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include "rtcdControl.h"



#include <coil/stringutil.h>


template <class T>
void getProperty(coil::Properties& prop, const char* key, T& value)
{
	if (prop.findNode(key) != 0)
	{
		T tmp;
		if (coil::stringTo(tmp, prop[key].c_str()))
		{
			value = tmp;
		}
	}
}

std::string getParam(std::string name)
{
	coil::Properties& prop(::RTC::Manager::instance().getConfig());
	std::string param = "";
	getProperty(prop, name.c_str(), param);
	coil::eraseBlank(param);
	return param;
}




void MyModuleInit(RTC::Manager* manager)
{
  rtcdControlInit(manager);
  RTC::RtcBase* comp;

  // Create a component
  comp = manager->createComponent("rtcdControl");

  if (comp==NULL)
  {
    std::cerr << "Component create failed." << std::endl;
    abort();
  }

  // Example
  // The following procedure is examples how handle RT-Components.
  // These should not be in this function.

  // Get the component's object reference
//  RTC::RTObject_var rtobj;
//  rtobj = RTC::RTObject::_narrow(manager->getPOA()->servant_to_reference(comp));

  // Get the port list of the component
//  PortServiceList* portlist;
//  portlist = rtobj->get_ports();

  // getting port profiles
//  std::cout << "Number of Ports: ";
//  std::cout << portlist->length() << std::endl << std::endl; 
//  for (CORBA::ULong i(0), n(portlist->length()); i < n; ++i)
//  {
//    PortService_ptr port;
//    port = (*portlist)[i];
//    std::cout << "Port" << i << " (name): ";
//    std::cout << port->get_port_profile()->name << std::endl;
//    
//    RTC::PortInterfaceProfileList iflist;
//    iflist = port->get_port_profile()->interfaces;
//    std::cout << "---interfaces---" << std::endl;
//    for (CORBA::ULong i(0), n(iflist.length()); i < n; ++i)
//    {
//      std::cout << "I/F name: ";
//      std::cout << iflist[i].instance_name << std::endl;
//      std::cout << "I/F type: ";
//      std::cout << iflist[i].type_name << std::endl;
//      const char* pol;
//      pol = iflist[i].polarity == 0 ? "PROVIDED" : "REQUIRED";
//      std::cout << "Polarity: " << pol << std::endl;
//    }
//    std::cout << "---properties---" << std::endl;
//    NVUtil::dump(port->get_port_profile()->properties);
//    std::cout << "----------------" << std::endl << std::endl;
//  }

  return;
}

int main (int argc, char** argv)
{
  RTC::Manager* manager;
  manager = RTC::Manager::init(argc, argv);

  // Initialize manager
  manager->init(argc, argv);

#ifdef _WINDOWS

  std::string path = getParam("manager.modules.load_path");
  coil::eraseBlank(path);

  coil::vstring pathList = coil::split(path, ",");

  for (int i = 0; i < pathList.size(); i++)
  {
	  std::string filepath = pathList[i];

	  char szFullPath[MAX_PATH];
	  _fullpath(szFullPath, filepath.c_str(), sizeof(szFullPath) / sizeof(szFullPath[0]));
	  std::string path = "PATH=";
	  path += getenv("PATH");
	  path += ";";
	  path += szFullPath;
	  putenv(path.c_str());

  }
#endif

  // Set module initialization proceduer
  // This procedure will be invoked in activateManager() function.
  manager->setModuleInitProc(MyModuleInit);

  // Activate manager and register to naming service
  manager->activateManager();

  // run the manager in blocking mode
  // runManager(false) is the default.
  manager->runManager();

  // If you want to run the manager in non-blocking mode, do like this
  // manager->runManager(true);

  return 0;
}
