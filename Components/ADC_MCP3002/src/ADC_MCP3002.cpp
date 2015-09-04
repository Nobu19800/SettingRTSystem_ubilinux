// -*- C++ -*-
/*!
 * @file  ADC_MCP3002.cpp
 * @brief ADC_MCP3002
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "ADC_MCP3002.h"

// Module specification
// <rtc-template block="module_spec">
static const char* adc_mcp3002_spec[] =
  {
    "implementation_id", "ADC_MCP3002",
    "type_name",         "ADC_MCP3002",
    "description",       "ADC_MCP3002",
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
    "conf.__constraints__.channel", "(0,1)",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
ADC_MCP3002::ADC_MCP3002(RTC::Manager* manager)
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
ADC_MCP3002::~ADC_MCP3002()
{
}



RTC::ReturnCode_t ADC_MCP3002::onInitialize()
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

	for(int i=0;i < 2;i++)
	{
		adc_ports.push_back(new ADC_MCP3002Comp(this,i));
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ADC_MCP3002::onFinalize()
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


RTC::ReturnCode_t ADC_MCP3002::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ADC_MCP3002::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ADC_MCP3002::onActivated(RTC::UniqueId ec_id)
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
		ADC = new MCP3002(response,_spi,_smf,m_cs_pin);
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

	for (std::vector<ADC_MCP3002Comp*>::iterator it = adc_ports.begin(); it != adc_ports.end();it++)
	{
		(*it)->setActive(false);
	}
	coil::eraseBlank(m_channel);

	std::vector<int> tmp;
	if(getValueInString(m_channel,tmp))
	{
		for (std::vector<int>::iterator it = tmp.begin(); it != tmp.end();it++)
		{
			if((*it) < 2 && (*it) >= 0)
			{
				adc_ports[(*it)]->setActive(true);
			}
		}
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ADC_MCP3002::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ADC_MCP3002::onExecute(RTC::UniqueId ec_id)
{
	if(ADC)
	{
		for (std::vector<ADC_MCP3002Comp*>::iterator it = adc_ports.begin(); it != adc_ports.end();it++)
		{
			(*it)->writeValue(ADC, m_voltage);
		}
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ADC_MCP3002::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ADC_MCP3002::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ADC_MCP3002::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ADC_MCP3002::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ADC_MCP3002::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



ADC_MCP3002Comp::ADC_MCP3002Comp(ADC_MCP3002 *rtc, int num)
{
	m_rtc = rtc;
	std::string name = "out"+coil::otos<int>(num);
	Out = new TimedDouble();
	outOut = new RTC::OutPort<TimedDouble>(name.c_str(),*Out);
	rtc->addOutPort(name.c_str(), *outOut);
	m_num = num;
	act = true;
}

ADC_MCP3002Comp::~ADC_MCP3002Comp()
{
	m_rtc->removePort(*outOut);
};


void ADC_MCP3002Comp::writeValue(MCP3002 *mcp, double v)
{
	if(act)
	{
		Out->data = v/1028.0 * (double)mcp->getValue(m_num);
		setTimestamp(*Out);
		outOut->write();
	}
}

void ADC_MCP3002Comp::setActive(bool a)
{
	act = a;
}



extern "C"
{
 
  void ADC_MCP3002Init(RTC::Manager* manager)
  {
    coil::Properties profile(adc_mcp3002_spec);
    manager->registerFactory(profile,
                             RTC::Create<ADC_MCP3002>,
                             RTC::Delete<ADC_MCP3002>);
  }
  
};


