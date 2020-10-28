!/bin/zsh

cmake . -Bbuild -Wdev -Werror=dev && cmake --build ./build
