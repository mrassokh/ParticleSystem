#define MAX_SPHERE_RADIUS 0.5f
#define Z (float3)(0.0f, 0.0f, 1.0f)
#define DIV 1 / MAX_SPHERE_RADIUS

typedef struct
{
	float4	position;
}			Particle;

void kernel update_sphere(global Particle * particles, float deltaTime, float3 gravityCenter, int isGravityActive)
{	int				i = get_global_id(0);

	global Particle *	particle = particles + i;


	float3 distance = particle->position.xyz - gravityCenter;
	if (isGravityActive) {
		float3 norm_distance = normalize(distance);
		float3 tang_1 = normalize(cross(norm_distance, Z));
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
};
