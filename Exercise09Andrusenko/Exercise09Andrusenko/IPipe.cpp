#include "IPipe.h"
#include <stdexcept>

using namespace std;

IPipe::~IPipe()
{
}

APipeNode::~APipeNode()
{
}

Pipe::Pipe()
{
}

Pipe::Pipe(const int size)
{
	if (size < 1) {
		throw std::invalid_argument("Size can not be lower than 1!");
	}

	this->size = size;
	matrix = new APipeNode** [size];
	for (int i = 0; i < size; i++) {
		matrix[i] = new APipeNode* [size];
		for (int j = 0; j < size; j++) {
			matrix[i][j] = 0;
		}
	}
}

Pipe::~Pipe()
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			delete matrix[i][j];
		}
	}

	for (int i = 0; i < size; i++) {
		delete matrix[i];
	}
	delete matrix;
}

void Pipe::addNode(APipeNode* pipeNode) const
{
	if (pipeNode->x > size && pipeNode->y > size) {
		throw std::invalid_argument("Wrong input parameters");
	}
	
	matrix[pipeNode->x][pipeNode->y] = pipeNode;
}

const APipeNode* Pipe::getNode(int x, int y) const
{
	if (x > size && y > size) {
		throw std::out_of_range("Wrong input parameters");
	}
	
	return matrix[x][y];
}

bool Pipe::isTubeOK() const
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (matrix[i][j] != nullptr) {
				if (!(matrix[i][j]->isCorrect(this))) {
					return false;
				}
			}
		}
	}
	return true;
}

PipeNode::PipeNode()
{
}

PipeNode::PipeNode(const int x, const int y, int type)
{
	this->x = x;
	this->y = y;
	this->type = type;
}

PipeNode::~PipeNode()
{
}

bool PipeNode::isCorrect(const IPipe* pipe) const
{
	if (this->type == 1) { // "-"
		return pipe->getNode(x, y - 1) != nullptr
			&& pipe->getNode(x, y + 1) != nullptr
			&& pipe->getNode(x, y - 1)->type != 2
			&& pipe->getNode(x, y + 1)->type != 2;
	}

	if (this->type == 2) { // "I"
		return pipe->getNode(x - 1, y) != nullptr
			&& pipe->getNode(x + 1, y) != nullptr
			&& pipe->getNode(x - 1, y)->type != 1
			&& pipe->getNode(x + 1, y)->type != 1
			&& pipe->getNode(x + 1, y)->type != 4;
	}

	if (this->type == 3) { // "+"
		return pipe->getNode(x - 1, y) != nullptr
			&& pipe->getNode(x + 1, y) != nullptr
			&& pipe->getNode(x, y - 1) != nullptr
			&& pipe->getNode(x, y + 1) != nullptr
			&& pipe->getNode(x - 1, y)->type != 1
			&& pipe->getNode(x + 1, y)->type != 1
			&& pipe->getNode(x, y - 1)->type != 2
			&& pipe->getNode(x, y + 1)->type != 2
			&& pipe->getNode(x + 1, y)->type != 4;
	}

	if (this->type == 4) { // "T"
		return pipe->getNode(x + 1, y) != nullptr
			&& pipe->getNode(x, y - 1) != nullptr
			&& pipe->getNode(x, y + 1) != nullptr
			&& pipe->getNode(x + 1, y)->type != 1
			&& pipe->getNode(x, y - 1)->type != 2
			&& pipe->getNode(x, y + 1)->type != 2
			&& pipe->getNode(x - 1, y)->type != 4;
	}

	// "O"
	return true;
}
