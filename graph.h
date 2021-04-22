#pragma once
struct edge {
	int edgeID;
	int vertexU;
	int vertexV;
	float weight;
	edge* next;
};
struct path {
	int v;
	float d;
	int pi;
};