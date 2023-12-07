SRC=./src
BUILD=./build

RUN=sysock

all:

cbuild:
	cmake -B $(BUILD) -S $(SRC)

crun: 
	$(BUILD)/$(RUN) $(ARGS)

cleanup:
	rm -rf $(BUILD)