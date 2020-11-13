#include "BoxCollider.h"
#include "GameObject.h"

using namespace std;
using namespace moddingApi;

bool BoxCollider::isColliding(BoxCollider a, BoxCollider b)
{
	GameObject* gA = (GameObject*)(a.gameObjectPtr);
	GameObject* gB = (GameObject*)(b.gameObjectPtr);

	Vector3 aMin = Vector3(
		gA->transform.position.x - (a.scale.x / 2) + a.center.x,
		gA->transform.position.y - (a.scale.y / 2) + a.center.y,
		gA->transform.position.z - (a.scale.z / 2) + a.center.z
	);

	Vector3 aMax = Vector3(
		gA->transform.position.x + (a.scale.x / 2) + a.center.x,
		gA->transform.position.y + (a.scale.y / 2) + a.center.y,
		gA->transform.position.z + (a.scale.z / 2) + a.center.z
	);

	Vector3 bMin = Vector3(
		gB->transform.position.x - (b.scale.x / 2) + b.center.x,
		gB->transform.position.y - (b.scale.y / 2) + b.center.y,
		gB->transform.position.z - (b.scale.z / 2) + b.center.z
	);

	Vector3 bMax = Vector3(
		gB->transform.position.x + (b.scale.x / 2) + b.center.x,
		gB->transform.position.y + (b.scale.y / 2) + b.center.y,
		gB->transform.position.z + (b.scale.z / 2) + b.center.z
	);

	return (aMin.x <= bMax.x && aMax.x >= bMin.x) && (aMin.y <= bMax.y && aMax.y >= bMin.y) && (aMin.z <= bMax.z && aMax.z >= bMin.z);
}