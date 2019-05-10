#include "ParticleSystemPoint.hpp"

ParticleSystemPoint::ParticleSystemPoint()
{

}

ParticleSystemPoint::~ParticleSystemPoint()
{

}

void 		ParticleSystemPoint::createGLBufers()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Particle) * m_particleCount, nullptr, GL_STREAM_DRAW);

	glBindVertexArray(m_VAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	setInstanceBuffer();
}

void 				ParticleSystemPoint::setInstanceBuffer()
{
	glBindVertexArray(m_VAO);
    glGenBuffers(1, &m_IBO);

    glBindBuffer(GL_ARRAY_BUFFER, m_IBO);
	glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4) * 4, (GLvoid*)(0 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4) * 4, (GLvoid*)(1 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4) * 4, (GLvoid*)(2 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4) * 4, (GLvoid*)(3 * sizeof(glm::vec4)));
    glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void 			ParticleSystemPoint::initGLBufers(std::string const & initKernelName)
{
	glFinish();
	cl::Kernel kernel;

	clearMemoryStack();
	addGLBuffer(m_VBO);

	m_CLE->getKernel(initKernelName, kernel);
	auto commandQueue = m_CLE->getCommandQueue();
	commandQueue.enqueueAcquireGLObjects(&m_memory);
	kernel.setArg(0, m_memory.front());
	kernel.setArg(1, m_particleCount);


	commandQueue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(m_particleCount), cl::NullRange);
	commandQueue.finish();
	commandQueue.enqueueReleaseGLObjects(&m_memory);
	cl::finish();
}

void 			ParticleSystemPoint::updateGLBufers(std::string const & updateKernelName, glm::vec3 const & gravityCenter, bool isGravityActive)
{
	glFinish();

	cl::Kernel kernel;
	m_CLE->getKernel(updateKernelName, kernel);

	auto commandQueue = m_CLE->getCommandQueue();
 	commandQueue.enqueueAcquireGLObjects(&m_memory);
	kernel.setArg(0, m_memory.front());
	kernel.setArg(1, m_deltaTime);
	kernel.setArg(2, gravityCenter);
	kernel.setArg(3,isGravityActive);

	commandQueue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(m_particleCount), cl::NullRange);
	commandQueue.enqueueReleaseGLObjects(&m_memory);
	commandQueue.finish();
	cl::finish();
}

void 				ParticleSystemPoint::setTexture(std::string const & textureName)
{

}
