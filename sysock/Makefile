SRC=./
BUILD=./build

RUN=${BUILD}/out

all: cleanup cmake cbuild crun

cleanup:
	rm -rf $(BUILD)

cmake:
	cmake -B $(BUILD) -S $(SRC)

cbuild:
	make --directory ${BUILD}

crun:
	${BUILD}/out ${ARGS}