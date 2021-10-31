#ifndef GAME_H
#define GAME_H

#include<iostream>
#include<vector>
#include<sstream>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<string>
using namespace std;

void ReadMap(ifstream& file, vector<vector<char>>& map1, vector<vector<char>>& map2);
void ReadData1(ifstream& file, vector<vector<char>>& stat1);
void ReadData2(ifstream& file, vector<vector<char>>& stat2);
void PrintMap(vector<vector<char>>map);
void PrintTableCloth(vector<vector<char>>stat);
void Read(ifstream& file, vector<vector<char>>& stat1, vector<vector<char>>& stat2);

#endif