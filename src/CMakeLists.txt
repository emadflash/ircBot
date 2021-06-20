add_library(
    irc
    main.c
    client.h
    irc.h
    parser.h
    irc.c
    parser.c
)

target_include_directories(irc PUBLIC .)
add_executable(ircbot main.c)
target_link_libraries(
  ircbot
  irc
)
