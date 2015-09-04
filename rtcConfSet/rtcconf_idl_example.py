#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

"""
 @file rtcconf_idl_examplefile.py
 @brief Python example implementations generated from rtcconf.idl
 @date $Date$


"""

import omniORB
from omniORB import CORBA, PortableServer
import RTCConfData, RTCConfData__POA


class ConfDataInterface_i (RTCConfData__POA.ConfDataInterface):
    """
    @class ConfDataInterface_i
    Example class implementing IDL interface RTCConfData.ConfDataInterface
    """

    def __init__(self):
        """
        @brief standard constructor
        Initialise member variables here
        """
        pass

    # boolean open(in string filename)
    def open(self, filename):
        raise CORBA.NO_IMPLEMENT(0, CORBA.COMPLETED_NO)
        # *** Implement me
        # Must return: result

    # boolean save(in string filename)
    def save(self, filename):
        raise CORBA.NO_IMPLEMENT(0, CORBA.COMPLETED_NO)
        # *** Implement me
        # Must return: result

    # boolean setConfData_Cpp(in string filename, out confDataSeq data)
    def setConfData_Cpp(self, filename):
        raise CORBA.NO_IMPLEMENT(0, CORBA.COMPLETED_NO)
        # *** Implement me
        # Must return: result, data

    # boolean setConfData_Py(in string filename, out confDataSeq data)
    def setConfData_Py(self, filename):
        raise CORBA.NO_IMPLEMENT(0, CORBA.COMPLETED_NO)
        # *** Implement me
        # Must return: result, data

    # boolean setData_Cpp(in confData data)
    def setData_Cpp(self, data):
        raise CORBA.NO_IMPLEMENT(0, CORBA.COMPLETED_NO)
        # *** Implement me
        # Must return: result

    # boolean getData_Cpp(in string name, out confData data)
    def getData_Cpp(self, name):
        raise CORBA.NO_IMPLEMENT(0, CORBA.COMPLETED_NO)
        # *** Implement me
        # Must return: result, data

    # boolean setDataSeq_Cpp(in confDataSeq data)
    def setDataSeq_Cpp(self, data):
        raise CORBA.NO_IMPLEMENT(0, CORBA.COMPLETED_NO)
        # *** Implement me
        # Must return: result

    # boolean getDataSeq_Cpp(out confDataSeq data)
    def getDataSeq_Cpp(self):
        raise CORBA.NO_IMPLEMENT(0, CORBA.COMPLETED_NO)
        # *** Implement me
        # Must return: result, data

    # boolean setData_Py(in confData data)
    def setData_Py(self, data):
        raise CORBA.NO_IMPLEMENT(0, CORBA.COMPLETED_NO)
        # *** Implement me
        # Must return: result

    # boolean getData_Py(in string name, out confData data)
    def getData_Py(self, name):
        raise CORBA.NO_IMPLEMENT(0, CORBA.COMPLETED_NO)
        # *** Implement me
        # Must return: result, data

    # boolean setDataSeq_Py(in confDataSeq data)
    def setDataSeq_Py(self, data):
        raise CORBA.NO_IMPLEMENT(0, CORBA.COMPLETED_NO)
        # *** Implement me
        # Must return: result

    # boolean getDataSeq_Py(out confDataSeq data)
    def getDataSeq_Py(self):
        raise CORBA.NO_IMPLEMENT(0, CORBA.COMPLETED_NO)
        # *** Implement me
        # Must return: result, data

    # boolean addModule_Cpp(in string filepath)
    def addModule_Cpp(self, filepath):
        raise CORBA.NO_IMPLEMENT(0, CORBA.COMPLETED_NO)
        # *** Implement me
        # Must return: result

    # boolean addModule_Py(in string filepath)
    def addModule_Py(self, filepath):
        raise CORBA.NO_IMPLEMENT(0, CORBA.COMPLETED_NO)
        # *** Implement me
        # Must return: result

    # boolean startRTCD_Cpp()
    def startRTCD_Cpp(self):
        raise CORBA.NO_IMPLEMENT(0, CORBA.COMPLETED_NO)
        # *** Implement me
        # Must return: result

    # boolean startRTCD_Py()
    def startRTCD_Py(self):
        raise CORBA.NO_IMPLEMENT(0, CORBA.COMPLETED_NO)
        # *** Implement me
        # Must return: result

    # boolean exitRTCD_Cpp()
    def exitRTCD_Cpp(self):
        raise CORBA.NO_IMPLEMENT(0, CORBA.COMPLETED_NO)
        # *** Implement me
        # Must return: result

    # boolean exitRTCD_Py()
    def exitRTCD_Py(self):
        raise CORBA.NO_IMPLEMENT(0, CORBA.COMPLETED_NO)
        # *** Implement me
        # Must return: result


if __name__ == "__main__":
    import sys
    
    # Initialise the ORB
    orb = CORBA.ORB_init(sys.argv)
    
    # As an example, we activate an object in the Root POA
    poa = orb.resolve_initial_references("RootPOA")

    # Create an instance of a servant class
    servant = ConfDataInterface_i()

    # Activate it in the Root POA
    poa.activate_object(servant)

    # Get the object reference to the object
    objref = servant._this()
    
    # Print a stringified IOR for it
    print orb.object_to_string(objref)

    # Activate the Root POA's manager
    poa._get_the_POAManager().activate()

    # Run the ORB, blocking this thread
    orb.run()

