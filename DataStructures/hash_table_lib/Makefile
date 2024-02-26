
NAME = hashTableLib.a

CC = cc
CFLAGS =  -Wall -Wextra -Werror
ARFLAGS = ar -rcs
REMOVE = rm -rf

OBJ_PATH = obj
SRC_PATH = src
INC_PATH = include

TOXIC_GREEN = \033[1;38;5;118m
MATCHING_COLOR = \033[1;38;5;129m
RESET = \033[0m
U_LINE = \033[4m

HEADERS	= -I $(INC_PATH)

SRC = $(shell find $(SRC_PATH) -name '*.c')
OBJ = $(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o,$(SRC))

.SILENT: all $(NAME) $(OBJ) clean fclean re test

all: $(NAME)

$(NAME): $(OBJ)
	$(ARFLAGS) $@ $(OBJ)
	echo "\n$(TOXIC_GREEN)$(U_LINE)🧪 $(NAME): Compiled 🧪$(RESET) \n"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)
	echo "$(MATCHING_COLOR)$(NAME) Compiling:$(RESET) $(notdir $<)"

clean:
	$(REMOVE) $(OBJ_PATH)

fclean: clean
	$(REMOVE) $(NAME)

re: fclean all


$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

test: all
	echo '#include "include/header.h"\n\nplayer *createPlayer(int index, int lose_val)\n{\n    player *new_player = (player *)malloc(sizeof(player));\n    if (new_player != NULL)\n    {\n        new_player->index = index;\n        new_player->lose_val = lose_val;\n        new_player->next = NULL;\n    }\n    return new_player;\n}\n\nint main()\n{\n    player *hash_table[TABLE_SIZE];\n    init_hash_table(hash_table);\n\n    int player_indices[] = {101, 102, 103, 104, 105};\n\n    for (int i = 0; i < sizeof(player_indices) / sizeof(player_indices[0]); i++)\n    {\n        int index = player_indices[i];\n        int lose_val = 0;\n        player *new_player = createPlayer(index, lose_val);\n\n        if (new_player != NULL)\n        {\n            insert_hash_table(new_player, hash_table);\n        }\n    }\n\n    printf("Hash Table:\\n");\n    print_hash_table(hash_table);\n    return 0;\n}' > test.c
	$(CC) test.c hashTableLib.a -o test
	./test

.PHONY: all clean fclean re test
