# tool macros
CC ?= clang
CFLAGS := -Iinclude
DBGFLAGS := -g
COBJFLAGS := $(CFLAGS) -c

# path macros
BIN_PATH := bin
OBJ_PATH := obj
SRC_PATH := src
DBG_PATH := debug

# compile macros
TARGET_NAME := document_matching
ifeq ($(OS),Windows_NT)
	TARGET_NAME := $(addsuffix .exe,$(TARGET_NAME))
endif
TARGET := $(BIN_PATH)/$(TARGET_NAME)
TARGET_DEBUG := $(DBG_PATH)/$(TARGET_NAME)

# src files & obj files
SRC := $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.c*)))
OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))
OBJ_DEBUG := $(addprefix $(DBG_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

# clean files list
CLEAN_LIST := $(BIN_PATH) \
			  $(OBJ_PATH) \
			  $(DBG_PATH)

# default rule
default: makedir all

# non-phony targets
$(TARGET): $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c*
	$(CC) $(COBJFLAGS) -o $@ $<

$(DBG_PATH)/%.o: $(SRC_PATH)/%.c*
	$(CC) $(COBJFLAGS) $(DBGFLAGS) -o $@ $<

$(TARGET_DEBUG): $(OBJ_DEBUG)
	$(CC) $(CFLAGS) $(DBGFLAGS) $(OBJ_DEBUG) -o $@

# phony rules
.PHONY: makedir
makedir:
ifeq ($(OS),Windows_NT)
	@if not exist "$(BIN_PATH)" mkdir $(BIN_PATH)
	@if not exist "$(OBJ_PATH)" mkdir $(OBJ_PATH)
	@if not exist "$(DBG_PATH)" mkdir $(DBG_PATH)
else
	@mkdir -p $(BIN_PATH) $(OBJ_PATH) $(DBG_PATH)
endif

.PHONY: all
all: $(TARGET) $(TARGET_DEBUG)

.PHONY: run
run: makedir all
	@./$(TARGET)

.PHONY: debug
debug: makedir all $(TARGET_DEBUG)
ifeq ($(OS),Windows_NT)
	@gdb ./$(TARGET_DEBUG)
else
	@lldb ./$(TARGET_DEBUG)
endif

.PHONY: clean
clean:
	@echo CLEAN $(BIN_PATH) $(OBJ_PATH) $(DBG_PATH)
ifeq ($(OS),Windows_NT)
	@echo Deleting files and directories in $(BIN_PATH), $(OBJ_PATH), and $(DBG_PATH)
	@if exist "$(BIN_PATH)" rmdir /S /Q "$(BIN_PATH)"
	@if exist "$(OBJ_PATH)" rmdir /S /Q "$(OBJ_PATH)"
	@if exist "$(DBG_PATH)" rmdir /S /Q "$(DBG_PATH)"
	@cls
else
	@rm -rf $(BIN_PATH) $(OBJ_PATH) $(DBG_PATH)
	@clear
endif


.PHONY: distclean
distclean:
	@echo CLEAN $(DISTCLEAN_LIST)
ifeq ($(OS),Windows_NT)
	@if exist "$(DISTCLEAN_LIST)" del /S /Q $(DISTCLEAN_LIST)
else
	@rm -f $(DISTCLEAN_LIST)
endif