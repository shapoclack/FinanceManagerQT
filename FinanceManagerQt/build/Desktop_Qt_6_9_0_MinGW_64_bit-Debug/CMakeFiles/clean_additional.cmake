# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\FinanceTracker_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\FinanceTracker_autogen.dir\\ParseCache.txt"
  "FinanceTracker_autogen"
  )
endif()
