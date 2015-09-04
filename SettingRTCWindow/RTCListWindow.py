#!/bin/env python
# -*- encoding: utf-8 -*-

##
#   @file .py
#   @brief 



import thread


import optparse
import sys,os,platform
import traceback
import re
import time
import random
import commands
import math
import imp
import webbrowser

import rtctree.tree

import RTC
import OpenRTM_aist

from OpenRTM_aist import CorbaNaming
from OpenRTM_aist import RTObject
from OpenRTM_aist import CorbaConsumer
from omniORB import CORBA
import CosNaming

from PyQt4 import QtCore, QtGui, QtWebKit


import imp

#from wasanbon.core.rtc.rtcprofile import RTCProfile

#import RTCConfData



def searchFile(name, dir):
    wk = os.walk(dir)
    for i in wk:
        
        for f in i[2]:
            if f == name:
                filepath = os.path.join(i[0],f)
                return filepath
    return ""


def getDirList(dir):
    ans = []
    files = os.listdir(dir)
    for f in files:
        path = os.path.join(dir,f)
        if os.path.isdir(path):
            ans.append(f)
    return ans

"""
class RTComponentProfile():
    def __init__(self):
        pass

    def setBasicInfo_doc(self, doc):
        reference = self.getKeyItem(doc,"rtcDoc:reference")
        license = self.getKeyItem(doc,"rtcDoc:license")
        creator = self.getKeyItem(doc,"rtcDoc:creator")
        algorithm = self.getKeyItem(doc,"rtcDoc:algorithm")
        inouts = self.getKeyItem(doc,"rtcDoc:inout")
        description = self.getKeyItem(doc,"rtcDoc:description")
        return RTCConfData.BasicInfo_Doc(reference,license,creator,algorithm,inouts,description)

    def setBasicInfo(self, rp):
        type = self.getKeyItem(rp.basicInfo,"xsi:type")
        saveProject = self.getKeyItem(rp.basicInfo,"rtcExt:saveProject")
        updateDate = self.getKeyItem(rp.basicInfo,"rtc:updateDate")
        creationDate = self.getKeyItem(rp.basicInfo,"rtc:creationDate")
        abstracts = self.getKeyItem(rp.basicInfo,"rtc:abstract")
        version = self.getKeyItem(rp.basicInfo,"rtc:version")
        vendor = self.getKeyItem(rp.basicInfo,"rtc:vendor")
        maxInstances = self.getKeyItem(rp.basicInfo,"rtc:maxInstances")
        executionType = self.getKeyItem(rp.basicInfo,"rtc:executionType")
        executionRate = self.getKeyItem(rp.basicInfo,"rtc:executionRate")
        description = self.getKeyItem(rp.basicInfo,"rtc:description")
        category = self.getKeyItem(rp.basicInfo,"rtc:category")
        componentKind = self.getKeyItem(rp.basicInfo,"rtc:componentKind")
        activityType = self.getKeyItem(rp.basicInfo,"rtc:activityType")
        componentType = self.getKeyItem(rp.basicInfo,"rtc:componentType")
        name = self.getKeyItem(rp.basicInfo,"rtc:name")
        doc = self.setBasicInfo_doc(rp.basicInfo.doc)
        return RTCConfData.BasicInfo(type,saveProject,updateDate,creationDate,abstracts,version,vendor,maxInstances,executionType,executionRate,description,category,componentKind,activityType,componentType,name,doc)
        

    def setAction(self, status):
        type = self.getKeyItem(status,"xsi:type")
        implemented = status.implemented

        return RTCConfData.Action(type, implemented)

    def setActions(self, rp):
        OnInitialize = self.setAction(rp.actions.OnInitialize)
        OnFinalize = self.setAction(rp.actions.OnFinalize)
        OnStartup = self.setAction(rp.actions.OnStartup)
        OnShutdown = self.setAction(rp.actions.OnShutdown)
        OnActivated = self.setAction(rp.actions.OnActivated)
        OnDeactivated = self.setAction(rp.actions.OnDeactivated)
        OnAborting = self.setAction(rp.actions.OnAborting)
        OnError = self.setAction(rp.actions.OnError)
        OnReset = self.setAction(rp.actions.OnReset)
        OnExecute = self.setAction(rp.actions.OnExecute)
        OnStateUpdate = self.setAction(rp.actions.OnStateUpdate)
        OnRateChanged = self.setAction(rp.actions.OnRateChanged)
        OnAction = self.setAction(rp.actions.OnAction)
        OnModeChanged = self.setAction(rp.actions.OnModeChanged)

        return RTCConfData.Actions(OnInitialize,OnFinalize,OnStartup,OnShutdown,OnActivated,OnDeactivated,OnAborting,OnError,OnReset,OnExecute,OnStateUpdate,OnRateChanged,OnAction,OnModeChanged)

    def setConfiguration_Doc(self, doc):
        constraint = self.getKeyItem(doc,"rtcDoc:constraint")
        range = self.getKeyItem(doc,"rtcDoc:range")
        unit = self.getKeyItem(doc,"rtcDoc:unit")
        description = self.getKeyItem(doc,"rtcDoc:description")
        defaultValue = self.getKeyItem(doc,"rtcDoc:defaultValue")
        dataname = self.getKeyItem(doc,"rtcDoc:dataname")
        return RTCConfData.Configuration_Doc(constraint,range,unit,description,defaultValue,dataname)

    def setConfiguration_Properties(self, conf):
        value = ""
        name = ""
        return RTCConfData.Configuration_Properties(value,name)

    def setConfiguration(self, conf):
        type = self.getKeyItem(conf,"xsi:type")
        variableName = self.getKeyItem(conf,"rtcExt:variableName")
        unit = self.getKeyItem(conf,"rtc:unit")
        defaultValue = self.getKeyItem(conf,"rtc:defaultValue")
        dataType = self.getKeyItem(conf,"rtc:type")
        name = self.getKeyItem(conf,"rtc:name")
        property = self.setConfiguration_Properties(conf)
        doc = self.setConfiguration_Doc(conf.doc)

        return RTCConfData.Configuration(type,variableName,unit,defaultValue,dataType,name,property,doc)

    def setDataPort_Doc(self, doc):
        operation = self.getKeyItem(doc,"rtcDoc:operation")
        occerrence = self.getKeyItem(doc,"rtcDoc:occerrence")
        unit = self.getKeyItem(doc,"rtcDoc:unit")
        semantics = self.getKeyItem(doc,"rtcDoc:semantics")
        number = self.getKeyItem(doc,"rtcDoc:number")
        type = self.getKeyItem(doc,"rtcDoc:type")
        description = self.getKeyItem(doc,"rtcDoc:description")
        return RTCConfData.DataPort_Doc(operation,occerrence,unit,semantics,number,type,description)

    def setDataPort(self, dp):
        type = self.getKeyItem(dp,"xsi:type")
        position = self.getKeyItem(dp,"rtcExt:position")
        variableName = self.getKeyItem(dp,"rtcExt:variableName")
        unit = self.getKeyItem(dp,"rtc:unit")
        subscriptionType = self.getKeyItem(dp,"rtc:subscriptionType")
        dataflowType = self.getKeyItem(dp,"rtc:dataflowType")
        interfaceType = self.getKeyItem(dp,"rtc:interfaceType")
        idlFile = self.getKeyItem(dp,"rtc:idlFile")
        datatype = self.getKeyItem(dp,"rtc:type")
        name = self.getKeyItem(dp,"rtc:name")
        portType = self.getKeyItem(dp,"rtc:portType")
        doc = self.setDataPort_Doc(dp.doc)

        return RTCConfData.DataPort(type,position,variableName,unit,subscriptionType,dataflowType,interfaceType,idlFile,datatype,name,portType,doc)

    def setServiceInterface_Doc(self, doc):
        docPostCondition = self.getKeyItem(doc,"rtcDoc:docPostCondition")
        docPreCondition = self.getKeyItem(doc,"rtcDoc:docPreCondition")
        docException = self.getKeyItem(doc,"rtcDoc:docException")
        docReturn = self.getKeyItem(doc,"rtcDoc:docReturn")
        docArgument = self.getKeyItem(doc,"rtcDoc:docArgument")
        description = self.getKeyItem(doc,"rtcDoc:description")

        return RTCConfData.ServiceInterface_Doc(docPostCondition,docPreCondition,docException,docReturn,docArgument,description)

    def setServiceInterface(self, interface):
        type = self.getKeyItem(interface,"xsi:type")
        variableName = self.getKeyItem(interface,"rtcExt:variableName")
        path = self.getKeyItem(interface,"rtc:path")
        interfeceType = self.getKeyItem(interface,"rtc:type")
        idlFile = self.getKeyItem(interface,"rtc:idlFile")
        instanceName = self.getKeyItem(interface,"rtc:instanceName")
        direction = self.getKeyItem(interface,"rtc:direction")
        name = self.getKeyItem(interface,"rtc:name")
        
        doc = self.setServiceInterface_Doc(interface.doc)

        return RTCConfData.ServiceInterface(type,variableName,path,interfeceType,idlFile,instanceName,direction,name,doc)

    def setServicePort_Doc(self, doc):
        ifdescription = self.getKeyItem(doc,"rtcDoc:ifdescription")
        description = self.getKeyItem(doc,"rtcDoc:description")
        

        return RTCConfData.ServicePort_Doc(ifdescription,description)

    def setServicePort(self, sp):
        type = self.getKeyItem(sp,"xsi:type")
        position = self.getKeyItem(sp,"rtcExt:position")
        name = self.getKeyItem(sp,"rtc:name")



        interfaces = []
        for i in sp.serviceInterfaces:
            interfaces.append(self.setServiceInterface(i))

        doc = self.setServicePort_Doc(sp.doc)

        return RTCConfData.ServicePort(type,position,name,interfaces,doc)

    def getProfile(self, name):
        filename = searchFile("RTC.xml",os.path.join("Components",name))
        
        ans = True
        if filename != "":
            rp = RTCProfile(filename)
        else:
            rp = RTCProfile()
            ans = False
            
        info = self.setBasicInfo(rp)
        act = self.setActions(rp)
        confs = []
        if rp.configurationSet:
            for c in rp.configurationSet.configurations:
                confs.append(self.setConfiguration(c))
        dports = []
        for d in rp.getDataPorts():
            dports.append(self.setDataPort(d))
            
        sports = []

        for s in rp.serviceports:
            sports.append(self.setServicePort(s))
            
        name = name
        version = self.getKeyItem(rp,"rtc:version")
        id = self.getKeyItem(rp,"rtc:id")
        language = rp.getLanguage()

        return (ans, RTCConfData.RTC_Profile(name,version,id,language,info,act,confs,dports,sports))

    def createComp(self, name):
        return True

    def removeComp(self, name):
        return True

    def getProfileList(self):
        profileList = []
        dirs = getDirList("../Components")
        for d in dirs:
            profile = self.getProfile(d)
            if profile[0]:
                profileList.append(profile[1])

        return (True, profileList)

    def getKeyItem(self, obj, key):
        
        if key in obj.keys():
            
            return obj[key]
        return ""

"""



class RenderPath_s(QtGui.QWidget):
    def __init__(self, parent=None):
        super(RenderPath_s, self).__init__(parent)
        self.path = QtGui.QPainterPath()

        self.penWidth = 1
        self.rotationAngle = 0

        self.centerPoint_x = 50
        self.centerPoint_y = 50

        self.pos_x = 0
        self.pos_y = 0

        self.setBackgroundRole(QtGui.QPalette.Base)
        
    def setPath(self, path):
        self.path = path

    def setFillRule(self, rule):
        self.path.setFillRule(rule)
        

    def setFillGradient(self, color1, color2):
        self.fillColor1 = color1
        self.fillColor2 = color2
        

    def setPenWidth(self, width):
        self.penWidth = width
        

    def setPenColor(self, color):
        self.penColor = color
        

    def setRotationAngle(self, degrees):
        self.rotationAngle = degrees

    def setCenterPoint(self, x, y):
        self.centerPoint_x = x
        self.centerPoint_y = y

    def setPosition(self, x, y):
        self.pos_x = x
        self.pos_y = y

    def updatePaint(self, painter):
        
        #painter = QtGui.QPainter(self.parent)
        painter.setRenderHint(QtGui.QPainter.Antialiasing)
        painter.scale(self.scene().width() / 100.0, self.scene().height() / 100.0)
        painter.translate(self.centerPoint_x, self.centerPoint_y)
        painter.rotate(-self.rotationAngle)
        painter.translate(-self.centerPoint_x, -self.centerPoint_y)

        painter.translate(self.pos_x, self.pos_y)

        painter.setPen(QtGui.QPen(self.penColor, self.penWidth,
                QtCore.Qt.SolidLine, QtCore.Qt.RoundCap, QtCore.Qt.RoundJoin))
        gradient = QtGui.QLinearGradient(0, 0, 0, 100)
        gradient.setColorAt(0.0, self.fillColor1)
        gradient.setColorAt(1.0, self.fillColor2)
        painter.setBrush(QtGui.QBrush(gradient))
        painter.drawPath(self.path)

class RenderPath(QtGui.QGraphicsItem):
    def __init__(self, scene, parent=None):
        super(RenderPath, self).__init__(parent,scene)
        #self.scene = scene
        #scene.addItem(self)
        self.path = QtGui.QPainterPath()
        #self.parent = parent
        self.penWidth = 1
        self.rotationAngle = 0

        self.centerPoint_x = 50
        self.centerPoint_y = 50

        self.pos_x = 0
        self.pos_y = 0

        self.width = 10
        self.height = 10

    def setPath(self, path):
        self.path = path

    def setFillRule(self, rule):
        self.path.setFillRule(rule)
        

    def setFillGradient(self, color1, color2):
        self.fillColor1 = color1
        self.fillColor2 = color2
        

    def setPenWidth(self, width):
        self.penWidth = width
        

    def setPenColor(self, color):
        self.penColor = color
        

    def setRotationAngle(self, degrees):
        self.rotationAngle = degrees

    def setCenterPoint(self, x, y):
        self.centerPoint_x = x
        self.centerPoint_y = y

    def setPosition(self, x, y):
        self.pos_x = x
        self.pos_y = y

    def boundingRect(self):
        pos_x = self.pos_x*self.scene().width()/100.0
        pos_y = self.pos_y*self.scene().height()/100.0
        width = self.width*self.scene().width()/100.0
        height = self.height*self.scene().height()/100.0
        
        if width < 0:
            pos_x += width
            width = -width

        if height < 0:
            pos_y += height
            height = -height
        
        return QtCore.QRectF(pos_x, pos_y, width, height)
        
    def drawText(self, text, painter, portsize, position, color=[0,0,0], size=10):
        
        if position == Port.LEFT:
            posx = 0
            posy = self.pos_y
        elif position == Port.RIGHT:
            posx = self.pos_x
            posy = self.pos_y
        elif position == Port.TOP:
            posx = self.pos_x
            posy = self.pos_y - portsize
        elif position == Port.BOTTOM:
            posx = self.pos_x
            posy = self.pos_y + portsize
        #painter = QtGui.QPainter(self.parent)
        #painter.scale(self.parent.width() / 100.0, self.parent.height() / 100.0)
        painter.setPen(QtGui.QColor(color[0], color[1], color[2]))
        painter.setFont(QtGui.QFont('Decorative', size))
        
        painter.drawText(posx*self.scene().width()/100.0, posy*self.scene().height()/100.0, text)  


    def paint(self, painter, option, widget=None):
        self.updatePaint(painter)
        
    def updatePaint(self, painter):
        
        #painter = QtGui.QPainter(self.parent)
        painter.setRenderHint(QtGui.QPainter.Antialiasing)
        painter.scale(self.scene().width() / 100.0, self.scene().height() / 100.0)
        painter.translate(self.centerPoint_x, self.centerPoint_y)
        painter.rotate(-self.rotationAngle)
        painter.translate(-self.centerPoint_x, -self.centerPoint_y)

        painter.translate(self.pos_x, self.pos_y)

        painter.setPen(QtGui.QPen(self.penColor, self.penWidth,
                QtCore.Qt.SolidLine, QtCore.Qt.RoundCap, QtCore.Qt.RoundJoin))
        gradient = QtGui.QLinearGradient(0, 0, 0, 100)
        gradient.setColorAt(0.0, self.fillColor1)
        gradient.setColorAt(1.0, self.fillColor2)
        painter.setBrush(QtGui.QBrush(gradient))
        painter.drawPath(self.path)
        
    

class Port(RenderPath):
    LEFT = 0
    RIGHT = 1
    TOP = 2
    BOTTOM = 3
    def __init__(self, profile, defsize, scene, parent):
        super(Port, self).__init__(scene, parent)
        self.profile = profile
        self.defsize = defsize
        #self.parent = parent

        
        self.size = defsize

class ServicePort(Port):
    def __init__(self, profile, defsize, scene, parent):
        Port.__init__(self, profile, defsize, scene, parent)


        
        
        rectPath = self.getPath()

        #self.renderPath = RenderPath(rectPath,self.parent)

        color = QtGui.QColor("black")
        self.setPenColor(color)

        color1 = QtGui.QColor("yellow")
        color2 = QtGui.QColor("yellow")

        self.setFillGradient(color1,color2)

        self.setCenterPoint(0,0)

        
        #self.renderPath.setPosition(30,30)
        #self.renderPath.setRotationAngle(45)

    def getPath(self):
        rectPath = QtGui.QPainterPath()

        
        
        if self.profile.position == "LEFT":
            rectPath.moveTo(0, 0)
            rectPath.lineTo(-self.size, 0)
            rectPath.lineTo(-self.size, self.size)
            rectPath.lineTo(0, self.size)

            self.position = Port.LEFT
            self.width = -self.size
            self.height = self.size

        elif self.profile.position == "RIGHT":
            rectPath.moveTo(0, 0)
            rectPath.lineTo(self.size, 0)
            rectPath.lineTo(self.size, self.size)
            rectPath.lineTo(0, self.size)

            self.position = Port.RIGHT
            self.width = self.size
            self.height = self.size

        elif self.profile.position == "TOP":
            rectPath.moveTo(0, 0)
            rectPath.lineTo(0, -self.size)
            rectPath.lineTo(self.size, -self.size)
            rectPath.lineTo(self.size, 0)

            self.position = Port.TOP
            self.width = self.size
            self.height = -self.size

        elif self.profile.position == "BOTTOM":
            rectPath.moveTo(0, 0)
            rectPath.lineTo(0, self.size)
            rectPath.lineTo(self.size, self.size)
            rectPath.lineTo(self.size, 0)

            self.position = Port.BOTTOM
            self.width = self.size
            self.height = self.size

        rectPath.closeSubpath()

        return rectPath

    def setSize(self, size):
        self.size = size
        path = self.getPath()
        self.setPath(path)

    def paint(self, painter, option, widget=None):
        text = self.profile.name
        self.drawText(text, painter, self.size, self.position)
        self.updatePaint(painter)

    def mouseDoubleClickEvent(self, event):
        self.vw = ViewServicePort(self.profile)
        self.vw.show()
    
        

class DataPort(Port):
    def __init__(self, profile, defsize, scene, parent):
        Port.__init__(self, profile, defsize, scene, parent)
        
        rectPath = self.getPath()
        

        #self.renderPath = RenderPath(rectPath,self.parent)

        color = QtGui.QColor("black")
        self.setPenColor(color)

        color1 = QtGui.QColor("yellow")
        color2 = QtGui.QColor("yellow")

        self.setFillGradient(color1,color2)

        self.setCenterPoint(0,0)
        #self.renderPath.setPosition(30,30)
        #self.renderPath.setRotationAngle(45)

    def getPath(self):
        rectPath = QtGui.QPainterPath()
        

        if self.profile.portType == "DataInPort" and self.profile.position == "LEFT":
            rectPath.moveTo(0, 0)
            rectPath.lineTo(-self.size, 0)
            rectPath.lineTo(-self.size/2.0, self.size/2.0)
            rectPath.lineTo(-self.size, self.size)
            rectPath.lineTo(0, self.size)

            self.position = Port.LEFT
            self.width = -self.size
            self.height = self.size

        elif self.profile.portType == "DataInPort" and self.profile.position == "RIGHT":
            rectPath.moveTo(0, 0)
            rectPath.lineTo(self.size, 0)
            rectPath.lineTo(self.size/2.0, self.size/2.0)
            rectPath.lineTo(self.size, self.size)
            rectPath.lineTo(0, self.size)

            self.position = Port.RIGHT
            self.width = self.size
            self.height = self.size


        elif self.profile.portType == "DataInPort" and self.profile.position == "TOP":
            rectPath.moveTo(0, 0)
            rectPath.lineTo(0, -self.size)
            rectPath.lineTo(self.size/2.0, -self.size/2.0)
            rectPath.lineTo(self.size, -self.size)
            rectPath.lineTo(self.size, 0)

            self.position = Port.TOP
            self.width = self.size
            self.height = -self.size


        elif self.profile.portType == "DataInPort" and self.profile.position == "BOTTOM":
            rectPath.moveTo(0, 0)
            rectPath.lineTo(0, self.size)
            rectPath.lineTo(self.size/2.0, self.size/2.0)
            rectPath.lineTo(self.size, self.size)
            rectPath.lineTo(self.size, 0)

            self.position = Port.BOTTOM
            self.width = self.size
            self.height = self.size

        elif self.profile.portType == "DataOutPort" and self.profile.position == "LEFT":
            rectPath.moveTo(0, 0)
            rectPath.lineTo(-self.size, self.size/2.0)
            rectPath.lineTo(0, self.size)

            self.position = Port.LEFT
            self.width = -self.size
            self.height = self.size

        elif self.profile.portType == "DataOutPort" and self.profile.position == "RIGHT":
            rectPath.moveTo(0, 0)
            rectPath.lineTo(self.size, self.size/2.0)
            rectPath.lineTo(0, self.size)


            self.position = Port.RIGHT
            self.width = self.size
            self.height = self.size

        elif self.profile.portType == "DataOutPort" and self.profile.position == "TOP":
            rectPath.moveTo(0, 0)
            rectPath.lineTo(self.size/2.0, -self.size)
            rectPath.lineTo(self.size, 0)


            self.position = Port.TOP
            self.width = self.size
            self.height = -self.size

        elif self.profile.portType == "DataOutPort" and self.profile.position == "BOTTOM":
            rectPath.moveTo(0, 0)
            rectPath.lineTo(self.size/2.0, self.size)
            rectPath.lineTo(self.size, 0)


            self.position = Port.BOTTOM
            self.width = self.size
            self.height = self.size

        
            
        rectPath.closeSubpath()

        return rectPath

    def setSize(self, size):
        self.size = size
        path = self.getPath()
        self.setPath(path)

    def paint(self, painter, option, widget=None):
        text = self.profile.name + "(" + self.profile.datatype + ")"
        self.drawText(text, painter, self.size, self.position)
        self.updatePaint(painter)

    def mouseDoubleClickEvent(self, event):
        self.vw = ViewDataPort(self.profile)
        self.vw.show()
    

class RenderRTC(RenderPath):
    def __init__(self, profile, scene, parent=None):
        super(RenderRTC, self).__init__(scene, parent)

        self.profile = profile
        
        #print self.parentWidget()

        self.rtc_defsize_x = 50
        self.rtc_defsize_y = 60
        #self.rtc_defsize_y = 60
        self.rtc_defpos_x = 25
        self.rtc_defpos_y = 20

        #self.maxSize_port = self.rtc_defsize_y*0.33
        #self.minSize_x = 30
        #self.minSize_y = 20

        #self.rtc_scale = 0.2
        

        self.dataports = []
        self.serviceports = []
        self.setRTC()

        #rp = RTCProfile('RTC.xml')

        

        
        for i in self.profile.dports:
            self.addDataPort(i)

        for i in self.profile.sports:
            self.addServicePort(i)
            #print i.keys()

        
        
        #self.addDataPort()

    def setRTC(self):
        """lc = len(self.countPort(Port.LEFT))
        rc = len(self.countPort(Port.RIGHT))

        

        count = lc
        if count < rc:
            count = rc

        print count
        size = self.rtc_defsize*self.rtc_scale*count*1.5"""

        """cdps_l = len(self.countPort(Port.LEFT)) + 2
        cdps_r = len(self.countPort(Port.RIGHT)) + 2
        cdps_t = len(self.countPort(Port.TOP)) + 2
        cdps_b = len(self.countPort(Port.BOTTOM)) + 2

        
        count_h = cdps_l
        if count_h < cdps_r:
            count_h = cdps_r

        size_x = self.rtc_defsize*self.rtc_scale*count_h*1.5

        count_v = cdps_t
        if count_v < cdps_b:
            count_v = cdps_b


        size_y = self.rtc_defsize*self.rtc_scale*count_v*1.5
        
        self.size_x = self.minSize_x
        if self.size_x < size_x:
            self.size_x = size_x

        self.size_y = self.minSize_y
        if self.size_y < size_y:
            self.size_y = size_y
        """

        self.path = QtGui.QPainterPath()
        self.path.moveTo(self.rtc_defpos_x, self.rtc_defpos_y)
        self.path.lineTo(self.rtc_defpos_x+self.rtc_defsize_x, self.rtc_defpos_y)
        self.path.lineTo(self.rtc_defpos_x+self.rtc_defsize_x, self.rtc_defpos_y+self.rtc_defsize_y)
        self.path.lineTo(self.rtc_defpos_x, self.rtc_defpos_y+self.rtc_defsize_y)
        self.path.closeSubpath()

        
        #self.RenderPath = RenderPath(rectPath,self)

        color = QtGui.QColor("black")
        self.setPenColor(color)

        color1 = QtGui.QColor("blue")
        color2 = QtGui.QColor("blue")

        self.setFillGradient(color1,color2)

        

    def addPort(self):
        
        size,count_d = self.calcPortSize()

        tmp = self.serviceports[:]
        tmp.extend(self.dataports)
        
        

        

        count = [0,0,0,0]

        offxsize = (self.rtc_defsize_x - size*float(count_d))/(float(count_d)+1.0)

        for dp in tmp:

            if dp.position == Port.LEFT:
                dp.setPosition(self.rtc_defpos_x,self.rtc_defpos_y+size*2.0*(float(count[dp.position])+0.5))
            elif dp.position == Port.RIGHT:
                dp.setPosition(self.rtc_defpos_x+self.rtc_defsize_x,self.rtc_defpos_y+size*2.0*(float(count[dp.position])+0.5))
            elif dp.position == Port.TOP:
                dp.setPosition(self.rtc_defpos_x+size*float(count[dp.position])+offxsize*float(count[dp.position]+1),self.rtc_defpos_y)
            elif dp.position == Port.BOTTOM:
                dp.setPosition(self.rtc_defpos_x+size*float(count[dp.position])+offxsize*float(count[dp.position]+1),self.rtc_defpos_y+self.rtc_defsize_y)
            count[dp.position] += 1
            dp.setSize(size)

        """
        if dp.position == Port.LEFT:
            dp.renderPath.setPosition(self.rtc_defpos_x,self.rtc_defpos_y+size*1.5*count)
        elif dp.position == Port.RIGHT:
            dp.renderPath.setPosition(self.rtc_defpos_x+self.size_x,self.rtc_defpos_y+size*1.5*count)
        elif dp.position == Port.TOP:
            dp.renderPath.setPosition(self.rtc_defpos_x+size*1.5*count,self.rtc_defpos_y)
        elif dp.position == Port.BOTTOM:
            dp.renderPath.setPosition(self.rtc_defpos_x+size*1.5*count,self.rtc_defpos_y+self.size_y)
        """

    def calcPortSize(self):

        

        cdps_l = len(self.countPort(Port.LEFT))
        cdps_r = len(self.countPort(Port.RIGHT))
        cdps_t = len(self.countPort(Port.TOP))
        cdps_b = len(self.countPort(Port.BOTTOM))

        
        count = cdps_l
        if count < cdps_r:
            count = cdps_r
        if count < cdps_t:
            count = cdps_t
        if count < cdps_b:
            count = cdps_b

        #count -= 1

        if count == 0:
            count = 1

        return self.rtc_defsize_y/(1.0+float(count*2)),count
        #return self.maxSize_port/count
        
    def addServicePort(self, profile):
        
        
        size,count = self.calcPortSize()
        
        dp = ServicePort(profile,size,self.scene(),self)

        
            
        self.serviceports.append(dp)
        self.setRTC()

        self.addPort()

    def countPort(self, position):
        ans = []
        for d in self.dataports:
            if d.position == position:
                ans.append(d)
        for d in self.serviceports:
            if d.position == position:
                ans.append(d)

        return ans
        

    def addDataPort(self, profile):
        
        size,count = self.calcPortSize()
        
        dp = DataPort(profile,size,self.scene(),self)

        
        
        self.dataports.append(dp)
        self.setRTC()

        self.addPort()

    """def minimumSizeHint(self):
        return QtCore.QSize(50, 50)

    def sizeHint(self):
        return QtCore.QSize(100, 100)"""
    

    #def paintEvent(self, event):
    def paint(self, painter, option, widget=None):
        self.updatePaint(painter)
        
def addLineEditBox(name, text, layout):
    nameLabel = QtGui.QLabel(name)
    nameEdit = QtGui.QLineEdit()
    nameLabel.setBuddy(nameEdit)

    nameEdit.setText(text)

    subLayout = QtGui.QHBoxLayout()
    subLayout.addWidget(nameLabel)
    subLayout.addWidget(nameEdit)
        
    layout.addLayout(subLayout)

def openWeb(url):
    webbrowser.open(str(url.toString().toLocal8Bit()))

def addWebView(name, text, layout):
    nameLabel = QtGui.QLabel(name)
    nameEdit = QtWebKit.QWebView()
    nameEdit.page().setLinkDelegationPolicy(QtWebKit.QWebPage.DelegateAllLinks)
    nameLabel.setBuddy(nameEdit)

    nameEdit.setHtml(text)
    nameEdit.linkClicked.connect(openWeb)

    subLayout = QtGui.QHBoxLayout()
    subLayout.addWidget(nameLabel)
    subLayout.addWidget(nameEdit)
        
    layout.addLayout(subLayout)

def addTextEditBox(name, text, layout):
    nameLabel = QtGui.QLabel(name)
    nameEdit = QtGui.QTextEdit()
    nameLabel.setBuddy(nameEdit)

    nameEdit.setText(text)

    subLayout = QtGui.QHBoxLayout()
    subLayout.addWidget(nameLabel)
    subLayout.addWidget(nameEdit)
        
    layout.addLayout(subLayout)



class ViewConfiguration(QtGui.QDialog):
    def __init__(self, profile, parent=None):
        super(ViewConfiguration, self).__init__(parent)
        
        self.setWindowTitle(u"コンフィギュレーションパラメータ")
        self.mainLayout = QtGui.QVBoxLayout()
        self.setLayout(self.mainLayout)

        self.profile = profile

        count = len(profile.confs)
        self.table = QtGui.QTableWidget(count,3)
        
        self.table.setHorizontalHeaderLabels([u"名前", u"デフォルト値", u"データ型"])

        for c in range(len(profile.confs)):
            self.addTable(profile.confs[c],c)

        self.table.itemClicked.connect(self.setTableSlot)

        self.mainLayout.addWidget(self.table)

        self.descriptionEdit = QtGui.QTextEdit()
        self.mainLayout.addWidget(self.descriptionEdit)
        
    def setTableSlot(self, item):
        
        num = self.table.currentRow()
        if num != -1:
            text = self.profile.confs[num].doc.description
            self.descriptionEdit.setText(text)
        

    def addTable(self, conf, num):
        name = QtGui.QTableWidgetItem(conf.name)
        defaultValue = QtGui.QTableWidgetItem(conf.defaultValue)
        detaType = QtGui.QTableWidgetItem(conf.dataType)
            
        self.table.setItem(num, 0, name)
        self.table.setItem(num, 1, defaultValue)
        self.table.setItem(num, 2, detaType)

class ViewServicePort(QtGui.QDialog):
    def __init__(self, profile, parent=None):
        super(ViewServicePort, self).__init__(parent)
        name = profile.name
        self.setWindowTitle(name)
        self.mainLayout = QtGui.QVBoxLayout()
        self.setLayout(self.mainLayout)
        self.profile = profile

        addLineEditBox(u"名前",profile.name,self.mainLayout)
        addTextEditBox(u"概要",profile.doc.description,self.mainLayout)

        


        

       
        count = len(profile.interfaces)
        
        self.table = QtGui.QTableWidget(count,3)
        
        self.table.setHorizontalHeaderLabels([u"名前", u"方向", u"IDLファイル"])

        for c in range(len(profile.interfaces)):
            self.addTable(profile.interfaces[c],c)

        self.table.itemClicked.connect(self.setTableSlot)

        self.mainLayout.addWidget(self.table)

        self.descriptionEdit = QtGui.QTextEdit()
        self.mainLayout.addWidget(self.descriptionEdit)
    def setTableSlot(self, item):
        
        num = self.table.currentRow()
        if num != -1:
            text = self.profile.interfaces[num].doc.description
            self.descriptionEdit.setText(text)
        

    def addTable(self, interface, num):
        name = QtGui.QTableWidgetItem(interface.name)
        direction = QtGui.QTableWidgetItem(interface.direction)
        idlFile = QtGui.QTableWidgetItem(interface.idlFile)
            
        self.table.setItem(num, 0, name)
        self.table.setItem(num, 1, direction)
        self.table.setItem(num, 2, idlFile)
        

class ViewDataPort(QtGui.QDialog):
    def __init__(self, profile, parent=None):
        super(ViewDataPort, self).__init__(parent)
        name = profile.name
        self.setWindowTitle(name)
        self.mainLayout = QtGui.QVBoxLayout()
        self.setLayout(self.mainLayout)
        self.profile = profile
        addLineEditBox(u"名前",profile.name,self.mainLayout)
        addLineEditBox(u"ポート",profile.portType,self.mainLayout)
        addLineEditBox(u"データ型",profile.datatype,self.mainLayout)
        addTextEditBox(u"概要",profile.doc.description,self.mainLayout)
        
class ViewWindow(QtGui.QDialog):
    def __init__(self, profile, parent=None):
        super(ViewWindow, self).__init__(parent)
        name = profile.name
        self.setWindowTitle(name)
        
        self.mainLayout = QtGui.QVBoxLayout()
         
        self.setLayout(self.mainLayout)
        self.profile = profile
        self.scene = QtGui.QGraphicsScene(0, 0, 170, 170)
        
        self.view = QtGui.QGraphicsView(self.scene)
        self.view.setViewportUpdateMode(QtGui.QGraphicsView.BoundingRectViewportUpdate)
        self.view.setBackgroundBrush(QtGui.QColor(230, 200, 167))

        self.view.setMinimumHeight(200)
        
        
        self.mainLayout.addWidget(self.view)
        
        self.renderWindow = RenderRTC(profile, self.scene)

        
        addLineEditBox(u"名前",profile.name,self.mainLayout)
        addLineEditBox(u"バージョン",profile.version,self.mainLayout)
        addLineEditBox(u"言語",profile.language,self.mainLayout)
        addLineEditBox(u"モジュール概要",profile.info.description,self.mainLayout)
        addWebView(u"概要",profile.info.abstracts,self.mainLayout)
        
        self.showConfigurationButton = QtGui.QPushButton(u"コンフィギュレーションパラメータ表示")
        self.showConfigurationButton.clicked.connect(self.showConfigurationSlot)
        self.mainLayout.addWidget(self.showConfigurationButton)
        

    def showConfigurationSlot(self):
        
        self.ViewConfiguration = ViewConfiguration(self.profile,self)
        self.ViewConfiguration.show()
        #self.show()



class RTCItem(QtGui.QGroupBox):
    def __init__(self, profile, m_window=None, name="", parent=None):
        super(RTCItem, self).__init__(name, parent)
        self.profile = profile
        #self.groupBox = QtGui.QGroupBox("")
        self.m_window = m_window
        self.mainLayout = QtGui.QVBoxLayout()
        self.setLayout(self.mainLayout)
        #self.groupBox.setLayout(self.mainLayout)

        self.scene = QtGui.QGraphicsScene(0, 0, 150, 150)
        #bar = self.scene.verticalScrollBar()
        #bar.valueChanged.connect(self.valueChanged)
        #self.scene.changed.connect(self.valueChanged)

        self.view = QtGui.QGraphicsView(self.scene)
        self.view.setViewportUpdateMode(QtGui.QGraphicsView.BoundingRectViewportUpdate)
        self.view.setBackgroundBrush(QtGui.QColor(230, 200, 167))
        self.mainLayout.addWidget(self.view)
        self.renderWindow = RenderRTC(profile, self.scene)
        #self.scene.addItem(self.renderWindow)
        #self.mainLayout.addWidget(self.renderWindow)

        

        self.showProfileButton = QtGui.QPushButton(u"詳細")
        self.showProfileButton.clicked.connect(self.showProfileSlot)
        self.mainLayout.addWidget(self.showProfileButton)

        

        self.runButton = QtGui.QPushButton(u"rtcdで起動")
        self.runButton.clicked.connect(self.runSlot)
        self.mainLayout.addWidget(self.runButton)

        self.runexeButton = QtGui.QPushButton(u"別プロセスで起動")
        self.runexeButton.clicked.connect(self.runexeSlot)
        self.mainLayout.addWidget(self.runexeButton)
        

        

        self.setMinimumSize(200,280)
        self.setMaximumSize(200,280)


    def valueChanged(self, v):
        print self.scene.items()
        for i in self.scene.items():
            pass
            #painter = QtGui.QPainter()
            #i.updatePaint(painter,)
        #self.widget().update()
        

    def showProfileSlot(self):
        self.viewWindow = ViewWindow(self.profile, self)
        self.viewWindow.show()

    def runexeSlot(self):
        self.m_window.createComp(encodestr(self.profile.name),1)
    
    def runSlot(self):
        self.m_window.createComp(encodestr(self.profile.name),0)

def encodestr(s):
    if isinstance(s, unicode):
        return s.encode('utf-8')
    return s

class RTC_Window(QtGui.QWidget):
    def __init__(self, parent=None):
        super(RTC_Window, self).__init__(parent)
        self.tab_widget = QtGui.QTabWidget(self)
        self.mainLayout = QtGui.QVBoxLayout()
        self.setLayout(self.mainLayout)
        self.mainLayout.addWidget(self.tab_widget)
        self.parent = parent
        self.tab_list = {}
    def loadList(self, data):
        category_List = {}
        for i in range(len(data)):
            category_name = data[i].info.category
            if category_name not in category_List:
                category_List[category_name] = []
            category_List[category_name].append(data[i])

        for k,v in category_List.items():
            cw = Category_Window(self)
            cw.loadList(v)
            self.tab_list[k] = cw
            self.tab_widget.addTab(cw,k)
            
            

class Category_Window(QtGui.QWidget):
    def __init__(self, parent=None):
        super(Category_Window, self).__init__(parent)
        self.parent = parent
        self.mainLayout = QtGui.QVBoxLayout()
        self.setLayout(self.mainLayout)
        """rp = RTComponentProfile()
        item1 = RTCItem(rp.getProfile("testXML")[1],"testXML")
        self.mainLayout.addWidget(item1)
        item1 = RTCItem(rp.getProfile("MyFirstComponent")[1],"MyFirstComponent")
        self.mainLayout.addWidget(item1)"""
        self.items = {}
        self.layouts = []
    def loadList(self, data):
        for i in range(len(data)):
            if i%3 == 0:
                self.layouts.append(QtGui.QHBoxLayout())
                self.mainLayout.addLayout(self.layouts[-1])
                
            self.items[data[i].name] = RTCItem(data[i],self.parent.parent,data[i].name)
            self.layouts[-1].addWidget(self.items[data[i].name])
        if len(self.layouts) > 0:
            self.layouts[-1].addStretch(0)
        self.mainLayout.addStretch(0)
            
            
    

class ScrollArea(QtGui.QScrollArea):
    def __init__(self, parent=None):
        super(ScrollArea, self).__init__(parent)
        bar = self.verticalScrollBar()
        bar.valueChanged.connect(self.valueChanged)

    def valueChanged(self, v):
        #print v
        #bar = self.verticalScrollBar()
        #bar->setValue(bar->value() - scrollSize);
        self.widget().update()
        #self.takeWidget().update()



        
