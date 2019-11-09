cmake_minimum_required(VERSION 3.10)

if(NOT DEFINED ENV{TRAVIS_BUILD_NUMBER})
    set(ENV{TRAVIS_BUILD_NUMBER} 1)
endif()

project(h05_tmp VERSION 0.0.0$ENV{TRAVIS_BUILD_NUMBER})

add_executable(${PROJECT_NAME}
    main.cpp
#    .travis.yml
)

add_executable(Tests
    "test.cpp"
)

set_target_properties(${PROJECT_NAME} Tests PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
set_target_properties(Tests
    PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(Tests
    ${Boost_LIBRARIES}
)

enable_testing()
add_test(proj_tests Tests)

#настройка создания пакета
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT my_mail@some_mail.com)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
include(CPack)
