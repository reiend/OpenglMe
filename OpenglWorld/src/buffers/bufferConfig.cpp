
#include "../includes/includes.h"
#include "./bufferConfig.h"


void configBuffer(unsigned int target, unsigned int& buffer, int dataSize, const void* data, GLenum usage) {
	glBindBuffer(target, buffer);
	glBufferData(target, dataSize, data, usage);
}
