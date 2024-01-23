//
// Created by henrywen on 2024/1/23.
//

#include <string>

#include "../base/FileUtil.h"

int main()
{
  AppendFile appendFile("/tmp/test.txt");
  std::string hello = "hello";
  appendFile.append(hello.c_str(), hello.size());

  return 0;
}
