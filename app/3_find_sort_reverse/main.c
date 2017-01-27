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

int AppendDataList(TNode *pFirstNode, int iAppendNum)
{
	TNode *NewData = NULL;
	TNode *lastNode = pFirstNode;

	int iCount = 0;

	while (iCount < iAppendNum)
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

int InsertDataList(TNode **pFirstNode, int iData, int index)
{
	if (!pFirstNode)
	{
		printf ("[Error] The first node is empty\n");
		return S_FAIL;
	}
	TNode *pInsertData = malloc(sizeof (TNode));
	TNode *pList = *pFirstNode;
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

	if (index == 0)
	{
		*pFirstNode = pInsertData;

	}
	else
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
	if (!pFirstNode)
	{
		printf ("[Error] The first node is empty\n");
		return S_FAIL;
	}

	TNode *pList = pFirstNode;
	TNode *pPrev = NULL;

	while (pList)
	{
		if (pList->iData == iData)
		{
			pPrev->pNext = pList->pNext;
			pList->pNext = NULL;
			free(pList);

			// This is re-assign from the current vlaue
			pList = pPrev;
		}
		pPrev = pList;
		pList = pList->pNext;
	}

	return S_OK;
}

void help()
{
	printf ("[Info] Please follow the command\n");
	printf ("choose the case you want\n");
	printf ("1. Create the data\n");
	printf ("2. [Value] Append the Value to list with assigned number\n");
	printf ("3. [Value] Find the value from list and show the index\n");
	printf ("4. [Data] [Index] Insert the data to the specific index\n");
	printf ("5. Delete the datat by index/data with following param.\n");
	/*printf ("   --index [Index] delete the data by index\n");
	printf ("   --data [Data] delete the data by data match\n");*/
	printf ("6. Reverse the List\n");
	printf ("7. Sort the list by different alg.\n");
	/*printf ("   --bubble Bubble sort\n");
	printf ("   --quick Quick sort\n");
	printf ("   --insert Insertion sort\n");
	printf ("   --select Selection sort\n");*/
	printf ("8. Display the List\n");
}

int main(int argc, char** argv)
{
	int iRet = S_OK;
	// First we need to pointer to ground
	TNode *pFirstNode = NULL;
	int iData = 0;
	int iIndex = 0;
	int iTerminated = 0;
	int iChoose = 0;
	int iAppendNum = 0;
	int iDelete = 0;
	int iSearchValue = 0 ;
	// for data creation.
	srand(0); 

	while (!iTerminated)
	{
		printf ("Choose What you want to do\n");
		help();
		scanf("%d", &iChoose);
		switch (iChoose)
		{
			case 1:
				iRet = CreateListnData(&pFirstNode);
				if (iRet == S_FAIL)
				{
					printf ("[Error] The Create list failed\n");
					return iRet;
				}
				break;
			case 2:
				printf ("Number of Append data\n?");
				scanf("%d", &iAppendNum);
				iRet = AppendDataList(pFirstNode, iAppendNum);
				if (iRet == S_FAIL)
				{
					printf ("[Error] Append the list failed\n");
					return iRet;
				}
				break;
			case 3:
				printf ("Find the value you want\n?");
				scanf("%d", &iSearchValue);
				break;
			case 4:
				printf ("Insert Data with specific index\n");
				printf ("1. Data = ?");
				scanf("%d", &iData);

				printf ("\n2. index = ?");
				scanf("%d", &iIndex);

				iRet = InsertDataList(&pFirstNode, iData, iIndex);
				if (iRet == S_FAIL)
				{
					printf ("[Error] Insert data fail\n");
					return iRet;
				}
				break;
			case 5:
				printf ("Delete 1. index or 2. data\n");
				scanf("%d", &iDelete);
				if (iDelete == 1)
				{
					printf ("Please Delete One data by specific index\n1. Index = ?");
					scanf("%d", &iIndex);

					iRet = DeleteDatByIndexList(pFirstNode, iIndex);
					if (iRet == S_FAIL)
					{
						printf ("[Error] Delete data from list by specific index failed\n");
						return iRet;
					}
				}
				else if(iDelete == 2)
				{
					printf ("Please Delete One data by specific data (repeated)\n1. Data = ?");
					scanf("%d", &iData);

					iRet = DeleteDatByDataList(pFirstNode, iData);
					if (iRet == S_FAIL)
					{
						printf ("[Error] Delete the data from list failed\n");
						return iRet;
					}
				}
				else
				{
					help();
				}
				break;
			case 6:
				printf ("Reverse the list\n");
				break;
			case 7:
				printf ("Sorting the Linked list.\n");
				break;
			case 8:
				iRet = DisplayList(pFirstNode);
				if (iRet == S_FAIL)
				{
					printf ("[Error] Display list failed\n");
					return iRet;
				}
				break;
			default:
				help();
				iTerminated = 1;
				break;
		}
	}

	iRet = ReleaseList(&pFirstNode);
	if (iRet == S_FAIL)
	{
		printf ("[Error] Release list failed\n");
		return iRet;
	}

	return S_OK;
}
