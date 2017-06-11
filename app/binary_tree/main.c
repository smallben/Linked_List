#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define DEPTH 3

typedef struct tree {
	int iData;
	struct tree *pLeft;
	struct tree *pRight;
} TLTree;

int POW(int iDepth)
{
	int i = 0, iAnswer = 1;
	for (i = 0; i < iDepth; i++)
	{
		iAnswer *= 2; 
	}
	return iAnswer;
}

int CreateRandomTree(TLTree *pTree, int iDepth)
{
	TLTree *pTemp = NULL;
	TLTree *pCur = pTree;
	TLTree *pPreCur = NULL;
	int iLeft = 0, iRight = 0;
	if (pTree == NULL)
	{
		printf ("Error - Tree address is not existed\n");
		return 1;
	}

	srand(time(0));

	int i = 0;
	int iNode = POW(iDepth);

	printf ("Create %d Node\n", iNode - 1);

	while (i < iNode - 1)
	{
		if (i == 0)
		{
			pTree->iData = 50;
			pTree->pLeft = NULL;
			pTree->pRight = NULL;
			i++;
			continue;
		}
		pTemp = (TLTree *) malloc(sizeof (TLTree));

		pTemp->iData = rand() % 100 + 1;
		pTemp->pLeft = NULL;
		pTemp->pRight = NULL;

		printf ("%d ", pTemp->iData);
		while (pCur != NULL)
		{
			if (pCur->iData > pTemp->iData)
			{
				iLeft = 1;
				iRight = 0;
				pPreCur = pCur;
				pCur = pCur->pLeft;
			}
			else if (pCur->iData < pTemp->iData)
			{
				iLeft = 0;
				iRight = 1;
				pPreCur = pCur;
				pCur = pCur->pRight;
			}
			else
			{
				pTemp->iData = rand() % 100 + 1;
			}
		}

		if (iLeft == 1)
		{
			iLeft = 0;
			printf ("Left : %d\n", pTemp->iData);
			pPreCur->pLeft = pTemp;
		}
		else if (iRight == 1)
		{
			iRight = 0;
			printf ("Right : %d\n", pTemp->iData);
			pPreCur->pRight = pTemp;
		}

		pTemp = NULL;
		pCur = pTree;
		i ++;
	}

	printf ("\n");
	return 0;
}

//DFS, pre-order
int DisplayTree (TLTree *pTree)
{
	if (pTree == NULL)
	{
		return 0;
	}

	printf ("%d ", pTree->iData);
	DisplayTree(pTree->pLeft);
	DisplayTree(pTree->pRight);
}

//In-order
int DisplayTree_InOrder (TLTree *pTree)
{
	if (pTree == NULL)
	{
		return 0;
	}

	DisplayTree_InOrder(pTree->pLeft);
	printf ("%d ", pTree->iData);
	DisplayTree_InOrder(pTree->pRight);
}

//Post-Order
int DisplayTree_PostOrder (TLTree *pTree)
{
	if (pTree == NULL)
	{
		return 0;
	}

	DisplayTree_PostOrder(pTree->pLeft);
	DisplayTree_PostOrder(pTree->pRight);
	printf ("%d ", pTree->iData);
}

int main()
{
	TLTree *pTree = NULL;
	pTree = (TLTree*) malloc (sizeof (TLTree));
	if (pTree == NULL)
	{
		printf ("error - Create failed\n");
		return 1;
	}

	CreateRandomTree(pTree, DEPTH);
	printf ("PreOrder: \n");
	DisplayTree(pTree);
	printf ("\n");
	printf ("InOrder: \n");
	DisplayTree_InOrder (pTree);
	printf ("\n");
	printf ("PostOrder: \n");
	DisplayTree_PostOrder (pTree);
	printf ("\n");

	return 0;
}
