CC = gcc
CFLAGS = -I./src -Wall -Wextra -Wshadow -Wformat=2 -fno-common -fstack-protector-all -fsanitize=address

build:
	@mkdir -p build
	@$(CC) $(CFLAGS) -c src/main.c 					-o build/main.o
	@$(CC) $(CFLAGS) -c src/utils/defer_file.c 		-o build/defer_file.o
	@$(CC) $(CFLAGS) -c src/utils/defer_task.c 		-o build/defer_task.o
	@$(CC) $(CFLAGS) -c src/utils/in_charr.c 		-o build/in_charr.o
	@$(CC) $(CFLAGS) -c src/utils/list_dir.c 		-o build/list_dir.o
	@$(CC) $(CFLAGS) -c src/utils/makefile.c 		-o build/makefile.o
	@$(CC) $(CFLAGS) -c src/utils/package_parser.c 	-o build/package_parser.o
	@$(CC) $(CFLAGS) -c src/utils/replacer.c 		-o build/replacer.o
	@$(CC) $(CFLAGS) -c src/utils/char_end.c 		-o build/char_end.o
	@$(CC) $(CFLAGS) -c src/utils/system_stream.c 	-o build/system_stream.o
	@$(CC) $(CFLAGS) -c src/utils/trim.c 			-o build/trim.o
	@$(CC) $(CFLAGS) build/main.o build/char_end.o build/defer_file.o build/defer_task.o build/in_charr.o build/list_dir.o build/makefile.o build/package_parser.o build/replacer.o build/system_stream.o build/trim.o -o build/main
	@chmod +x build/main

clean:
	@rm -rf build
