default: fract

.PHONY: test
.PHONY: fract
.PHONY: deploy

BUILD_DIR=build
INCLUDE_DIR=include
fract:
	cd src && $(MAKE)

test: deploy
	cd test && $(MAKE)

deploy: fract
	cp -t $(BUILD_DIR) \
		src/fractal \
		src/libfract.so.1.0 \
		src/builder.ui
	cd $(BUILD_DIR) && \
	ln -sf libfract.so.1.0 libfract.so.1 && \
	ln -sf libfract.so.1.0 libfract.so
	cp -t $(INCLUDE_DIR) src/*.hpp
