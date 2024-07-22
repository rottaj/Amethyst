cmake_minimum_required(VERSION 3.27)
project(Agent C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        Agent/Agent.c
        Agent/Core/Src/Win32.c
        Agent/Core/Src/Tasks.c
        Agent/Core/Src/Serializer.c
        Agent/Core/Src/Http.c
        Agent/Core/Src/Commands.c
        Agent/Core/Lib/cJSON/cJSON.c
        Agent/Core/Lib/base64/base64.c
)

add_executable(agent ${SOURCE_FILES})

target_link_libraries(agent PRIVATE wininet iphlpapi gdi32)



# FOR DEVELOPMENT Moves exe to Shared Folder.
add_custom_command(TARGET agent
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:agent> C:\\Users\\j4ck\\Documents\\Projects\\Win-SharedFolder)
