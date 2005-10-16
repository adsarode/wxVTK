#
# This module finds if wxWindows is installed and determines where the
# include files and libraries are. It also determines what the name of
# the library is. This code sets the following variables:
#
#  WXWINDOWS_LIBRARY         = full path to the wxWindows library and linker flags on unix
#  CMAKE_WX_CXX_FLAGS        = compiler flags for building wxWindows 
#  WXWINDOWS_INCLUDE_DIR    = include path of wxWindows

IF(WIN32)

  SET (WXWINDOWS_POSSIBLE_LIB_PATHS
    $ENV{WXWIN}/lib
    "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\wxWindows_is1;Inno Setup: App Path]/lib"
  )

  FIND_LIBRARY(WXWINDOWS_STATIC_LIBRARY
    NAMES wx wxmsw
    PATHS ${WXWINDOWS_POSSIBLE_LIB_PATHS} 
  )

  FIND_LIBRARY(WXWINDOWS_STATIC_DEBUG_LIBRARY
    NAMES wxd wxmswd
    PATHS ${WXWINDOWS_POSSIBLE_LIB_PATHS} 
  )

  FIND_LIBRARY(WXWINDOWS_SHARED_LIBRARY
    NAMES wx23_2 wx22_9 wxmsw240
    PATHS ${WXWINDOWS_POSSIBLE_LIB_PATHS} 
  )

  FIND_LIBRARY(WXWINDOWS_SHARED_DEBUG_LIBRARY
    NAMES wx23_2d wx22_9d wxmsw240d
    PATHS ${WXWINDOWS_POSSIBLE_LIB_PATHS} 
  )

  SET (WXWINDOWS_POSSIBLE_INCLUDE_PATHS
    $ENV{WXWIN}/include
    "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\wxWindows_is1;Inno Setup: App Path]/include"
  )

  FIND_PATH(WXWINDOWS_INCLUDE_DIR
    wx/wx.h
    ${WXWINDOWS_POSSIBLE_INCLUDE_PATHS} 
  )

  IF(WXWINDOWS_SHARED_LIBRARY OR WXWINDOWS_SHARED_DEBUG_LIBRARY)
    OPTION(WXWINDOWS_USE_SHARED_LIBS 
           "Use shared versions of wxWindows libraries" ON)
    MARK_AS_ADVANCED(WXWINDOWS_USE_SHARED_LIBS)
  ENDIF(WXWINDOWS_SHARED_LIBRARY OR WXWINDOWS_SHARED_DEBUG_LIBRARY)

  IF(WXWINDOWS_SHARED_DEBUG_LIBRARY OR WXWINDOWS_STATIC_DEBUG_LIBRARY)
    OPTION(WXWINDOWS_USE_DEBUG_LIBS 
           "Use debug versions of wxWindows libraries" OFF)
    MARK_AS_ADVANCED(WXWINDOWS_USE_DEBUG_LIBS)
  ENDIF(WXWINDOWS_SHARED_DEBUG_LIBRARY OR WXWINDOWS_STATIC_DEBUG_LIBRARY)

  SET(CMAKE_WX_LIBRARIES ${CMAKE_WX_LIBRARIES} comctl32 ctl3d32 wsock32 rpcrt4)

  IF(WXWINDOWS_USE_DEBUG_LIBS)
    #In all case we know what preprocessor definitions we'll need: (from http://www.wxwindows.org/technote/vc_ide.htm)
    #for debug:
    ADD_DEFINITIONS(-DWIN32 -D_DEBUG -D_WINDOWS -D__WINDOWS__ -D__WXMSW__ -D__WXDEBUG__ -DWXDEBUG=1 -D__WIN95__ -D__WIN32__ -DWINVER=0x0400 -DSTRICT)
    IF(WXWINDOWS_USE_SHARED_LIBS)
      SET(WXWINDOWS_LIBRARY ${WXWINDOWS_SHARED_DEBUG_LIBRARY} ${CMAKE_WX_LIBRARIES})
    ELSE(WXWINDOWS_USE_SHARED_LIBS)
      SET(WXWINDOWS_LIBRARY ${WXWINDOWS_SHARED_LIBRARY} ${CMAKE_WX_LIBRARIES})
    ENDIF(WXWINDOWS_USE_SHARED_LIBS)
  ELSE(WXWINDOWS_USE_DEBUG_LIBS)
    #for release:
    ADD_DEFINITIONS(-DNDEBUG -DWIN32 -D_WINDOWS -D__WINDOWS__ -D__WXMSW__ -D__WIN95__ -D__WIN32__ -DWINVER=0x0400 -DSTRICT)
    IF(WXWINDOWS_USE_STATIC_LIBS)
      SET(WXWINDOWS_LIBRARY ${WXWINDOWS_STATIC_DEBUG_LIBRARY} ${CMAKE_WX_LIBRARIES})
    ELSE(WXWINDOWS_USE_STATIC_LIBS)
      SET(WXWINDOWS_LIBRARY ${WXWINDOWS_STATIC_LIBRARY} ${CMAKE_WX_LIBRARIES})
    ENDIF(WXWINDOWS_USE_STATIC_LIBS)
  ENDIF(WXWINDOWS_USE_DEBUG_LIBS)


  MARK_AS_ADVANCED(
    WXWINDOWS_STATIC_LIBRARY
    WXWINDOWS_STATIC_DEBUG_LIBRARY
    WXWINDOWS_SHARED_LIBRARY
    WXWINDOWS_SHARED_DEBUG_LIBRARY
    WXWINDOWS_INCLUDE_DIR
  )

ELSE(WIN32)

  #MESSAGE( ${CMAKE_CURRENT_SOURCE_DIR} )
  INCLUDE( "${CMAKE_CURRENT_SOURCE_DIR}/Modules/UseConfig.cmake")

  FIND_PROGRAM(CMAKE_WX_CONFIG wx-config ../wx/bin ../../wx/bin)
  #SET(CMAKE_WX_CXX_FLAGS "`${CMAKE_WX_CONFIG} --cflags`")
  #SET(WXWINDOWS_LIBRARY "`${CMAKE_WX_CONFIG} --libs --gl-libs`")
  #ARGS "--libs --gl-libs"
  FIND_LIBPATH( ${CMAKE_WX_CONFIG}  "--libs")
  FIND_INCLUDEPATH(${CMAKE_WX_CONFIG} "--cxxflags")
  #MESSAGE("${CONFIG_INCLUDE_PATH}")
  #MESSAGE("${CONFIG_LIBRARIES}")
  SET(WX_INCLUDE_PATH ${CONFIG_INCLUDE_PATH})
  SET(WX_LIBRARIES ${CONFIG_LIBRARIES})

ENDIF(WIN32)  

MARK_AS_ADVANCED(
  CMAKE_WX_CXX_FLAGS
  WXWINDOWS_INCLUDE_DIR
)

IF(WXWINDOWS_LIBRARY)
  IF(WXWINDOWS_INCLUDE_DIR OR CMAKE_WX_CXX_FLAGS)
    SET(CMAKE_WX_CAN_COMPILE 1)
  ENDIF(WXWINDOWS_INCLUDE_DIR OR CMAKE_WX_CXX_FLAGS)
ENDIF(WXWINDOWS_LIBRARY)
