cd ..\..\workspace
start ..\Manager\Cpp\rtcd_p\Release\rtcd_p.exe -f ../projects/test/Cpp/rtc.conf
start python ..\Manager\Python\rtcd.py -f ../projects/test/Python/rtc.conf
cd ..\projects\test
sleep 5
cmd /c composite.bat
cmd /c rtsystem.bat
