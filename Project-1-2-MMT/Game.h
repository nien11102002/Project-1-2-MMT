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

void ReadMap(ifstream& file, vector<vector<char>>& map1, vector<vector<char>>& map2);
void ReadData(ifstream& file, vector<vector<char>>& stat);
void PrintMap(vector<vector<char>>map);
void PrintTableCloth(vector<vector<char>>stat);
void Read(ifstream& file, vector<vector<char>>& stat1, vector<vector<char>>& stat2);
int Random();
void RunGame(vector<vector<char>>& map1, vector<vector<char>>& map2, vector<vector<char>>& stat1, vector<vector<char>>& stat2,string Directive);
int count(vector<vector<char>>enermystat);
void Attack(vector<vector<char>>& map, vector<vector<char>>& allystat, vector<vector<char>>& enermystat, bool& flag, int player,string Directive);
void DFS(vector<vector<char>>enermystat, int i, int j, int n, vector<vector<bool>>& visited);
void PrintPlayBoard(vector<vector<char>> cloth, vector<vector<char>> map);
void StartGame(int& ID, string& Player2);

//server
void SendInvite(bool& choice);
#endif

