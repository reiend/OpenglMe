



#include "./bufferEntity.h"
#include "./vertices.h"
#include "../includes/includes.h"

unsigned int* buffer;

BufferEntity::BufferEntity(GLenum target, GLenum usage, int count) {
	bufferInit(count);
	this->createBuffer(target, usage);
}

BufferEntity::~BufferEntity() {
	clearBuffer();
}

void BufferEntity::bufferInit(int count) {
	this->buffer = new unsigned int[count];
	glGenBuffers(count, buffer);
}

void BufferEntity::createBuffer(GLenum target, GLenum usage) {
	glBindBuffer(target, (*buffer));
	glBufferData(target, Vertices::vertexSize, Vertices::vertexPos, usage);
}

unsigned int* BufferEntity::getBuffer() {
	return buffer;
}


void BufferEntity::clearBuffer() {
	delete[] buffer;
	buffer = nullptr;
}