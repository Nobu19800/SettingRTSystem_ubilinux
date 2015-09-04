#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

"""
 @file exitRTCs.py
 @brief rtcConfSetReq.rtcとmanager_composite.mgrを終了させる


"""


import os.path
import sys, traceback
import time
import struct



import rtctree.tree
import rtctree.path


# Import RTM module
import RTC
import OpenRTM_aist







##
# @brief rtcConfSetReq.rtcとmanager_composite.mgrを終了させる
# @param node ノード
def getNode(node):
    #values = node._children.values()
    values = node.children
    for v in values:
        if v.is_component:
            if v.name == "rtcConfSetReq0.rtc" or v.name == "rtcConfSet0.rtc" or v.name == "rtcdControl0.rtc" or v.name == "rtcdControlPy0.rtc":
                try:
                    v.exit()
                except:
                    info = sys.exc_info()
                    tbinfo = traceback.format_tb( info[2] )
                    for tbi in tbinfo:
                        print tbi
        elif v.is_manager:
            
            if v.name == "manager_composite.mgr":
                try:
                    v.shutdown()
                except:
                    info = sys.exc_info()
                    tbinfo = traceback.format_tb( info[2] )
                    for tbi in tbinfo:
                        print tbi
        else:            
            getNode(v)



##
# @brief メイン関数
def main():
    path = ['/', 'localhost']
    tree = rtctree.tree.RTCTree(servers='localhost')
    getNode(tree.get_node(path))
    

if __name__ == "__main__":
    main()