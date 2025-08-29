# file is connections/mainfiles/CMakeLists.txt
add_executable(preprocessor.elf preprocessor.cpp)

# add_custom_command(
#     OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/cvk_impl_frontendconnectionside.cpp
#     COMMAND preprocessor.elf impl_frontendconnectionside.cpp impl_frontendconnectionside.hpp impl_backendconnectionside.hpp
#     DEPENDS preprocessor.elf impl_frontendconnectionside.cpp impl_frontendconnectionside.hpp impl_backendconnectionside.hpp
#     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
# )

# add_custom_command(
#     OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/cvk_impl_frontendconnectionside.hpp
#     COMMAND preprocessor.elf impl_frontendconnectionside.hpp impl_backendconnectionside.hpp
#     DEPENDS preprocessor.elf impl_frontendconnectionside.hpp impl_backendconnectionside.hpp
#     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
# )

# add_custom_command(
#     OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/cvk_impl_backendconnectionside.cpp
#     COMMAND preprocessor.elf impl_backendconnectionside.cpp impl_frontendconnectionside.hpp impl_backendconnectionside.hpp
#     DEPENDS preprocessor.elf impl_backendconnectionside.cpp impl_frontendconnectionside.hpp impl_backendconnectionside.hpp
#     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
# )

# add_custom_command(
#     OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/cvk_impl_backendconnectionside.hpp
#     COMMAND preprocessor.elf impl_backendconnectionside.hpp impl_frontendconnectionside.hpp
#     DEPENDS preprocessor.elf impl_backendconnectionside.hpp impl_frontendconnectionside.hpp
#     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
# )

# add_custom_command(
#     OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/../impl_frontendconnectionside.hpp
#     DEPENDS preprocessor.elf cvk_impl_frontendconnectionside.hpp
#     COMMAND ${CMAKE_COMMAND} -E create_symlink
#             ${CMAKE_CURRENT_SOURCE_DIR}/cvk_impl_frontendconnectionside.hpp
#             ${CMAKE_CURRENT_SOURCE_DIR}/../frontendconnectionside.hpp
#     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
# )
# add_custom_command(
#     OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/../impl_backendconnectionside.hpp
#     DEPENDS preprocessor.elf cvk_impl_backendconnectionside.hpp
#     COMMAND ${CMAKE_COMMAND} -E create_symlink
#             ${CMAKE_CURRENT_SOURCE_DIR}/cvk_impl_backendconnectionside.hpp
#             ${CMAKE_CURRENT_SOURCE_DIR}/../backendconnectionside.hpp
#     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
# )

set(CON_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/cvk_impl_frontendconnectionside.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cvk_impl_backendconnectionside.cpp
)

set(CON_SOURCES ${CON_SOURCES} PARENT_SCOPE )

add_custom_target(generate_connections ALL
    # DEPENDS ${CON_SOURCES}
    # DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/../impl_backendconnectionside.hpp
    # DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/../impl_frontendconnectionside.hpp
    # DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/cvk_impl_backendconnectionside.hpp
    # DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/cvk_impl_frontendconnectionside.hpp
    BYPRODUCTS
        ${CMAKE_CURRENT_SOURCE_DIR}/cvk_impl_frontendconnectionside.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/cvk_impl_frontendconnectionside.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/cvk_impl_backendconnectionside.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/cvk_impl_backendconnectionside.hpp
    # regenerate each time for fetching updated files
    COMMAND preprocessor.elf impl_frontendconnectionside.cpp impl_frontendconnectionside.hpp impl_backendconnectionside.hpp
    COMMAND preprocessor.elf impl_frontendconnectionside.hpp impl_backendconnectionside.hpp
    COMMAND preprocessor.elf impl_backendconnectionside.cpp impl_frontendconnectionside.hpp impl_backendconnectionside.hpp
    COMMAND preprocessor.elf impl_backendconnectionside.hpp impl_frontendconnectionside.hpp
    COMMAND ${CMAKE_COMMAND} -E create_symlink
            ${CMAKE_CURRENT_SOURCE_DIR}/cvk_impl_frontendconnectionside.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/../frontendconnectionside.hpp
    COMMAND ${CMAKE_COMMAND} -E create_symlink
            ${CMAKE_CURRENT_SOURCE_DIR}/cvk_impl_backendconnectionside.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/../backendconnectionside.hpp
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_dependencies(generate_connections preprocessor.elf)

add_dependencies(generate_connections preprocessor.elf)
