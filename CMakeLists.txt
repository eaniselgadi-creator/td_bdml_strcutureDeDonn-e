cmake_minimum_required(VERSION 3.16)
project(td_bdml C)

# C11 strict, sans extensions du compilateur
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(td_bdml
        main.c
        flower.c   flower.h
        list.c     list.h
        dataset.c  dataset.h
        knn.c      knn.h
        queue.c    queue.h
        sensor.c   sensor.h
        stack.c    stack.h
        json_check.c json_check.h
)

if (MSVC)
    target_compile_options(td_bdml PRIVATE /W4)
    target_compile_definitions(td_bdml PRIVATE _CRT_SECURE_NO_WARNINGS)  # fopen
else ()
    target_compile_options(td_bdml PRIVATE -Wall -Wextra)
endif ()

# Bibliotheque mathematique (sqrtf, fabsf) : a lier explicitement sous Linux / macOS
if (UNIX)
    target_link_libraries(td_bdml PRIVATE m)
endif ()

# CLion lance le programme depuis le dossier de build (cmake-build-debug) :
# on y copie les fichiers de donnees pour que les chemins relatifs fonctionnent.
set(DATA_FILES
        flowers.csv sensor.csv
        config_ok.json config_ko1.json config_ko2.json config_tricky.json)
foreach (f ${DATA_FILES})
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${f} ${CMAKE_CURRENT_BINARY_DIR}/${f} COPYONLY)
endforeach ()
