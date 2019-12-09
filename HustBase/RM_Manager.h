#ifndef RM_MANAGER_H_H
#define RM_MANAGER_H_H

#include "PF_Manager.h"
#include "str.h"

typedef int SlotNum;

typedef struct {
	PageNum pageNum;	//��¼����ҳ��ҳ��
	SlotNum slotNum;		//��¼�Ĳ�ۺ�
	bool bValid; 			//true��ʾΪһ����Ч��¼�ı�ʶ��
}RID;

typedef struct {
	bool bValid;		 // False��ʾ��δ�������¼
	RID  rid; 		 // ��¼�ı�ʶ�� 
	char *pData; 		 //��¼���洢������ 
}RM_Record;

typedef struct {
	int nRecords;   // ��ǰ�ļ��а����ļ�¼��
	int recordSize;  // ÿ����¼�Ĵ�С
	int recordsPerPage; // ÿ��ҳ�����װ�صļ�¼����
	int firstRecordOffset; //ÿҳ��һ����¼���������еĿ�ʼλ��
}RM_FileSubHeader;


typedef struct
{
	int bLhsIsAttr, bRhsIsAttr;//���������ԣ�1������ֵ��0��
	AttrType attrType;
	int LattrLength, RattrLength;
	int LattrOffset, RattrOffset;
	CompOp compOp;
	void *Lvalue, *Rvalue;
}Con;

typedef struct {//�ļ����
	bool bOpen;//����Ƿ�򿪣��Ƿ����ڱ�ʹ�ã�
	//��Ҫ�Զ������ڲ��ṹ
}RM_FileHandle;

typedef struct {
	bool  bOpen;		//ɨ���Ƿ�� 
	RM_FileHandle  *pRMFileHandle;		//ɨ��ļ�¼�ļ����
	int  conNum;		//ɨ���漰���������� 
	Con  *conditions;	//ɨ���漰����������ָ��
	PF_PageHandle  PageHandle; //�����е�ҳ����
	PageNum  pn; 	//ɨ�輴�������ҳ���
	SlotNum  sn;		//ɨ�輴������Ĳ�ۺ�
}RM_FileScan;


// ��ȡһ������ɨ�������ļ�¼������÷����ɹ���
// ����ֵrecӦ������¼��������¼��ʶ����
// ���û�з�������ɨ�������ļ�¼���򷵻�RM_EOF��
RC GetNextRec(RM_FileScan *rmFileScan, RM_Record *rec);

// ��һ���ļ�ɨ�衣
// ���������ôӵڶ���������ʼ���������������ʼ��һ���ɲ���rmFileScanָ����ļ�ɨ��ṹ��
// ��ʹ���У��û�Ӧ�ȵ��ô˺�����ʼ���ļ�ɨ��ṹ��
// Ȼ���ٵ���GetNextRec��������������ļ������������ļ�¼��
// �����������conNumΪ0������ζ�ż����ļ��е����м�¼��
// ���������Ϊ�գ���Ҫ��ÿ����¼���������Ƚϣ�ֻ���������������ļ�¼�ű����ء�
RC OpenScan(RM_FileScan *rmFileScan, RM_FileHandle *fileHandle, int conNum, Con *conditions);

// �ر�һ���ļ�ɨ�裬�ͷ���Ӧ����Դ��
RC CloseScan(RM_FileScan *rmFileScan);

// ����ָ���ļ��еļ�¼��
// recָ��ļ�¼�ṹ�е�rid�ֶ�ΪҪ���µļ�¼�ı�ʶ����
// pData�ֶ�ָ���µļ�¼���ݡ�
RC UpdateRec(RM_FileHandle *fileHandle, const RM_Record *rec);

// ��ָ���ļ���ɾ����ʶ��Ϊrid�ļ�¼��
RC DeleteRec(RM_FileHandle *fileHandle, const RID *rid);

// ����һ���µļ�¼��ָ���ļ��У�pDataΪָ���¼�¼���ݵ�ָ�룬
// ���ظü�¼�ı�ʶ��rid��
RC InsertRec(RM_FileHandle *fileHandle, char *pData, RID *rid);

// ��ȡָ���ļ��б�ʶ��Ϊrid�ļ�¼���ݵ�recָ��ļ�¼�ṹ�С�
RC GetRec(RM_FileHandle *fileHandle, RID *rid, RM_Record *rec);

// �رո��������Ӧ�ļ�¼�ļ���
RC RM_CloseFile(RM_FileHandle *fileHandle);

// �����ļ�����ָ���ļ�¼�ļ����������ļ����ָ�롣
RC RM_OpenFile(char *fileName, RM_FileHandle *fileHandle);

// ����һ����ΪfileName�ļ�¼�ļ���
// ���ļ���ÿ����¼�Ĵ�СΪrecordSize
RC RM_CreateFile(char *fileName, int recordSize);



#endif