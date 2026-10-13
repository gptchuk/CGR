cmake_minimum_required(VERSION 3.20)

project(OpenGLProject LANGUAGES C CXX)

# ==================================================
# Configuração do C++
# ==================================================

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ==================================================
# Diretórios do projeto
# ==================================================

set(PROJECT_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(EXTERNAL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external")

set(GLFW_DIR "${EXTERNAL_DIR}/glfw")
set(GLAD_DIR "${EXTERNAL_DIR}/glad")

# ==================================================
# Validação das dependências
# ==================================================

if(NOT EXISTS "${GLFW_DIR}/CMakeLists.txt")
    message(FATAL_ERROR
        "GLFW nao encontrado: ${GLFW_DIR}/CMakeLists.txt")
endif()

if(NOT EXISTS "${GLAD_DIR}/src/glad.c")
    message(FATAL_ERROR
        "GLAD 1 nao encontrado: ${GLAD_DIR}/src/glad.c")
endif()

if(NOT EXISTS "${GLAD_DIR}/include/glad/glad.h")
    message(FATAL_ERROR
        "Header do GLAD nao encontrado.")
endif()

# ==================================================
# GLFW
# ==================================================

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory("${GLFW_DIR}" "${CMAKE_BINARY_DIR}/glfw")

# ==================================================
# GLAD
# ==================================================

add_library(glad STATIC
    "${GLAD_DIR}/src/glad.c"
)

target_include_directories(glad PUBLIC
    "${GLAD_DIR}/include"
)

# ==================================================
# Descoberta automática dos arquivos C++
# ==================================================

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/*.cpp"
)

if(NOT PROJECT_SOURCES)
    message(FATAL_ERROR
        "Nenhum arquivo .cpp encontrado em src/.")
endif()

# ==================================================
# Executável
# ==================================================

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    "${PROJECT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# ==================================================
# OpenGL
# ==================================================

find_package(OpenGL REQUIRED)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    GLFW_INCLUDE_NONE
)

find_package(OpenGL REQUIRED)

if(NOT TARGET OpenGL::GLU)
    message(FATAL_ERROR
        "GLU nao encontrada. Verifique sua instalacao.")
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    glad
    OpenGL::GL
    OpenGL::GLU
)

# ==================================================
# Mensagens informativas
# ==================================================

message(STATUS "Projeto: ${PROJECT_NAME}")
message(STATUS "Fontes C++ encontrados: ${PROJECT_SOURCES}")
message(STATUS "GLFW: ${GLFW_DIR}")
message(STATUS "GLAD: ${GLAD_DIR}")