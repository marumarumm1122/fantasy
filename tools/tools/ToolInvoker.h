#if !defined(__tool__ToolInvoker__)
#define __tool__ToolInvoker__
#include <stdio.h>
#include "ArgumentParser.h"
class CToolInvoker
{
private:
	CArgumentParser *m_parser;
	static const char *CH_EXPORT_HEADER_FILE_NAME;
    static const char *WORK_FILE_EXT_CONST_NAME;
    static const char *WORK_FILE_EXT_CONST_VALUE;
	enum eCOLUMN_TYPE{
        eCOLUMN_TYPE_NONE,
        eCOLUMN_TYPE_USHORT,
        eCOLUMN_TYPE_BYTE,
        eCOLUMN_TYPE_UINT,
    };
	// データ行数.
	int m_nLine;
    
    // 入力データ行数.
    int m_nInputLine;
    
    // 入力データ.
    void *vInputBuff;

	// データ個数(データ部).
	int m_nCount;
    
    // １レコードのサイズ
    int m_nRecordSize;
    
    // １レコードのカラム数.
    int m_nRecordColumnSize;
    
    // １レコードの各バイト数
    eCOLUMN_TYPE m_nBytesOfColumns[64];
    
	short m_shErrorCode;

    bool WriteInputBuffer();
    bool HelpCheck();
	bool VersionCheck();
    bool InputFileRead();
    bool LoadInputFile();
    bool MakeSchema();
    void SplitCanma(char *ch_in,int startByte);
    bool LoadMemory();
    
	CToolInvoker():
    m_nInputLine(0),
    m_nRecordSize(0),
    m_nRecordColumnSize(0),
    m_shErrorCode(0)
    {}
public:
	CToolInvoker(CArgumentParser *parser):
		m_parser(parser),
		m_nLine(0),
    m_nInputLine(0),
    m_nCount(0),
    m_nRecordSize(0),
    m_nRecordColumnSize(0),
    m_shErrorCode(0)
		{
            for(int nCnt=0;nCnt<64;nCnt++){
                m_nBytesOfColumns[nCnt] = eCOLUMN_TYPE_NONE;
            }
	}
	int Invoke();
	short GetErrorCode()
    {
		return m_shErrorCode;
	}

};
#endif // !defined(__tool__ToolInvoker__)
