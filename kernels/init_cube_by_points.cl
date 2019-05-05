#define QUAD_SIZE	0.3f
#define NULITY	(float4)(0.0f, 0.0f, 0.0f, 0.0f)
#define INF	(float4)(10000.0f, 10000.0f, 10000.0f, 1.0f)

typedef float4 Particle;

void kernel initialize_Cube(global Particle * particles, int particleCount)
{
	int				i = get_global_id(0);
	global Particle * particle = particles + i;

	uint	subDivCount = cbrt((float)particleCount);

	uint	x = fmod((float)i, (float)subDivCount);
	uint	y = fmod((float)i / subDivCount, (float)subDivCount);
	uint	z = i / (subDivCount * subDivCount);

	float	particleArea = QUAD_SIZE / subDivCount;
	float	particleArea2 = particleArea / 2.0f;

	particle->x = x * particleArea - 0.3 + particleArea2 + QUAD_SIZE / 2;
	particle->y = y * particleArea - 0.3 + particleArea2  + QUAD_SIZE / 2;
	particle->z = z * particleArea - 0.3 + particleArea2;
	particle->w = 0.0f;
}
