#if !defined(__tool__ArgumentParser__)
#define __tool__ArgumentParser__
#include <stdio.h>
class CArgumentParser
{
private:
	const int n_argc;
	char **ch_argv;
	short m_shErrorCode;
public:
	enum eFORMAT{
		eFORMAT_START = 0,

	    eFORMAT_TEXT = eFORMAT_START,
	    eFORMAT_BINARY ,

	    eFORMAT_NUM,
	    eFORMAT_MAX = eFORMAT_NUM - 1,
	};
	enum eBYTE_ORDER{
		eBYTE_ORDER_START = 0,

	    eBYTE_ORDER_BIGENDIAN = eBYTE_ORDER_START,
	    eBYTE_ORDER_LITTLEENDIAN ,

	    eBYTE_ORDER_NUM,
	    eBYTE_ORDER_MAX = eBYTE_ORDER_NUM - 1,
	};
	
	enum eARGUMENT{
		eARGUMENT_START = 0,

		eARGUMENT_INPUT_FILE_COMMAND = eARGUMENT_START,
		eARGUMENT_INPUT_FILE_DATA,
		eARGUMENT_OUTPUT_FILE_COMMAND,
		eARGUMENT_OUTPUT_FILE_DATA,
		eARGUMENT_ENDIAN_COMMAND,
		eARGUMENT_ENDIAN_DATA,
		eARGUMENT_FILEVERSION_COMMAND,
		eARGUMENT_FILEVERSION_DATA,
        eARGUMENT_OUTPUT_HEADER_NAME_COMMAND,
		eARGUMENT_OUTPUT_HEADER_NAME_DATA,
        eARGUMENT_OUTPUT_ENUM_NAME_COMMAND,
		eARGUMENT_OUTPUT_ENUM_NAME_DATA,
        eARGUMENT_VERSION_COMMAND,
		eARGUMENT_HELP_COMMAND,
        eARGUMENT_FILE_SCHEMA_COMMAND,
        eARGUMENT_FILE_SCHEMA_DATA,
        
		eARGUMENT_NUM,
		eARGUMENT_MAX = eARGUMENT_NUM - 1,

	};
private:
	// 引数チェック用
	const char *m_chCheckArgs[eARGUMENT_NUM];
	eBYTE_ORDER m_byteOrder;
	CArgumentParser():n_argc(0),m_shErrorCode(0){}
public:
	CArgumentParser(int argc, char **argv):
		n_argc(argc),
		m_shErrorCode(0)
		{
		ch_argv = argv;

	    for(int nCnt=0;nCnt<eARGUMENT_NUM;nCnt++){
	    	m_chCheckArgs[nCnt] = NULL;
	    }

	}
	char **GetParseArgs()
    {
		return (char**)m_chCheckArgs;
	}
	bool Parse();
	eBYTE_ORDER GetByteOrder(){
		return m_byteOrder;
	}
	short GetErrorCode()
    {
		return m_shErrorCode;
	}
	void Usage();
private:
	void Error(const char *ch_message);

	// 引数を解釈.
	bool ParseArguments();

	// 妥当性の検証.
    bool ArgumentCheck();
};
#endif // !defined(__tool__ArgumentParser__)
