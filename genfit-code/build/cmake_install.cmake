# Install script for directory: /Users/sakamoto/Desktop/myfit/genfit-code

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/Users/sakamoto/Desktop/myfit/genfit-code")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/./include" TYPE DIRECTORY FILES
    "/Users/sakamoto/Desktop/myfit/genfit-code/./core/include/"
    "/Users/sakamoto/Desktop/myfit/genfit-code/./eventDisplay/include/"
    "/Users/sakamoto/Desktop/myfit/genfit-code/./fields/include/"
    "/Users/sakamoto/Desktop/myfit/genfit-code/../MyMagField/"
    "/Users/sakamoto/Desktop/myfit/genfit-code/./finitePlanes/include/"
    "/Users/sakamoto/Desktop/myfit/genfit-code/./fitters/include/"
    "/Users/sakamoto/Desktop/myfit/genfit-code/./GBL/include/"
    "/Users/sakamoto/Desktop/myfit/genfit-code/./measurements/include/"
    "/Users/sakamoto/Desktop/myfit/genfit-code/./trackReps/include/"
    "/Users/sakamoto/Desktop/myfit/genfit-code/./utilities/include/"
    REGEX "/\\.svn$" EXCLUDE)
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/./lib" TYPE SHARED_LIBRARY FILES
    "/Users/sakamoto/Desktop/myfit/genfit-code/build/lib/libgenfit2.2.0.0.dylib"
    "/Users/sakamoto/Desktop/myfit/genfit-code/build/lib/libgenfit2.2.0.dylib"
    "/Users/sakamoto/Desktop/myfit/genfit-code/build/lib/libgenfit2.dylib"
    )
  FOREACH(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./lib/libgenfit2.2.0.0.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./lib/libgenfit2.2.0.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./lib/libgenfit2.dylib"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
        -id "libgenfit2.2.0.dylib"
        "${file}")
      execute_process(COMMAND /usr/bin/install_name_tool
        -delete_rpath "/usr/local/root/lib"
        "${file}")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "${file}")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDFOREACH()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/Users/sakamoto/Desktop/myfit/genfit-code/build/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/Users/sakamoto/Desktop/myfit/genfit-code/build/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
