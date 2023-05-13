#include "VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout()
    : m_Stride(0)
{
    // Constructor that initializes the stride to zero
}

// Specialized version of the Push() function for adding elements of type float
void VertexBufferLayout::AddFloat(unsigned int count)
{
    Push(GL_FLOAT, count, GL_FALSE);
}

// Specialized version of the Push() function for adding elements of type unsigned int
void VertexBufferLayout::AddUnsignedInt(unsigned int count)
{
    Push(GL_UNSIGNED_INT, count, GL_FALSE);
}

// Specialized version of the Push() function for adding elements of type unsigned char
void VertexBufferLayout::AddUnsignedChar(unsigned int count)
{
    Push(GL_UNSIGNED_BYTE, count, GL_TRUE);
}


void VertexBufferLayout::Push(unsigned int type, unsigned int count, unsigned char normalized)
{
    m_Elements.push_back({ type, count, normalized });// Add a new element of type GL_FLOAT, GL_UNSIGNED_INT, GL_UNSIGNED_BYTE to the vector
    m_Stride += count * VertexBufferElement::GetSizeOfType(type); // Increase the stride by the size of the new element
}
