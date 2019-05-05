#define MAX_SPHERE_RADIUS 0.3f
#define DOUBLE_MAX_SPHERE_RADIUS 2 * MAX_SPHERE_RADIUS
#define Z (float3)(0.0f, 0.0f, 1.0f)
#define DIV 1 / MAX_SPHERE_RADIUS

typedef struct
{
	float4	position;
}			Particle;

void kernel update_sphere(global Particle * particles, float deltaTime, float3 gravityCenter, int isGravityActive)
{
	int				i = get_global_id(0);
	global Particle *	particle = particles + i;

	float3 distance = particle->position.xyz - gravityCenter;
	float dist = length(distance);
	if (dist > DOUBLE_MAX_SPHERE_RADIUS) {
		particle->position.xyz -= normalize(distance) * 0.01f;
		//return;
	}
	if (isGravityActive) {
		float3 tang_1 = normalize(cross(distance, Z));
		particle->position.xyz +=tang_1 * deltaTime;
	} else {
		float3 velocity = particle->position.xyz - gravityCenter;
		float parDist_0 =  (MAX_SPHERE_RADIUS - dist) * DIV;
		float parDist_1 =  dist * DIV;
		float squareParDist_1 = parDist_1 * parDist_1;
		velocity = velocity*parDist_0 /parDist_1;
		particle->position.xyz += velocity * deltaTime * cos(particle->position.w);
		particle->position.w+= deltaTime;
	}
};
