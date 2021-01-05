#ifndef IPIPE_H
#define IPIPE_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>


struct APipeNode;

struct IPipe
{
    virtual ~IPipe();
    virtual void addNode(APipeNode* pipeNode) const = 0;
    virtual const APipeNode* getNode(int x, int y) const = 0;
    virtual bool isTubeOK() const = 0;
};

struct APipeNode {
    virtual ~APipeNode();
    virtual bool isCorrect(const IPipe* pipe) const = 0;
    int x;
    int y;
    int type;
};


struct Pipe : IPipe {
private:
    APipeNode*** matrix;
    int size;
public:
    Pipe();
    Pipe(const int size);
    ~Pipe();
    void addNode(APipeNode* pipeNode) const override;
    const APipeNode* getNode(int x, int y) const override;
    bool isTubeOK() const override;
};

struct PipeNode : APipeNode {
    PipeNode();
    PipeNode(const int x, const int y, int type);
    ~PipeNode();
    bool isCorrect(const IPipe* pipe) const override;
};

#endif // !IPIPE_H