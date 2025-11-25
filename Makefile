all:
	g++ -c src/indexer/indexer.cpp -o output/indexer.o
	g++ -c src/index/index.cpp -o output/index.o
	g++ -c src/serializer/serializer.cpp -o output/serializer.o
	g++ -c src/query-processor/query-processor.cpp -o output/query-processor.o
	g++ -c src/text-processor/text-processor.cpp -o output/text-processor.o
	g++ -c src/command-line-interface.cpp -o output/command-line-interface.o
	g++ output/text-processor.o output/indexer.o output/index.o output/serializer.o output/query-processor.o output/command-line-interface.o -o output/main

clean:
	rm -rf output
