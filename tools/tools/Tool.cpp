#include "Tool.h"
#include <stdio.h>
#include <string.h>
#include "ArgumentParser.h"
#include "ToolInvoker.h"

const char *CTool::TOOL_VERSION = "1.0";
short CTool::Main()
{
    CArgumentParser parser(n_argc,ch_argv);
    if(!parser.Parse()){
        printf("parsing Error.\n");
        return parser.GetErrorCode();
    }

    CToolInvoker invoker(&parser);
    int ret = invoker.Invoke();
    if(ret>0){
        printf("invoke Error.\n");
        return invoker.GetErrorCode();
    }
    
    return 0;
    
}
