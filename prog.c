#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
int* CreateGraph(int vertexes) {
	int* Mtrx = (int*)malloc(sizeof(int) * vertexes * vertexes);
	if (!Mtrx) return 0;
	for (int i = 0; i != vertexes; i++) {
		*(Mtrx + i * vertexes + i) = 0;
		for (int j = 0; j < i; j++) {
			*(Mtrx + i * vertexes + j) = rand() % 2;
			*(Mtrx + j * vertexes + i) = *(Mtrx + i * vertexes + j);
		}
	}
	return Mtrx;
}

void ShowGraph(int* graph, int vertexes) {
	if (!graph) return;
	for (int i = 0; i != vertexes; i++) {
		for (int j = 0; j != vertexes; j++) {
			printf("%i ", *(graph + i * vertexes + j));
		}
		printf("|%i", i + 1);
		printf("\n");
	}
}

int GetEdges(int* graph, int vertexes) {
	int edges = 0;
	for (int i = 1; i != vertexes; i++) {
		for (int j = 0; j < i; j++) {
			if (*(graph + i * vertexes + j))
				edges++;
		}
	}
	return edges;
}

void FindEdges(int* graph, int vertexes) {
	for (int i = 0; i != vertexes; i++) {
		int count = 0;
		for (int j = 0; j != vertexes; j++) {
			if (*(graph + j * vertexes + i) == 1)
				count++;
		}
		if (!count) printf("Вершина %i - изолированная\n", i + 1);
		else {
			if (count == 1) printf("Вершина %i - концевая\n", i + 1);
			if (count == vertexes - 1) printf("Вершина %i - доминирующая\n", i + 1);
		}
	}
}

int main() {
	setlocale(LC_ALL, "RU");
	srand(time(NULL));
	int vertexNum = 0;
	printf("Введите кол-во вершин для графа: ");
	(void)scanf("%i", &vertexNum);
	if (!vertexNum) return 1;
	int* Smej = CreateGraph(vertexNum);
	ShowGraph(Smej, vertexNum);
	int edgesNum = GetEdges(Smej, vertexNum);
	printf("\nПараметры графа\n   Размер: %i\n   Отличительные вершины:\n", edgesNum);
	FindEdges(Smej, vertexNum);
	int* Inci = (int*)malloc(sizeof(int) * edgesNum * vertexNum);
	//Создание
	for (int i = 0; i < vertexNum; i++) {
		for (int j = 0; j < edgesNum; j++) {
			Inci[i * edgesNum + j] = 0; // Изначально все элементы равны 0
		}
	}
	int edgeIndex = 0;
	for (int i = 0; i < vertexNum; i++) {
		for (int j = 0; j < i; j++) {
			if (*(Smej + i * vertexNum + j)) {
				Inci[i * edgesNum + edgeIndex] = 1;
				Inci[j * edgesNum + edgeIndex] = 1;
				edgeIndex++;
			}
		}
	}
	//вывод
	for (int i = 0; i < vertexNum; i++) {
		for (int j = 0; j < edgesNum; j++) {
			printf("%d ", Inci[i * edgesNum + j]);
		}
		printf("|%i\n", i+1);
	}
	printf("\nПараметры графа\n   Размер: %i\n   Отличительные вершины:\n", edgesNum);
	for (int i = 0; i < vertexNum; i++) {
		int count = 0;
		for (int j = 0; j < edgesNum; j++) {
			if (Inci[i * edgesNum + j] == 1) {
				count++;
			}
		}
		if (!count) printf("Вершина %i - изолированная\n", i + 1);
		else {
			if (count == 1) printf("Вершина %i - концевая\n", i + 1);
			if (count == edgesNum) printf("Вершина %i - доминирующая\n", i + 1);
		}
	}

	free(Inci);
	free(Smej);
	return 0;
}
