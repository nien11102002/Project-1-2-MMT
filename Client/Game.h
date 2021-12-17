#ifndef GAME_H
#define GAME_H

#include<iostream>
#include<vector>
#include<sstream>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;

static int const quantity = 12;
static bool game_over = false;

void ReadMap(ifstream& file, vector<vector<char>>& map1);
void ReadData(ifstream& file, vector<vector<char>>& stat);
int Random();
void RunGame(vector<vector<char>>& map1, vector<vector<char>>& map2, vector<vector<char>>& stat1, vector<vector<char>>& stat2, string Directive);
int count(vector<vector<char>>enermystat);

void DFS(vector<vector<char>>enermystat, int i, int j, int n, vector<vector<bool>>& visited);
void PrintPlayBoard(vector<vector<char>> cloth, vector<vector<char>> map);

#endif


