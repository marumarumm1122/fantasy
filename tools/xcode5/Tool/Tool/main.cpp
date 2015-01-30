//
//  main.cpp
//  Tool
//
//  Created by 堀江佑介 on 2015-01-31.
//  Copyright (c) 2015 堀江佑介. All rights reserved.
//

#include <iostream>
#include "Tool.h"

int main(int argc, const char * argv[])
{

    char ** chArgv = (char**)argv;
	CTool theTool(argc,chArgv);
	
    short sh_error = theTool.Main();
    if(sh_error>0){
    	printf("error code %d\n",sh_error);
    	return sh_error;
    }
    return 0;
}

