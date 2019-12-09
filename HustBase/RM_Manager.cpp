#include "stdafx.h"
#include "RM_Manager.h"
#include "str.h"


RC OpenScan(RM_FileScan *rmFileScan,RM_FileHandle *fileHandle,int conNum,Con *conditions)//��ʼ��ɨ��
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

// ����һ����ΪfileName�ļ�¼�ļ������ļ���ÿ����¼�Ĵ�СΪrecordSize
RC RM_CreateFile(char *fileName, int recordSize)
{
	RC rc;

	// ���ļ�����ȡҳ����
	PF_FileHandle pfFileHandle;

	if ((rc = CreateFile(fileName)))
	{
		return rc;
	}
	if ((rc = openFile(fileName, &pfFileHandle)))
	{
		return rc;
	}

	// ����ҳ��������ҳ����Ϣ����ҳ(��1ҳ)
	PF_PageHandle pfPageHandle;

	if ((rc = AllocatePage(&pfFileHandle, &pfPageHandle)))
	{
		return rc;
	}
	assert(pfPageHandle.pFrame->page.pageNum == 1);

	// ��pData[0]��ʼ�����һ�����ݽṹRM_FileSubHeader��¼������Ϣ�������г�ʼ��
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
