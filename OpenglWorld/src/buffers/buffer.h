
#ifndef BUFFER_H
#define BUFFER_H

#include "../includes/includes.h"



enum class BufferType {
	VBO,
	EBO,
	VAO,
};

class Buffer {
private:
	unsigned int bufferObject;

public:
	Buffer(BufferType type, unsigned int target = 0, int count = 1);
	unsigned int getBufferObject();
	void clearBuffer(BufferType type, int count);
private:
	void bufferConfigType(BufferType type, unsigned int target) const;
	void createBufferVBO(unsigned int target) const;
	void createBufferEBO(unsigned int target) const;
	void createBufferVAO() const;

};



#endif
