cmake_minimum_required(VERSION 3.10)
project(DecodificadorPRT7 VERSION 1.0.0 LANGUAGES CXX)

# Configuración del estándar de C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Directorios de inclusión
include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

# Archivos fuente
set(SOURCES
    src/ListaDeCarga.cpp
    src/RotorDeMapeo.cpp
    src/TramaLoad.cpp
    src/TramaMap.cpp
    main.cpp
)

# Archivos de cabecera
set(HEADERS
    include/TramaBase.h
    include/TramaLoad.h
    include/TramaMap.h
    include/ListaDeCarga.h
    include/RotorDeMapeo.h
)

# Crear ejecutable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Configuración de instalacion
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)