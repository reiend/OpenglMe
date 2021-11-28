
#ifndef BUFFER_ENTITY_H
#define BUFFER_ENTITY_H

#include "./bufferInfo.h"
#include "../includes/includes.h"



class BufferEntity {

private:
	unsigned int* buffer;

public:
	BufferEntity(int count);
	~BufferEntity();
	virtual void bufferInit(int count);
	virtual void bufferConfigType(GLenum target, GLenum usage = GL_STATIC_DRAW);
	unsigned int* getBuffer();
	void clearBuffer();

};

#endif