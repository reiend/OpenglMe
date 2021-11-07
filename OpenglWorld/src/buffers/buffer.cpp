
#include "../includes/includes.h"
#include "./buffer.h"

void setBuffers(int count, unsigned int& vertexBufferObject, unsigned int& vertexArrayObject, 
	unsigned int& elementBufferObject) {

	// Create A buffer
	glGenBuffers(count, &vertexBufferObject);
	glGenVertexArrays(count, &vertexArrayObject);
	glGenBuffers(count, &elementBufferObject);
	glBindVertexArray(vertexArrayObject);

}

