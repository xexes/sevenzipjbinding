# Install script for directory: /tmp/workspace/xexes/sevenzipjbinding

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  
    MACRO(COPY_FROM_SRC SRC DEST EXCLUDE_PATTERN)
        FILE(GLOB_RECURSE Files RELATIVE ${SRC} ${SRC}/*)
        FILE(MAKE_DIRECTORY "${DEST}")
        FOREACH(File ${Files})
	        IF(NOT File MATCHES ".*(/|^)[.]svn/.*")
	            IF("x${EXCLUDE_PATTERN}" STREQUAL "x" OR NOT File MATCHES "${EXCLUDE_PATTERN}")
                    configure_file(
                            ${SRC}/${File}
                            ${DEST}/${File}
                            @ONLY)
                ENDIF()
            ENDIF()
        ENDFOREACH()
    ENDMACRO()

    FILE(MAKE_DIRECTORY "/tmp/workspace/xexes/sevenzipjbinding/build-local/prepackage.tmp/javadoc/")
    EXECUTE_PROCESS(COMMAND "/bin/javadoc"
                                -public -version -author -quiet
                                -sourcepath /tmp/workspace/xexes/sevenzipjbinding/jbinding-java/src 
                                -subpackages net.sf.sevenzipjbinding 
                                -d /tmp/workspace/xexes/sevenzipjbinding/build-local/prepackage.tmp/javadoc/
                    WORKING_DIRECTORY .
    )
    
    # Copy javadoc back into the source folder
    EXECUTE_PROCESS(COMMAND /usr/local/bin/cmake
                                -E copy_directory
                                .
                                "/tmp/workspace/xexes/sevenzipjbinding/doc/web/javadoc"
                    WORKING_DIRECTORY "/tmp/workspace/xexes/sevenzipjbinding/build-local/prepackage.tmp/javadoc/"
    )
    
    # Generate web site
    EXECUTE_PROCESS(COMMAND /usr/local/bin/cmake
                                -D SEVENZIPJBINDING_VERSION=25.01-1.00
                                -P "/tmp/workspace/xexes/sevenzipjbinding/doc/build_html.cmake"
                                /tmp/workspace/xexes/sevenzipjbinding/doc/web/javadoc
                    WORKING_DIRECTORY "/tmp/workspace/xexes/sevenzipjbinding/doc/"
    )
    
    COPY_FROM_SRC("/tmp/workspace/xexes/sevenzipjbinding/jbinding-java/src" "/tmp/workspace/xexes/sevenzipjbinding/build-local/prepackage.tmp/java-src/" "")
    COPY_FROM_SRC("/tmp/workspace/xexes/sevenzipjbinding/jbinding-cpp" "/tmp/workspace/xexes/sevenzipjbinding/build-local/prepackage.tmp/cpp-src/" CMakeLists.txt)

    EXECUTE_PROCESS(COMMAND "/bin/jar" cMf /tmp/workspace/xexes/sevenzipjbinding/build-local/prepackage.tmp/java-src.zip .
    WORKING_DIRECTORY /tmp/workspace/xexes/sevenzipjbinding/build-local/prepackage.tmp/java-src/)

    EXECUTE_PROCESS(COMMAND "/bin/jar" cMf /tmp/workspace/xexes/sevenzipjbinding/build-local/prepackage.tmp/cpp-src.zip .
    WORKING_DIRECTORY /tmp/workspace/xexes/sevenzipjbinding/build-local/prepackage.tmp/cpp-src/)

    EXECUTE_PROCESS(COMMAND "/bin/jar" cMf /tmp/workspace/xexes/sevenzipjbinding/build-local/prepackage.tmp/javadoc.zip .
    WORKING_DIRECTORY /tmp/workspace/xexes/sevenzipjbinding/build-local/prepackage.tmp/javadoc/)

    EXECUTE_PROCESS(COMMAND "/bin/jar" cMf /tmp/workspace/xexes/sevenzipjbinding/build-local/prepackage.tmp/website.zip .
    WORKING_DIRECTORY "/tmp/workspace/xexes/sevenzipjbinding/doc/web")

endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE FILE FILES
    "/tmp/workspace/xexes/sevenzipjbinding/AUTHORS"
    "/tmp/workspace/xexes/sevenzipjbinding/ChangeLog"
    "/tmp/workspace/xexes/sevenzipjbinding/COPYING"
    "/tmp/workspace/xexes/sevenzipjbinding/LGPL"
    "/tmp/workspace/xexes/sevenzipjbinding/README"
    "/tmp/workspace/xexes/sevenzipjbinding/ReleaseNotes.txt"
    "/tmp/workspace/xexes/sevenzipjbinding/THANKS"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE FILE RENAME "CMakeLists.txt" FILES "/tmp/workspace/xexes/sevenzipjbinding/CMakeFile-bin-dist.txt")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES
    "/tmp/workspace/xexes/sevenzipjbinding/build-local/jbinding-java/sevenzipjbinding.jar"
    "/tmp/workspace/xexes/sevenzipjbinding/build-local/sevenzipjbinding-Linux-amd64.jar"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE FILE FILES
    "/tmp/workspace/xexes/sevenzipjbinding/build-local/prepackage.tmp/java-src.zip"
    "/tmp/workspace/xexes/sevenzipjbinding/build-local/prepackage.tmp/cpp-src.zip"
    "/tmp/workspace/xexes/sevenzipjbinding/build-local/prepackage.tmp/javadoc.zip"
    "/tmp/workspace/xexes/sevenzipjbinding/build-local/prepackage.tmp/website.zip"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/tmp/workspace/xexes/sevenzipjbinding/build-local/jbinding-cpp/cmake_install.cmake")

endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/tmp/workspace/xexes/sevenzipjbinding/build-local/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
if(CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_COMPONENT MATCHES "^[a-zA-Z0-9_.+-]+$")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
  else()
    string(MD5 CMAKE_INST_COMP_HASH "${CMAKE_INSTALL_COMPONENT}")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INST_COMP_HASH}.txt")
    unset(CMAKE_INST_COMP_HASH)
  endif()
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/tmp/workspace/xexes/sevenzipjbinding/build-local/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
