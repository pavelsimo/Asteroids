CMAKE_MINIMUM_REQUIRED(VERSION 2.8.4)
PROJECT(Asteroids)

# Modules
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Ouput directories
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Move all targets to /bin (e.g. Release, Debug)
IF(WIN32)
    FOREACH(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
        STRING( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
        SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${PROJECT_SOURCE_DIR}/bin)
        SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${PROJECT_SOURCE_DIR}/bin)
        SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${PROJECT_SOURCE_DIR}/bin)
    ENDFOREACH(OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)
ENDIF(WIN32)

ADD_EXECUTABLE(
    ${PROJECT_NAME}
    src/main.cpp
    src/World.cpp
    src/Drawing.cpp
    src/MathUtilities.cpp
    src/Vector2.cpp
    src/AABB2.cpp
    src/Actor.cpp
    src/Player.cpp
    src/Bullet.cpp
    src/Asteroid.cpp
    src/AsteroidFactory.cpp
    src/EnemyShip.cpp
    src/BitmapFont.cpp
    src/Texture.cpp
    src/BitmapFontXMLParser.cxx
    src/SoundManager.cpp
    src/FileSystem.cpp
    src/Game.cpp
    src/AsteroidGame.cpp
)

# C++11
INCLUDE(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
IF(COMPILER_SUPPORTS_CXX11)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSEIF(COMPILER_SUPPORTS_CXX0X)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
ELSE()
        MESSAGE(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
ENDIF()

# OpenGL
FIND_PACKAGE(OpenGL REQUIRED)
INCLUDE_DIRECTORIES(${OpenGL_INCLUDE_DIRS})
LINK_DIRECTORIES(${OpenGL_LIBRARY_DIRS})
ADD_DEFINITIONS(${OpenGL_DEFINITIONS})
IF(NOT OPENGL_FOUND)
    MESSAGE(ERROR " OPENGL not found!")
ENDIF(NOT OPENGL_FOUND)

#---------------------
# WINDOWS
#---------------------

IF(WIN32)
    
    INCLUDE_DIRECTORIES(
        ${PROJECT_SOURCE_DIR}/deps/win32/devil/include
        ${PROJECT_SOURCE_DIR}/deps/win32/glut/include
        ${PROJECT_SOURCE_DIR}/deps/win32/openal/include
        ${PROJECT_SOURCE_DIR}/deps/win32/xercesc/include
        ${PROJECT_SOURCE_DIR}/deps/win32/xsd/include
    )

    TARGET_LINK_LIBRARIES(
        ${PROJECT_NAME}
        ${OPENGL_LIBRARIES}
        ${PROJECT_SOURCE_DIR}/deps/win32/glut/lib/freeglut.lib
        ${PROJECT_SOURCE_DIR}/deps/win32/devil/lib/DevIL.lib
        ${PROJECT_SOURCE_DIR}/deps/win32/devil/lib/ILU.lib
        ${PROJECT_SOURCE_DIR}/deps/win32/devil/lib/ILUT.lib
        ${PROJECT_SOURCE_DIR}/deps/win32/openal/lib/OpenAL32.lib
        ${PROJECT_SOURCE_DIR}/deps/win32/openal/lib/alut.lib
        ${PROJECT_SOURCE_DIR}/deps/win32/xercesc/lib/xerces-c_3.lib
    )

ENDIF(WIN32)

if (UNIX)
    
    # GLUT
    FIND_PACKAGE(GLUT REQUIRED)
    INCLUDE_DIRECTORIES(${GLUT_INCLUDE_DIRS})
    LINK_DIRECTORIES(${GLUT_LIBRARY_DIRS})
    ADD_DEFINITIONS(${GLUT_DEFINITIONS})
    IF(NOT GLUT_FOUND)
        MESSAGE(ERROR " GLUT not found!")
    ENDIF(NOT GLUT_FOUND)

    # DevIL
    FIND_PACKAGE(DevIL REQUIRED)
    IF(NOT IL_FOUND)
        MESSAGE(ERROR " DevIL not found!")
    ENDIF(NOT IL_FOUND)

    # OpenAL
    FIND_PACKAGE(OPENAL REQUIRED)
    IF(NOT OPENAL_FOUND)
        MESSAGE(ERROR " OPENAL not found!")
    ENDIF(NOT OPENAL_FOUND)

    # ALUT
    FIND_PACKAGE(ALUT REQUIRED)
    IF(NOT ALUT_FOUND)
        MESSAGE(ERROR " ALUT not found!")
    ENDIF(NOT ALUT_FOUND)

    # Xerces-C
    FIND_PACKAGE(XercesC REQUIRED)
    IF(NOT XERCESC_FOUND)
        MESSAGE(ERROR " Xerces-C not found!")
    ENDIF(NOT XERCESC_FOUND)

    # SDL2
    FIND_PACKAGE(SDL2 REQUIRED)
    INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIR})
    IF(NOT SDL2_FOUND)
        MESSAGE(ERROR " SDL2 not found!")
    ENDIF(NOT SDL2_FOUND)

    TARGET_LINK_LIBRARIES(
        ${PROJECT_NAME}
        ${OPENGL_LIBRARIES}
        ${SDL2_LIBRARY}
        #${GLUT_LIBRARY}
        ${IL_LIBRARIES}
        ${ILU_LIBRARIES}
        ${ILUT_LIBRARIES}
        ${OPENAL_LIBRARY}
        ${ALUT_LIBRARY}
        ${XERCESC_LIBRARY}
    )
    
endif (UNIX)

# Copy fonts
ADD_CUSTOM_COMMAND(
    TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/fonts ${PROJECT_SOURCE_DIR}/bin/fonts
)

# Copy sounds
ADD_CUSTOM_COMMAND(
    TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/sounds ${PROJECT_SOURCE_DIR}/bin/sounds
)

IF(WIN32)
    # Gather all *.dll files
    FILE(GLOB_RECURSE DLLFiles ${PROJECT_SOURCE_DIR}/deps/*.dll)
    
    FOREACH(DLLFile ${DLLFiles})
        ADD_CUSTOM_COMMAND(
            TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy 
            ${DLLFile} ${PROJECT_SOURCE_DIR}/bin
        )
    ENDFOREACH()
ENDIF(WIN32)

INSTALL (
    TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin
)
