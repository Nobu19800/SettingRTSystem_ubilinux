cmake_minimum_required (VERSION 2.6)



#if(WIN32)
#	set(BOOST_PATH "C:/boost_1_52_0")
#	set(LUA_PATH "C:/Program Files (x86)/Lua/5.1")
#endif(WIN32)

set(LUABIND_PATH "luabind-0.9.1")

project(MultipleOrderedEC)



set(CMAKE_AUTOMOC ON)


find_package(Qt5Widgets)

find_package(OpenRTM REQUIRED)



if (DEFINED OPENRTM_INCLUDE_DIRS)
  string(REGEX REPLACE "-I" ";"
    OPENRTM_INCLUDE_DIRS "${OPENRTM_INCLUDE_DIRS}")
  string(REGEX REPLACE " ;" ";"
    OPENRTM_INCLUDE_DIRS "${OPENRTM_INCLUDE_DIRS}")
endif (DEFINED OPENRTM_INCLUDE_DIRS)

if (DEFINED OPENRTM_LIBRARY_DIRS)
  string(REGEX REPLACE "-L" ";"
    OPENRTM_LIBRARY_DIRS "${OPENRTM_LIBRARY_DIRS}")
  string(REGEX REPLACE " ;" ";"
    OPENRTM_LIBRARY_DIRS "${OPENRTM_LIBRARY_DIRS}")
endif (DEFINED OPENRTM_LIBRARY_DIRS)

if (DEFINED OPENRTM_LIBRARIES)
  string(REGEX REPLACE "-l" ";"
    OPENRTM_LIBRARIES "${OPENRTM_LIBRARIES}")
  string(REGEX REPLACE " ;" ";"
    OPENRTM_LIBRARIES "${OPENRTM_LIBRARIES}")
endif (DEFINED OPENRTM_LIBRARIES)


#if(WIN32)

#  set(BOOST_ROOT $ENV{BOOST_ROOT})

#endif()

find_package(Boost REQUIRED)

find_package(Lua51 REQUIRED)

include_directories(${OPENRTM_INCLUDE_DIRS})
include_directories(${OMNIORB_INCLUDE_DIRS})

#if(WIN32)
#	include_directories(${BOOST_PATH})
#	include_directories(${LUA_PATH}/include)
#endif(WIN32)


include_directories(${Boost_INCLUDE_DIRS})
include_directories(${LUA_INCLUDE_DIR})

include_directories(${LUABIND_PATH})


add_definitions(${OPENRTM_CFLAGS})
add_definitions(${OMNIORB_CFLAGS})

add_definitions(-DNOMINMAX)

link_directories(${OPENRTM_LIBRARY_DIRS})
link_directories(${OMNIORB_LIBRARY_DIRS})

#if(WIN32)
#	link_directories(${LUA_PATH}/lib)
#	link_directories(${BOOST_PATH}/libs)
#endif(WIN32)





set(luabind_srcs ${LUABIND_PATH}/src/class.cpp ${LUABIND_PATH}/src/class_info.cpp ${LUABIND_PATH}/src/class_registry.cpp ${LUABIND_PATH}/src/class_rep.cpp ${LUABIND_PATH}/src/create_class.cpp ${LUABIND_PATH}/src/error.cpp ${LUABIND_PATH}/src/exception_handler.cpp ${LUABIND_PATH}/src/function.cpp ${LUABIND_PATH}/src/inheritance.cpp ${LUABIND_PATH}/src/link_compatibility.cpp ${LUABIND_PATH}/src/object_rep.cpp ${LUABIND_PATH}/src/open.cpp ${LUABIND_PATH}/src/pcall.cpp ${LUABIND_PATH}/src/scope.cpp ${LUABIND_PATH}/src/stack_content_by_name.cpp ${LUABIND_PATH}/src/weak_ref.cpp ${LUABIND_PATH}/src/wrapper_base.cpp )

IF (${Qt5Widgets_FOUND})

	set(ec_srcs AddButton.cpp AddButton2.cpp AddButton3.cpp FileStreamFunc.cpp Config.cpp ExComp.cpp FEComp.cpp FrameComp.cpp mainwindow.cpp MPComp.cpp MPLua.cpp MPTask.cpp MultipleOrderedEC.cpp SetComp.cpp)



	QT5_ADD_RESOURCES(QRC MultipleOrderedEC.qrc)

	qt5_wrap_cpp(moc_mainwindow.cpp mainwindow.h)
	qt5_wrap_cpp(moc_AddButton.cpp AddButton.h)
	qt5_wrap_cpp(moc_AddButton2.cpp AddButton2.h)
	qt5_wrap_cpp(moc_AddButton3.cpp AddButton3.h)
	qt5_wrap_cpp(moc_ExComp.cpp ExComp.h)
	qt5_wrap_cpp(moc_FEComp.cpp FEComp.h)
	qt5_wrap_cpp(moc_FrameComp.cpp FrameComp.h)
	qt5_wrap_cpp(moc_SetComp.cpp SetComp.h)


	ADD_LIBRARY(MultipleOrderedEC SHARED  ${ec_srcs} ${luabind_srcs} ${QRC})
	
	QT5_USE_MODULES(MultipleOrderedEC Widgets)
ELSE (${Qt5Widgets_FOUND})
	set(ec_srcs FileStreamFunc.cpp MPComp.cpp MPLua.cpp MPTask.cpp MultipleOrderedEC.cpp )
	ADD_LIBRARY(MultipleOrderedEC SHARED  ${ec_srcs} ${luabind_srcs})
	
ENDIF (${Qt5Widgets_FOUND})



#if(WIN32)
#	target_link_libraries(MultipleOrderedEC ${OPENRTM_LIBRARIES} lua5.1.lib lua51.lib)
#elseif(UNIX)
#	target_link_libraries(MultipleOrderedEC ${OPENRTM_LIBRARIES} liblua5.1.so)
#endif(WIN32)

target_link_libraries(MultipleOrderedEC ${OPENRTM_LIBRARIES} ${LUA_LIBRARIES})



