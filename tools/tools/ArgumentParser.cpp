#include <stdio.h>
#include <string.h>
#include <iostream>
#include "ArgumentParser.h"
#include "Error.h"

bool CArgumentParser::Parse()
{
	if(!ParseArguments()){
		return false;
	}
	if(!ArgumentCheck()){
		return false;
	}
	return true;

}
bool CArgumentParser::ArgumentCheck()
{
    return true;//debug
    if(m_chCheckArgs[eARGUMENT_VERSION_COMMAND]!=NULL || m_chCheckArgs[eARGUMENT_HELP_COMMAND]!=NULL){
        return true;
    }
	if(m_chCheckArgs[eARGUMENT_INPUT_FILE_COMMAND]==NULL ){
        m_shErrorCode = ERR_ARG_REQUIRED_PARAMETER_INPUT_FILE;
        return false;
    }
    if(m_chCheckArgs[eARGUMENT_OUTPUT_FILE_COMMAND]==NULL ){
        m_shErrorCode = ERR_ARG_REQUIRED_PARAMETER_OUTPUT_FILE;
        return false;
    }
    if(m_chCheckArgs[eARGUMENT_ENDIAN_COMMAND]==NULL ){
        m_shErrorCode = ERR_ARG_REQUIRED_PARAMETER_ENDIAN;
        return false;
    }
    if(m_chCheckArgs[eARGUMENT_FILEVERSION_COMMAND]==NULL ){
        m_shErrorCode = ERR_ARG_REQUIRED_PARAMETER_FILEVERSION;
        return false;
    }
	return true;
}
bool CArgumentParser::ParseArguments()
{
	for(int nCnt=1;nCnt<n_argc;nCnt++){
    	if(strncmp(ch_argv[nCnt],"-f",2)==0){
    		if(nCnt+1>=n_argc){
    			Error("argument index out of bounds '-f'.");
                m_shErrorCode = ERR_ARG_ILLEGAL_PARAMETER_INPUT_FILE_VALUE;
    			return false;
    		}
    	    m_chCheckArgs[eARGUMENT_INPUT_FILE_COMMAND] = ch_argv[nCnt];
    	    m_chCheckArgs[eARGUMENT_INPUT_FILE_DATA] = ch_argv[++nCnt];
    	    continue;
        }
    	if(strncmp(ch_argv[nCnt],"-o",2)==0){
    		if(nCnt+1>=n_argc){
    			Error("argument index out of bounds '-o'.");
                m_shErrorCode = ERR_ARG_ILLEGAL_PARAMETER_OUTPUT_FILE_VALUE;
    			return false;
    		}
    	    m_chCheckArgs[eARGUMENT_OUTPUT_FILE_COMMAND] = ch_argv[nCnt];
    	    m_chCheckArgs[eARGUMENT_OUTPUT_FILE_DATA] = ch_argv[++nCnt];
    	    continue;
        }
        if(strncmp(ch_argv[nCnt],"-s",2)==0){
    		if(nCnt+1>=n_argc){
    			Error("argument index out of bounds '-s'.");
                m_shErrorCode = ERR_ARG_ILLEGAL_PARAMETER_OUTPUT_FILE_VALUE;
    			return false;
    		}
    	    m_chCheckArgs[eARGUMENT_FILE_SCHEMA_COMMAND] = ch_argv[nCnt];
    	    m_chCheckArgs[eARGUMENT_FILE_SCHEMA_DATA] = ch_argv[++nCnt];
    	    continue;
        }
        
        
        
        
        
    	if(strncmp(ch_argv[nCnt],"-e",2)==0){
    		if(nCnt+1>=n_argc){
    			Error("argument index out of bounds '-e'.");
                m_shErrorCode = ERR_ARG_ILLEGAL_PARAMETER_ENDIAN_VALUE;
    			return false;
    		}
    		if(strncmp(ch_argv[nCnt+1],"be",2)==0){
                m_chCheckArgs[eARGUMENT_ENDIAN_COMMAND] = ch_argv[nCnt];
                m_chCheckArgs[eARGUMENT_ENDIAN_DATA] = ch_argv[++nCnt];
                m_byteOrder = eBYTE_ORDER_BIGENDIAN;
            }else if(strncmp(ch_argv[nCnt+1],"le",2)==0){
                m_chCheckArgs[eARGUMENT_ENDIAN_COMMAND] = ch_argv[nCnt];
                m_chCheckArgs[eARGUMENT_ENDIAN_DATA] = ch_argv[++nCnt];
                m_byteOrder = eBYTE_ORDER_LITTLEENDIAN;
            }else{
    			Error("argument endian is not word be/le.");
                m_shErrorCode = ERR_ARG_UNKNOWN_PARAMETER_ENDIAN_VALUE;
    			return false;
    		}
    	    continue;
        }
    	if(strncmp(ch_argv[nCnt],"-n",2)==0){
    		if(nCnt+1>=n_argc){
    			Error("argument index out of bounds '-n'.");
                m_shErrorCode = ERR_ARG_ILLEGAL_PARAMETER_FILEVERSION_VALUE;
    			return false;
    		}
            if(atoi(ch_argv[nCnt+1])==0){
                Error("File version must be numeric value,and version value has must 1.0 or later");
                m_shErrorCode = ERR_ARG_NOT_DIGIT_PARAMETER_FILEVERSION_VALUE;
                return false;
            }
    	    m_chCheckArgs[eARGUMENT_FILEVERSION_COMMAND] = ch_argv[nCnt];
    	    m_chCheckArgs[eARGUMENT_FILEVERSION_DATA] = ch_argv[++nCnt];
    	    continue;
        }
        if(strncmp(ch_argv[nCnt],"-v",2)==0){
            m_chCheckArgs[eARGUMENT_VERSION_COMMAND] = ch_argv[nCnt];
            continue;
        }
        if(strncmp(ch_argv[nCnt],"-h",2)==0){
            m_chCheckArgs[eARGUMENT_HELP_COMMAND] = ch_argv[nCnt];
            continue;
        }
    	if(strncmp(ch_argv[nCnt],"-H",2)==0){
    		if(nCnt+1>=n_argc){
    			Error("argument index out of bounds '-H'.");
                m_shErrorCode = ERR_ARG_ILLEGAL_PARAMETER_OUTPUT_FILE_VALUE;
    			return false;
    		}
    	    m_chCheckArgs[eARGUMENT_OUTPUT_HEADER_NAME_COMMAND] = ch_argv[nCnt];
    	    m_chCheckArgs[eARGUMENT_OUTPUT_HEADER_NAME_DATA] = ch_argv[++nCnt];
    	    continue;
        }
    	if(strncmp(ch_argv[nCnt],"-E",2)==0){
    		if(nCnt+1>=n_argc){
    			Error("argument index out of bounds '-E'.");
                m_shErrorCode = ERR_ARG_ILLEGAL_PARAMETER_OUTPUT_FILE_VALUE;
    			return false;
    		}
    	    m_chCheckArgs[eARGUMENT_OUTPUT_ENUM_NAME_COMMAND] = ch_argv[nCnt];
    	    m_chCheckArgs[eARGUMENT_OUTPUT_ENUM_NAME_DATA] = ch_argv[++nCnt];
    	    continue;
        }

    }
	return true;
}
void CArgumentParser::Usage()
{
#if defined(_WIN32)
    printf( "usage: StrDataConverter.exe -f <input> -o <output> -e <byte order> -n <file version> -H <output header name> -E <output enum name>\n" );
#else   // defined(_WIN32)
    printf("usage: StrDataConverter.bin -f <input> -o <output> -e <byte order> -n <file version> -H <output header name> -E <output enum name>\n" );
#endif  // defined(_WIN32)
    printf( "-f : input filename\n" );
    printf( "-o : output filename\n" );
    printf( "-e : byte order(be or le) be by default\n" );
    printf( "-v : version\n" );
    printf( "-n : file version\n");
    printf( "-h : help\n");
    printf( "-H : output header name\n");
    printf( "-E : output enum name\n");
}
void CArgumentParser::Error(const char *ch_message)
{
	printf("%s\n",ch_message);
    Usage();
}
