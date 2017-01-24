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

	(*pFirstNode)->pNext = (rand() % 100) + 1; 
	(*pFirstNode)->iData = -1;

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

int InsertDataList(TNode *pFirstNode, int iData, int index)
{
	if (!pFirstNode)
	{
		printf ("[Error] The first node is empty\n");
		return S_FAIL;
	}
	TNode *pInsertData = malloc(sizeof (TNode));
	TNode *pList = pFirstNode;
	TNode *pPrev = NULL;

	int iCount = 0;

	pInsertData->iData = iData;

	printf ("[Info] Replace the %dth value to %d\n", index, iData);
	while (pList)
	{
		if (iCount == index)
		{
			break;
		}
		pPrev = pList;
		pList = pList->pNext;
		iCount ++;
	}

	pInsertData->pNext = pList;
	pPrev->pNext = pInsertData;

	return S_OK;
}

int DeleteDatByIndexList(TNode *pFirstNode, int iIndex)
{
	if (!pFirstNode)
	{
		printf ("[Error] The first node is empty\n");
		return S_FAIL;
	}

	TNode *pList = pFirstNode;
	TNode *pPrev = NULL;
	int iCount = 0;

	while (pList)
	{
		if (iCount == iIndex)
		{
			break;
		}
		pPrev = pList;
		pList = pList->pNext;
		iCount ++;
	}
	pPrev->pNext = pList->pNext;

	pList->pNext = NULL;
	free(pList);

	return S_OK;
}

int DeleteDatByDataList(TNode *pFirstNode, int iData)
{

	return S_OK;
}

int main()
{
	int iRet = S_OK;
	// First we need to pointer to ground
	TNode *pFirstNode = NULL;
	int iData = 0;
	int iIndex = 0;
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

	printf ("Please Insert One data\n1. Data = ?");
	scanf("%d", &iData);

	printf ("\n2. index = ?");
	scanf("%d", &iIndex);

	iRet = InsertDataList(pFirstNode, iData, iIndex);
	if (iRet == S_FAIL)
	{
		printf ("[Error] Insert data fail\n");
		return iRet;
	}

	iRet = DisplayList(pFirstNode);
	if (iRet == S_FAIL)
	{
		printf ("[Error] Display list failed\n");
		return iRet;
	}

	printf ("Please Delete One data by specific index\n1. Index = ?");
	scanf("%d", &iIndex);

	iRet = DeleteDatByIndexList(pFirstNode, iIndex);
	if (iRet == S_FAIL)
	{
		printf ("[Error] Delete data from list by specific index failed\n");
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
