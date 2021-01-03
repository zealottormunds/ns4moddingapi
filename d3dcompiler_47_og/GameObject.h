#ifndef GAMEOBJECT_H 
#define GAMEOBJECT_H
#pragma once

#include <string>
#include <vector>
#include "Rigidbody.h"
#include "BoxCollider.h"

namespace moddingApi
{
	class GameObject
	{
	public:
		void Initialize();

		GameObject(std::string _name) : transform(new Transform()), message("null"), name(_name)
		{
			Initialize();
		}

		GameObject(std::string _name, Vector3 pos, std::string _msg) : transform(new Transform(pos)), message(_msg), name(_name)
		{
			Initialize();
		}

		bool enabled = true;
		std::string name;
		std::string tag;
		int internalid;
		bool destroyOnLoad;
		Transform * transform;
		Rigidbody * rigidbody;
		Vector3 * lastCastPosition = new Vector3(0, 0, 0);

		float degrees = 0;
		Vector3 * lastCastDirection = new Vector3(0, 0, 0);

		float interactionRange = 50;
		bool interact = true;
		std::string modelPath = "";
		std::string modelName = "";
		std::string modelAnmPath = "";
		std::string modelAnmName = "";
		void UpdateModel(std::string p, std::string n);
		void UpdateAnim(std::string p, std::string n);
		void SetPosition(Vector3 pos);

		std::string message;

		bool isCollision = false;
		bool updateForce = false;
		bool useCollision = false;

		void Start();
		void Update();
		void UpdateDisabled();
		void Destroy();
		void DontDestroyOnLoad(bool t = true);

		std::vector<std::string> componentNames;
		std::vector<uintptr_t> componentList;
		void* AddComponent(std::string component);
		uintptr_t GetComponent(std::string component);
		int GetComponentIndex(std::string component);
		void RemoveComponent(std::string component);
		void RemoveComponent(int index);
		void UpdateComponent();

		int destroyInTimer = -1;

		static void LoopGameObjects();
		static void DeleteAll(bool statics = false);
		static GameObject Null;
		static uintptr_t Find(std::string _name);
		static std::vector<uintptr_t> gList;
		static int gListGetIndex(std::string _name);
		static int gCount;
	};
}

#endif