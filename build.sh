
clang src/main.c src/hacky_display.c -g -Wno-multichar -Wno-format -Wno-bool-operation -ferror-limit=1 -mavx  -lcurl -lpthread -lX11 -o snafuzz

