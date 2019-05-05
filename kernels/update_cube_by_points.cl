#define MAX_SPHERE_RADIUS 0.3f
#define Z (float3)(0.0f, 0.0f, 1.0f)
#define DIV 1 / MAX_SPHERE_RADIUS

typedef struct
{
	float4	position;
}			Particle;

void kernel update_Cube(global Particle * particles, float deltaTime, float3 gravityCenter, int isGravityActive)
{
	int				i = get_global_id(0);



	//uint 	hexPoint = i % 10;
	//if (hexPoint)
	//	return;
	global Particle *	particle = particles + i;
	//Particle start = *particle;

	float3 distance = particle->position.xyz - gravityCenter;
	if (isGravityActive) {
		float3 tang_1 = normalize(cross(distance, Z));
		particle->position.xyz +=tang_1 * deltaTime;
	} else {
		float3 velocity = particle->position.xyz - gravityCenter;
		float dist = length(distance);
		float parDist_0 =  (MAX_SPHERE_RADIUS - dist) * DIV;
		float parDist_1 =  dist * DIV;
		float squareParDist_1 = parDist_1 * parDist_1;
		velocity = velocity*parDist_0 /parDist_1;
		particle->position.xyz += velocity * deltaTime * cos(particle->position.w);
		particle->position.w+= deltaTime;
	}

	/*float4 deltaPos = particle->position - start.position;
	for (int j = 1; j < 10; ++j) {
		global Particle * particle_index = particles + i + j;
		particle_index->position += deltaPos;
	}*/
};
