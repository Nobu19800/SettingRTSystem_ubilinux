# Python stubs generated by omniidl from idl/rtcconf.idl

import omniORB, _omnipy
from omniORB import CORBA, PortableServer
_0_CORBA = CORBA

_omnipy.checkVersion(3,0, __file__)

# #include "BasicDataType.idl"
import BasicDataType_idl
_0_RTC = omniORB.openModule("RTC")
_0_RTC__POA = omniORB.openModule("RTC__POA")

#
# Start of module "RTCConfData"
#
__name__ = "RTCConfData"
_0_RTCConfData = omniORB.openModule("RTCConfData", r"idl/rtcconf.idl")
_0_RTCConfData__POA = omniORB.openModule("RTCConfData__POA", r"idl/rtcconf.idl")


# struct confData
_0_RTCConfData.confData = omniORB.newEmptyClass()
class confData (omniORB.StructBase):
    _NP_RepositoryId = "IDL:RTCConfData/confData:1.0"

    def __init__(self, id, data):
        self.id = id
        self.data = data

_0_RTCConfData.confData = confData
_0_RTCConfData._d_confData  = (omniORB.tcInternal.tv_struct, confData, confData._NP_RepositoryId, "confData", "id", (omniORB.tcInternal.tv_string,0), "data", (omniORB.tcInternal.tv_string,0))
_0_RTCConfData._tc_confData = omniORB.tcInternal.createTypeCode(_0_RTCConfData._d_confData)
omniORB.registerType(confData._NP_RepositoryId, _0_RTCConfData._d_confData, _0_RTCConfData._tc_confData)
del confData

# struct BasicInfo_Doc
_0_RTCConfData.BasicInfo_Doc = omniORB.newEmptyClass()
class BasicInfo_Doc (omniORB.StructBase):
    _NP_RepositoryId = "IDL:RTCConfData/BasicInfo_Doc:1.0"

    def __init__(self, reference, license, creator, algorithm, inouts, description):
        self.reference = reference
        self.license = license
        self.creator = creator
        self.algorithm = algorithm
        self.inouts = inouts
        self.description = description

_0_RTCConfData.BasicInfo_Doc = BasicInfo_Doc
_0_RTCConfData._d_BasicInfo_Doc  = (omniORB.tcInternal.tv_struct, BasicInfo_Doc, BasicInfo_Doc._NP_RepositoryId, "BasicInfo_Doc", "reference", (omniORB.tcInternal.tv_wstring,0), "license", (omniORB.tcInternal.tv_wstring,0), "creator", (omniORB.tcInternal.tv_wstring,0), "algorithm", (omniORB.tcInternal.tv_wstring,0), "inouts", (omniORB.tcInternal.tv_wstring,0), "description", (omniORB.tcInternal.tv_wstring,0))
_0_RTCConfData._tc_BasicInfo_Doc = omniORB.tcInternal.createTypeCode(_0_RTCConfData._d_BasicInfo_Doc)
omniORB.registerType(BasicInfo_Doc._NP_RepositoryId, _0_RTCConfData._d_BasicInfo_Doc, _0_RTCConfData._tc_BasicInfo_Doc)
del BasicInfo_Doc

# struct BasicInfo
_0_RTCConfData.BasicInfo = omniORB.newEmptyClass()
class BasicInfo (omniORB.StructBase):
    _NP_RepositoryId = "IDL:RTCConfData/BasicInfo:1.0"

    def __init__(self, type, saveProject, updateDate, creationDate, abstracts, version, vendor, maxInstances, executionType, executionRate, description, category, componentKind, activityType, componentType, name, doc):
        self.type = type
        self.saveProject = saveProject
        self.updateDate = updateDate
        self.creationDate = creationDate
        self.abstracts = abstracts
        self.version = version
        self.vendor = vendor
        self.maxInstances = maxInstances
        self.executionType = executionType
        self.executionRate = executionRate
        self.description = description
        self.category = category
        self.componentKind = componentKind
        self.activityType = activityType
        self.componentType = componentType
        self.name = name
        self.doc = doc

_0_RTCConfData.BasicInfo = BasicInfo
_0_RTCConfData._d_BasicInfo  = (omniORB.tcInternal.tv_struct, BasicInfo, BasicInfo._NP_RepositoryId, "BasicInfo", "type", (omniORB.tcInternal.tv_wstring,0), "saveProject", (omniORB.tcInternal.tv_wstring,0), "updateDate", (omniORB.tcInternal.tv_wstring,0), "creationDate", (omniORB.tcInternal.tv_wstring,0), "abstracts", (omniORB.tcInternal.tv_wstring,0), "version", (omniORB.tcInternal.tv_wstring,0), "vendor", (omniORB.tcInternal.tv_wstring,0), "maxInstances", (omniORB.tcInternal.tv_wstring,0), "executionType", (omniORB.tcInternal.tv_wstring,0), "executionRate", (omniORB.tcInternal.tv_wstring,0), "description", (omniORB.tcInternal.tv_wstring,0), "category", (omniORB.tcInternal.tv_wstring,0), "componentKind", (omniORB.tcInternal.tv_wstring,0), "activityType", (omniORB.tcInternal.tv_wstring,0), "componentType", (omniORB.tcInternal.tv_wstring,0), "name", (omniORB.tcInternal.tv_wstring,0), "doc", omniORB.typeMapping["IDL:RTCConfData/BasicInfo_Doc:1.0"])
_0_RTCConfData._tc_BasicInfo = omniORB.tcInternal.createTypeCode(_0_RTCConfData._d_BasicInfo)
omniORB.registerType(BasicInfo._NP_RepositoryId, _0_RTCConfData._d_BasicInfo, _0_RTCConfData._tc_BasicInfo)
del BasicInfo

# struct Action
_0_RTCConfData.Action = omniORB.newEmptyClass()
class Action (omniORB.StructBase):
    _NP_RepositoryId = "IDL:RTCConfData/Action:1.0"

    def __init__(self, type, implemented):
        self.type = type
        self.implemented = implemented

_0_RTCConfData.Action = Action
_0_RTCConfData._d_Action  = (omniORB.tcInternal.tv_struct, Action, Action._NP_RepositoryId, "Action", "type", (omniORB.tcInternal.tv_wstring,0), "implemented", (omniORB.tcInternal.tv_wstring,0))
_0_RTCConfData._tc_Action = omniORB.tcInternal.createTypeCode(_0_RTCConfData._d_Action)
omniORB.registerType(Action._NP_RepositoryId, _0_RTCConfData._d_Action, _0_RTCConfData._tc_Action)
del Action

# struct Actions
_0_RTCConfData.Actions = omniORB.newEmptyClass()
class Actions (omniORB.StructBase):
    _NP_RepositoryId = "IDL:RTCConfData/Actions:1.0"

    def __init__(self, OnInitialize, OnFinalize, OnStartup, OnShutdown, OnActivated, OnDeactivated, OnAborting, OnError, OnReset, OnExecute, OnStateUpdate, OnRateChanged, OnAction, OnModeChanged):
        self.OnInitialize = OnInitialize
        self.OnFinalize = OnFinalize
        self.OnStartup = OnStartup
        self.OnShutdown = OnShutdown
        self.OnActivated = OnActivated
        self.OnDeactivated = OnDeactivated
        self.OnAborting = OnAborting
        self.OnError = OnError
        self.OnReset = OnReset
        self.OnExecute = OnExecute
        self.OnStateUpdate = OnStateUpdate
        self.OnRateChanged = OnRateChanged
        self.OnAction = OnAction
        self.OnModeChanged = OnModeChanged

_0_RTCConfData.Actions = Actions
_0_RTCConfData._d_Actions  = (omniORB.tcInternal.tv_struct, Actions, Actions._NP_RepositoryId, "Actions", "OnInitialize", omniORB.typeMapping["IDL:RTCConfData/Action:1.0"], "OnFinalize", omniORB.typeMapping["IDL:RTCConfData/Action:1.0"], "OnStartup", omniORB.typeMapping["IDL:RTCConfData/Action:1.0"], "OnShutdown", omniORB.typeMapping["IDL:RTCConfData/Action:1.0"], "OnActivated", omniORB.typeMapping["IDL:RTCConfData/Action:1.0"], "OnDeactivated", omniORB.typeMapping["IDL:RTCConfData/Action:1.0"], "OnAborting", omniORB.typeMapping["IDL:RTCConfData/Action:1.0"], "OnError", omniORB.typeMapping["IDL:RTCConfData/Action:1.0"], "OnReset", omniORB.typeMapping["IDL:RTCConfData/Action:1.0"], "OnExecute", omniORB.typeMapping["IDL:RTCConfData/Action:1.0"], "OnStateUpdate", omniORB.typeMapping["IDL:RTCConfData/Action:1.0"], "OnRateChanged", omniORB.typeMapping["IDL:RTCConfData/Action:1.0"], "OnAction", omniORB.typeMapping["IDL:RTCConfData/Action:1.0"], "OnModeChanged", omniORB.typeMapping["IDL:RTCConfData/Action:1.0"])
_0_RTCConfData._tc_Actions = omniORB.tcInternal.createTypeCode(_0_RTCConfData._d_Actions)
omniORB.registerType(Actions._NP_RepositoryId, _0_RTCConfData._d_Actions, _0_RTCConfData._tc_Actions)
del Actions

# struct Configuration_Doc
_0_RTCConfData.Configuration_Doc = omniORB.newEmptyClass()
class Configuration_Doc (omniORB.StructBase):
    _NP_RepositoryId = "IDL:RTCConfData/Configuration_Doc:1.0"

    def __init__(self, constraint, range, unit, description, defaultValue, dataname):
        self.constraint = constraint
        self.range = range
        self.unit = unit
        self.description = description
        self.defaultValue = defaultValue
        self.dataname = dataname

_0_RTCConfData.Configuration_Doc = Configuration_Doc
_0_RTCConfData._d_Configuration_Doc  = (omniORB.tcInternal.tv_struct, Configuration_Doc, Configuration_Doc._NP_RepositoryId, "Configuration_Doc", "constraint", (omniORB.tcInternal.tv_wstring,0), "range", (omniORB.tcInternal.tv_wstring,0), "unit", (omniORB.tcInternal.tv_wstring,0), "description", (omniORB.tcInternal.tv_wstring,0), "defaultValue", (omniORB.tcInternal.tv_wstring,0), "dataname", (omniORB.tcInternal.tv_wstring,0))
_0_RTCConfData._tc_Configuration_Doc = omniORB.tcInternal.createTypeCode(_0_RTCConfData._d_Configuration_Doc)
omniORB.registerType(Configuration_Doc._NP_RepositoryId, _0_RTCConfData._d_Configuration_Doc, _0_RTCConfData._tc_Configuration_Doc)
del Configuration_Doc

# struct Configuration_Properties
_0_RTCConfData.Configuration_Properties = omniORB.newEmptyClass()
class Configuration_Properties (omniORB.StructBase):
    _NP_RepositoryId = "IDL:RTCConfData/Configuration_Properties:1.0"

    def __init__(self, value, name):
        self.value = value
        self.name = name

_0_RTCConfData.Configuration_Properties = Configuration_Properties
_0_RTCConfData._d_Configuration_Properties  = (omniORB.tcInternal.tv_struct, Configuration_Properties, Configuration_Properties._NP_RepositoryId, "Configuration_Properties", "value", (omniORB.tcInternal.tv_wstring,0), "name", (omniORB.tcInternal.tv_wstring,0))
_0_RTCConfData._tc_Configuration_Properties = omniORB.tcInternal.createTypeCode(_0_RTCConfData._d_Configuration_Properties)
omniORB.registerType(Configuration_Properties._NP_RepositoryId, _0_RTCConfData._d_Configuration_Properties, _0_RTCConfData._tc_Configuration_Properties)
del Configuration_Properties

# struct Configuration
_0_RTCConfData.Configuration = omniORB.newEmptyClass()
class Configuration (omniORB.StructBase):
    _NP_RepositoryId = "IDL:RTCConfData/Configuration:1.0"

    def __init__(self, type, variableName, unit, defaultValue, dataType, name, property, doc):
        self.type = type
        self.variableName = variableName
        self.unit = unit
        self.defaultValue = defaultValue
        self.dataType = dataType
        self.name = name
        self.property = property
        self.doc = doc

_0_RTCConfData.Configuration = Configuration
_0_RTCConfData._d_Configuration  = (omniORB.tcInternal.tv_struct, Configuration, Configuration._NP_RepositoryId, "Configuration", "type", (omniORB.tcInternal.tv_wstring,0), "variableName", (omniORB.tcInternal.tv_wstring,0), "unit", (omniORB.tcInternal.tv_wstring,0), "defaultValue", (omniORB.tcInternal.tv_wstring,0), "dataType", (omniORB.tcInternal.tv_wstring,0), "name", (omniORB.tcInternal.tv_wstring,0), "property", omniORB.typeMapping["IDL:RTCConfData/Configuration_Properties:1.0"], "doc", omniORB.typeMapping["IDL:RTCConfData/Configuration_Doc:1.0"])
_0_RTCConfData._tc_Configuration = omniORB.tcInternal.createTypeCode(_0_RTCConfData._d_Configuration)
omniORB.registerType(Configuration._NP_RepositoryId, _0_RTCConfData._d_Configuration, _0_RTCConfData._tc_Configuration)
del Configuration

# typedef ... ConfigurationSet
class ConfigurationSet:
    _NP_RepositoryId = "IDL:RTCConfData/ConfigurationSet:1.0"
    def __init__(self, *args, **kw):
        raise RuntimeError("Cannot construct objects of this type.")
_0_RTCConfData.ConfigurationSet = ConfigurationSet
_0_RTCConfData._d_ConfigurationSet  = (omniORB.tcInternal.tv_sequence, omniORB.typeMapping["IDL:RTCConfData/Configuration:1.0"], 0)
_0_RTCConfData._ad_ConfigurationSet = (omniORB.tcInternal.tv_alias, ConfigurationSet._NP_RepositoryId, "ConfigurationSet", (omniORB.tcInternal.tv_sequence, omniORB.typeMapping["IDL:RTCConfData/Configuration:1.0"], 0))
_0_RTCConfData._tc_ConfigurationSet = omniORB.tcInternal.createTypeCode(_0_RTCConfData._ad_ConfigurationSet)
omniORB.registerType(ConfigurationSet._NP_RepositoryId, _0_RTCConfData._ad_ConfigurationSet, _0_RTCConfData._tc_ConfigurationSet)
del ConfigurationSet

# struct DataPort_Doc
_0_RTCConfData.DataPort_Doc = omniORB.newEmptyClass()
class DataPort_Doc (omniORB.StructBase):
    _NP_RepositoryId = "IDL:RTCConfData/DataPort_Doc:1.0"

    def __init__(self, operation, occerrence, unit, semantics, number, type, description):
        self.operation = operation
        self.occerrence = occerrence
        self.unit = unit
        self.semantics = semantics
        self.number = number
        self.type = type
        self.description = description

_0_RTCConfData.DataPort_Doc = DataPort_Doc
_0_RTCConfData._d_DataPort_Doc  = (omniORB.tcInternal.tv_struct, DataPort_Doc, DataPort_Doc._NP_RepositoryId, "DataPort_Doc", "operation", (omniORB.tcInternal.tv_wstring,0), "occerrence", (omniORB.tcInternal.tv_wstring,0), "unit", (omniORB.tcInternal.tv_wstring,0), "semantics", (omniORB.tcInternal.tv_wstring,0), "number", (omniORB.tcInternal.tv_wstring,0), "type", (omniORB.tcInternal.tv_wstring,0), "description", (omniORB.tcInternal.tv_wstring,0))
_0_RTCConfData._tc_DataPort_Doc = omniORB.tcInternal.createTypeCode(_0_RTCConfData._d_DataPort_Doc)
omniORB.registerType(DataPort_Doc._NP_RepositoryId, _0_RTCConfData._d_DataPort_Doc, _0_RTCConfData._tc_DataPort_Doc)
del DataPort_Doc

# struct DataPort
_0_RTCConfData.DataPort = omniORB.newEmptyClass()
class DataPort (omniORB.StructBase):
    _NP_RepositoryId = "IDL:RTCConfData/DataPort:1.0"

    def __init__(self, type, position, variableName, unit, subscriptionType, dataflowType, interfaceType, idlFile, datatype, name, portType, doc):
        self.type = type
        self.position = position
        self.variableName = variableName
        self.unit = unit
        self.subscriptionType = subscriptionType
        self.dataflowType = dataflowType
        self.interfaceType = interfaceType
        self.idlFile = idlFile
        self.datatype = datatype
        self.name = name
        self.portType = portType
        self.doc = doc

_0_RTCConfData.DataPort = DataPort
_0_RTCConfData._d_DataPort  = (omniORB.tcInternal.tv_struct, DataPort, DataPort._NP_RepositoryId, "DataPort", "type", (omniORB.tcInternal.tv_wstring,0), "position", (omniORB.tcInternal.tv_wstring,0), "variableName", (omniORB.tcInternal.tv_wstring,0), "unit", (omniORB.tcInternal.tv_wstring,0), "subscriptionType", (omniORB.tcInternal.tv_wstring,0), "dataflowType", (omniORB.tcInternal.tv_wstring,0), "interfaceType", (omniORB.tcInternal.tv_wstring,0), "idlFile", (omniORB.tcInternal.tv_wstring,0), "datatype", (omniORB.tcInternal.tv_wstring,0), "name", (omniORB.tcInternal.tv_wstring,0), "portType", (omniORB.tcInternal.tv_wstring,0), "doc", omniORB.typeMapping["IDL:RTCConfData/DataPort_Doc:1.0"])
_0_RTCConfData._tc_DataPort = omniORB.tcInternal.createTypeCode(_0_RTCConfData._d_DataPort)
omniORB.registerType(DataPort._NP_RepositoryId, _0_RTCConfData._d_DataPort, _0_RTCConfData._tc_DataPort)
del DataPort

# typedef ... DataPorts
class DataPorts:
    _NP_RepositoryId = "IDL:RTCConfData/DataPorts:1.0"
    def __init__(self, *args, **kw):
        raise RuntimeError("Cannot construct objects of this type.")
_0_RTCConfData.DataPorts = DataPorts
_0_RTCConfData._d_DataPorts  = (omniORB.tcInternal.tv_sequence, omniORB.typeMapping["IDL:RTCConfData/DataPort:1.0"], 0)
_0_RTCConfData._ad_DataPorts = (omniORB.tcInternal.tv_alias, DataPorts._NP_RepositoryId, "DataPorts", (omniORB.tcInternal.tv_sequence, omniORB.typeMapping["IDL:RTCConfData/DataPort:1.0"], 0))
_0_RTCConfData._tc_DataPorts = omniORB.tcInternal.createTypeCode(_0_RTCConfData._ad_DataPorts)
omniORB.registerType(DataPorts._NP_RepositoryId, _0_RTCConfData._ad_DataPorts, _0_RTCConfData._tc_DataPorts)
del DataPorts

# struct ServiceInterface_Doc
_0_RTCConfData.ServiceInterface_Doc = omniORB.newEmptyClass()
class ServiceInterface_Doc (omniORB.StructBase):
    _NP_RepositoryId = "IDL:RTCConfData/ServiceInterface_Doc:1.0"

    def __init__(self, docPostCondition, docPreCondition, docException, docReturn, docArgument, description):
        self.docPostCondition = docPostCondition
        self.docPreCondition = docPreCondition
        self.docException = docException
        self.docReturn = docReturn
        self.docArgument = docArgument
        self.description = description

_0_RTCConfData.ServiceInterface_Doc = ServiceInterface_Doc
_0_RTCConfData._d_ServiceInterface_Doc  = (omniORB.tcInternal.tv_struct, ServiceInterface_Doc, ServiceInterface_Doc._NP_RepositoryId, "ServiceInterface_Doc", "docPostCondition", (omniORB.tcInternal.tv_wstring,0), "docPreCondition", (omniORB.tcInternal.tv_wstring,0), "docException", (omniORB.tcInternal.tv_wstring,0), "docReturn", (omniORB.tcInternal.tv_wstring,0), "docArgument", (omniORB.tcInternal.tv_wstring,0), "description", (omniORB.tcInternal.tv_wstring,0))
_0_RTCConfData._tc_ServiceInterface_Doc = omniORB.tcInternal.createTypeCode(_0_RTCConfData._d_ServiceInterface_Doc)
omniORB.registerType(ServiceInterface_Doc._NP_RepositoryId, _0_RTCConfData._d_ServiceInterface_Doc, _0_RTCConfData._tc_ServiceInterface_Doc)
del ServiceInterface_Doc

# struct ServiceInterface
_0_RTCConfData.ServiceInterface = omniORB.newEmptyClass()
class ServiceInterface (omniORB.StructBase):
    _NP_RepositoryId = "IDL:RTCConfData/ServiceInterface:1.0"

    def __init__(self, type, variableName, path, interfeceType, idlFile, instanceName, direction, name, doc):
        self.type = type
        self.variableName = variableName
        self.path = path
        self.interfeceType = interfeceType
        self.idlFile = idlFile
        self.instanceName = instanceName
        self.direction = direction
        self.name = name
        self.doc = doc

_0_RTCConfData.ServiceInterface = ServiceInterface
_0_RTCConfData._d_ServiceInterface  = (omniORB.tcInternal.tv_struct, ServiceInterface, ServiceInterface._NP_RepositoryId, "ServiceInterface", "type", (omniORB.tcInternal.tv_wstring,0), "variableName", (omniORB.tcInternal.tv_wstring,0), "path", (omniORB.tcInternal.tv_wstring,0), "interfeceType", (omniORB.tcInternal.tv_wstring,0), "idlFile", (omniORB.tcInternal.tv_wstring,0), "instanceName", (omniORB.tcInternal.tv_wstring,0), "direction", (omniORB.tcInternal.tv_wstring,0), "name", (omniORB.tcInternal.tv_wstring,0), "doc", omniORB.typeMapping["IDL:RTCConfData/ServiceInterface_Doc:1.0"])
_0_RTCConfData._tc_ServiceInterface = omniORB.tcInternal.createTypeCode(_0_RTCConfData._d_ServiceInterface)
omniORB.registerType(ServiceInterface._NP_RepositoryId, _0_RTCConfData._d_ServiceInterface, _0_RTCConfData._tc_ServiceInterface)
del ServiceInterface

# struct ServicePort_Doc
_0_RTCConfData.ServicePort_Doc = omniORB.newEmptyClass()
class ServicePort_Doc (omniORB.StructBase):
    _NP_RepositoryId = "IDL:RTCConfData/ServicePort_Doc:1.0"

    def __init__(self, ifdescription, description):
        self.ifdescription = ifdescription
        self.description = description

_0_RTCConfData.ServicePort_Doc = ServicePort_Doc
_0_RTCConfData._d_ServicePort_Doc  = (omniORB.tcInternal.tv_struct, ServicePort_Doc, ServicePort_Doc._NP_RepositoryId, "ServicePort_Doc", "ifdescription", (omniORB.tcInternal.tv_wstring,0), "description", (omniORB.tcInternal.tv_wstring,0))
_0_RTCConfData._tc_ServicePort_Doc = omniORB.tcInternal.createTypeCode(_0_RTCConfData._d_ServicePort_Doc)
omniORB.registerType(ServicePort_Doc._NP_RepositoryId, _0_RTCConfData._d_ServicePort_Doc, _0_RTCConfData._tc_ServicePort_Doc)
del ServicePort_Doc

# typedef ... ServiceInterfaces
class ServiceInterfaces:
    _NP_RepositoryId = "IDL:RTCConfData/ServiceInterfaces:1.0"
    def __init__(self, *args, **kw):
        raise RuntimeError("Cannot construct objects of this type.")
_0_RTCConfData.ServiceInterfaces = ServiceInterfaces
_0_RTCConfData._d_ServiceInterfaces  = (omniORB.tcInternal.tv_sequence, omniORB.typeMapping["IDL:RTCConfData/ServiceInterface:1.0"], 0)
_0_RTCConfData._ad_ServiceInterfaces = (omniORB.tcInternal.tv_alias, ServiceInterfaces._NP_RepositoryId, "ServiceInterfaces", (omniORB.tcInternal.tv_sequence, omniORB.typeMapping["IDL:RTCConfData/ServiceInterface:1.0"], 0))
_0_RTCConfData._tc_ServiceInterfaces = omniORB.tcInternal.createTypeCode(_0_RTCConfData._ad_ServiceInterfaces)
omniORB.registerType(ServiceInterfaces._NP_RepositoryId, _0_RTCConfData._ad_ServiceInterfaces, _0_RTCConfData._tc_ServiceInterfaces)
del ServiceInterfaces

# struct ServicePort
_0_RTCConfData.ServicePort = omniORB.newEmptyClass()
class ServicePort (omniORB.StructBase):
    _NP_RepositoryId = "IDL:RTCConfData/ServicePort:1.0"

    def __init__(self, type, position, name, interfaces, doc):
        self.type = type
        self.position = position
        self.name = name
        self.interfaces = interfaces
        self.doc = doc

_0_RTCConfData.ServicePort = ServicePort
_0_RTCConfData._d_ServicePort  = (omniORB.tcInternal.tv_struct, ServicePort, ServicePort._NP_RepositoryId, "ServicePort", "type", (omniORB.tcInternal.tv_wstring,0), "position", (omniORB.tcInternal.tv_wstring,0), "name", (omniORB.tcInternal.tv_wstring,0), "interfaces", omniORB.typeMapping["IDL:RTCConfData/ServiceInterfaces:1.0"], "doc", omniORB.typeMapping["IDL:RTCConfData/ServicePort_Doc:1.0"])
_0_RTCConfData._tc_ServicePort = omniORB.tcInternal.createTypeCode(_0_RTCConfData._d_ServicePort)
omniORB.registerType(ServicePort._NP_RepositoryId, _0_RTCConfData._d_ServicePort, _0_RTCConfData._tc_ServicePort)
del ServicePort

# typedef ... ServicePorts
class ServicePorts:
    _NP_RepositoryId = "IDL:RTCConfData/ServicePorts:1.0"
    def __init__(self, *args, **kw):
        raise RuntimeError("Cannot construct objects of this type.")
_0_RTCConfData.ServicePorts = ServicePorts
_0_RTCConfData._d_ServicePorts  = (omniORB.tcInternal.tv_sequence, omniORB.typeMapping["IDL:RTCConfData/ServicePort:1.0"], 0)
_0_RTCConfData._ad_ServicePorts = (omniORB.tcInternal.tv_alias, ServicePorts._NP_RepositoryId, "ServicePorts", (omniORB.tcInternal.tv_sequence, omniORB.typeMapping["IDL:RTCConfData/ServicePort:1.0"], 0))
_0_RTCConfData._tc_ServicePorts = omniORB.tcInternal.createTypeCode(_0_RTCConfData._ad_ServicePorts)
omniORB.registerType(ServicePorts._NP_RepositoryId, _0_RTCConfData._ad_ServicePorts, _0_RTCConfData._tc_ServicePorts)
del ServicePorts

# struct RTC_Profile
_0_RTCConfData.RTC_Profile = omniORB.newEmptyClass()
class RTC_Profile (omniORB.StructBase):
    _NP_RepositoryId = "IDL:RTCConfData/RTC_Profile:1.0"

    def __init__(self, name, version, id, language, info, act, confs, dports, sports):
        self.name = name
        self.version = version
        self.id = id
        self.language = language
        self.info = info
        self.act = act
        self.confs = confs
        self.dports = dports
        self.sports = sports

_0_RTCConfData.RTC_Profile = RTC_Profile
_0_RTCConfData._d_RTC_Profile  = (omniORB.tcInternal.tv_struct, RTC_Profile, RTC_Profile._NP_RepositoryId, "RTC_Profile", "name", (omniORB.tcInternal.tv_wstring,0), "version", (omniORB.tcInternal.tv_wstring,0), "id", (omniORB.tcInternal.tv_wstring,0), "language", (omniORB.tcInternal.tv_wstring,0), "info", omniORB.typeMapping["IDL:RTCConfData/BasicInfo:1.0"], "act", omniORB.typeMapping["IDL:RTCConfData/Actions:1.0"], "confs", omniORB.typeMapping["IDL:RTCConfData/ConfigurationSet:1.0"], "dports", omniORB.typeMapping["IDL:RTCConfData/DataPorts:1.0"], "sports", omniORB.typeMapping["IDL:RTCConfData/ServicePorts:1.0"])
_0_RTCConfData._tc_RTC_Profile = omniORB.tcInternal.createTypeCode(_0_RTCConfData._d_RTC_Profile)
omniORB.registerType(RTC_Profile._NP_RepositoryId, _0_RTCConfData._d_RTC_Profile, _0_RTCConfData._tc_RTC_Profile)
del RTC_Profile

# typedef ... RTC_ProfileList
class RTC_ProfileList:
    _NP_RepositoryId = "IDL:RTCConfData/RTC_ProfileList:1.0"
    def __init__(self, *args, **kw):
        raise RuntimeError("Cannot construct objects of this type.")
_0_RTCConfData.RTC_ProfileList = RTC_ProfileList
_0_RTCConfData._d_RTC_ProfileList  = (omniORB.tcInternal.tv_sequence, omniORB.typeMapping["IDL:RTCConfData/RTC_Profile:1.0"], 0)
_0_RTCConfData._ad_RTC_ProfileList = (omniORB.tcInternal.tv_alias, RTC_ProfileList._NP_RepositoryId, "RTC_ProfileList", (omniORB.tcInternal.tv_sequence, omniORB.typeMapping["IDL:RTCConfData/RTC_Profile:1.0"], 0))
_0_RTCConfData._tc_RTC_ProfileList = omniORB.tcInternal.createTypeCode(_0_RTCConfData._ad_RTC_ProfileList)
omniORB.registerType(RTC_ProfileList._NP_RepositoryId, _0_RTCConfData._ad_RTC_ProfileList, _0_RTCConfData._tc_RTC_ProfileList)
del RTC_ProfileList

# typedef ... confDataSeq
class confDataSeq:
    _NP_RepositoryId = "IDL:RTCConfData/confDataSeq:1.0"
    def __init__(self, *args, **kw):
        raise RuntimeError("Cannot construct objects of this type.")
_0_RTCConfData.confDataSeq = confDataSeq
_0_RTCConfData._d_confDataSeq  = (omniORB.tcInternal.tv_sequence, omniORB.typeMapping["IDL:RTCConfData/confData:1.0"], 0)
_0_RTCConfData._ad_confDataSeq = (omniORB.tcInternal.tv_alias, confDataSeq._NP_RepositoryId, "confDataSeq", (omniORB.tcInternal.tv_sequence, omniORB.typeMapping["IDL:RTCConfData/confData:1.0"], 0))
_0_RTCConfData._tc_confDataSeq = omniORB.tcInternal.createTypeCode(_0_RTCConfData._ad_confDataSeq)
omniORB.registerType(confDataSeq._NP_RepositoryId, _0_RTCConfData._ad_confDataSeq, _0_RTCConfData._tc_confDataSeq)
del confDataSeq

# typedef ... stringSeq
class stringSeq:
    _NP_RepositoryId = "IDL:RTCConfData/stringSeq:1.0"
    def __init__(self, *args, **kw):
        raise RuntimeError("Cannot construct objects of this type.")
_0_RTCConfData.stringSeq = stringSeq
_0_RTCConfData._d_stringSeq  = (omniORB.tcInternal.tv_sequence, (omniORB.tcInternal.tv_string,0), 0)
_0_RTCConfData._ad_stringSeq = (omniORB.tcInternal.tv_alias, stringSeq._NP_RepositoryId, "stringSeq", (omniORB.tcInternal.tv_sequence, (omniORB.tcInternal.tv_string,0), 0))
_0_RTCConfData._tc_stringSeq = omniORB.tcInternal.createTypeCode(_0_RTCConfData._ad_stringSeq)
omniORB.registerType(stringSeq._NP_RepositoryId, _0_RTCConfData._ad_stringSeq, _0_RTCConfData._tc_stringSeq)
del stringSeq

# interface ConfDataInterface
_0_RTCConfData._d_ConfDataInterface = (omniORB.tcInternal.tv_objref, "IDL:RTCConfData/ConfDataInterface:1.0", "ConfDataInterface")
omniORB.typeMapping["IDL:RTCConfData/ConfDataInterface:1.0"] = _0_RTCConfData._d_ConfDataInterface
_0_RTCConfData.ConfDataInterface = omniORB.newEmptyClass()
class ConfDataInterface :
    _NP_RepositoryId = _0_RTCConfData._d_ConfDataInterface[1]

    def __init__(self, *args, **kw):
        raise RuntimeError("Cannot construct objects of this type.")

    _nil = CORBA.Object._nil


_0_RTCConfData.ConfDataInterface = ConfDataInterface
_0_RTCConfData._tc_ConfDataInterface = omniORB.tcInternal.createTypeCode(_0_RTCConfData._d_ConfDataInterface)
omniORB.registerType(ConfDataInterface._NP_RepositoryId, _0_RTCConfData._d_ConfDataInterface, _0_RTCConfData._tc_ConfDataInterface)

# ConfDataInterface operations and attributes
ConfDataInterface._d_open = (((omniORB.tcInternal.tv_string,0), ), (omniORB.tcInternal.tv_boolean, ), None)
ConfDataInterface._d_save = (((omniORB.tcInternal.tv_string,0), ), (omniORB.tcInternal.tv_boolean, ), None)
ConfDataInterface._d_setConfData_Cpp = (((omniORB.tcInternal.tv_string,0), ), (omniORB.tcInternal.tv_boolean, omniORB.typeMapping["IDL:RTCConfData/confDataSeq:1.0"]), None)
ConfDataInterface._d_setConfData_Py = (((omniORB.tcInternal.tv_string,0), ), (omniORB.tcInternal.tv_boolean, omniORB.typeMapping["IDL:RTCConfData/confDataSeq:1.0"]), None)
ConfDataInterface._d_setData_Cpp = ((omniORB.typeMapping["IDL:RTCConfData/confData:1.0"], ), (omniORB.tcInternal.tv_boolean, ), None)
ConfDataInterface._d_getData_Cpp = (((omniORB.tcInternal.tv_string,0), ), (omniORB.tcInternal.tv_boolean, omniORB.typeMapping["IDL:RTCConfData/confData:1.0"]), None)
ConfDataInterface._d_setDataSeq_Cpp = ((omniORB.typeMapping["IDL:RTCConfData/confDataSeq:1.0"], ), (omniORB.tcInternal.tv_boolean, ), None)
ConfDataInterface._d_getDataSeq_Cpp = ((), (omniORB.tcInternal.tv_boolean, omniORB.typeMapping["IDL:RTCConfData/confDataSeq:1.0"]), None)
ConfDataInterface._d_setData_Py = ((omniORB.typeMapping["IDL:RTCConfData/confData:1.0"], ), (omniORB.tcInternal.tv_boolean, ), None)
ConfDataInterface._d_getData_Py = (((omniORB.tcInternal.tv_string,0), ), (omniORB.tcInternal.tv_boolean, omniORB.typeMapping["IDL:RTCConfData/confData:1.0"]), None)
ConfDataInterface._d_setDataSeq_Py = ((omniORB.typeMapping["IDL:RTCConfData/confDataSeq:1.0"], ), (omniORB.tcInternal.tv_boolean, ), None)
ConfDataInterface._d_getDataSeq_Py = ((), (omniORB.tcInternal.tv_boolean, omniORB.typeMapping["IDL:RTCConfData/confDataSeq:1.0"]), None)
ConfDataInterface._d_addModule_Cpp = (((omniORB.tcInternal.tv_string,0), ), (omniORB.tcInternal.tv_boolean, ), None)
ConfDataInterface._d_addModule_Py = (((omniORB.tcInternal.tv_string,0), ), (omniORB.tcInternal.tv_boolean, ), None)
ConfDataInterface._d_startRTCD_Cpp = ((), (omniORB.tcInternal.tv_boolean, ), None)
ConfDataInterface._d_startRTCD_Py = ((), (omniORB.tcInternal.tv_boolean, ), None)
ConfDataInterface._d_exitRTCD_Cpp = ((), (omniORB.tcInternal.tv_boolean, ), None)
ConfDataInterface._d_exitRTCD_Py = ((), (omniORB.tcInternal.tv_boolean, ), None)
ConfDataInterface._d_getRelPath = (((omniORB.tcInternal.tv_string,0), ), ((omniORB.tcInternal.tv_string,0), ), None)
ConfDataInterface._d_setSystem = ((), (omniORB.tcInternal.tv_boolean, ), None)
ConfDataInterface._d_setExRTCList = ((omniORB.typeMapping["IDL:RTCConfData/stringSeq:1.0"], ), (omniORB.tcInternal.tv_boolean, ), None)
ConfDataInterface._d_getExRTCList = ((), (omniORB.tcInternal.tv_boolean, omniORB.typeMapping["IDL:RTCConfData/stringSeq:1.0"]), None)
ConfDataInterface._d_createProject = (((omniORB.tcInternal.tv_string,0), ), (omniORB.tcInternal.tv_boolean, ), None)
ConfDataInterface._d_getProfile = (((omniORB.tcInternal.tv_string,0), ), (omniORB.tcInternal.tv_boolean, omniORB.typeMapping["IDL:RTCConfData/RTC_Profile:1.0"]), None)
ConfDataInterface._d_getProfileList = ((), (omniORB.tcInternal.tv_boolean, omniORB.typeMapping["IDL:RTCConfData/RTC_ProfileList:1.0"]), None)
ConfDataInterface._d_createComp = (((omniORB.tcInternal.tv_string,0), omniORB.tcInternal.tv_short), (omniORB.tcInternal.tv_boolean, ), None)
ConfDataInterface._d_removeComp = (((omniORB.tcInternal.tv_string,0), ), (omniORB.tcInternal.tv_boolean, ), None)

# ConfDataInterface object reference
class _objref_ConfDataInterface (CORBA.Object):
    _NP_RepositoryId = ConfDataInterface._NP_RepositoryId

    def __init__(self):
        CORBA.Object.__init__(self)

    def open(self, *args):
        return _omnipy.invoke(self, "open", _0_RTCConfData.ConfDataInterface._d_open, args)

    def save(self, *args):
        return _omnipy.invoke(self, "save", _0_RTCConfData.ConfDataInterface._d_save, args)

    def setConfData_Cpp(self, *args):
        return _omnipy.invoke(self, "setConfData_Cpp", _0_RTCConfData.ConfDataInterface._d_setConfData_Cpp, args)

    def setConfData_Py(self, *args):
        return _omnipy.invoke(self, "setConfData_Py", _0_RTCConfData.ConfDataInterface._d_setConfData_Py, args)

    def setData_Cpp(self, *args):
        return _omnipy.invoke(self, "setData_Cpp", _0_RTCConfData.ConfDataInterface._d_setData_Cpp, args)

    def getData_Cpp(self, *args):
        return _omnipy.invoke(self, "getData_Cpp", _0_RTCConfData.ConfDataInterface._d_getData_Cpp, args)

    def setDataSeq_Cpp(self, *args):
        return _omnipy.invoke(self, "setDataSeq_Cpp", _0_RTCConfData.ConfDataInterface._d_setDataSeq_Cpp, args)

    def getDataSeq_Cpp(self, *args):
        return _omnipy.invoke(self, "getDataSeq_Cpp", _0_RTCConfData.ConfDataInterface._d_getDataSeq_Cpp, args)

    def setData_Py(self, *args):
        return _omnipy.invoke(self, "setData_Py", _0_RTCConfData.ConfDataInterface._d_setData_Py, args)

    def getData_Py(self, *args):
        return _omnipy.invoke(self, "getData_Py", _0_RTCConfData.ConfDataInterface._d_getData_Py, args)

    def setDataSeq_Py(self, *args):
        return _omnipy.invoke(self, "setDataSeq_Py", _0_RTCConfData.ConfDataInterface._d_setDataSeq_Py, args)

    def getDataSeq_Py(self, *args):
        return _omnipy.invoke(self, "getDataSeq_Py", _0_RTCConfData.ConfDataInterface._d_getDataSeq_Py, args)

    def addModule_Cpp(self, *args):
        return _omnipy.invoke(self, "addModule_Cpp", _0_RTCConfData.ConfDataInterface._d_addModule_Cpp, args)

    def addModule_Py(self, *args):
        return _omnipy.invoke(self, "addModule_Py", _0_RTCConfData.ConfDataInterface._d_addModule_Py, args)

    def startRTCD_Cpp(self, *args):
        return _omnipy.invoke(self, "startRTCD_Cpp", _0_RTCConfData.ConfDataInterface._d_startRTCD_Cpp, args)

    def startRTCD_Py(self, *args):
        return _omnipy.invoke(self, "startRTCD_Py", _0_RTCConfData.ConfDataInterface._d_startRTCD_Py, args)

    def exitRTCD_Cpp(self, *args):
        return _omnipy.invoke(self, "exitRTCD_Cpp", _0_RTCConfData.ConfDataInterface._d_exitRTCD_Cpp, args)

    def exitRTCD_Py(self, *args):
        return _omnipy.invoke(self, "exitRTCD_Py", _0_RTCConfData.ConfDataInterface._d_exitRTCD_Py, args)

    def getRelPath(self, *args):
        return _omnipy.invoke(self, "getRelPath", _0_RTCConfData.ConfDataInterface._d_getRelPath, args)

    def setSystem(self, *args):
        return _omnipy.invoke(self, "setSystem", _0_RTCConfData.ConfDataInterface._d_setSystem, args)

    def setExRTCList(self, *args):
        return _omnipy.invoke(self, "setExRTCList", _0_RTCConfData.ConfDataInterface._d_setExRTCList, args)

    def getExRTCList(self, *args):
        return _omnipy.invoke(self, "getExRTCList", _0_RTCConfData.ConfDataInterface._d_getExRTCList, args)

    def createProject(self, *args):
        return _omnipy.invoke(self, "createProject", _0_RTCConfData.ConfDataInterface._d_createProject, args)

    def getProfile(self, *args):
        return _omnipy.invoke(self, "getProfile", _0_RTCConfData.ConfDataInterface._d_getProfile, args)

    def getProfileList(self, *args):
        return _omnipy.invoke(self, "getProfileList", _0_RTCConfData.ConfDataInterface._d_getProfileList, args)

    def createComp(self, *args):
        return _omnipy.invoke(self, "createComp", _0_RTCConfData.ConfDataInterface._d_createComp, args)

    def removeComp(self, *args):
        return _omnipy.invoke(self, "removeComp", _0_RTCConfData.ConfDataInterface._d_removeComp, args)

    __methods__ = ["open", "save", "setConfData_Cpp", "setConfData_Py", "setData_Cpp", "getData_Cpp", "setDataSeq_Cpp", "getDataSeq_Cpp", "setData_Py", "getData_Py", "setDataSeq_Py", "getDataSeq_Py", "addModule_Cpp", "addModule_Py", "startRTCD_Cpp", "startRTCD_Py", "exitRTCD_Cpp", "exitRTCD_Py", "getRelPath", "setSystem", "setExRTCList", "getExRTCList", "createProject", "getProfile", "getProfileList", "createComp", "removeComp"] + CORBA.Object.__methods__

omniORB.registerObjref(ConfDataInterface._NP_RepositoryId, _objref_ConfDataInterface)
_0_RTCConfData._objref_ConfDataInterface = _objref_ConfDataInterface
del ConfDataInterface, _objref_ConfDataInterface

# ConfDataInterface skeleton
__name__ = "RTCConfData__POA"
class ConfDataInterface (PortableServer.Servant):
    _NP_RepositoryId = _0_RTCConfData.ConfDataInterface._NP_RepositoryId


    _omni_op_d = {"open": _0_RTCConfData.ConfDataInterface._d_open, "save": _0_RTCConfData.ConfDataInterface._d_save, "setConfData_Cpp": _0_RTCConfData.ConfDataInterface._d_setConfData_Cpp, "setConfData_Py": _0_RTCConfData.ConfDataInterface._d_setConfData_Py, "setData_Cpp": _0_RTCConfData.ConfDataInterface._d_setData_Cpp, "getData_Cpp": _0_RTCConfData.ConfDataInterface._d_getData_Cpp, "setDataSeq_Cpp": _0_RTCConfData.ConfDataInterface._d_setDataSeq_Cpp, "getDataSeq_Cpp": _0_RTCConfData.ConfDataInterface._d_getDataSeq_Cpp, "setData_Py": _0_RTCConfData.ConfDataInterface._d_setData_Py, "getData_Py": _0_RTCConfData.ConfDataInterface._d_getData_Py, "setDataSeq_Py": _0_RTCConfData.ConfDataInterface._d_setDataSeq_Py, "getDataSeq_Py": _0_RTCConfData.ConfDataInterface._d_getDataSeq_Py, "addModule_Cpp": _0_RTCConfData.ConfDataInterface._d_addModule_Cpp, "addModule_Py": _0_RTCConfData.ConfDataInterface._d_addModule_Py, "startRTCD_Cpp": _0_RTCConfData.ConfDataInterface._d_startRTCD_Cpp, "startRTCD_Py": _0_RTCConfData.ConfDataInterface._d_startRTCD_Py, "exitRTCD_Cpp": _0_RTCConfData.ConfDataInterface._d_exitRTCD_Cpp, "exitRTCD_Py": _0_RTCConfData.ConfDataInterface._d_exitRTCD_Py, "getRelPath": _0_RTCConfData.ConfDataInterface._d_getRelPath, "setSystem": _0_RTCConfData.ConfDataInterface._d_setSystem, "setExRTCList": _0_RTCConfData.ConfDataInterface._d_setExRTCList, "getExRTCList": _0_RTCConfData.ConfDataInterface._d_getExRTCList, "createProject": _0_RTCConfData.ConfDataInterface._d_createProject, "getProfile": _0_RTCConfData.ConfDataInterface._d_getProfile, "getProfileList": _0_RTCConfData.ConfDataInterface._d_getProfileList, "createComp": _0_RTCConfData.ConfDataInterface._d_createComp, "removeComp": _0_RTCConfData.ConfDataInterface._d_removeComp}

ConfDataInterface._omni_skeleton = ConfDataInterface
_0_RTCConfData__POA.ConfDataInterface = ConfDataInterface
omniORB.registerSkeleton(ConfDataInterface._NP_RepositoryId, ConfDataInterface)
del ConfDataInterface
__name__ = "RTCConfData"

#
# End of module "RTCConfData"
#
__name__ = "rtcconf_idl"

_exported_modules = ( "RTCConfData", )

# The end.
