#ifndef ENGINE_H
#define ENGINE_H

#pragma once
//#pragma comment(lib, "winmm.lib")

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include <thread>
#include <atomic>
#include <condition_variable>
#include "graphics.h"

class IOHandler
{
public:
	IOHandler();

	int ConstructConsole(int width, int height);
    virtual void Draw(int x, int y,int col);
	void Fill(int x1, int y1, int x2, int y2, int col);
	void Clip(int& x, int& y);
	void DrawLine(int x1, int y1, int x2, int y2, int col);
	void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int col);
	void FillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int col=colors(4));
	void DrawWireFrameModel(const std::vector<std::pair<float, float>>& vecModelCoordinates, float x, float y, float r = 0.0f, float s = 1.0f, int col = 255);

	~IOHandler();

public:
	void Start();
	int ScreenWidth();
	int ScreenHeight();
private:
	void GameThread();

public:
	// User MUST OVERRIDE THESE!!
	virtual bool OnUserCreate() = 0;
	virtual bool OnUserUpdate(float fElapsedTime) = 0;

	// Optional for clean up
	virtual bool OnUserDestroy() { return true; }


protected:
	int m_nScreenWidth;
	int m_nScreenHeight;

	static std::atomic<bool> m_bAtomActive;
	static std::condition_variable m_cvGameFinished;
	static std::mutex m_muxGame;
};


#endif // ENGINE_H
