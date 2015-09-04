cd /d %~dp0
cmake ../../Composite/ECandStateSharedComposite/ -G "Visual Studio 9 2008" -D CMAKE_INSTALL_PREFIX="C:/OpenRTM-aist" ../../Composite/ECandStateSharedComposite/
copy ..\..\Composite\ECandStateSharedComposite\RTC.xml RTC.xml
