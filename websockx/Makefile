SRC=./
BUILD=./build

RUN=${BUILD}/out

all: cmake out

cmake: cleanup cbuild

cleanup:
	rm -rf $(BUILD)

cbuild:
	cmake -B $(BUILD) -S $(SRC)

out: cbin crun

cbin:
	make --directory ${BUILD}

crun:
	${RUN} ${ARGS}