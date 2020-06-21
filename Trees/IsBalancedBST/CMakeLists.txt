project (IsBalancedBST)

include_directories(${PROJECT_SOURCE_DIR}/../../Common/Trees)
set(Source ${PROJECT_NAME}.cpp)
add_executable(${PROJECT_NAME} ${Source})
target_link_libraries(${PROJECT_NAME} Trees)
