#define QUAD_SIZE	0.3f
#define NULITY	(float4)(0.0f, 0.0f, 0.0f, 0.0f)
#define INF	(float4)(10000.0f, 10000.0f, 10000.0f, 1.0f)

typedef struct
{
	float4	position;
}			Particle;

void kernel initialize_Cube(global Particle * particles, int particleCount)
{
	int				i = get_global_id(0);
	global float4 *	position = &(particles[i].position);

	uint	subDivCount = cbrt((float)particleCount);

	uint	x = fmod((float)i, (float)subDivCount);
	uint	y = fmod((float)i / subDivCount, (float)subDivCount);
	uint	z = i / (subDivCount * subDivCount);

	float	particleArea = QUAD_SIZE / subDivCount;
	float	particleArea2 = particleArea / 2.0f;

	position->x = x * particleArea - 0.3 + particleArea2 + QUAD_SIZE / 2;
	position->y = y * particleArea - 0.3 + particleArea2  + QUAD_SIZE / 2;
	position->z = z * particleArea - 0.3 + particleArea2;
	position->w = 0.0f;
}
