cmake_minimum_required(VERSION 3.12)
project(LeapFrogCppUcsdEdu_10)

set(CMAKE_CXX_STANDARD 11)

# Add source files to the project
set(SOURCE_FILES
    common.hpp
    energy.hpp
    file_io.hpp
    integrator.hpp
    main.cpp
    particle.hpp
    simulation.hpp
    system.hpp
    vec3.hpp
)

# Add executable target
add_executable(LeapFrogCppUcsdEdu_10 ${SOURCE_FILES})

# Set the output directory for the executable
set_target_properties(LeapFrogCppUcsdEdu_10 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# Additional configuration if needed
# ...

# Add any required libraries or dependencies
# ...

# Add any compilation flags or options
# ...