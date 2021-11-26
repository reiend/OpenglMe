
#ifndef BUFFER_H
#define BUFFER_H

#include "../includes/includes.h"



enum class BufferType {
	vbo,
	ebo,
};

class Buffer {
private:
	unsigned int bufferObject = 1;

public:
	Buffer(BufferType type, unsigned int target, int count = 1);
	unsigned int getBufferObject();

private:
	void bufferConfigType(BufferType type, unsigned int target) const;
	void createBufferVBO(unsigned int target) const;
	void createBufferEBO(unsigned int target) const;
};

#endif
