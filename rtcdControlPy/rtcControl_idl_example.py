#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

"""
 @file rtcControl_idl_examplefile.py
 @brief Python example implementations generated from rtcControl.idl
 @date $Date$


"""

import omniORB
from omniORB import CORBA, PortableServer
import rtcControl, rtcControl__POA


class RTCDataInterface_i (rtcControl__POA.RTCDataInterface):
    """
    @class RTCDataInterface_i
    Example class implementing IDL interface rtcControl.RTCDataInterface
    """

    def __init__(self):
        """
        @brief standard constructor
        Initialise member variables here
        """
        pass

    # boolean getRTC(out rtcPathSeq paths)
    def getRTC(self):
        raise CORBA.NO_IMPLEMENT(0, CORBA.COMPLETED_NO)
        # *** Implement me
        # Must return: result, paths

    # boolean createComp(in string filename, in string filepath)
    def createComp(self, filename, filepath):
        raise CORBA.NO_IMPLEMENT(0, CORBA.COMPLETED_NO)
        # *** Implement me
        # Must return: result

    # boolean removeComp(in string name)
    def removeComp(self, name):
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
    servant = RTCDataInterface_i()

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

