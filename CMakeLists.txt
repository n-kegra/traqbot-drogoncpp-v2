add_library(traQBot)
target_include_directories(traQBot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(traQBot PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/traQBot/events.cpp)

# target_link_libraries(traQBot PRIVATE traQApi)
target_link_libraries(traQBot PRIVATE Drogon::Drogon)
