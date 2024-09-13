build-library:
	cd lib && ./build.sh

run-library-tests: build-library
	cd lib/test && ./run-tests.sh

run-cli: build-library
	cd cli && ./build-cli.sh
	./cli/build/cli