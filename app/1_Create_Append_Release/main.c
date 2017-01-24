#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define S_OK 0
#define S_FAIL 1
#define SAMPLE_MAX_NUM 10

// implement the single linked list in this

typedef struct Node {
	int iData;
	struct Node *pNext;
} TNode;

int CreateListnData(TNode **pFirstNode)
{
	//printf ("[%s] pFirstNode address: %x, %x\n", __func__, pFirstNode, *pFirstNode);
	if (*pFirstNode != NULL)
	{
		printf("[Error] Create already with pointer address %x\n", *pFirstNode);
		return S_FAIL;
	}

	*pFirstNode = malloc(sizeof(TNode));
	if (*pFirstNode == NULL)
	{
		printf ("[%d] %s\n", errno, strerror(errno));
		return S_FAIL;
	}
	//printf ("[Info] Create pointer address is %x, %x\n", *pFirstNode);

	(*pFirstNode)->pNext = NULL; 
	(*pFirstNode)->iData = (rand() % 100) + 1;

	//printf ("[Info] The ith data is %d\n", (*pFirstNode)->iData);

	return S_OK;
}

int DisplayList(TNode *pFirstNode)
{
	TNode *list = pFirstNode;
	int iCount = 0;

	printf ("=================Data showing=================\n");
	if (list == NULL)
	{
		printf ("No Data\n");
		return S_FAIL;
	}

	while (list)
	{
		printf ("%dth = %d\n", iCount, list->iData);
		list = list->pNext;
		iCount++;
	}

	printf ("==============================================\n");
	return S_OK;
}

int ReleaseList(TNode **pFirstNode)
{
	// Delete the list data and release the first addr.
	if (!pFirstNode && !(*pFirstNode))
	{
		printf ("[Info] There are no address..");
		return S_OK;
	}

	TNode *list = *pFirstNode;
	TNode *prev = NULL;
	if (list == NULL)
	{
		printf ("No Data\n");
		return S_FAIL;
	}

	while (list)
	{
		//printf ("Release %d\n", list->iData);
		prev = list;
		list = list->pNext;
		free (prev);
	}
	pFirstNode = NULL;

	return S_OK;
}

int AppendDataList(TNode *pFirstNode)
{
	TNode *NewData = NULL;
	TNode *lastNode = pFirstNode;

	int iCount = 0;

	while (iCount < SAMPLE_MAX_NUM)
	{
		while(lastNode->pNext != NULL) lastNode = lastNode->pNext;
		NewData = malloc(sizeof(TNode));
		if (NewData == NULL)
		{
			printf ("[Error] Create temp list failed\n");
			return S_FAIL;
		}
		NewData->iData = (rand() % 100) + 1;
		NewData->pNext = NULL;

		//printf ("%dth %d\n", iCount + 1, NewData->iData);

		lastNode->pNext = NewData;
		NewData = NULL;

		iCount ++;
	}

	return S_OK;
}

int main()
{
	int iRet = S_OK;
	// First we need to pointer to ground
	TNode *pFirstNode = NULL;
	// for data creation.
	srand(0); 

	printf ("This Sample is: \n1. Create and Insert one data\n2. Append Data with No.11 random value\n3. Display List\n4. Release List\n");

	//printf ("pFirstNode address: %x\n", &pFirstNode);
	iRet = CreateListnData(&pFirstNode);
	if (iRet == S_FAIL)
	{
		printf ("[Error] The Create list failed\n");
		return iRet;
	}

	iRet = AppendDataList(pFirstNode);
	if (iRet == S_FAIL)
	{
		printf ("[Error] Append the list failed\n");
		return iRet;
	}
	
	iRet = DisplayList(pFirstNode);
	if (iRet == S_FAIL)
	{
		printf ("[Error] Display list failed\n");
		return iRet;
	}

	iRet = ReleaseList(&pFirstNode);
	if (iRet == S_FAIL)
	{
		printf ("[Error] Release list failed\n");
		return iRet;
	}

	return S_OK;
}
