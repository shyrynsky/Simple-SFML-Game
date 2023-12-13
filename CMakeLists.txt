cmake_minimum_required(VERSION 3.5)
project(Game VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

# Указываем папку, куда установили библиотеки
set(CMAKE_PREFIX_PATH C:/Users/Shyrynsky/Documents/libraries)

# Сообщаем, что используем статические библиотеки
set(SFML_STATIC_LIBRARIES TRUE)

# Находим и импортируем библиотеки
find_package(SFML COMPONENTS graphics audio REQUIRED)
# find_package(SFML COMPONENTS audio REQUIRED)

add_executable(Game WIN32 main.cpp gameView.cpp gameField.cpp gameLogic.cpp gameRes.cpp gameTemplates.cpp gameSets.cpp MenuHandler.cpp)

# Добавление заголовочных файлов
target_include_directories(Game PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Линкуем наш экзешник с sfml-graphics
target_link_libraries(Game sfml-graphics sfml-audio)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
