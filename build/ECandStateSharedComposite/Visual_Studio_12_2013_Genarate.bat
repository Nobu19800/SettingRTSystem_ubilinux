cd /d %~dp0
cmake ../../Composite/ECandStateSharedComposite/ -G "Visual Studio 12 2013" -D CMAKE_INSTALL_PREFIX="C:/OpenRTM-aist" ../../Composite/ECandStateSharedComposite/
copy ..\..\Composite\ECandStateSharedComposite\RTC.xml RTC.xml
