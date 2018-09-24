// Program to check conflict serializibility from a given schedule.
// Author: Chandramani Adil
// Date: 24-09-2018
#include <iostream>
#include <algorithm>
#include <string.h>
#include <vector>
#include <stack>
#include <cmath>
#include <bitset>
#include <cstdio>
using namespace std;
#define MAX_SIZE 100

typedef struct op
{
  char operation;   //R or W
  int trans_no;     //numeric for Transcation number
  char resource[10];// array to allow string as resource name
}op;

//global variables
vector<op>data;   // vector to hold all transaction details
vector<int>adjlist[MAX_SIZE];// Adjacency list to hold dependencies
vector<op>transaction[MAX_SIZE]; // To hold transaction details
int V = 0; //holds count for total number of distinct transactions.

void print(vector<int> data) //custom printf fucntion
{
  int i;
  for(i=0;i<data.size();i++)
    cout << data[i] << " ";
  cout << "\n";
}

bool isCyclicUtil(int v,bool visited[],bool recStack[])
{
  int i;
  if(visited[v] == false)
  {
      visited[v] = true;
      recStack[v] = true;
      vector<int>::iterator i;
      for(i = adjlist[v].begin(); i != adjlist[v].end(); ++i)
      {
          if ( !visited[*i] && isCyclicUtil(*i, visited, recStack) ) //divide and conquer approach to visit all nod
              return true;
          else if (recStack[*i])
              return true;
      }
  }
  recStack[v] = false;
  return false;
}

bool isCyclic()
{
  bool *visited = new bool[V];
  bool *recStack = new bool[V];
  for(int i = 1; i <= V ; i++)
  {
      visited[i] = false;
      recStack[i] = false;
  }
  for(int i = 1; i <= V ; i++)
      if (isCyclicUtil(i, visited, recStack))
          return true;
  return false;
}

void topologicalSortUtil(int v,bool visited[],stack<int> &Stack)
{
  visited[v] = true;
  vector<int>::iterator i;
  for (i = adjlist[v].begin(); i != adjlist[v].end(); ++i)
      if (!visited[*i])
          topologicalSortUtil(*i, visited, Stack); //same approach as above
  Stack.push(v);
}

void  topologicalsort()
{
  stack<int> Stack;
  bool *visited = new bool[V];
  for (int i = 1; i <= V; i++)
      visited[i] = false;
  for (int i = 1; i <= V; i++)
    if (visited[i] == false)
      topologicalSortUtil(i, visited, Stack);
  cout<<"Order:\n";
  while (Stack.empty() == false)
  {
      cout << Stack.top() << " ";
      Stack.pop();
  }
  cout << "\n";
}

int main(int argc,char* argv[])
{
    char operation;
    int trans_no;
    char resource[10],input[10];
    int i,j;
    FILE *fp;
    op temp;
    printf("Enter input file name:");
    scanf("%s",&input);
    fp = fopen(input,"r");
    while(!feof(fp))
    {
      fscanf(fp,"%c %d %s",&operation,&trans_no,&resource);
      if(feof(fp))
        break;
      if(operation == 'R')
      {
        temp.operation = operation;
        strcpy(temp.resource,resource);
        temp.trans_no = trans_no;
        if(trans_no > V)
          V = trans_no;
        transaction[resource[10]].push_back(temp);
        data.push_back(temp);
      }
      else if(operation == 'W')
      {
        temp.operation = operation;
        strcpy(temp.resource,resource);
        temp.trans_no = trans_no;
        if(trans_no > V)
          V = trans_no;
        transaction[resource[10]].push_back(temp);
        data.push_back(temp);
      }
    }
    fclose(fp);
    cout<<"\n\nOperation|TransactionNo|Resource\n";
    for(i=0;i<data.size();i++)
    {
      cout << data[i].operation << "\t" << data[i].trans_no << "\t" << data[i].resource << "\n";
      if(data[i].operation == 'W')
      {
        for(j = i+1;j < data.size();j++)
        {
          if(data[i].trans_no != data[j].trans_no && !strcmp(data[i].resource,data[j].resource)) //W-W & W-R conflict checking
          {
            adjlist[data[i].trans_no].push_back(data[j].trans_no);
          }
        }
      }
      else if(data[i].operation == 'R')
      {
        for(j = i+1;j<data.size();j++)
        {
          if(data[i].trans_no != data[j].trans_no && !strcmp(data[i].resource,data[j].resource) && data[j].operation == 'W') //R-W conflict checking
          {
            adjlist[data[i].trans_no].push_back(data[j].trans_no);
          }
        }
      }
    }
    cout << "\nAdjacency List \n";
    for(i=1;i <= V;i++)
    {
        cout <<"T:"<< i << "-->";
        print(adjlist[i]);
    }
    cout<<"Is it conflict Serializable? ";
    if(isCyclic())
      cout << "Not Serializable \n";
    else
    {
      cout << "Serializable\n";
      topologicalsort();
    }
}


