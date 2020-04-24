add_executable(HelloYellow HelloYellow.cpp HelloYellow.h)
target_link_libraries(HelloYellow YellowEngine)
target_link_options(HelloYellow PUBLIC  /SUBSYSTEM:console)