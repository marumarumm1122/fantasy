
#define FILEOPENANDERROR(fp,filename,mode)\
fp = fopen(filename,mode);\
if (fp == NULL){\
	printf("File open error[%s]\n", filename);\
	m_shErrorCode = ERR_INV_OUTPUT_FILE_NOT_OPEN;\
	return false;\
}

