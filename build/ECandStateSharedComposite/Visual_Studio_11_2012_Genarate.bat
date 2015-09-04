cd /d %~dp0
cmake ../../Composite/ECandStateSharedComposite/ -G "Visual Studio 11 2012" -D CMAKE_INSTALL_PREFIX="C:/OpenRTM-aist" ../../Composite/ECandStateSharedComposite/
copy ..\..\Composite\ECandStateSharedComposite\RTC.xml RTC.xml
