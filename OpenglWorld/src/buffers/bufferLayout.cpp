
#include "../includes/includes.h"
#include "bufferLayout.h"

void setBufferLayout(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer, GLuint indexEnable) {
	// Specify layout for opengl
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	glEnableVertexAttribArray(indexEnable);
}