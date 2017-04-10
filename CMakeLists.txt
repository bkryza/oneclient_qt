cmake_minimum_required(VERSION 3.1.0)

project(qtosxmenubar)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 14)

# Find the QtWidgets library
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5MacExtras REQUIRED)

# Tell CMake to create the helloworld executable
add_executable(qtosxmenubar
  # MACOSX_BUNDLE
  src/main.cc
  src/systemtray.cc
  src/logowidgetaction.cc
  src/activemountwidgetaction.cc
  src/focusdetectingwidget.cc
  qt_resources/resources.qrc)

# Use the Widgets module from Qt 5.
target_link_libraries(qtosxmenubar Qt5::Widgets Qt5::MacExtras)
