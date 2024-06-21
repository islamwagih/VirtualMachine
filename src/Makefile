SRC_FILES = vm.c
CC_FLAGS_DEBUG = -Wall -Wextra -Werror -g -std=c11
CC_FLAGS_RELEASE = -Wall -Wextra -std=c11
CC = clang
build:
	${CC} ${SRC_FILES} ${CC_FLAGS_DEBUG} -o exe
run: build
	./exe


