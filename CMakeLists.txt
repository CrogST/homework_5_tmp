cmake_minimum_required(VERSION 3.10)

if(NOT DEFINED ENV{TRAVIS_BUILD_NUMBER})
    set(ENV{TRAVIS_BUILD_NUMBER} 1)
endif()

project(h05_tmp VERSION 0.0.0$ENV{TRAVIS_BUILD_NUMBER})

set(bin_name print_ip)
set(ENV{TRAVIS_PACKET_NAME}} ${bin_name})
add_executable(${bin_name}
    main.cpp
    print_ip.h
    .travis.yml
    .doxygen.conf
    )

add_executable(Tests
    "test.cpp"
    )

set_target_properties(${bin_name} Tests PROPERTIES
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
install(TARGETS ${bin_name} RUNTIME DESTINATION bin)
set(CPACK_PACKAGE_NAME ${bin_name})
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT my_mail@some_mail.com)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
include(CPack)
