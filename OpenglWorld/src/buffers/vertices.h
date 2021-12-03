

#ifndef VERTICES_H
#define VERTICES_H

namespace Vertices {

	inline constexpr float vertexPos[]{
		// positions          // colors           // texture coords
		// -> 8 stride
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,			// top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,			// bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,			// bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f			// top left 
	};

	inline constexpr unsigned int indexPos[]{
		// first triangle
		0, 1, 3,
		// second triangle
		1, 2, 3
	};

	inline constexpr unsigned int vertexSize{ sizeof(vertexPos) };
	inline constexpr unsigned int indexSize{ sizeof(indexPos) };



}

#endif