TEMPLATE = vcapp
TARGET = MultipleOrderedEC

CONFIG += assistant

QT += network

HEADERS	    =   mainwindow.h \
		SetComp.h \
		ExComp.h \
		FrameComp.h \
		AddButton.h \
		AddButton2.h \
		AddButton3.h \
		FEComp.h \
		CompSearch.h \
		MPComp.h \
		Config.h \
		MPLua.h \
		MultipleOrderedEC.h \
		MPTask.h
SOURCES	    =   mainwindow.cpp \
		SetComp.cpp \
		ExComp.cpp \
		FrameComp.cpp \
		AddButton.cpp \
		AddButton2.cpp \
		AddButton3.cpp \
		CompSearch.cpp \
		FEComp.cpp \
		MPComp.cpp \
		Config.cpp \
		MPLua.cpp \
		MultipleOrderedEC.cpp \
		MPTask.cpp
RESOURCES   =	MultipleOrderedEC.qrc



# install
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS diagramscene.pro images
INSTALLS += target sources


