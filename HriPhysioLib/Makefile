build-library:
	cd lib && ./build.sh

run-library-tests: build-library
	cd lib/test && ./run-tests.sh

run-cli: build-library
	python3 cli/scripts/generate_data.py  # Run the Python script
	cd cli && ./build-cli.sh
	./cli/build/cli

run-plot:
	python3 cli/scripts/plot_data.py