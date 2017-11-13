#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct Node Node;

struct Node {
	int Vertex;
	Node *next;
};

bool BuildGraphFromFile(void);
void AddToList(Node **, int, int);
void PrintList(Node **, int);
void PrintListInternal(Node **, int);
void DoBreadthFirstSearch(Node **, Node **, int);
void DoDepthFirstSearch(Node **, int, int);
void DepthFirstSearchInternal(Node **, Node *, int *);

int main(void) {

	if (BuildGraphFromFile() != true) {
		return 1;
	}
}

bool BuildGraphFromFile(void) {
	int counter = 0;
	int v1, v2;
	int level = 0;
	int total;
	int i;
	char c[256];
	FILE *f;
	Node **VertexArray;
	Node **LevelArray;
	f = fopen("graph_input.txt", "r");
	if (f == NULL) {
		printf("Cant open file \n");
		return false;
	}
	while (fgets(c, sizeof(c), f) != NULL) {
		if (counter == 0) {
			sscanf(c, "%d", &total);
			total += 1;
			VertexArray = (Node **)malloc(sizeof(Node *)*total);
			for (i = 0; i < total; i++) {
				VertexArray[i] = NULL;
			}
			LevelArray = (Node **)malloc(sizeof(Node *)*total);
			for (i = 0; i < total; i++) {
				LevelArray[i] = NULL;
			}
		}
		else if (counter == total) {
			sscanf(c, "%d", &level);
			printf("level is %d \n", level);
		}
		else {
			sscanf(c, "%d %d", &v1, &v2);
			printf("Num is %d - %d and counter is %d and total is %d\n", v1, v2, counter, total);
			AddToList(VertexArray, v1, v2);
			AddToList(VertexArray, v2, v1);

		}
		counter++;
	}
	PrintList(VertexArray, total);
	DoBreadthFirstSearch(VertexArray, LevelArray, total);
	PrintList(LevelArray, total);
	DoDepthFirstSearch(VertexArray, total, 1);
	fclose(f);
}

void DoDepthFirstSearch(Node **Root, int total, int startnode) {
	int *Visited;
	int i;
	Visited = (int *)malloc(sizeof(int)*total);
	for (i = 0; i < total; i++) {
		Visited[i] = 0;
	}
	AddToList(Root, 0, startnode);
	DepthFirstSearchInternal(Root, Root[0], Visited);
}
void DepthFirstSearchInternal(Node **Root, Node *CurrentNode, int *Visited) {
	Node *NextNode;

	if (Visited[CurrentNode->Vertex] == 1) {
		return;
	}
	Visited[CurrentNode->Vertex] = 1;
	printf("Node visited is %d \n", CurrentNode->Vertex);
	NextNode = Root[CurrentNode->Vertex];
	DepthFirstSearchInternal(Root, NextNode, Visited);
	NextNode = NextNode->next;
	while (NextNode != NULL) {
		DepthFirstSearchInternal(Root, NextNode, Visited);
		NextNode = NextNode->next;
	}

}
void DoBreadthFirstSearch(Node **Root, Node **LevelTable, int total) {
	int i;
	int level = 0;
	int *VisitedTable;
	Node *CurrentNode;
	Node *CurrentLevelNode;
	VisitedTable = (int *)malloc(sizeof(int)*total);
	for (i = 0; i < total; i++) {
		VisitedTable[i] = 0;
	}
	level = 1;
	AddToList(LevelTable, level, 1);
	VisitedTable[level] = 1;
	while (LevelTable[level] != NULL) {
		CurrentLevelNode = LevelTable[level];
		while (CurrentLevelNode != NULL) {
			CurrentNode = Root[CurrentLevelNode->Vertex];
			while (CurrentNode != NULL) {
				if (VisitedTable[CurrentNode->Vertex] == 0) {
					AddToList(LevelTable, level + 1, CurrentNode->Vertex);
					VisitedTable[CurrentNode->Vertex] = 1;
				}
				CurrentNode = CurrentNode->next;
			}
			CurrentLevelNode = CurrentLevelNode->next;
		}
		level++;
	}
}


void PrintList(Node **Root, int total) {
	int i;
	for (i = 0; i < total; i++) {
		if (Root[i] != NULL) {
			PrintListInternal(&Root[i], i);
		}
	}
}

void PrintListInternal(Node **Root, int index) {
	Node *CurrentNode;
	CurrentNode = *Root;
	printf("at vertex %d , the connected vertex are ", index);
	while (CurrentNode != NULL) {
		printf("%d ", CurrentNode->Vertex);
		CurrentNode = CurrentNode->next;
	}
	printf("\n");
}
void AddToList(Node **Root, int index, int v2) {
	Node *CurrentNode;
	if (Root[index] == NULL) {
		CurrentNode = (Node *)malloc(sizeof(Node));
		CurrentNode->Vertex = v2;
		CurrentNode->next = NULL;
		Root[index] = CurrentNode;
	}
	else {
		CurrentNode = Root[index];
		while (CurrentNode->next != NULL) {
			CurrentNode = CurrentNode->next;
		}
		CurrentNode->next = (Node *)malloc(sizeof(Node));
		CurrentNode->next->Vertex = v2;
		CurrentNode->next->next = NULL;
	}
}