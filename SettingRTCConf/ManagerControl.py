#!/bin/env python
# -*- encoding: utf-8 -*-

##
#   @file ManagerControl.py
#   @brief マネージャ操作オブジェクト



import thread


import optparse
import sys,os,platform
import re
import time
import random
import commands
import math
import imp



import RTC
import OpenRTM_aist

from OpenRTM_aist import CorbaNaming
from OpenRTM_aist import RTObject
from OpenRTM_aist import CorbaConsumer
from omniORB import CORBA
import CosNaming



##
# @class ManagerControl
# @brief マネージャ操作オブジェクト
#
class ManagerControl:
    TextBox = 1
    Combox = 2
    TextCombox = 3
    SpinBox = 4
    DoubleSpinBox = 5
    ##
    # @brief コンストラクタ
    # @param self 
    # @param conf_filepath 設定ファイルのパス
    def __init__(self, conf_filepath):
        self.conf_filepath = conf_filepath
        
        
        if conf_filepath == "":
            self.mgr = OpenRTM_aist.Manager.init(sys.argv)
        else:
            self.mgr = OpenRTM_aist.Manager.init([os.path.abspath(__file__), '-f', conf_filepath])

        self.mgr.activateManager()
        self.mgr.runManager(True)
        
        
        self.compList = {}

        
        self.SetParam()
        

        
    ##
    # @brief コンフィギュレーションパラメータ設定ファイルを読み込む
    # @param self 
    def SetParam(self):

        self.confNameList = [{"default":"localhost","type":ManagerControl.TextBox,"list":[],"name":"corba.nameservers","label":u"RTC等を登録するネームサーバ"},
                             {"default":"%n.rtc","type":ManagerControl.TextBox,"list":[],"name":"naming.formats","label":u"RTCをネームサーバに登録する際のフォーマット"},
                             {"default":"NORMAL","type":ManagerControl.Combox,"list":["SILENT","ERROR","WARN","NORMAL","INFO","DEBUG","TRACE","VERBOSE","PARANOID"],"name":"logger.log_level","label":u"ログレベル"},
                              {"default":"1000","type":ManagerControl.SpinBox,"list":[],"name":"exec_cxt.periodic.rate","label":u"実行コンテキストの周期"},
                               {"default":"NO","type":ManagerControl.Combox,"list":["YES","NO"],"name":"manager.is_master","label":u"マスターマネージャにするかどうか？"},
                              {"default":"","type":ManagerControl.Combox,"list":[],"name":"manager.modules.load_path","label":u"モジュール探索パス"},
                             {"default":"","type":ManagerControl.Combox,"list":[],"name":"manager.modules.preload","label":u"あらかじめロードしておくモジュール"},
                              {"default":"","type":ManagerControl.Combox,"list":[],"name":"manager.components.precreate","label":u"スタート時に起動するコンポーネント名"},
                             {"default":"1.0","type":ManagerControl.TextBox,"list":[],"name":"config.version","label":u"バージョン"},
                              {"default":"manager","type":ManagerControl.TextBox,"list":[],"name":"manager.name","label":u"managerの名前"},
                            {"default":"%n.mgr","type":ManagerControl.TextBox,"list":[],"name":"manager.naming_formats","label":u"managerの名前のフォーマット"},
                              {"default":"YES","type":ManagerControl.Combox,"list":["YES","NO"],"name":"manager.corba_servant","label":u"マネージャのCORBAサーバントを起動するか"},
                             {"default":"localhost:2810","type":ManagerControl.TextBox,"list":[],"name":"corba.master_manager","label":u"マスターマネージャのアドレスとポート番号"},
                             {"default":"YES","type":ManagerControl.Combox,"list":["YES","NO"],"name":"manager.shutdown_on_nortcs","label":u"RTCが一つもなくなった場合にプロセスを終了させるかどうか(RTCの削除で判定)"},
                              {"default":"YES","type":ManagerControl.Combox,"list":["YES","NO"],"name":"manager.shutdown_auto","label":u"RTCが一つもなくなった場合にプロセスを終了させるかどうか(時間で判定)"},
                             {"default":"","type":ManagerControl.TextCombox,"list":["C++","Python","Java"],"name":"manager.supported_languages","label":u"サポートする言語"},
                              {"default":"py","type":ManagerControl.TextBox,"list":[],"name":"manager.modules.Python.suffixes","label":u"RTCモジュールの拡張子"},
                             {"default":"rtcd_python","type":ManagerControl.TextBox,"list":[],"name":"manager.modules.Python.manager_cmd","label":u"マネージャプログラム名"},
                              {"default":"rtcprof_python","type":ManagerControl.TextBox,"list":[],"name":"manager.modules.Python.profile_cmd","label":u"プロファイル取得コマンド名"},
                             {"default":"","type":ManagerControl.TextBox,"list":[],"name":"corba.args","label":u"CORBAに与える引数"},
                              {"default":"","type":ManagerControl.TextBox,"list":[],"name":"corba.endpoint","label":u"エンドポイント"},
                             {"default":"","type":ManagerControl.TextCombox,"list":[],"name":"corba.endpoints","label":u"エンドポイント(複数)"},
                              {"default":"","type":ManagerControl.TextBox,"list":[],"name":"corba.nameservice.replace_endpoint","label":u"エンドポイントの置き換え"},
                             {"default":"corba","type":ManagerControl.Combox,"list":["corba"],"name":"naming.type","label":u"ネームサービスのタイプ"},
                              {"default":"YES","type":ManagerControl.Combox,"list":["YES","NO"],"name":"naming.update.enable","label":u"RTC生成後ネームサーバーの起動をした場合に登録できるか"},
                             {"default":"10.0","type":ManagerControl.DoubleSpinBox,"list":[],"name":"naming.update.interval","label":u"ネームサーバの確認および再登録を行う周期"},
                              {"default":"NO","type":ManagerControl.Combox,"list":["YES","NO"],"name":"naming.update.rebind","label":u"すでに名前と参照が登録されているネームサーバ上で名前が削除されるなどした場合に再度登録を行う"},
                             {"default":"YES","type":ManagerControl.Combox,"list":["YES","NO"],"name":"manager.modules.abs_path_allowed","label":u"モジュールを絶対パスで指定するか"},
                              {"default":"YES","type":ManagerControl.Combox,"list":["YES","NO"],"name":"logger.enable","label":u"ロガーの有効化・無効化"},
                             {"default":"./rtc%p.log","type":ManagerControl.TextBox,"list":[],"name":"logger.file_name","label":u"ログファイル名"},
                              {"default":"%b %d %H:%M:%S","type":ManagerControl.TextBox,"list":[],"name":"logger.date_format","label":u"ログに記載する日付・時刻のフォーマット"},
                             {"default":"YES","type":ManagerControl.Combox,"list":["YES","NO"],"name":"timer.enable","label":u"タイマ機能の有効/無効"},
                              {"default":"0.1","type":ManagerControl.DoubleSpinBox,"list":[],"name":"timer.tick","label":u"タイマの精度"},
                             {"default":"PeriodicExecutionContext","type":ManagerControl.TextCombox,"list":["PeriodicExecutionContext","ExtTrigExecutionContext","OpenHRPExecutionContext","ArtExecutionContext","RTPreemptEC"],"name":"exec_cxt.periodic.type","label":u"実行コンテキストのタイプ"},
                            {"default":"YES","type":ManagerControl.Combox,"list":["YES","NO"],"name":"exec_cxt.periodic.gui","label":u"MultipleOrderedEC使用時にGUIを表示するか"},
                            {"default":"","type":ManagerControl.TextBox,"list":[],"name":"exec_cxt.periodic.filename","label":u"MultipleOrderedEC使用時に実行順序を設定してあるファイル名"}
                             ]
        self.confList = []

        
        self.prop  = OpenRTM_aist.Properties()
        self.prop.setDefaults(OpenRTM_aist.default_config)
        if self.conf_filepath == "":
            fd = file("rtc.conf","r")
        else:
            fd = file(self.conf_filepath,"r")
            
        self.prop.load(fd)
        fd.close()
        #self.prop = OpenRTM_aist.Manager.instance().getConfig()
        

        for n in self.confNameList:
            p = self.getParam(n["name"])
            self.confList.append({"default":n["default"],"type":n["type"],"list":n["list"],"name":n["name"],"label":n["label"],"value":p.split(",")})
            
        
        
        
        
        
    ##
    # @brief 指定したプロパティの値を読み込み
    # @param self
    # @param name プロパティ名
    # @return プロパティの値
    def getParam(self, name):
        param = self.getProperty(self.prop, name, "")
        p = [param]
        OpenRTM_aist.StringUtil.eraseBlank(p)
        return p[0]

    
        

    
        

    
    ##
    # @brief rtc.confの設定を取得する関数
    # @param self
    # @param prop プロパティリスト
    # @param key キー
    # @param value プロパティの値
    # @return プロパティの値
    def getProperty(self, prop, key, value):
        
        if  prop.findNode(key) != None:
            
            value = prop.getProperty(key)
        return value
    
    ##
    # @brief 指定したファイルからRTCの初期化関数を取得
    # @param self
    # @param filename ファイル名
    # @param filepath ファイルパス
    # @return RTCの初期化関数
    def getFunc(self, filename, filepath):
        try:
            sys.path.append(filepath[0])
            (file, pathname, description) = imp.find_module(filename, filepath)
            mod = imp.load_module(filename, file, pathname, description)
            func = getattr(mod,filename+"Init",None)

            return func
        except:
            return None
        
        

    ##
    # @brief RTC削除
    # @param self
    # @param name RTC名
    def deleteComp(self, name):
        
        if self.compList.has_key(name):
            if len(self.compList[name]["compList"]) != 0:
                self.compList[name]["compList"][-1].exit()
                del self.compList[name]["compList"][-1]
            #if len(self.compList[name]["compList"]) == 0:
            #    del self.compList[name]

    ##
    # @brief RTC追加
    # @param self
    # @param name RTC名
    # @param comp RTCオブジェクト
    def addComp(self, name, comp):
        
        if self.compList.has_key(name):
            self.compList[name]["compList"].append(comp)

    ##
    # @brief 実行コンテキスト追加
    # @param self
    # @param filepath ファイル名
    def createEC(self, filepath):
        filepath[0] = os.path.relpath(filepath[0])
                

    ##
    # @brief RTC追加
    # @param self
    # @param filename ファイル名
    # @param filepath ファイルパス
    # @return 成功でTrue、失敗でFalse
    def createComp(self, filename, filepath):
        
        
        filepath[0] = os.path.relpath(filepath[0])

        

        preLoadComp = None
        if self.compList.has_key(filename):
            func = self.compList[filename]["func"]
            preLoadComp = self.compList[filename]
            
        
                
                

        if preLoadComp == None:    
            func = self.getFunc(filename, filepath)
            if func == None:
                return False
            func(self.mgr)
            
        if func:
            
            self.comp = self.mgr.createComponent(filename)
            if not self.comp:
                return False
            if preLoadComp:
                preLoadComp["compList"].append(self.comp)
            else:
                self.compList[filename] = {"filename":filename,"filepath":filepath,"func":func,"compList":[self.comp]}
        else:
            return False

        return True
