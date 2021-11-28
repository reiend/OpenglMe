



#include "./bufferEntity.h"
#include "./vertices.h"

unsigned int* buffer;

BufferEntity::BufferEntity(int count) {
	bufferInit(count);
}

BufferEntity::~BufferEntity() {
	clearBuffer();
}

void BufferEntity::bufferInit(int count) {
	this->buffer = new unsigned int[count];
	glGenBuffers(count, buffer);
}

void BufferEntity::bufferConfigType(GLenum target, GLenum usage) {
	glBindBuffer(target, *(this->getBuffer()));
	glBufferData(target, Vertices::vertexSize, Vertices::vertexPos, usage);
}

unsigned int* BufferEntity::getBuffer() {
	return buffer;
}


void BufferEntity::clearBuffer() {
	delete[] buffer;
	buffer = nullptr;
}