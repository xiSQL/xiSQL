/*
  MIT License (MIT)

  Copyright (c) 2015 xiSQL

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
 */

#include <stdio.h>
#include <dlfcn.h>

int main(int argc, char *argv[]){
  void *pHandle = NULL;
  int (*startup)(int, char*[]);
  char *errorInfo = NULL;
  int res = 0;

  pHandle = dlopen("xisql.so", RTLD_NOW);
  if (pHandle == NULL){
    printf("xisql[error]: %s.\r\n", dlerror());
    return 0;
  }

  startup = dlsym(pHandle, "startup");
  errorInfo = dlerror();
  if (errorInfo != NULL){
    printf("xisql[error]: startup method error: %s.\r\n", errorInfo);
    dlclose(pHandle);
    return 0;
  }
   
  res = (*startup)(argc, argv);
  if (res != 0){
    printf("return error.\r\n");
  }
  dlclose(pHandle);
}

