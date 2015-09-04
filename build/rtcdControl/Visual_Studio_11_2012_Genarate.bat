cd /d %~dp0
cmake ../../rtcdControl/ -G "Visual Studio 11 2012" -D CMAKE_INSTALL_PREFIX="C:/OpenRTM-aist" ../../rtcdControl/
copy ..\..\rtcdControl\RTC.xml RTC.xml
