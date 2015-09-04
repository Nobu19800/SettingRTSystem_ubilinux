// -*- C++ -*-
/*!
 * @file  ADC_MCP3208.cpp
 * @brief ADC_MCP3208
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "ADC_MCP3208.h"

// Module specification
// <rtc-template block="module_spec">
static const char* adc_mcp3208_spec[] =
  {
    "implementation_id", "ADC_MCP3208",
    "type_name",         "ADC_MCP3208",
    "description",       "ADC_MCP3208",
    "version",           "1.0.0",
    "vendor",            "Miyamoto Nobuhiko",
    "category",          "Device",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.cs_pin", "4",
    "conf.default.channel", "0",
    "conf.default.voltage", "5",
    // Widget
    "conf.__widget__.cs_pin", "text",
    "conf.__widget__.channel", "checkbox",
    "conf.__widget__.voltage", "text",
    // Constraints
    "conf.__constraints__.channel", "(0,1,2,3,4,5,6,7)",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
ADC_MCP3208::ADC_MCP3208(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager)

    // </rtc-template>
{
	ADC = NULL;
	_spi = NULL;
}

/*!
 * @brief destructor
 */
ADC_MCP3208::~ADC_MCP3208()
{
}





RTC::ReturnCode_t ADC_MCP3208::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("cs_pin", m_cs_pin, "4");
  bindParameter("channel", m_channel, "0");
  bindParameter("voltage", m_voltage, "5");
  // </rtc-template>
  _smf = new i2c_smf("/tmp/edisonspismf");

	for(int i=0;i < 8;i++)
	{
		adc_ports.push_back(new ADC_MCP3208Comp(this,i));
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ADC_MCP3208::onFinalize()
{
	if(ADC)
	{
		delete ADC;
	}
	if(_spi)
	{
		_smf->sem_lock();
		delete _spi;
		_smf->sem_unlock();
	}
	delete _smf;
  return RTC::RTC_OK;
}




RTC::ReturnCode_t ADC_MCP3208::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ADC_MCP3208::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ADC_MCP3208::onActivated(RTC::UniqueId ec_id)
{
	mraa_result_t response;
	if(_spi == NULL)
	{
		_smf->sem_lock();
		_spi = new mraa::Spi(0);
		_smf->sem_unlock();
	}
	if(ADC == NULL)
	{
		ADC = new MCP3208(response,_spi,_smf,m_cs_pin);
		if(response != MRAA_SUCCESS)
		{
			delete ADC;
			ADC = NULL;
			return RTC::RTC_ERROR;
		}
	}
	else
	{
		response = ADC->setPinNum(m_cs_pin);
		if(response != MRAA_SUCCESS)
		{
			return RTC::RTC_ERROR;
		}
	}

	for (std::vector<ADC_MCP3208Comp*>::iterator it = adc_ports.begin(); it != adc_ports.end();it++)
	{
		(*it)->setActive(false);
	}
	coil::eraseBlank(m_channel);

	std::vector<int> tmp;
	if(getValueInString(m_channel,tmp))
	{
		for (std::vector<int>::iterator it = tmp.begin(); it != tmp.end();it++)
		{
			if((*it) < 8 && (*it) >= 0)
			{
				adc_ports[(*it)]->setActive(true);
			}
		}
	}


  return RTC::RTC_OK;
}


RTC::ReturnCode_t ADC_MCP3208::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ADC_MCP3208::onExecute(RTC::UniqueId ec_id)
{
	if(ADC)
	{
		for (std::vector<ADC_MCP3208Comp*>::iterator it = adc_ports.begin(); it != adc_ports.end();it++)
		{
			(*it)->writeValue(ADC, m_voltage);
		}
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ADC_MCP3208::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ADC_MCP3208::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ADC_MCP3208::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ADC_MCP3208::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ADC_MCP3208::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


ADC_MCP3208Comp::ADC_MCP3208Comp(ADC_MCP3208 *rtc, int num)
{
	m_rtc = rtc;
	std::string name = "out"+coil::otos<int>(num);
	Out = new TimedDouble();
	outOut = new RTC::OutPort<TimedDouble>(name.c_str(),*Out);
	rtc->addOutPort(name.c_str(), *outOut);
	m_num = num;
	act = true;
}

ADC_MCP3208Comp::~ADC_MCP3208Comp()
{
	m_rtc->removePort(*outOut);
};


void ADC_MCP3208Comp::writeValue(MCP3208 *mcp, double v)
{
	if(act)
	{
		Out->data = v/4096.0 * (double)mcp->getValue(m_num);
		setTimestamp(*Out);
		outOut->write();
	}
}

void ADC_MCP3208Comp::setActive(bool a)
{
	act = a;
}

extern "C"
{
 
  void ADC_MCP3208Init(RTC::Manager* manager)
  {
    coil::Properties profile(adc_mcp3208_spec);
    manager->registerFactory(profile,
                             RTC::Create<ADC_MCP3208>,
                             RTC::Delete<ADC_MCP3208>);
  }
  
};


