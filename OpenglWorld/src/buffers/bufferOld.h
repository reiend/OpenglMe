
#ifndef BUFFER_H
#define BUFFER_H

#include "../includes/includes.h"
#include "./bufferInfo.h"

class Buffer {
private:
	unsigned int bufferObject;

public:
	Buffer(BufferType type, unsigned int target = 0, int count = 1);
	unsigned int getBufferObject();
	void clearBuffer(BufferType type, int count);
	void setBufferLayout(GLuint index, GLint size, GLsizei stride, const void* pointer=((void*)0), GLenum type = GL_FLOAT, GLboolean normalized = GL_FALSE);
	void createBufferTBO(unsigned activeTexture, GLenum target, GLuint texture);

private:
	void bufferConfigType(BufferType type, unsigned int target) const;
	void createBufferVBO(unsigned int target) const;
	void createBufferEBO(unsigned int target) const;
	void createBufferVAO() const;

};



#endif
