#include "VertexBuffer.h"
VertexBuffer::VertexBuffer()
    :vb_id(0)
{
    // Empty constructor at program start
}

VertexBuffer::~VertexBuffer()
{
    // Destructor: deletes the vertex buffer object identified by the ID.
    glDeleteBuffers(1, &vb_id);
}


void VertexBuffer::createVertexBuffer(const void* data, unsigned int size)
{
    // Main Constructor
    glGenBuffers(1, &vb_id);
    glBindBuffer(GL_ARRAY_BUFFER, vb_id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}


void VertexBuffer::Bind() const
{
    // Bind this vertex buffer with its id
    glBindBuffer(GL_ARRAY_BUFFER, vb_id);
}

void VertexBuffer::UnBind() const
{
    // Unbinds the currently bound vertex buffer object.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}