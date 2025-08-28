# file is connections/mainfiles/CMakeLists.txt
add_executable(preprocessor.elf preprocessor.cpp)

# add_custom_command(
#     OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/cvk_frontendconnectionside.cpp
#     COMMAND preprocessor.elf frontendconnectionside.cpp frontendconnectionside.hpp backendconnectionside.hpp
#     DEPENDS preprocessor.elf frontendconnectionside.cpp frontendconnectionside.hpp backendconnectionside.hpp
#     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
# )

# add_custom_command(
#     OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/cvk_frontendconnectionside.hpp
#     COMMAND preprocessor.elf frontendconnectionside.hpp backendconnectionside.hpp
#     DEPENDS preprocessor.elf frontendconnectionside.hpp backendconnectionside.hpp
#     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
# )

# add_custom_command(
#     OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/cvk_backendconnectionside.cpp
#     COMMAND preprocessor.elf backendconnectionside.cpp frontendconnectionside.hpp backendconnectionside.hpp
#     DEPENDS preprocessor.elf backendconnectionside.cpp frontendconnectionside.hpp backendconnectionside.hpp
#     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
# )

# add_custom_command(
#     OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/cvk_backendconnectionside.hpp
#     COMMAND preprocessor.elf backendconnectionside.hpp frontendconnectionside.hpp
#     DEPENDS preprocessor.elf backendconnectionside.hpp frontendconnectionside.hpp
#     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
# )

# add_custom_command(
#     OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/../frontendconnectionside.hpp
#     DEPENDS preprocessor.elf cvk_frontendconnectionside.hpp
#     COMMAND ${CMAKE_COMMAND} -E create_symlink
#             ${CMAKE_CURRENT_SOURCE_DIR}/cvk_frontendconnectionside.hpp
#             ${CMAKE_CURRENT_SOURCE_DIR}/../frontendconnectionside.hpp
#     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
# )
# add_custom_command(
#     OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/../backendconnectionside.hpp
#     DEPENDS preprocessor.elf cvk_backendconnectionside.hpp
#     COMMAND ${CMAKE_COMMAND} -E create_symlink
#             ${CMAKE_CURRENT_SOURCE_DIR}/cvk_backendconnectionside.hpp
#             ${CMAKE_CURRENT_SOURCE_DIR}/../backendconnectionside.hpp
#     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
# )

set(CON_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/cvk_frontendconnectionside.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cvk_backendconnectionside.cpp
)

set(CON_SOURCES ${CON_SOURCES} PARENT_SCOPE )

add_custom_target(generate_connections ALL
    # DEPENDS ${CON_SOURCES}
    # DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/../backendconnectionside.hpp
    # DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/../frontendconnectionside.hpp
    # DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/cvk_backendconnectionside.hpp
    # DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/cvk_frontendconnectionside.hpp
    COMMAND preprocessor.elf frontendconnectionside.cpp frontendconnectionside.hpp backendconnectionside.hpp
    COMMAND preprocessor.elf frontendconnectionside.hpp backendconnectionside.hpp
    COMMAND preprocessor.elf backendconnectionside.cpp frontendconnectionside.hpp backendconnectionside.hpp
    COMMAND preprocessor.elf backendconnectionside.hpp frontendconnectionside.hpp
    COMMAND ${CMAKE_COMMAND} -E create_symlink
            ${CMAKE_CURRENT_SOURCE_DIR}/cvk_frontendconnectionside.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/../frontendconnectionside.hpp
    COMMAND ${CMAKE_COMMAND} -E create_symlink
            ${CMAKE_CURRENT_SOURCE_DIR}/cvk_backendconnectionside.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/../backendconnectionside.hpp
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)