cmake_minimum_required(VERSION 3.1.0)

project(oneclient_qt)

#
# Setup CPack
#
INCLUDE(CPack)
INCLUDE(InstallRequiredSystemLibraries)

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Onedata Oneclient")
SET(CPACK_PACKAGE_VENDOR "Onedata")
# SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/ReadMe.txt")
# SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/Copyright.txt")
SET(CPACK_PACKAGE_VERSION_MAJOR "3")
SET(CPACK_PACKAGE_VERSION_MINOR "0")
SET(CPACK_PACKAGE_VERSION_PATCH "0")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${CMake_VERSION_MAJOR}.${CMake_VERSION_MINOR}")

if(APPLE)
set(CMAKE_PREFIX_PATH "~/Qt/5.8/clang_64")
set(MACOSX_BUNDLE_INFO_STRING "Onedata Oneclient GUI")
# set(MACOSX_BUNDLE_ICON_FILE )
# set(MACOSX_BUNDLE_GUI_IDENTIFIER
set(MACOSX_BUNDLE_LONG_VERSION_STRING "3.0.0-rc14")
set(MACOSX_BUNDLE_BUNDLE_NAME "Oneclient")
set(MACOSX_BUNDLE_SHORT_VERSION_STRING "3.0.0")
set(MACOSX_BUNDLE_BUNDLE_VERSION "3.0.0-rc14")
set(MACOSX_BUNDLE_COPYRIGHT "Onedata")
set(CPACK_PACKAGE_ICON ${CMAKE_CURRENT_SOURCE_DIR}/qt_resources/onedata-icon.icns)
set(CPACK_BUNDLE_ICON ${CMAKE_CURRENT_SOURCE_DIR}/qt_resources/onedata-icon.icns)
set(CPACK_PACKAGE_NAME "Oneclient")
set(CPACK_PACKAGE_VERSION "3.0.0-rc14")
# set(CPACK_PACKAGE_VERSION "3.0.0-rc14")
SET(CPACK_PACKAGE_FILE_NAME "Oneclient-3.0.0.rc14")
set(CPACK_DMG_VOLUME_NAME "Oneclient")
set(CPACK_GENERATOR "DragNDrop")


endif(APPLE)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 14)

# Find the QtWidgets library
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
if(APPLE)
  find_package(Qt5MacExtras REQUIRED)
endif(APPLE)

# Boost
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
find_package(Boost 1.63.0 REQUIRED COMPONENTS date_time serialization)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  include_directories(${Boost_INCLUDE_DIR}/libs/interprocess/include)
endif(Boost_FOUND)

if(APPLE)
# NOTE: Don't include the path in MACOSX_BUNDLE_ICON_FILE -- this is
# the property added to Info.plist
set(MACOSX_BUNDLE_ICON_FILE onedata-icon.icns)

# And this part tells CMake where to find and install the file itself
set(oneclient_ICON ${CMAKE_CURRENT_SOURCE_DIR}/qt_resources/onedata-icon.icns)
set_source_files_properties(${oneclient_ICON} PROPERTIES
       MACOSX_PACKAGE_LOCATION "Resources")
endif()

# Tell CMake to create the helloworld executable
add_executable(oneclient_qt
  MACOSX_BUNDLE
  src/main.cc
  src/systemtray.cc
  src/logowidgetaction.cc
  src/activemountwidgetaction.cc
  src/focusdetectingwidget.cc
  src/providersettings.cc
  src/providersettingseditor.cc
  src/settingsmanager.cc
<<<<<<< HEAD
  src/oneclientmessagelistener.cc
  src/hash.cc
  qt_resources/resources.qrc
  ${oneclient_ICON})
=======
  qt_resources/resources.qrc)
>>>>>>> origin/master

# Use the Widgets module from Qt 5.
if(APPLE)
target_link_libraries(oneclient_qt ${Boost_SERIALIZATION_LIBRARY} Qt5::Widgets Qt5::MacExtras)
else()
target_link_libraries(oneclient_qt ${Boost_SERIALIZATION_LIBRARY} Qt5::Widgets)
endif()

add_custom_target(dist COMMAND ${CMAKE_MAKE_PROGRAM} package)

if(VERBOSE)
  message(STATUS "\n#--------------- Internal Variables -------------#")
  message(STATUS "DEPLIBS: ${DEPLIBS}")
  message(STATUS "core_DEPENDS: ${core_DEPENDS}")
  message(STATUS "#---------------------------------------------")
  message(STATUS "SYSTEM_LDFLAGS        : ${SYSTEM_LDFLAGS}")
  message(STATUS "CMAKE_DL_LIBS         : ${CMAKE_DL_LIBS}")
  message(STATUS "CMAKE_C_FLAGS         : ${CMAKE_C_FLAGS}")
  message(STATUS "CMAKE_CXX_FLAGS       : ${CMAKE_CXX_FLAGS}")
  message(STATUS "CMAKE_EXE_LINKER_FLAGS: ${CMAKE_EXE_LINKER_FLAGS}")
  message(STATUS "#---------------------------------------------#")
  message(STATUS "bindir     : ${bindir}")
  message(STATUS "includedir : ${includedir}")
  message(STATUS "libdir     : ${libdir}")
  message(STATUS "datarootdir: ${datarootdir}")
  message(STATUS "#---------------------------------------------#")
  message(STATUS "GIT_REV: ${APP_SCMID}")
  message(STATUS "#---------------------------------------------#")
  message(STATUS "CPACK_GENERATOR       : ${CPACK_GENERATOR}")
  message(STATUS "CPACK_SOURCE_GENERATOR: ${CPACK_SOURCE_GENERATOR}")
  message(STATUS "#---------------------------------------------#")
endif()