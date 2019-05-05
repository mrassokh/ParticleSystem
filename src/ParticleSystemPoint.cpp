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

	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)(8* sizeof(GLfloat)));

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
	std::cout << "init gl buffer" << initKernelName << "\n\n\n\n";
	clearMemoryStack();
	addGLBuffer(m_VBO);

	m_CLE->getKernel(initKernelName, kernel);
	auto commandQueue = m_CLE->getCommandQueue();
	commandQueue.enqueueAcquireGLObjects(&m_memory);
	//cl::Buffer buffer_C(m_CLE->getContext(), CL_MEM_READ_WRITE, sizeof(Particle) * m_particleCount);
	//Particle C[m_particleCount];
	kernel.setArg(0, m_memory.front());
	kernel.setArg(1, m_particleCount);
	//kernel.setArg(1, buffer_C);


	commandQueue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(m_particleCount), cl::NullRange);
	//commandQueue.enqueueReadBuffer(buffer_C, CL_TRUE, 0, sizeof(Particle) * m_particleCount, C);
	commandQueue.finish();
	commandQueue.enqueueReleaseGLObjects(&m_memory);
	cl::finish();
	/*for (int i =0; i < m_particleCount; ++i) {
		std::cout << "particle " << i << "has position" << C[i].position.x << " / " << C[i].position.y << " / "<< C[i].position.z << " / "<< C[i].position.w<<  std::endl;
		std::cout << "particle " << i << "has color" << C[i].color.x << " / " << C[i].color.y << " / "<< C[i].color.z << " / "<< C[i].color.w << std::endl;
		std::cout << "particle " << i << "has velocity" << C[i].velocity.x << " / " << C[i].velocity.y << " / "<< C[i].velocity.z << " / "<< C[i].velocity.w <<std::endl;
	}*/
}

void 			ParticleSystemPoint::updateGLBufers(std::string const & updateKernelName, glm::vec3 const & gravityCenter, bool isGravityActive)
{
	glFinish();

	cl::Kernel kernel;
	m_CLE->getKernel(updateKernelName, kernel);
	//std::cout << "update with " << updateKernelName << "and particle count " << m_particleCount;
	auto commandQueue = m_CLE->getCommandQueue();
 	commandQueue.enqueueAcquireGLObjects(&m_memory);
	/*cl_float4  gravityCenter1;
	gravityCenter1.x = gravityCenter.x;
	gravityCenter1.y = gravityCenter.y;
	gravityCenter1.z = gravityCenter.z;
	gravityCenter1.w = 0;*/
	// = cl_float4(gravityCenter, 1.0f);
	kernel.setArg(0, m_memory.front());
	kernel.setArg(1, m_deltaTime);
	kernel.setArg(2, gravityCenter);
	//kernel.setArg(2, gravityCenter1);
	kernel.setArg(3,isGravityActive);

	commandQueue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(m_particleCount), cl::NullRange);
	commandQueue.enqueueReleaseGLObjects(&m_memory);
	commandQueue.finish();
	cl::finish();
}

void 				ParticleSystemPoint::setTexture(std::string const & textureName)
{

}
