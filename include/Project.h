#ifndef PROJECT_H
#define PROJECT_H

//#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <strstream>
#include "graphics.h"

#include "Engine.h"
#include "../MathHandler.h"
#include "../Point.h"


using namespace std;
struct triangle
{
	OVec3 p[3];
    OVec3 col;

};

struct mesh
{
	std::vector<triangle> tris;
	bool LoadFromObjectFile(string sFilename)
	{
 		ifstream f(sFilename);
		if (!f.is_open())
        {
			return false;

        }
		vector<OVec3> verts;

		while (!f.eof())
		{
			char line[128];
			f.getline(line, 128);
			//cout << line << "\n";
			//f2<<line<<"\n";
			strstream s;
			s << line;

			char junk;

			if (line[0] == 'v')
			{
				OVec3 v;
				s >> junk >> v.m_x >> v.m_y >> v.m_z;
				verts.push_back(v);
			}

			if (line[0] == 'f')
			{
				int f[3];
				s >> junk >> f[0] >> f[1] >> f[2];
				tris.push_back({ verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1] });
			}
		}
		f.close();
		//f2.close();
		return true;
	}

};

class Project : public Engine
{
public:
	Project();


public:

	struct DirLight {
        OVec3 direction = OVec3(0.0f, 0.0f, 1.0f);
		OVec3 ambient = OVec3(0.05f, 0.05f, 0.05f);
		OVec3 diffuse = OVec3(0.8f, 0.8f,0.8f);;
		OVec3 specular = OVec3(.5f, .5f, .5f);;
	}m_DirLight;

	struct PointLight {
		OVec3 position=OVec3();

		float constant=0;
		float linear=0;
		float quadratic=0;

		OVec3 ambient=	OVec3();
		OVec3 diffuse=	OVec3();
		OVec3 specular=	OVec3();
	};


	struct SpotLight {
		OVec3 position = OVec3(3.0f, 0, 0);
		OVec3 direction = OVec3(0, 0, -2.0f);
		float cutOff = cos(radians(2.5f));
		float outerCutOff = cos(radians(5.0f));

		float constant = 1.0f;
		float linear = 0.5f;
		float quadratic = 0.032f;;

		OVec3 ambient = OVec3(1.0f, 1.0f, 1.0f);
		OVec3 diffuse = OVec3(1.0f, 1.0f, 1.0f);
		OVec3 specular = OVec3(1.0f, 1.0f, 1.0f);
	}
    spotLight;

    PointLight m_PointLights[4];
public:
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime)override;

public:
    void onKeyDown(int key) override;

public:

	int Triangle_ClipAgainstPlane(OVec3 plane_p, OVec3 plane_n, triangle& in_tri, triangle& out_tri1, triangle& out_tri2);
	OVec3 setIllumination(OVec3 FragPos, OVec3 Normal);
	void setTRS(OVec3 tranlate, OVec3 rotate, OVec3 scale);
	void drawModel(mesh& model);
private:
	mesh meshRocket;
	mesh meshAxes;
	mesh meshSphere;


	OMat4 matProj;
	OMat4 matWorld;
	OMat4 matView;


	OVec3 viewPos;
	OVec3 vCamera;
	OVec3 vLookDir;
	OVec3 vForward;
	OVec3 vUp=OVec3(0, 1, 0);
	OVec3 vTarget=OVec3(0, 0, 1);

	float fYaw;


	float light_factor;
	OVec3 pointLightPositions[4];

	bool firstMouse = true;
    float m_deltaTime=0.0f;
	float m_time=100;
	float fTheta;

    OVec3 pos=OVec3(0,-5,25.0f);
};


#endif // PROJECT_H
