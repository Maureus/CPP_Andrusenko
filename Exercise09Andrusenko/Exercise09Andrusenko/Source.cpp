#include <iostream>
#include <fstream>
#include <sstream>

#include "IPipe.h"

using namespace std;



int main() {
	try
	{
		IPipe* pipe;
		int size = 0;
		ifstream in;
		string line;
		char c;
		in.open("positions.txt");
		if (in.is_open()) {
			getline(in, line);
			size = stoi(line);
			pipe = new Pipe(size);
			int i = 0;
			while (getline(in, line)) {
				for (int j = 0; j < line.length(); j++) {
					c = line.at(j);
					switch (c) {
					case '-':
						pipe->addNode(new PipeNode(i, j, 1));
						break;
					case 'I':
						pipe->addNode(new PipeNode(i, j, 2));
						break;
					case '+':
						pipe->addNode(new PipeNode(i, j, 3));
						break;
					case 'O':
						pipe->addNode(new PipeNode(i, j, 0));
						break;
					case 'T':
						pipe->addNode(new PipeNode(i, j, 4));
						break;
					}
				}
				i++;
			}
			cout << "Is tube ok? ";
			cout << pipe->isTubeOK() << endl;
			in.close();
		}
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
	}

	return 0;
}