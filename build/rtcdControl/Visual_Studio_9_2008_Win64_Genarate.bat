cd /d %~dp0
cmake ../../rtcdControl/ -G "Visual Studio 9 2008 Win64" -D CMAKE_INSTALL_PREFIX="C:/OpenRTM-aist" ../../rtcdControl/
copy ..\..\rtcdControl\RTC.xml RTC.xml
