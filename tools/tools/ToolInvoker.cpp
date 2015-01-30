#include <stdio.h>
#include "Error.h"
#include "Tool.h"
#include <string.h>
#include "ToolInvoker.h"
#include <stdlib.h>
#if defined(_WIN32)
#include <WinSock2.h>
#endif  // defined(_WIN32)
#include "Commons.h"

namespace{
    
}

int CToolInvoker::Invoke()
{
    // バージョンチェック.
    //if(VersionCheck()){
    //    return 0;
    //}
    
    // ヘルプチェック.
    //if(HelpCheck()){
    //    return 0;
    //}
    
    // 入力ファイルをオープンしてvoid*に格納していく.
    if(!LoadInputFile()){
        return m_shErrorCode;
    }
    
    // 格納したバッファをファイルに書き出す
    if(!WriteInputBuffer()){
        return m_shErrorCode;
    }
    
    return 0;
}
bool CToolInvoker::WriteInputBuffer(){
    char **ch_args = m_parser->GetParseArgs();
    FILE *fp;
	FILEOPENANDERROR(fp, ch_args[CArgumentParser::eARGUMENT_OUTPUT_FILE_DATA], "wb");
    
    // write version.
    short *sh_version = reinterpret_cast<short*>(malloc(sizeof(short)));
    short n_versionTmp = atoi(ch_args[CArgumentParser::eARGUMENT_FILEVERSION_DATA]);
    if(m_parser->GetByteOrder()==CArgumentParser::eBYTE_ORDER_BIGENDIAN){
    	printf("convert BIG ENDIAN\n");
        n_versionTmp = htons(n_versionTmp);
    }else{
        //n_versionTmp = ntohs(n_versionTmp);
    }
    sh_version[0] = n_versionTmp;
    fwrite(sh_version,sizeof(short),1,fp);
    
    // write buffer.
    fwrite(vInputBuff,m_nInputLine*m_nRecordSize,1,fp);
    
    fclose(fp);
    return true;
}
bool CToolInvoker::MakeSchema(){
    FILE *fp;
    //fpos_t n_fsize;
    char ch_read[64];
    int n_columnIdx = 0;

    char **ch_args = m_parser->GetParseArgs();
	FILEOPENANDERROR(fp, ch_args[CArgumentParser::eARGUMENT_FILE_SCHEMA_DATA], "rb");
    eCOLUMN_TYPE n_size = eCOLUMN_TYPE_NONE;
    while ( fgets(ch_read, 64, fp) != NULL ) {
        if(strncmp(ch_read,"USHORT",6)==0){
            n_size = eCOLUMN_TYPE_USHORT;
            m_nRecordSize+=2;
        }else if(strncmp(ch_read,"BYTE",4)==0){
            n_size = eCOLUMN_TYPE_BYTE;
            m_nRecordSize+=1;
        }else if(strncmp(ch_read,"UINT",4)==0){
            n_size = eCOLUMN_TYPE_UINT;
            m_nRecordSize+=4;
        }else{
            break;
        }
        m_nBytesOfColumns[n_columnIdx++] = n_size;
        
    }
    fclose(fp);
    m_nRecordColumnSize = n_columnIdx;
    return true;
}
void CToolInvoker::SplitCanma(char *ch_in,int startByte){
    char ch_temp[64];
    char *ch_buff = reinterpret_cast<char*>(vInputBuff);
    int nSCnt = 0;
    int nAppend = startByte;
    for(int nColumnIdx = 0;nColumnIdx < m_nRecordColumnSize;nColumnIdx++){
        int nCnt = 0;
        while(nSCnt<m_nRecordSize){
            if(ch_in[nSCnt]=='"' || ch_in[nSCnt]==' '|| ch_in[nSCnt]=='\t'|| ch_in[nSCnt]=='\n'|| ch_in[nSCnt]=='\r'){
                nSCnt++;
                continue;
            }
            if(ch_in[nSCnt]==','){
                ch_temp[nCnt++] = '\0';
                nSCnt++;
                break;
            }
            ch_temp[nCnt++] = ch_in[nSCnt];
            nSCnt++;
        }
        
        eCOLUMN_TYPE nSize = m_nBytesOfColumns[nColumnIdx];
        switch(nSize){
            case eCOLUMN_TYPE_USHORT:
            {
                unsigned short ush = (unsigned short)atoi(ch_temp);
                unsigned short *ushp = &ush;
                memcpy(ch_buff+nAppend,ushp,2);
                nAppend+=2;
                break;
            }
            case eCOLUMN_TYPE_BYTE:
            {
                char ch = (char)atoi(ch_temp);
                memcpy(ch_buff+nAppend,&ch,1);
                nAppend+=1;
                break;
            }
            case eCOLUMN_TYPE_UINT:
            {
                unsigned int un = (unsigned int)atoi(ch_temp);
                memcpy(ch_buff+nAppend,&un,4);
                nAppend+=4;
                break;
            }
            case eCOLUMN_TYPE_NONE:
                break;
        }
    }
    
}
bool CToolInvoker::LoadMemory(){
    FILE *fp;
    //fpos_t n_fsize;
    char ch_read[256];

    char **ch_args = m_parser->GetParseArgs();
	FILEOPENANDERROR(fp, ch_args[CArgumentParser::eARGUMENT_INPUT_FILE_DATA], "rb");
    while ( fgets(ch_read, 256, fp) != NULL ) {
        if(vInputBuff==NULL){
            vInputBuff = malloc(m_nRecordSize);
        }else{
            vInputBuff = realloc(vInputBuff,(m_nInputLine+1)*m_nRecordSize);
            //realloc(vInputBuff,(m_nInputLine+1)*m_nRecordSize);
        }
        SplitCanma(ch_read,m_nInputLine*m_nRecordSize);
        m_nInputLine++;
    }
    fclose(fp);
    return true;
}
bool CToolInvoker::LoadInputFile(){
    // カラム定義に応じたメモリマップを作る.
    if(!MakeSchema()){
        return false;
    }
    
    // 入力ファイルをインプットに溜め込む.
    if(!LoadMemory()){
        return false;
    }
    
    return true;
    
}
