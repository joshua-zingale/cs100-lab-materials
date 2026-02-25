html: info
	genhtml build/coverage.info --output-directory build/CODE_COVERAGE
info: example-example.gcda
	lcov --capture --directory build --output-file build/coverage.info
gcov: example-example.gcda example-example.gcno
	gcov build/example-example.gcno -t > build/example.cpp.gcov
example-example.gcda: example
	./build/example
example-example.gcno: example
example: example.cpp
	gcc -ftest-coverage -fprofile-arcs example.cpp -o build/example
clean:
	find build -type f ! -name ".gitkeep" -delete 
	rm -rf build/CODE_COVERAGE
