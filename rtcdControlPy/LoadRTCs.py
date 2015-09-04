#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

"""
 @file LoadRTCs.py
 @brief LoadRTCs


"""
import OpenRTM_aist

import sys
import traceback
import os

import struct

import imp


##
# @brief バイナリファイルから文字列読み込み
# @param ifs ファイルストリーム
# @return 文字列
def ReadString(ifs):
    s = struct.unpack("i",ifs.read(4))[0]
    a = ifs.read(s)

    return a

##
# @class RTC_FinalizeListener
# @brief RTC終了時のリスナ(未実装)
# 
# 
class RTC_FinalizeListener:
    ##
    # @brief コンストラクタ
    # @param self
    # @param rtc
    # @param comp_list
    #
    def __init__(self, rtc, comp_list):
        self.rtc = rtc
        self.comp_list = comp_list

    ##
    # @brief コールバック
    # @param self
    # @param ec_id
    # @param ret
    #
    def callback(self, ec_id, ret):
        print self.rtc,self.comp_list

##
# @class LoadRTCs
# @brief RTCのロード、起動関連
# 
# 
class LoadRTCs:
    ##
    # @brief コンストラクタ
    # @param self
    # @param mgr マネージャオブジェクト
    # 
    def __init__(self, mgr):
        self.mgr = mgr
        self.compList = {}

    ##
    # @brief ファイルを開いてRTCを起動
    # @param self
    # 
    def openFile(self):
        prop = OpenRTM_aist.Manager.instance().getConfig()
        value = ""
        value = self.getProperty(prop, "manager.modules.loadRTCs", value)
        if value != "":
            #print value
            if os.path.exists(value):
                f = open(value, 'rb')
                m = struct.unpack("i",f.read(4))[0]
                for i in range(0,m):
                    name = ReadString(f).replace("\0","")
                    filename = ReadString(f).replace("\0","")
                    d = struct.unpack("i",f.read(4))[0]
                    path = ReadString(f).replace("\0","")
                    dir = ReadString(f).replace("\0","")
                    
                    for j in range(0,d):
                        self.createComp(name,filename,dir)
                f.close()

    ##
    # @brief rtc.confの設定を取得する関数
    # @param self
    # @param prop プロパティ
    # @param key キー
    # @param value 値
    # @return 値
    def getProperty(self, prop, key, value):
        
        if  prop.findNode(key) != None:
            #print value
            value = prop.getProperty(key)
        return value

    ##
    # @brief RTCを起動
    # @param self
    # @param name RTC名
    # @param filename ファイル名
    # @param filepath ファイルパス
    # @return 成功でTrue、失敗でFalse
    def createComp(self, name, filename, filepath):
        self.updateCompList()
        filepath = os.path.relpath(filepath)
        
        preLoadComp = None
        if self.compList.has_key(name):
            func = self.compList[name]["func"]
            preLoadComp = self.compList[name]
            
        
                
                

        if preLoadComp == None:    
            func = self.getFunc(filename, filepath)
            if func == None:
                return False
            func(self.mgr)
            
        if func:
            
            comp = self.mgr.createComponent(filename)
            
            if not comp:
                return False
            
            
            if preLoadComp:
                callback_func = RTC_FinalizeListener(comp,preLoadComp)
                preLoadComp["compList"].append({"component":comp,"callback_func":callback_func})
            else:
                
                self.compList[name] = {"filename":filename,"filepath":filepath,"func":func,"compList":[]}

                callback_func = RTC_FinalizeListener(comp,self.compList[name])
                self.compList[name]["compList"].append({"component":comp,"callback_func":callback_func})

            
            #comp.addPostComponentActionListener(OpenRTM_aist.PostComponentActionListenerType.POST_ON_FINALIZE, callback_func.callback)
        else:
            return False

        return True
    
        
    ##
    # @brief RTCを終了
    # @param self
    # @param name RTC名
    # @return 成功でTrue、失敗でFalse    
    def removeComp(self, name):
        self.updateCompList()
        if self.compList.has_key(name):
            if len(self.compList[name]["compList"]) != 0:
                self.compList[name]["compList"][-1]["component"].exit()
                del self.compList[name]["compList"][-1]
            else:
                return False
        else:
            return False
        return True
        
    ##
    # @brief 起動中のRTCのリストを更新(終了している場合はリストから削除)
    # @param self
    def updateCompList(self):
        pass
        for i,c in self.compList.items():
            for j in c["compList"]:
                #print j.getObjRef().get_owned_contexts()
                if j["component"]._exiting:
                    c["compList"].remove(j)
                    
                
                
        
    ##
    # @brief 起動中のRTCのリスト取得
    # @param self
    # @return (True、RTCのリスト)
    def getCompList(self):
        import rtcControl
        self.updateCompList()
        
        names = []
        for i,c in self.compList.items():
            
            if len(c["compList"]) != 0:
                
                data = rtcControl.RTC_Data(i,c["filename"],len(c["compList"]))
                
                names.append(data)
            
                    
        return (True,names)

    ##
    # @brief RTC初期化関数を取得
    # @param self
    # @param filename ファイル名
    # @param filepath ディレクトリパス
    # @return 初期化関数
    def getFunc(self, filename, filepath):
        try:
            sys.path.append(filepath)
            (file, pathname, description) = imp.find_module(filename, [filepath])
            mod = imp.load_module(filename, file, pathname, description)
            func = getattr(mod,filename+"Init",None)

            return func
        except:
            return None

