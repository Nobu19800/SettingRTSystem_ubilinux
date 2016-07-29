# coding=utf-8
#---------------------------------------------------------------------------
# Copyright 2011 utahta
#---------------------------------------------------------------------------
import sys
from setuptools import setup
\

NAME = 'rtcConfSet'
LICENSE = 'GPL'
AUTHOR = ''
AUTHOR_EMAIL = ''
DESCRIPTION = ''
URL = ''

if sys.platform == 'win32':
    # Windows
    import py2exe, innosetup
    
    PY2EXE_OPTIONS = {'compressed': 1,
                      'optimize': 2,
                      'bundle_files': 3,
                      'includes': ["lxml._elementpath","commands","ActArray_idl","AIO_idl","Bumper_idl","Camera_idl","DIO_idl","Fiducial_idl","GPS_idl","Gripper_idl","IMU_idl","INS_idl","Limb_idl","Map_idl","Multicamera_idl","PanTilt_idl","Paths_idl","PointCloud_idl","Position_idl","Ranger_idl","RFID_idl"],}
    
    INNOSETUP_OPTIONS = {'inno_script': innosetup.DEFAULT_ISS,
                         'bundle_vcr': True,
                         'zip': False,
                         }
    setup(
        name = NAME,
        version = 0,
        license = LICENSE,
        author = AUTHOR,
        author_email = AUTHOR_EMAIL,
        description = DESCRIPTION,
        url = URL,
        scripts = ['rtcConfSet.py'],
        windows=[{"script": "rtcConfSet.py"}],
        options = {'py2exe': PY2EXE_OPTIONS,
                   'innosetup': INNOSETUP_OPTIONS},
        zipfile = 'rtcConfSet.lib',
    )

elif sys.platform == 'darwin':
    # Mac
    OPTIONS = {
               "argv_emulation": False,
               "includes": ["sip", "BeautifulSoup", "html5lib", "jsm"],
               'iconfile': 'jsm.icns',
               }
    setup(
        name = NAME,
        version = VERSION,
        license = LICENSE,
        author = AUTHOR,
        author_email = AUTHOR_EMAIL,
        description = DESCRIPTION,
        url = URL,
        app = ['rtcConfSet.py'],
        options = {'py2app': OPTIONS},
        setup_requires=["py2app"],
    )