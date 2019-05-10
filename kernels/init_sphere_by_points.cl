#define SPHERE_RADIUS	0.3f
#define LIVE_TIME		2.0f

typedef float4 Particle;

void kernel initialize_sphere(global Particle * particles, int particleCount)
{

	int				i = get_global_id(0);
	global Particle * particle = particles + i;

	uint	subDivCount = cbrt((float)particleCount);
	float2	delta = (float2)(M_PI * 2 / subDivCount, M_PI / subDivCount);
	float	radiusDelta = (SPHERE_RADIUS )/ subDivCount;

	uint	x = fmod(i, (float)subDivCount);
	uint	y = fmod((float)i / subDivCount, (float)subDivCount);
	uint	r = i / (subDivCount * subDivCount);

	float radius = radiusDelta * r;

	float2	offset = (r % 2 == 0)
		? delta / 2
		: (float2)(0);

	particle->x = radius * sin(delta.x * y + offset.x) * sin(delta.y * x + offset.y) / 1.f;
	particle->y = radius * cos(delta.x * y + offset.x)/ 1.f;
	particle->z = radius * sin(delta.x * y + offset.x) * cos(delta.y * x + offset.y)/ 1.f;
	particle->w = 10 * length(particle->xyz);//0.0f;
	//particle->w = 0.0f;
}
