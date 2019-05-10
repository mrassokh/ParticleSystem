#define MAX_SPHERE_RADIUS 0.3f
#define DOUBLE_MAX_SPHERE_RADIUS 2 * MAX_SPHERE_RADIUS
#define Z (float3)(0.0f, 0.0f, 1.0f)
#define DIV 1 / MAX_SPHERE_RADIUS
#define INF	(float4)(10000.0f, 10000.0f, 10000.0f, 1.0f)

typedef float4 Particle;

void kernel update_sphere(global Particle * particles, float deltaTime, float3 gravityCenter, int isGravityActive)
{
	int				i = get_global_id(0);
	global Particle *	particle = particles + i;

	float3 distance = particle->xyz - gravityCenter;
	//float distance_length = length(distance);
	if (isGravityActive) {
		float3 tang_1 = normalize(cross(distance, Z));
		particle->xyz +=tang_1 * deltaTime;
	} else {
		float dist = length(distance);
		float parDist_0 =  (MAX_SPHERE_RADIUS - dist) * DIV;
		float parDist_1 =  dist * DIV;
		float squareParDist_1 = parDist_1 * parDist_1;
		float3 velocity = distance * parDist_0 /parDist_1;
		velocity.y = velocity.y >= 0.0 ? velocity.y + parDist_0 *  parDist_1  : -velocity.y /10 + 1.5f * parDist_1;

		particle->xyz += velocity * deltaTime * cos(particle->w);
	}
	particle->w+= deltaTime;
};


/*if (distance_length > MAX_SPHERE_RADIUS) {
	*particle = INF;
	return;
}

float parDist_0 =  (MAX_SPHERE_RADIUS - distance_length) * DIV;
float parDist_1 =  distance_length * DIV;
float squareParDist_1 = parDist_1 * parDist_1;

float4 velocity;
velocity = *particle * 0.1f /parDist_1;
velocity.x *= parDist_0;
velocity.z *= parDist_0;
velocity.y = velocity.y >= 0.0 ? velocity.y + parDist_0 *  parDist_1  : -velocity.y /10 + 1.5f * parDist_1;
particle->xyz +=  velocity.xyz * deltaTime ;*/