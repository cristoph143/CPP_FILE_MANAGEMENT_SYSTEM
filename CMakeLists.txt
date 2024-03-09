# CMakeList.txt : CMake project for CPP_FILE_MANAGE, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("CPP_FILE_MANAGE")

# Add source to this project's executable.
add_executable(CPP_FILE_MANAGE "CPP_FILE_MANAGE.cpp" "CPP_FILE_MANAGE.h" "include/FileOps/FileOpsUtility.h" "include/MenuOps/Menu.h" "src/FileOps/FileOpsUtility.cpp" "src/MenuOps/Menu.cpp"  "src/FileOps/FileBaseOps.cpp" "include/FileOps/FileBaseOps.h" "include/FileOps/WriteToFileOps.h" "src/FileOps/WriteToFileOps.cpp" "include/FileOps/FileOpsDefinitions.h" "include/FileOps/ReadFromFileOps.h" "src/FileOps/ReadFromFileOps.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CPP_FILE_MANAGE PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
