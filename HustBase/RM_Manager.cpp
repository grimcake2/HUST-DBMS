#include "stdafx.h"
#include "RM_Manager.h"
#include "str.h"


RC OpenScan(RM_FileScan *rmFileScan,RM_FileHandle *fileHandle,int conNum,Con *conditions)//初始化扫描
{
	return SUCCESS;
}

RC GetNextRec(RM_FileScan *rmFileScan,RM_Record *rec)
{
	return SUCCESS;
}

RC GetRec (RM_FileHandle *fileHandle,RID *rid, RM_Record *rec) 
{
	return SUCCESS;
}

RC InsertRec (RM_FileHandle *fileHandle,char *pData, RID *rid)
{
	return SUCCESS;
}

RC DeleteRec (RM_FileHandle *fileHandle,const RID *rid)
{
	return SUCCESS;
}

RC UpdateRec (RM_FileHandle *fileHandle,const RM_Record *rec)
{
	return SUCCESS;
}

// 创建一个名为fileName的记录文件，该文件中每条记录的大小为recordSize
RC RM_CreateFile(char *fileName, int recordSize)
{
	RC rc;

	// 打开文件，获取页面句柄
	PF_FileHandle pfFileHandle;

	if ((rc = CreateFile(fileName)))
	{
		return rc;
	}
	if ((rc = openFile(fileName, &pfFileHandle)))
	{
		return rc;
	}

	// 根据页面句柄生成页面信息控制页(第1页)
	PF_PageHandle pfPageHandle;

	if ((rc = AllocatePage(&pfFileHandle, &pfPageHandle)))
	{
		return rc;
	}
	assert(pfPageHandle.pFrame->page.pageNum == 1);

	// 从pData[0]开始，存放一个数据结构RM_FileSubHeader记录控制信息，并进行初始化
	RM_FileSubHeader *rmFileSubHeader;

	rmFileSubHeader = (RM_FileSubHeader *)pfPageHandle.pFrame->page.pData;
	rmFileSubHeader->nRecords = 0;
	rmFileSubHeader->recordSize = recordSize;
	rmFileSubHeader->recordsPerPage = (PF_PAGE_SIZE - sizeof(RM_FileSubHeader)) / recordSize;
	if ((rc = MarkDirty(&pfPageHandle)) || (rc = UnpinPage(&pfPageHandle)) || (rc = CloseFile(&pfFileHandle)))
	{
		return rc;
	}

	return SUCCESS;
}
RC RM_OpenFile(char *fileName, RM_FileHandle *fileHandle)
{
	return SUCCESS;
}

RC RM_CloseFile(RM_FileHandle *fileHandle)
{
	return SUCCESS;
}
