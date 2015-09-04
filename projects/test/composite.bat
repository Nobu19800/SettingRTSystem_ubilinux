cmd /c rtcomp /localhost/test.rtc -a /localhost/MyFirstComponent0.rtc -a /localhost/MySecondComponent0.rtc
cmd /c rtconf /localhost/test.rtc set exported_ports MyFirstComponent0.in,MyFirstComponent0.out,MyFirstComponent0.service,MySecondComponent0.in,MySecondComponent0.out,MySecondComponent0.service
